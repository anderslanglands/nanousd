# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NanoUSD is a C wrapper library for Pixar's USD (Universal Scene Description) library with Python bindings. It provides a simplified C API for working with USD files, making it easier to integrate USD functionality into C-based applications, with a ctypes-based Python wrapper for high-level scripting and automation.

## Build System

This project uses CMake as its build system, uv for the python wrapper, and uses just to orchestrate everything. Key build commands (all run from project root)

```bash
# Configure and build the project
# Requires OpenUSD to be discoverable via CMAKE_PREFIX_PATH
# User will run this when required
just configure

# Build the C library
just build

# Run ctest unit tests
just test

# Generate the python bindings. Only needs to be done when nanousd.h changes
just bind

# Run the python tests (main way of testing)
just pytest

# Run the python example
just pyexample

# Generate documentation
just docs
```

## Dependencies

- **Pixar USD**: The core USD library (required)
- **GoogleTest**: For unit testing (automatically downloaded via FetchContent)
- **uv**: Python package manager for managing Python dependencies and virtual environments
- **ctypesgen**: Automatically generates Python ctypes bindings from C header files
- **NumPy**: For efficient array operations in Python bindings
- **Sphinx**: For documentation generation
- **Exhale**: For API documentation from C headers

## Project Structure

### C Library (`libnanousd/`)
The C library has been refactored into a modular architecture with separate source files:

**Core Implementation Files:**
- `nanousd.h` - Main C API header that aggregates all modular headers
- `nanousd.cpp` - Core stage management and prim operations implementation
- `nanousd-types.h` - Core type definitions, constants, and error codes

**Specialized Implementation Files:**
- `nanousd-array.h` / `nanousd-array.cpp` - Array type definitions and functions
- `nanousd-property.h` / `nanousd-property.cpp` - Property and attribute access functions
- `nanousd-prim.cpp` - Prim-specific operations implementation
- `nanousd-mesh.h` / `nanousd-mesh.cpp` - Mesh geometry functions and operations

**Functional Domain Headers (Header-only):**
- `nanousd-iterator.h` - Iterator definitions for traversing collections
- `nanousd-camera.h` - Camera-specific functionality (FOV, exposure, aperture, clipping, transforms)
- `nanousd-material.h` - Material and shader system functions for building shader networks

**Examples and Tests:**
- `example01.cpp` - Example application demonstrating basic USD file reading and property inspection
- `tests/nusd_test.cpp` - GoogleTest-based unit tests
- `CMakeLists.txt` - CMake configuration for C library
- `tests/CMakeLists.txt` - Test configuration

### Python Bindings (`python/`)
- **Package Configuration:**
  - `pyproject.toml` - Python package configuration with uv management and py-build-cmake
  - `uv.lock` - Lock file for reproducible Python environment

- **Python Package (`nanousd/`):**
  - `__init__.py` - Main module with Stage class, iterators, and core functionality
  - `ffi.py` - Auto-generated ctypes bindings (do not edit manually)
  - `tokens.py` - USD type constants and enumerations
  - `array.py` - NumPy-compatible array wrapper classes
  - `_get_property.py` - Property retrieval logic with type detection
  - `_set_property.py` - Property setting logic with validation

- **Examples and Tests:**
  - `example01.py` - Python example demonstrating USD file operations
  - `tests/test_nanousd.py` - Main Python unit tests using pytest
  - `tests/test_color_space.py` - Color space functionality tests
  - `tests/test_primvars.py` - Primvar functionality tests
  - `tests/__init__.py` - Test package initialization

- **Documentation (`docs/`):**
  - `conf.py` - Sphinx configuration
  - `index.rst` - Documentation index
  - `Doxyfile.in` - Doxygen configuration template
  - `Makefile` / `make.bat` - Documentation build scripts
  - `api/` - Generated API documentation
  - `CLAUDE.md` - Python-specific documentation

### Build System and Configuration
- `justfile` - Task runner configuration for orchestrating builds and tests
- `test01.usda` - Sample USD file for testing and examples
- `build/` - CMake build output directory (generated)
- `dist/` - Distribution files (generated)
- `README.md` - Project documentation
- `DESIGN_NOTES.md` - Design and architecture notes

## Core Architecture

### C Library (Modular Implementation)
The library follows a C wrapper pattern with modular architecture:

