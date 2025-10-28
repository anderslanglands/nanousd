# NanoUSD C API Design Notes

This document analyzes the current NanoUSD C API design and provides specific recommendations for improvements. The API is already excellent overall (A- grade) but has several areas where consistency and usability could be enhanced.

## Overall Assessment

**Strengths:**
- Excellent consistency in naming and patterns
- Comprehensive error handling with `nusd_result_t`
- Proper opaque handle design for C/C++ interop
- Strong type safety with USD type checking
- Systematic documentation with Doxygen
- ✅ **Well-organized modular header structure** (IMPLEMENTED 2024)
- ✅ **Time-aware USD operations** with time_code parameter support (IMPLEMENTED 2024)
- ✅ **Comprehensive documentation** for all getter/setter functions (IMPLEMENTED 2024)
- ✅ **NUSD_NULL_PARAMETER error code** added to enum (IMPLEMENTED 2024)

**Areas for Improvement:**
- Memory management consistency across array types
- Parameter validation implementation in function bodies
- String ownership clarity in documentation

---

## ✅ Recently Implemented Improvements (2024)

### ✅ **MAJOR: Modular Header Organization** 
**Status: IMPLEMENTED**

The previous monolithic `nanousd.h` with 172+ functions has been successfully refactored into a well-organized modular structure:

- **`nanousd-types.h`** (153 lines): Core types, constants, and result codes
- **`nanousd-iterators.h`** (148 lines): Iterator types and functions 
- **`nanousd-arrays.h`** (694 lines): Array types and utility functions
- **`nanousd-properties.h`** (1,745 lines): All property getter/setter functions
- **`nanousd-cameras.h`** (38 lines): Camera-specific functionality
- **`nanousd.h`** (248 lines): Main API with stage and prim management, includes all modules

This addresses the **Priority 2 recommendation #6 "Group Related Functions"** and makes the API much more navigable and maintainable.

### ✅ **MAJOR: Time-Aware USD Operations**
**Status: IMPLEMENTED**

Added comprehensive `time_code` parameter support to all 74 getter/setter functions:
- Added `NUSD_TIMECODE_DEFAULT 0.0` constant for consistent defaults
- Updated all function signatures with proper parameter positioning
- Modified all implementations to pass time_code to underlying USD Get/Set calls
- Added comprehensive documentation based on OpenUSD API patterns
- Enables proper animation and temporal data support

### ✅ **Parameter Validation Error Code**
**Status: IMPLEMENTED**

Added `NUSD_RESULT_NULL_PARAMETER` to the error enum in `nanousd-types.h`, addressing part of **Priority 1 recommendation #2**.

### ✅ **Comprehensive Documentation**
**Status: IMPLEMENTED**

All getter/setter functions now have detailed documentation including:
- Clear parameter descriptions with time_code behavior
- Return value documentation
- Usage notes and warnings
- String lifetime documentation for token functions

---

## Priority 1 - Critical Issues

### 1. Standardize Array Memory Management

**Issue:** The `int64_array` type uses a different memory management pattern than other array types, creating inconsistency and potential confusion.

**Current inconsistent implementation:**

```c
// Most arrays use VtArray pattern (nanousd.cpp:102-105)
struct nusd_uint_array_s {
    PXR_NS::VtUIntArray value;
};

// But int64_array uses raw pointer pattern (nanousd.cpp:112-115)
struct nusd_int64_array_s {
    int64_t* data;
    size_t size;
};
```

**Current inconsistent getters:**

```c
// VtArray pattern getter (nanousd.cpp:2195-2208)
nusd_result_t nusd_attribute_get_uint_array(nusd_stage_t stage, char const* attribute_path, nusd_uint_array_t* uint_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *uint_array = new nusd_uint_array_s();
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(&(*uint_array)->value);
    return NUSD_RESULT_OK;
}

// Raw pointer pattern getter (example from int64)
nusd_result_t nusd_attribute_get_int64_array(/*...*/) {
    // Creates VtArray temporarily, copies to raw array, manual memory management
    VtArray<int64_t> array;
    attr.Get(&array);
    (*int64_array)->data = new int64_t[array.size()];
    for (size_t i = 0; i < array.size(); i++) {
        (*int64_array)->data[i] = array[i];
    }
    (*int64_array)->size = array.size();
}
```

