# CLAUDE.md - Python Wrapper

This file provides detailed guidance about the Python wrapper implementation for NanoUSD.

## Overview

The Python wrapper provides a high-level, Pythonic interface to the NanoUSD C API. It uses ctypes for low-level C interop and provides NumPy-compatible array classes for efficient data manipulation.

## Architecture

### Modular Design

The Python wrapper is organized into specialized modules for maintainability and clear separation of concerns:

1. **Low-Level Layer (`ffi.py`)**: Auto-generated ctypes bindings
2. **High-Level Layer**: Modular Python API with specialized submodules

```
Python User Code
       ↓
High-Level Python API (nanousd module)
├── __init__.py         - Main Stage class, core functionality, ctypes fixes
├── tokens.py           - USD type constants (FLOAT, COLOR3F, etc.)
├── array.py            - NumPy-compatible array wrapper classes
├── _get_property.py    - Property retrieval logic with type handling
└── _set_property.py    - Property setting logic with type validation
       ↓
Auto-Generated ctypes Bindings (ffi.py)
       ↓
NanoUSD C Library (libnanousd.so)
       ↓
Pixar USD C++ Library
```

### Module Organization

**Core Files:**
- **`__init__.py`**: Main entry point containing Stage class, iterators, exceptions, and ctypes argument fixes
- **`ffi.py`**: Auto-generated ctypes bindings (never edit manually)

**Specialized Modules:**
- **`tokens.py`**: USD type constants exposed as module-level variables
- **`array.py`**: NumPy-compatible array wrapper classes with operator support
- **`_get_property.py`**: Property retrieval with automatic type detection and conversion
- **`_set_property.py`**: Property setting with type validation and conversion

This modular approach provides:
- **Clear separation of concerns**: Each module has a specific responsibility
- **Maintainability**: Logic is organized by function rather than packed into one large file  
- **Reusability**: Submodules can be imported independently if needed
- **Testability**: Each module can be tested in isolation

## Code Generation

### Automatic Binding Generation

The `ffi.py` file is **automatically generated** using ctypesgen and should **never be edited manually**.

**Generation Command:**
```bash
just bind
# Runs: cd python && uv run ctypesgen -L../build -lnanousd -o nanousd/ffi.py [headers...]
```

**Source Headers:**
- `nanousd.h` - Main API aggregation
- `nanousd-types.h` - Core types and constants
- `nanousd-arrays.h` - Array type definitions
- `nanousd-iterators.h` - Iterator patterns
- `nanousd-properties.h` - Property access functions
- `nanousd-cameras.h` - Camera functionality
- `nanousd-materials.h` - Material and shader system

**Generated Content:**
- C function signatures as Python callables
- Struct definitions as ctypes classes
- Type constants as module-level variables
- Proper argument and return type specifications

### Important Notes

- **Never edit `ffi.py` manually** - changes will be overwritten
- Run `just bind` after any C header modifications
- ctypesgen syntax errors from system headers can be safely ignored
- The generation process is deterministic and reproducible

## High-Level Python API

### Stage Class (`__init__.py`)

The `Stage` class is the main entry point and wraps `nusd_stage_t`:

```python
class Stage:
    def __init__(self, stage_handle):
        self._stage = stage_handle  # Opaque C handle
    
    @classmethod
    def open(cls, file_path: str):
        # Calls nusd_stage_open_file()
        
    @classmethod  
    def create_in_memory(cls, identifier: str):
        # Calls nusd_stage_create_in_memory()
```

The Stage class delegates complex property operations to specialized modules:
- **Property Getting**: `get_property()` → `_get_property.py`
- **Property Setting**: `set_property()` → `_set_property.py`
- **Type Constants**: Imported from `tokens.py`
- **Array Results**: Returned as instances from `array.py`

### Type Constants Module (`tokens.py`)

All USD type constants are centralized in a dedicated module:

```python
# tokens.py
from . import ffi as _lib

ASSET = _lib.NUSD_TYPE_ASSET
BOOL = _lib.NUSD_TYPE_BOOL
COLOR3F = _lib.NUSD_TYPE_COLOR3F
FLOAT = _lib.NUSD_TYPE_FLOAT
FLOAT3 = _lib.NUSD_TYPE_FLOAT3
MATRIX4D = _lib.NUSD_TYPE_MATRIX4D
# ... all other USD types
```