**Core Principles:**
- C++ USD objects are wrapped in opaque C handles (e.g., `nusd_stage_t`, `nusd_prim_iterator_t`)
- Iterator pattern for traversing prims, properties, and relationships
- Type-safe getters for various USD data types (float, double, int, bool, vectors, matrices, arrays)
- Comprehensive error handling with `nusd_result_t` return codes
- Modular source organization with specialized implementation files

**Implementation Organization:**
- **Core Functions** (`nanousd.cpp`): Stage management, prim operations, path utilities, asset handling
- **Array Handling** (`nanousd-array.cpp`): All array type implementations and memory management
- **Property System** (`nanousd-property.cpp`): Attribute and relationship access with comprehensive USD type support
- **Prim Operations** (`nanousd-prim.cpp`): Specialized prim functionality, transforms, primvars
- **Mesh Support** (`nanousd-mesh.cpp`): Mesh geometry operations and manipulation

**Header Organization:**
- **Main Header** (`nanousd.h`): Aggregates all functionality, includes all modular headers
- **Type System** (`nanousd-types.h`): Core type definitions, constants, error codes
- **Arrays** (`nanousd-array.h`): Array type definitions with comprehensive type coverage
- **Properties** (`nanousd-property.h`): Property access functions with color space support
- **Mesh Operations** (`nanousd-mesh.h`): Mesh-specific functionality
- **Functional Headers** (header-only):
  - `nanousd-iterator.h` - Iterator definitions
  - `nanousd-camera.h` - Camera functionality (FOV, exposure, aperture, transforms)
  - `nanousd-material.h` - Material and shader system functions

### Python Bindings (Modular Architecture)
The Python layer provides a clean, modular interface with specialized modules:

**Core Infrastructure:**
- **ctypes Integration**: Auto-generated bindings via ctypesgen from all C headers
- **NumPy Integration**: USD arrays exposed as NumPy-compatible arrays with full operator support
- **Pythonic API**: Object-oriented interface with context managers and iterators
- **Type Safety**: USD type constants exposed as module-level constants
- **Memory Management**: Automatic cleanup of C resources via Python `__del__` methods

**Module Organization:**
- **Main Module** (`__init__.py`): `Stage` class, iterators, exceptions, ctypes fixes
- **Type Constants** (`tokens.py`): Centralized USD type definitions
- **Array Wrappers** (`array.py`): NumPy-compatible array classes with mathematical operations
- **Property Access** (`_get_property.py`): Centralized property retrieval with type detection
- **Property Setting** (`_set_property.py`): Centralized property setting with validation

**Key Components:**
- **Stage Management**: Creating, opening, saving USD stages (`Stage` class)
- **Prim Operations**: Defining and validating prims, transforms, primvars
- **Property Access**: Reading attributes and relationships with automatic type conversion
- **Iterator Interface**: Pythonic iteration over scene hierarchy and properties
- **Array Types**: NumPy-compatible array classes with mathematical operations
- **Material System**: Material definition, shader creation, and shader network connections
- **Camera Controls**: Camera definition, transform setting, FOV, exposure, and aperture controls
- **Asset Management**: Asset path handling for textures and external file references
- **Token Support**: String token handling for shader IDs and metadata
- **Color Space Support**: Color space metadata for attributes

## Testing

### C Library Tests
Run C library tests using CTest:
```bash
just test
```

### Python Tests
Run Python tests using pytest (primary testing method):
```bash
just pytest
```

The Python tests cover:
- Stage creation and opening
- Prim definition and property creation
- Type-safe property getting/setting for all USD types
- NumPy array integration and mathematical operations
- Material and shader system functionality
- Camera controls and transform operations
- Asset path handling and external file references
- Token and token array operations
- Error handling with custom exception types
- Comprehensive edge case testing

## Example Usage

### C API
See `example01.cpp` for a complete C example that:
1. Opens a USD file
2. Traverses all prims in the scene
3. Inspects properties and their values
4. Handles different USD data types properly

### Python API
See `python/example01.py` for Python usage:
```python
import nanousd as nusd
import numpy as np

# Open a USD stage
stage = nusd.Stage.open("test01.usda")

# Get array properties as NumPy-compatible arrays
float_array = stage.get_property("/World.testFloatArray")
result = float_array * 2.0  # Element-wise operations work

# Get vector properties as NumPy arrays
float3 = stage.get_property("/World.testFloat3")
print(float3)  # [x, y, z]

# Create new stages and prims
stage = nusd.Stage.create_in_memory("new_stage")
stage.define_prim("/World", "Xform")
stage.prim_create_property("/World", "color", nusd.COLOR3F, [1.0, 0.5, 0.0])
```