**Recommended fix:**

```c
// Standardize int64_array to use VtArray pattern
struct nusd_int64_array_s {
    PXR_NS::VtInt64Array value;  // Changed from raw pointer
};

// Simplified, consistent getter
nusd_result_t nusd_attribute_get_int64_array(nusd_stage_t stage, char const* attribute_path, nusd_int64_array_t* int64_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int64_array = new nusd_int64_array_s();
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT64ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(&(*int64_array)->value);  // Direct VtArray access
    return NUSD_RESULT_OK;
}

// Consistent utility functions
size_t nusd_int64_array_size(nusd_int64_array_t int64_array) {
    return int64_array->value.size();  // Changed from ->size
}

int64_t* nusd_int64_array_data(nusd_int64_array_t int64_array) {
    return int64_array->value.data();  // Changed from ->data
}

void nusd_int64_array_destroy(nusd_int64_array_t int64_array) {
    delete int64_array;  // Simplified from delete[] + delete
}
```

### 2. Add Parameter Validation

**Issue:** Functions don't explicitly validate null pointers, leading to potential crashes and unclear behavior.

**Current implementation (nanousd.cpp:2182-2193):**

```c
nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, unsigned int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);  // No null check
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));  // attribute_path could be null
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(value);  // value could be null
    return NUSD_RESULT_OK;
}
```

**Recommended improvement:**

```c
// Add new error codes to enum
enum nusd_result_e {
    NUSD_RESULT_OK = 0,
    NUSD_RESULT_NULL_PARAMETER,          // New
    NUSD_RESULT_INVALID_ATTRIBUTE_PATH,
    // ... existing codes
};

nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, unsigned int* value) {
    // Explicit parameter validation
    if (!stage) {
        return NUSD_RESULT_NULL_PARAMETER;
    }
    if (!attribute_path) {
        return NUSD_RESULT_NULL_PARAMETER;
    }
    if (!value) {
        return NUSD_RESULT_NULL_PARAMETER;
    }
    
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(value);
    return NUSD_RESULT_OK;
}
```

**Documentation improvement (nanousd.h):**

```c
/// Gets the value of the given attribute as an unsigned int, if the attribute is of that type.
/// 
/// @param stage Stage handle containing the attribute. Must not be null.
/// @param attribute_path Path to the attribute in USD format (e.g., "/World.myAttr"). Must not be null.
/// @param value Output pointer to store the retrieved value. Must not be null.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any parameter is null
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if the attribute doesn't exist
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of unsigned int type
/// 
/// @note The value is only written on success (NUSD_RESULT_OK)
NANOUSD_API
nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, unsigned int* value);
```

### 3. Clarify String Ownership

**Issue:** Functions that return `char const*` don't clearly document string lifetime and ownership.

**Current unclear implementation (nanousd.h:456):**

```c
/// Gets token value from an attribute
NANOUSD_API
nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, char const** token);
```

**Current implementation (nanousd.cpp:696-712):**

```c
nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, char const** token) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKEN) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    TfToken tok;
    attr.Get(&tok);
    *token = tok.GetText();  // Lifetime unclear!
    return NUSD_RESULT_OK;
}
```

**Recommended clarification:**

```c
/// Gets token value from an attribute
/// 
/// @param stage Stage handle containing the attribute. Must not be null.
/// @param attribute_path Path to the attribute in USD format. Must not be null.
/// @param token Output pointer to receive the token string. Must not be null.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any parameter is null
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if the attribute doesn't exist
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of token type
/// 
/// @note The returned string pointer is valid until the stage is destroyed
/// @note The returned string is owned by USD and must NOT be freed by the caller
/// @note The string may become invalid if the attribute value changes
/// @warning Do not store the returned pointer beyond the lifetime of the stage
NANOUSD_API
nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, char const** token);
```