This approach provides:
- **Centralized type management**: All constants in one place
- **Clean imports**: `from nanousd import FLOAT, COLOR3F`
- **Easy maintenance**: Changes only need to be made in one file

### Array Module (`array.py`)

NumPy-compatible array wrapper classes with a common base:

```python
class ArrayBase(NDArrayOperatorsMixin):
    def __array__(self, dtype=None):
        return np.asarray(self._view, dtype=dtype)
    
    def __array_ufunc__(self, ufunc, method, *inputs, **kwargs):
        # Handle elementwise operations like arr * 2
    
    def __array_function__(self, func, types, args, kwargs):
        # Delegate NumPy function calls like np.mean(self)

class FloatArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_float_array_size(array)
        data = _lib.nusd_float_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))
```

### Property Module Patterns

#### 1. Property Getting (`_get_property.py`)
Centralized type detection and conversion:

```python
def _get_property(stage, property_path: str, time_code: float = 0.0):
    # 1. Get property type
    property_type = _lib.nusd_type_t()
    result = _lib.nusd_property_get_type(stage._stage, property_path, byref(property_type))
    
    # 2. Branch based on type
    if property_type == _lib.NUSD_TYPE_FLOAT:
        # Handle float...
    elif property_type == _lib.NUSD_TYPE_FLOATARRAY:
        # Return FloatArray wrapper
    # ... etc for all types
```

#### 2. Property Setting (`_set_property.py`)  
Centralized type validation and conversion:

```python
def _set_property(stage, property_path: str, property_type, value: Any, time_code: float = 0.0):
    if property_type == FLOAT:
        if not isinstance(value, float):
            raise SetPropertyError(f"incompatible types...")
        result = _lib.nusd_attribute_set_float(stage._stage, property_path, c_float(value), time_code)
```

#### 3. Direct C Function Wrappers
Simple one-to-one mapping to C functions (in `Stage` class):

```python
def define_prim(self, prim_path: str, prim_type: str):
    result = _lib.nusd_stage_define_prim(self._stage, prim_path, prim_type)
    if result != _lib.NUSD_RESULT_OK:
        raise DefinePrimError(f'failed to define prim <{prim_path}> of type "{prim_type}": {result}')
```

#### 4. Optional Parameter Methods
Methods with optional value setting:

```python
def shader_create_input(self, shader_path: str, input_name: str, input_type: str, value=None, time_code=0.0):
    # Create the input
    result = _lib.nusd_shader_create_input(self._stage, shader_path, input_name, input_type)
    if result != _lib.NUSD_RESULT_OK:
        raise CreatePropertyError(f'failed to create input: {result}')
    
    # Optionally set value
    if value is not None:
        self.set_property(f"{shader_path}.inputs:{input_name}", input_type, value, time_code)
```

### ctypes Argument Fixes (`__init__.py`)

The main module contains ctypes argument type fixes for functions where ctypesgen generates incorrect signatures:

```python
# Fix up ctypesgen's sometimes wonky typing
_lib.nusd_prim_iterator_next.argtypes = [_lib.nusd_prim_iterator_t, POINTER(c_char_p)]
_lib.nusd_attribute_get_token.argtypes = [_lib.nusd_stage_t, _lib.String, c_double, POINTER(c_char_p)]
_lib.nusd_attribute_get_color_space.argtypes = [_lib.nusd_stage_t, _lib.String, POINTER(c_char_p)]
```

## Modular Type System

### Type Constants (`tokens.py`)

All USD type constants are now centralized and cleanly exposed:

```python
# Import pattern - all types available at module level
from nanousd import FLOAT, COLOR3F, ASSET, BOOL, MATRIX4D

# Internal organization in tokens.py
FLOAT = _lib.NUSD_TYPE_FLOAT
COLOR3F = _lib.NUSD_TYPE_COLOR3F
ASSET = _lib.NUSD_TYPE_ASSET
# ... all other USD types
```

### Type Mapping Patterns (`_get_property.py` & `_set_property.py`)

The property modules handle all type conversions between USD/C and Python:

#### Scalar Types (`_get_property.py`)
```python
# C: nusd_attribute_get_float(stage, path, time, &value)
# Python: Returns unwrapped value
if property_type == _lib.NUSD_TYPE_FLOAT:
    value = c_float(0.0)
    result = _lib.nusd_attribute_get_float(stage._stage, property_path, time_code, byref(value))
    if result != _lib.NUSD_RESULT_OK:
        raise GetPropertyError(f'failed to get value for "{property_path}": {result}')
    return value.value  # Extract from ctypes wrapper
```

#### Array Types (`_get_property.py`)
```python
# C: nusd_attribute_get_float_array(stage, path, time, &array_handle)
# Python: Returns NumPy-compatible array wrapper from array.py
if property_type == _lib.NUSD_TYPE_FLOATARRAY:
    value = _lib.nusd_float_array_t()
    result = _lib.nusd_attribute_get_float_array(stage._stage, property_path, time_code, byref(value))
    if result != _lib.NUSD_RESULT_OK:
        raise GetPropertyError(f'failed to get value for "{property_path}": {result}')
    return FloatArray(value)  # Return array wrapper class
```

#### Property Setting with Validation (`_set_property.py`)
```python
# Type validation and conversion for setting properties
if property_type == FLOAT:
    if not isinstance(value, (int, float)):
        raise SetPropertyError(f"incompatible types for property <{property_path}>...")
    result = _lib.nusd_attribute_set_float(stage._stage, property_path, c_float(value), time_code)
elif property_type == FLOATARRAY:
    if not isinstance(value, np.ndarray) or value.dtype != np.float32:
        raise SetPropertyError(f"incompatible types for property <{property_path}>...")
    result = _lib.nusd_attribute_set_float_array(
        stage._stage, property_path, 
        value.ctypes.data_as(POINTER(c_float)), 
        c_size_t(value.shape[0]), time_code
    )
```

#### Vector Types
```python
# C: nusd_attribute_get_float3(stage, path, time, array_ptr)
# Python: Returns NumPy array
if property_type in [_lib.NUSD_TYPE_FLOAT3, _lib.NUSD_TYPE_COLOR3F]:
    value = (c_float * 3)()
    result = _lib.nusd_attribute_get_float3(stage._stage, property_path, time_code, value)
    if result != _lib.NUSD_RESULT_OK:
        raise GetPropertyError(f'failed to get value for "{property_path}": {result}')
    return np.array(value)  # Convert to NumPy
```

#### String and Iterator Types
```python
# TOKEN: Simple string extraction
if property_type == _lib.NUSD_TYPE_TOKEN:
    value = c_char_p()
    result = _lib.nusd_attribute_get_token(stage._stage, property_path, time_code, byref(value))
    return value.value.decode("utf-8") if value.value else ""

# TOKENARRAY: Iterator pattern converted to Python list
if property_type == _lib.NUSD_TYPE_TOKENARRAY:
    value = _lib.nusd_token_array_iterator_t()
    result = _lib.nusd_attribute_get_token_array(stage._stage, property_path, time_code, byref(value))
    
    tokens = []
    tok = c_char_p()
    while _lib.nusd_token_array_iterator_next(value, byref(tok)):
        tokens.append(tok.value.decode("utf-8"))
    
    _lib.nusd_token_array_iterator_destroy(value)  # Always cleanup
    return tokens
```

## Array Classes (`array.py`)

### NumPy Integration with Common Base

All array classes inherit from a common `ArrayBase` that provides full NumPy compatibility:

```python
class ArrayBase(NDArrayOperatorsMixin):
    def __array__(self, dtype=None):
        return np.asarray(self._view, dtype=dtype)
    
    def __array_ufunc__(self, ufunc, method, *inputs, **kwargs):
        # Handle elementwise operations like arr * 2 or np.add(arr1, arr2)
        if method != "__call__":
            return NotImplemented
        
        # Convert ArrayBase inputs to raw arrays
        new_inputs = [x._view if isinstance(x, ArrayBase) else x for x in inputs]
        return getattr(ufunc, method)(*new_inputs, **kwargs)
    
    def __array_function__(self, func, types, args, kwargs):
        # Delegate NumPy function calls like np.mean(self)
        if not all(issubclass(t, (ArrayBase, np.ndarray)) for t in types):
            return NotImplemented
        new_args = [a._view if isinstance(a, ArrayBase) else a for a in args]
        return func(*new_args, **kwargs)

class FloatArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_float_array_size(array)
        data = _lib.nusd_float_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))  # NumPy view
    
    def __del__(self):
        _lib.nusd_float_array_destroy(self._array)  # Automatic cleanup
```