Run the Python example:
```bash
just pyexample
```

## Core Functionality

### Material and Shader System
NanoUSD provides comprehensive support for USD's material and shader system:

**C API:**
- `nusd_material_define()` - Create UsdShadeMaterial prims
- `nusd_shader_define()` - Create UsdShadeShader prims with specific shader IDs
- `nusd_shader_create_input()` - Create shader inputs with automatic "inputs:" namespace
- `nusd_shader_create_output()` - Create shader outputs with automatic "outputs:" namespace  
- `nusd_shader_connect()` - Connect shader outputs to inputs for material networks

**Python API:**
- `Stage.material_define()` - Material creation wrapper
- `Stage.shader_define()` - Shader creation with ID specification
- `Stage.shader_create_input()` - Input creation with optional value setting
- `Stage.shader_create_output()` - Output creation with optional value setting
- `Stage.shader_connect()` - Shader network connection

**Example workflow:**
```python
# Create material and shaders
stage.material_define("/World/Materials/MyMaterial")
stage.shader_define("/World/Materials/MyMaterial/Surface", "UsdPreviewSurface")
stage.shader_define("/World/Materials/MyMaterial/Texture", "UsdUVTexture")

# Create inputs and outputs
stage.shader_create_input("/World/Materials/MyMaterial/Surface", "diffuseColor", nusd.COLOR3F)
stage.shader_create_output("/World/Materials/MyMaterial/Texture", "rgb", nusd.COLOR3F)

# Connect texture to surface
stage.shader_connect(
    "/World/Materials/MyMaterial/Texture.outputs:rgb",
    "/World/Materials/MyMaterial/Surface.inputs:diffuseColor"
)
```

### Asset Path System
Full support for USD asset paths for referencing external files:

**Supported Types:**
- `ASSET` - Single asset path (textures, models, etc.)
- `ASSETARRAY` - Arrays of asset paths

**C API:**
- `nusd_attribute_get_asset()` - Get single asset path
- `nusd_attribute_set_asset()` - Set single asset path
- `nusd_attribute_get_asset_array()` - Get asset path arrays with iterator
- `nusd_attribute_set_asset_array()` - Set asset path arrays

**Python Integration:**
- Full support in `get_property()` and `set_property()`
- Asset paths returned as Python strings
- Asset arrays returned as Python lists
- Supports relative paths, special characters, and empty values

### Token System
String token support for shader identifiers and metadata:

**Supported Types:**
- `TOKEN` - Single string token
- `TOKENARRAY` - Arrays of string tokens

**Common Use Cases:**
- Shader IDs (e.g., "UsdPreviewSurface", "UsdUVTexture")
- Purpose tokens ("default", "render", "proxy")
- Metadata and identifier strings

### Camera System
Comprehensive camera functionality:

**C API:**
- `nusd_camera_define()` - Create camera prims
- `nusd_camera_set_fov_w()` - Set horizontal field of view
- `nusd_camera_set_exposure()` - Set exposure parameters (ISO, time, f-stop)
- `nusd_camera_set_aperture()` - Set sensor dimensions
- `nusd_camera_set_clipping_range()` - Set near/far clipping planes

**Python Wrappers:**
- All camera functions available with proper error handling
- Support for time-coded animation
- Integration with transform system

### Transform System
Transform and matrix operations:

**Matrix Types:**
- `MATRIX2D`, `MATRIX3D`, `MATRIX4D` - Single matrices
- `MATRIX2DARRAY`, `MATRIX3DARRAY`, `MATRIX4DARRAY` - Matrix arrays

**Transform Functions:**
- `nusd_prim_set_transform()` - Set prim transforms
- `nusd_prim_compute_local_to_world_transform()` - Compute world transforms

## Development Notes

### C Library (Modular Development)
- **Modular Architecture**: Code is organized into specialized implementation files for maintainability
- **Stage Management**: Global stage registry (`STAGES`) manages USD stage lifecycles
- **Thread Safety**: Token initialization is thread-safe using mutex protection
- **Memory Management**: All array types provide size and data access functions with proper cleanup
- **C Compatibility**: The C API closely mirrors USD's C++ patterns while remaining C-compatible

**File Responsibilities:**
- `nanousd.cpp`: Core stage operations, prim management, path utilities
- `nanousd-array.cpp`: All array type implementations and memory management
- `nanousd-property.cpp`: Property system with comprehensive type support
- `nanousd-prim.cpp`: Specialized prim operations, transforms, primvars
- `nanousd-mesh.cpp`: Mesh geometry operations