---

## Priority 2 - Design Improvements

### 4. Reduce API Surface

**Issue:** 172 functions with repetitive patterns create a large API surface that's hard to navigate.

**Current repetitive patterns (nanousd.h examples):**

```c
// Scalar getters - very repetitive
NANOUSD_API nusd_result_t nusd_attribute_get_float(nusd_stage_t stage, char const* attribute_path, float* value);
NANOUSD_API nusd_result_t nusd_attribute_get_double(nusd_stage_t stage, char const* attribute_path, double* value);
NANOUSD_API nusd_result_t nusd_attribute_get_int(nusd_stage_t stage, char const* attribute_path, int* value);
NANOUSD_API nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, unsigned int* value);
NANOUSD_API nusd_result_t nusd_attribute_get_int64(nusd_stage_t stage, char const* attribute_path, int64_t* value);
NANOUSD_API nusd_result_t nusd_attribute_get_uint64(nusd_stage_t stage, char const* attribute_path, uint64_t* value);
// ... continues for many more types
```

**Recommended macro-based approach:**

```c
// Define a macro for scalar getters
#define NUSD_DECLARE_SCALAR_GETTER(type_name, c_type, usd_type_constant) \
    /// Gets the value of the given attribute as a c_type. \
    /// @param stage Stage handle. Must not be null. \
    /// @param attribute_path Attribute path. Must not be null. \
    /// @param value Output value. Must not be null. \
    /// @return NUSD_RESULT_OK on success, error code on failure \
    NANOUSD_API \
    nusd_result_t nusd_attribute_get_##type_name(nusd_stage_t stage, char const* attribute_path, c_type* value);

// Use macro to declare all scalar getters
NUSD_DECLARE_SCALAR_GETTER(float, float, NUSD_TYPE_FLOAT)
NUSD_DECLARE_SCALAR_GETTER(double, double, NUSD_TYPE_DOUBLE)
NUSD_DECLARE_SCALAR_GETTER(int, int, NUSD_TYPE_INT)
NUSD_DECLARE_SCALAR_GETTER(uint, unsigned int, NUSD_TYPE_UINT)
NUSD_DECLARE_SCALAR_GETTER(int64, int64_t, NUSD_TYPE_INT64)
NUSD_DECLARE_SCALAR_GETTER(uint64, uint64_t, NUSD_TYPE_UINT64)
NUSD_DECLARE_SCALAR_GETTER(uchar, unsigned char, NUSD_TYPE_UCHAR)
NUSD_DECLARE_SCALAR_GETTER(bool, bool, NUSD_TYPE_BOOL)

#undef NUSD_DECLARE_SCALAR_GETTER
```

**Implementation macro (nanousd.cpp):**

```c
#define NUSD_IMPLEMENT_SCALAR_GETTER(type_name, c_type, usd_type_constant) \
    nusd_result_t nusd_attribute_get_##type_name(nusd_stage_t stage, char const* attribute_path, c_type* value) { \
        if (!stage || !attribute_path || !value) { \
            return NUSD_RESULT_NULL_PARAMETER; \
        } \
        UsdStage* _stage = reinterpret_cast<UsdStage*>(stage); \
        UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path)); \
        if (!attr) { \
            return NUSD_RESULT_INVALID_ATTRIBUTE_PATH; \
        } \
        if (attr.GetTypeName().GetAsToken().GetText() != usd_type_constant) { \
            return NUSD_RESULT_WRONG_TYPE; \
        } \
        attr.Get(value); \
        return NUSD_RESULT_OK; \
    }

// Generate all implementations
NUSD_IMPLEMENT_SCALAR_GETTER(float, float, NUSD_TYPE_FLOAT)
NUSD_IMPLEMENT_SCALAR_GETTER(double, double, NUSD_TYPE_DOUBLE)
// ... etc
```

### 5. Add Const Qualifiers