### Array Class Patterns

All array classes in `array.py` follow the same pattern:
1. **Inherit from `ArrayBase`**: Gets full NumPy operator support
2. **Wrap C array handle**: Store the C array handle for cleanup
3. **Create NumPy view**: Use `np.ctypeslib.as_array()` to create `_view`
4. **Automatic cleanup**: `__del__()` destroys the C array when Python object is garbage collected
5. **Shape handling**: Vectors have shape `(size, N)`, scalars have shape `(size,)`, matrices have shape `(size, N, N)`

## Memory Management

### Automatic Cleanup

Python's garbage collection handles C resource cleanup:

```python
def __del__(self):
    if hasattr(self, '_array') and self._array:
        _lib.nusd_float_array_destroy(self._array)
```

### Manual Resource Management

For iterators and temporary objects:

```python
# Always destroy iterators after use
iterator = _lib.nusd_token_array_iterator_t()
try:
    # Use iterator...
    pass
finally:
    _lib.nusd_token_array_iterator_destroy(iterator)
```

### Asset Path Handling

Special case for asset paths requiring explicit cleanup:

```python
if property_type == _lib.NUSD_TYPE_ASSET:
    value = _lib.nusd_asset_path_t()
    result = _lib.nusd_attribute_get_asset(self._stage, property_path, time_code, byref(value))
    
    asset_value = _lib.nusd_asset_path_get_asset_path(value)
    path_result = asset_value.decode("utf-8") if asset_value else ""
    _lib.nusd_asset_path_destroy(value)  # Manual cleanup required
    return path_result
```

## Error Handling

### Exception Mapping

C error codes are mapped to Python exceptions:

```python
class NanoUSDError(Exception):
    """Base exception for NanoUSD errors"""
    pass

class StageOpenError(NanoUSDError):
    """Failed to open USD stage"""
    pass

class GetPropertyError(NanoUSDError):
    """Failed to get property value"""
    pass

# Usage pattern:
if result != _lib.NUSD_RESULT_OK:
    raise GetPropertyError(f'failed to get value for "{property_path}": {result}')
```

### Common Error Patterns

1. **Null Parameter Validation**: Handled by C API
2. **Type Mismatches**: Raise `SetPropertyError` with descriptive message
3. **Path Errors**: Raise `GetPropertyError` or `SetPropertyError`
4. **Stage Errors**: Raise `StageOpenError` or `DefinePrimError`

## Testing Patterns

### Test Structure

Tests follow consistent patterns:

```python
def test_function_name():
    """Test description"""
    # 1. Create in-memory stage
    stage = nusd.Stage.create_in_memory("test_name")
    
    # 2. Set up test data
    stage.define_prim("/World", "Xform")
    
    # 3. Test the functionality
    stage.prim_create_property("/World", "testProp", nusd.FLOAT, 42.0)
    
    # 4. Verify results
    value = stage.get_property("/World.testProp")
    assert value == 42.0
```

### Array Testing

Array tests verify NumPy compatibility:

```python
def test_float_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    
    # Test NumPy array input
    test_data = np.array([1, 2, 3, 4, 5], dtype=np.float32)
    stage.set_property("/World.testArray", nusd.FLOATARRAY, test_data)
    
    # Test array wrapper output
    value = stage.get_property("/World.testArray")
    assert isinstance(value, nusd.FloatArray)
    assert np.array_equal(value, test_data)
```

## Development Workflow

### Making Changes to the Modular System

1. **Modify C Headers**: Update function signatures or add new functions
2. **Regenerate Bindings**: Run `just bind` to update `ffi.py`
3. **Update Appropriate Module**: Add/modify functionality in the correct module:
   - **Core methods**: Add to `Stage` class in `__init__.py`
   - **Type constants**: Add to `tokens.py`
   - **Array classes**: Add to `array.py`
   - **Property getting**: Add type handling to `_get_property.py`
   - **Property setting**: Add type validation to `_set_property.py`