### Python Bindings (Modular Architecture)
- **Auto-generation**: The `ffi.py` file is auto-generated by ctypesgen and should **never be edited manually**
- **Modular Design**: Functionality is split across specialized modules for maintainability
- **Array Integration**: Array classes inherit from `NDArrayOperatorsMixin` for full NumPy compatibility
- **Memory Management**: Automatic cleanup via Python's garbage collection and `__del__` methods
- **Type Safety**: Type constants exposed at module level for easy access

**Module Responsibilities:**
- `__init__.py`: Main `Stage` class, iterators, exceptions, ctypes argument fixes
- `tokens.py`: Centralized USD type constants
- `array.py`: NumPy-compatible array wrapper classes
- `_get_property.py`: Property retrieval logic with type detection
- `_set_property.py`: Property setting logic with validation

### Development Workflow (Updated)
- **C Development**: Work in appropriate specialized C files (`nanousd-*.cpp`, `nanousd-*.h`)
- **Python Layer**: Automatically generated and provides the main user interface
- **Binding Generation**: **CRITICAL** - After modifying ANY C header, run `just bind` to regenerate Python bindings
- **Testing**: Use `just pytest` as the primary testing method (covers both C and Python functionality)
- **Type Conversions**: Python layer handles conversions and provides user-friendly API
- **Documentation**: Use `just docs` to generate comprehensive API documentation

**Important Notes:**
- **Never edit `ffi.py` manually** - changes will be overwritten
- **Regenerate bindings** after ANY header modifications (not just `nanousd.h`)
- **ctypesgen warnings** from system headers can be safely ignored
- **Modular development** allows working on specific functionality without affecting the entire codebase

## Current Status

### Recent Major Additions (Latest Commit)
The codebase recently received comprehensive ASSET and ASSETARRAY support along with a complete material/shader system:

**Material & Shader System:**
- Full UsdShadeMaterial and UsdShadeShader support
- Shader input/output creation with automatic namespace handling
- Shader connection system for building material networks
- Support for common shader types (UsdPreviewSurface, UsdUVTexture, etc.)

**Asset Path System:**
- ASSET and ASSETARRAY type support for external file references
- Complete C API with iterator support for arrays
- Full Python integration in get_property/set_property
- Proper memory management with automatic cleanup

**Token System:**
- TOKEN and TOKENARRAY support for string identifiers
- Integration with shader IDs and metadata
- Full round-trip support between C and Python

**Testing Status:**
- **C Tests**: 57/57 passing (includes color space functions)
- **Python Tests**: 78/78 passing (includes modular test files)
- Comprehensive coverage of all new functionality including color space metadata

### API Completeness
The library now supports most core USD functionality needed for scene description:

**Core Types Supported:**
- All numeric types (float, double, int, uint, etc.) and their arrays
- All vector types (float2/3/4, double2/3/4, etc.) and their arrays  
- All matrix types (matrix2d/3d/4d) and their arrays
- Bool and bool arrays
- Asset paths and asset path arrays
- Tokens and token arrays
- Comprehensive color space support

**Major Functionality:**
- ✅ Stage management (create, open, save)
- ✅ Prim operations (define, properties, relationships)
- ✅ Property system (all USD types, arrays, time-coded values)
- ✅ Material and shader networks
- ✅ Camera controls and transforms
- ✅ Asset path management
- ✅ Iterator patterns for collections
- ✅ Comprehensive error handling
- ✅ Full Python integration with NumPy

### File Organization (Modular Architecture)
The codebase has been refactored into a fully modular architecture with specialized implementation files:

**Core Headers and Implementation:**
- `nanousd.h` - Main API aggregation header that includes all modular headers
- `nanousd.cpp` - Core stage operations, prim management, path utilities, asset handling
- `nanousd-types.h` - Core type definitions, constants, error codes, and basic types

**Specialized Implementation Modules:**
- `nanousd-array.h` / `nanousd-array.cpp` - Array type definitions and implementations (bool, float, double, int, uint, matrix arrays)
- `nanousd-property.h` / `nanousd-property.cpp` - Property and attribute access with comprehensive USD type support including color space metadata
- `nanousd-prim.cpp` - Specialized prim functionality, transforms, primvars (implementation only)
- `nanousd-mesh.h` / `nanousd-mesh.cpp` - Mesh geometry operations and manipulation