**Issue:** Input parameters that aren't modified should be marked `const` for better API design.

**Current missing const (nanousd.h examples):**

```c
// Array handles that are only read from should be const
size_t nusd_float_array_size(nusd_float_array_t float_array);
float* nusd_float_array_data(nusd_float_array_t float_array);

// Array data pointers for setters should be const
nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);
```

**Recommended const additions:**

```c
// Array utility functions should take const handles when only reading
size_t nusd_float_array_size(const nusd_float_array_t float_array);
const float* nusd_float_array_data(const nusd_float_array_t float_array);  // Return const data

// Array setters should take const data pointers
nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, const float* data, size_t num_elements);

// Vector setters should take const arrays
nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage, char const* attribute_path, const float* value);
nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage, char const* attribute_path, const float* value);
nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage, char const* attribute_path, const float* value);
```

### ✅ 6. Group Related Functions *(IMPLEMENTED)*

**Status: IMPLEMENTED** - The API has been successfully refactored into a modular header structure:

**Current modular organization:**

- **`nanousd.h`**: Main header with stage management and includes
- **`nanousd-types.h`**: Core types, enums, constants
- **`nanousd-iterators.h`**: All iterator-related functions  
- **`nanousd-arrays.h`**: Array types and utility functions
- **`nanousd-properties.h`**: All property getter/setter functions
- **`nanousd-cameras.h`**: Camera-specific functionality

This approach is **superior** to the originally recommended sectioned approach because:
- **Better compile-time performance**: Users only include what they need
- **Cleaner dependency management**: Clear separation of concerns
- **Easier maintenance**: Related functionality is co-located
- **Reduced header pollution**: Smaller compilation units

The modular approach maintains the same level of organization while providing better encapsulation and performance characteristics.

---

## Priority 3 - Usability Enhancements

### 7. Add Helper Macros

**Issue:** Common patterns like error checking require repetitive boilerplate code.

**Current repetitive pattern in user code:**

```c
// User has to write this pattern repeatedly
nusd_result_t result;
float value;
result = nusd_attribute_get_float(stage, "/World.myFloat", &value);
if (result != NUSD_RESULT_OK) {
    printf("Error getting float: %d\n", result);
    return result;
}

double other_value;
result = nusd_attribute_get_double(stage, "/World.myDouble", &other_value);
if (result != NUSD_RESULT_OK) {
    printf("Error getting double: %d\n", result);
    return result;
}
```

**Recommended helper macros:**

```c
// Add to nanousd.h
#define NUSD_CHECK_RESULT(call, error_msg) \
    do { \
        nusd_result_t _result = (call); \
        if (_result != NUSD_RESULT_OK) { \
            fprintf(stderr, "NanoUSD Error: %s (code: %d)\n", error_msg, _result); \
            return _result; \
        } \
    } while(0)

#define NUSD_GET_ATTRIBUTE(stage, path, type, var_name) \
    type var_name; \
    NUSD_CHECK_RESULT(nusd_attribute_get_##type(stage, path, &var_name), \
                      "Failed to get " #type " attribute " path)

// Usage becomes much cleaner:
NUSD_GET_ATTRIBUTE(stage, "/World.myFloat", float, value);
NUSD_GET_ATTRIBUTE(stage, "/World.myDouble", double, other_value);
```

### 8. Add Error String Functions

**Issue:** Error codes are numeric and not human-readable for debugging.

**Current error handling:**

```c
nusd_result_t result = nusd_stage_open("file.usd", &stage);
if (result != NUSD_RESULT_OK) {
    printf("Error: %d\n", result);  // Not helpful: "Error: 21"
}
```

**Recommended error string function:**