4. **Fix ctypes Issues**: Add argument type fixes to `__init__.py` if needed
5. **Write Tests**: Add comprehensive tests (may need new test file)
6. **Verify**: Run `just pytest` to ensure everything works

### Module-Specific Guidelines

#### Adding Type Constants (`tokens.py`)
```python
# Simply add new constants following the pattern
NEW_TYPE = _lib.NUSD_TYPE_NEW_TYPE
NEW_TYPE_ARRAY = _lib.NUSD_TYPE_NEW_TYPE_ARRAY
```

#### Adding Array Classes (`array.py`)
```python
class NewTypeArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_new_type_array_size(array)
        data = _lib.nusd_new_type_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, N))  # Adjust shape
    
    def __del__(self):
        _lib.nusd_new_type_array_destroy(self._array)
```

#### Adding Property Support (`_get_property.py` & `_set_property.py`)
Add type handling to both modules following existing patterns.

#### Adding Core Methods (`__init__.py`)
Add new Stage methods with proper error handling and documentation.

### Common Gotchas

1. **Import Order**: `tokens.py` and `array.py` are imported with `*` in `__init__.py`
2. **Encoding**: C strings need `.decode("utf-8")` in Python
3. **Memory**: Array handles must be destroyed in `__del__()`
4. **Types**: Ensure ctypes type matching between C and Python
5. **ctypes Fixes**: Add to `__init__.py` if ctypesgen generates wrong signatures
6. **Module Dependencies**: `_get_property.py` and `_set_property.py` import from `array.py` and `tokens.py`

### Best Practices

1. **Modular Organization**: Put new functionality in the appropriate module
2. **Consistent Error Handling**: Always check `result != NUSD_RESULT_OK`
3. **Type Safety**: Validate input types before calling C functions in `_set_property.py`
4. **Documentation**: Include docstrings with parameter types and examples
5. **Testing**: Test both success and failure cases comprehensively
6. **Memory Safety**: Ensure all C resources are properly cleaned up
7. **Import Hygiene**: Use relative imports within the package

## Extension Points

### Adding New Types (Modular Approach)

To add support for a new USD type:

1. **C API**: Add getter/setter functions in appropriate header
2. **Regenerate**: Run `just bind` to get new ctypes bindings
3. **Type Constants**: Add to `tokens.py`
4. **Array Classes**: Add to `array.py` if it's an array type
5. **Property Integration**: Add type handling to `_get_property.py` and `_set_property.py`
6. **Testing**: Add comprehensive tests for the new type

### Adding New Functionality (Modular Approach)

To add new high-level functionality:

1. **C Functions**: Implement in C API with proper error handling
2. **Python Wrapper**: Create high-level method in `Stage` class in `__init__.py`
3. **Error Handling**: Map C errors to appropriate Python exceptions
4. **ctypes Fixes**: Add argument type fixes to `__init__.py` if needed
5. **Documentation**: Add examples and usage patterns
6. **Testing**: Create comprehensive test coverage

## Benefits of Modular Architecture

The refactored modular structure provides significant benefits:

### Maintainability
- **Clear separation of concerns**: Each module has a specific, well-defined purpose
- **Easier debugging**: Issues can be isolated to specific modules
- **Simpler code reviews**: Changes are localized to relevant modules

### Scalability
- **Independent development**: Different team members can work on different modules
- **Targeted testing**: Modules can be tested in isolation
- **Focused imports**: Only import what you need

### Code Quality
- **Reduced complexity**: Large monolithic file broken into manageable pieces
- **Better organization**: Related functionality grouped together
- **Easier refactoring**: Changes are contained within module boundaries

### Development Efficiency
- **Faster iteration**: Smaller files load and compile faster
- **Clearer responsibilities**: Developers know exactly where to add new functionality
- **Better IDE support**: Smaller files work better with code intelligence features

This modular architecture provides a solid, scalable foundation for extending NanoUSD's Python capabilities while maintaining type safety, performance, and code quality.