**Functional Domain Headers (Header-only):**
- `nanousd-iterator.h` - Iterator patterns for traversing collections (prims, properties, tokens, assets)
- `nanousd-camera.h` - Camera-specific functionality (FOV, exposure, aperture, clipping, transforms)
- `nanousd-material.h` - Material and shader system functions for building shader networks

**Function Groups:**
The API is organized into logical function groups using Doxygen `@defgroup`:
- **Stage Functions** - Stage creation, opening, saving, and management
- **Prim Functions** - Prim definition, validation, hierarchy operations, transforms, primvars
- **Property Functions** - Attribute and relationship access with type-safe getters/setters
- **Camera Functions** - Camera definition and parameter control
- **Material Functions** - Material and shader network creation
- **Iterators** - Collection traversal patterns

**Benefits of Modular Architecture:**
- **Maintainability**: Code is organized by functionality, making it easier to find and modify
- **Scalability**: New functionality can be added in focused modules without affecting other areas
- **Compile Times**: Changes to specific modules only require recompiling affected files
- **Team Development**: Multiple developers can work on different modules simultaneously
- **Testing**: Individual modules can be tested in isolation
- **Documentation**: Clear separation makes API documentation more organized

This modular approach provides a solid foundation for extending NanoUSD's capabilities while maintaining code quality and organization for both C and Python consumers.

## Python Wrapper Patterns for C Function Integration

### Core Principles for Adding C Functions to Python Stage Class

When adding new C functions to the Python wrapper, follow these established patterns found in the `Stage` class:

### 1. **Import and Setup Pattern**
```python
from . import ffi as _lib  # Auto-generated ctypes bindings
from ctypes import c_void_p, c_bool, c_char_p, POINTER, byref, c_float, c_double
```

### 2. **ctypes Argument Type Fixes**
For functions where ctypesgen generates incorrect signatures, add fixes at module level:
```python
# Fix up ctypesgen's sometimes wonky typing
_lib.function_name.argtypes = [_lib.nusd_stage_t, _lib.String, POINTER(c_char_p)]
```

### 3. **Stage Class Method Patterns**

#### **A. Simple C Function Wrapper (No Return Data)**
Pattern for functions that only return success/error codes:
```python
def function_name(self, path: str, value: type):
    result = _lib.nusd_c_function(
        self._stage,
        path.encode("ascii"),
        c_type(value)
    )
    if result != _lib.NUSD_RESULT_OK:
        raise AppropriateError(f'failed to do operation for "{path}": {result}')
```

**Example:** `define_prim`, `camera_define`, `material_define`

#### **B. C Function with String Encoding**
All string parameters must be encoded to ASCII before passing to C:
```python
def function_name(self, path: str):
    result = _lib.nusd_c_function(self._stage, path.encode("ascii"))
    if result != _lib.NUSD_RESULT_OK:
        raise DefinePrimError(f'failed for "{path}": {result}')
```

#### **C. C Function with Output Parameters**
For functions that return data via output parameters, use `byref()`:
```python
def function_name(self, path: str) -> ReturnType:
    output_var = c_type()  # or (c_type * size)() for arrays
    result = _lib.nusd_c_function(
        self._stage,
        path.encode("ascii"),
        byref(output_var)
    )
    if result != _lib.NUSD_RESULT_OK:
        raise GetPropertyError(f'failed to get data for "{path}": {result}')
    
    return process_output(output_var)  # Convert ctypes to Python types
```

**Example:** `attribute_get_color_space`, `prim_compute_local_to_world_transform`

#### **D. C Function with Array Input**
For functions taking array inputs, convert NumPy arrays to ctypes pointers:
```python
def function_name(self, path: str, data: np.ndarray):
    # Validate input
    if not isinstance(data, np.ndarray) or data.dtype != expected_dtype:
        raise SetPropertyError("invalid array type/shape")
    
    result = _lib.nusd_c_function(
        self._stage,
        path.encode("ascii"),
        data.ctypes.data_as(POINTER(c_type)),
        c_size_t(len(data))
    )
    if result != _lib.NUSD_RESULT_OK:
        raise SetPropertyError(f'failed to set data for "{path}": {result}')
```

**Example:** `prim_set_transform`