```c
// Add to nanousd.h
/// Converts a result code to a human-readable string.
/// @param result The result code to convert
/// @return A string description of the error (never null)
NANOUSD_API const char* nusd_result_to_string(nusd_result_t result);

// Implementation in nanousd.cpp
const char* nusd_result_to_string(nusd_result_t result) {
    switch (result) {
        case NUSD_RESULT_OK: return "Success";
        case NUSD_RESULT_NULL_PARAMETER: return "Null parameter provided";
        case NUSD_RESULT_INVALID_ATTRIBUTE_PATH: return "Invalid attribute path";
        case NUSD_RESULT_INVALID_RELATIONSHIP_PATH: return "Invalid relationship path";
        case NUSD_RESULT_INVALID_PRIM_PATH: return "Invalid prim path";
        case NUSD_RESULT_WRONG_TYPE: return "Attribute type mismatch";
        case NUSD_RESULT_CREATE_STAGE_FAILED: return "Stage creation failed";
        case NUSD_RESULT_OPEN_STAGE_FAILED: return "Stage opening failed";
        case NUSD_RESULT_DEFINE_PRIM_FAILED: return "Prim definition failed";
        case NUSD_RESULT_INVALID_PROPERTY_PATH: return "Invalid property path";
        case NUSD_RESULT_INVALID_PROPERTY_TYPE: return "Invalid property type";
        case NUSD_RESULT_CREATE_RELATIONSHIP_FAILED: return "Relationship creation failed";
        case NUSD_RESULT_CREATE_ATTRIBUTE_FAILED: return "Attribute creation failed";
        default: return "Unknown error";
    }
}

// Much better error handling:
nusd_result_t result = nusd_stage_open("file.usd", &stage);
if (result != NUSD_RESULT_OK) {
    printf("Error: %s\n", nusd_result_to_string(result));  // "Error: Stage opening failed"
}
```

### 9. Optional Safety Layer

**Issue:** No debug mode with extra validation for development vs. production builds.

**Recommended debug mode implementation:**

```c
// Add to nanousd.h
#ifndef NUSD_DEBUG_MODE
#define NUSD_DEBUG_MODE 0  // Can be overridden by build system
#endif

#if NUSD_DEBUG_MODE
#define NUSD_DEBUG_VALIDATE(condition, error_code) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "NanoUSD Debug: Validation failed: %s at %s:%d\n", \
                    #condition, __FILE__, __LINE__); \
            return error_code; \
        } \
    } while(0)
#else
#define NUSD_DEBUG_VALIDATE(condition, error_code) ((void)0)
#endif

// Usage in implementation:
nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, unsigned int* value) {
    // Always validate critical parameters
    if (!stage || !attribute_path || !value) {
        return NUSD_RESULT_NULL_PARAMETER;
    }
    
    // Additional debug-only validations
    NUSD_DEBUG_VALIDATE(strlen(attribute_path) > 0, NUSD_RESULT_INVALID_ATTRIBUTE_PATH);
    NUSD_DEBUG_VALIDATE(attribute_path[0] == '/', NUSD_RESULT_INVALID_ATTRIBUTE_PATH);
    
    // ... rest of implementation
}
```

---

## Updated Implementation Priority

With the major structural improvements now implemented, the remaining priorities are:

### **Remaining High Priority**
1. **Memory Management Consistency** - Fix int64_array to match other arrays  
2. **Parameter Validation Implementation** - Add actual null checks in function bodies
3. **String Ownership Documentation** - Clarify lifetimes in remaining functions

### **Medium Priority Enhancements**  
4. **Const Correctness** - Add const qualifiers to appropriate parameters
5. **Error String Function** - Greatly improves debugging experience  
6. **Helper Macros** - Reduces boilerplate in user code

### ✅ **COMPLETED**
7. ✅ **Header Organization** - Excellently implemented with modular structure
8. ✅ **Time-Aware Operations** - Comprehensive time_code parameter support
9. ✅ **Documentation** - All getter/setter functions fully documented
10. ✅ **Error Codes** - NUSD_RESULT_NULL_PARAMETER added

## Current API Grade: **A** (upgraded from A-)

The API has been significantly improved with the modular header structure, comprehensive time support, and thorough documentation. The remaining issues are more focused and would elevate it to **A+** when completed.