#### **E. C Function with Array Output**
For functions returning arrays, create ctypes array and convert to NumPy:
```python
def function_name(self, path: str) -> np.ndarray:
    output_array = (c_type * expected_size)()
    result = _lib.nusd_c_function(
        self._stage,
        path.encode("ascii"),
        output_array
    )
    if result != _lib.NUSD_RESULT_OK:
        raise GetPropertyError(f'failed to get array for "{path}": {result}')
    
    return np.array(output_array).reshape(shape)
```

#### **F. Optional Value Pattern**
For functions that optionally set values after creation:
```python
def function_name(self, path: str, name: str, type_: str, value=None, time_code=0.0):
    # First create the thing
    result = _lib.nusd_create_function(self._stage, path, name, type_)
    if result != _lib.NUSD_RESULT_OK:
        raise CreatePropertyError(f'failed to create "{name}": {result}')
    
    # Optionally set value
    if value is not None:
        full_path = f"{path}.{namespace}:{name}"  # Build full property path
        self.set_property(full_path, type_, value, time_code)
```

**Example:** `prim_create_property`, `shader_create_input`

### 4. **Error Handling Patterns**

#### **Standard Error Check Pattern**
```python
if result != _lib.NUSD_RESULT_OK:
    raise AppropriateError(f'descriptive message with "{context}": {result}')
```

#### **Specific Error Code Handling**
```python
if result == _lib.NUSD_RESULT_SPECIFIC_ERROR:
    raise SpecificError("specific error message")
elif result != _lib.NUSD_RESULT_OK:
    raise GeneralError(f'general error for "{context}": {result}')
```

**Example:** `shader_create_input` checking for `NUSD_RESULT_WRONG_TYPE`

#### **Multiple Error Conditions**
```python
if result == _lib.NUSD_RESULT_INVALID_ATTRIBUTE_PATH:
    raise GetPropertyError(f'cannot find path "{path}"')
elif result == _lib.NUSD_RESULT_CONNECTION_FAILED:
    raise SetPropertyError(f'failed to connect')
elif result != _lib.NUSD_RESULT_OK:
    raise SetPropertyError(f'general failure: {result}')
```

### 5. **Type Conversion Patterns**

#### **Python to C Types**
```python
# Strings: always encode to ASCII
path.encode("ascii")

# Numbers: wrap in appropriate ctypes
c_float(value), c_double(value), c_int(value)

# Arrays: use ctypes data pointer
array.ctypes.data_as(POINTER(c_type))

# Output parameters: use byref()
byref(output_variable)
```

#### **C to Python Types**
```python
# Strings: decode from bytes
c_char_p_var.value.decode("utf-8") if c_char_p_var.value else ""

# Arrays: convert to NumPy
np.array(c_array_var).reshape(shape)

# Simple values: extract .value
c_type_var.value
```

### 6. **Exception Classes Used**
- `DefinePrimError` - Prim/object creation failures
- `CreatePropertyError` - Property/attribute creation failures  
- `SetPropertyError` - Setting values, validation errors
- `GetPropertyError` - Getting values, path not found
- `StageOpenError` - Stage opening failures
- `StageCreateError` - Stage creation failures

### 7. **Common Method Naming Conventions**
- `thing_define()` - Create USD objects (prims, materials, etc.)
- `thing_set_property()` - Set properties/attributes on objects
- `thing_get_property()` - Get properties/attributes from objects
- `thing_create_sub_thing()` - Create sub-components (inputs, outputs, etc.)

### 8. **Documentation Pattern**
```python
def method_name(self, param1: type, param2: type) -> return_type:
    """Brief description of what the method does.
    
    Args:
        param1: Description of parameter
        param2: Description of parameter with examples (e.g., "value", "other")
        
    Returns:
        Description of return value
        
    Raises:
        SpecificError: When this specific condition occurs
        GeneralError: When general failure happens
        
    Note:
        Additional usage information, constraints, or behavior notes.
        Common values, expected ranges, coordinate systems, etc.
    """
```

### 9. **Integration Notes**
- Always check for `_lib.NUSD_RESULT_OK` after C function calls
- Use descriptive error messages that include the failing path/context
- Validate Python inputs before passing to C (type, shape, etc.)
- Handle optional parameters appropriately (None checks)
- Use established exception types for consistency
- Follow the encoding pattern: Python strings → `.encode("ascii")` → C
- Follow the decoding pattern: C strings → `.decode("utf-8")` → Python
- Use `self._stage` as the first parameter to all C stage functions
- Use `self.set_property()` and `self.get_property()` for property operations when appropriate

This pattern analysis provides the foundation for consistently integrating new C functions into the Python wrapper while maintaining the established coding style and error handling approach.