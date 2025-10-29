# CLAUDE.md - Python Wrapper

This file provides detailed guidance about the Python wrapper implementation for NanoUSD.

## Overview

The Python wrapper provides a high-level, Pythonic interface to the NanoUSD C API. It uses ctypes for low-level C interop and provides NumPy-compatible array classes for efficient data manipulation.

## Architecture

### Two-Layer Design

1. **Low-Level Layer (`ffi.py`)**: Auto-generated ctypes bindings
2. **High-Level Layer (`__init__.py`)**: Pythonic wrapper classes and functions

```
Python User Code
       ↓
High-Level Python API (__init__.py)
       ↓
Auto-Generated ctypes Bindings (ffi.py)
       ↓
NanoUSD C Library (libnanousd.so)
       ↓
Pixar USD C++ Library
```

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

### Stage Class

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

### Method Patterns

#### 1. Direct C Function Wrappers
Simple one-to-one mapping to C functions:

```python
def define_prim(self, prim_path: str, prim_type: str):
    result = _lib.nusd_stage_define_prim(self._stage, prim_path, prim_type)
    if result != _lib.NUSD_RESULT_OK:
        raise DefinePrimError(f'failed to define prim <{prim_path}> of type "{prim_type}": {result}')
```

#### 2. Type-Polymorphic Methods
Single Python method handling multiple USD types:

```python
def get_property(self, property_path: str, time_code: float = 0.0):
    # 1. Get property type
    property_type = _lib.nusd_type_t()
    result = _lib.nusd_property_get_type(self._stage, property_path, byref(property_type))
    
    # 2. Branch based on type
    if property_type == _lib.NUSD_TYPE_FLOAT:
        # Handle float...
    elif property_type == _lib.NUSD_TYPE_ASSET:
        # Handle asset...
    # ... etc for all types
```

#### 3. Optional Parameter Methods
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

## Type System

### USD Type Constants

Constants from C API are exposed at module level:

```python
# In __init__.py
FLOAT = _lib.NUSD_TYPE_FLOAT
COLOR3F = _lib.NUSD_TYPE_COLOR3F
ASSET = _lib.NUSD_TYPE_ASSET
# ... etc
```

### Type Mapping Patterns

#### Scalar Types
```python
# C: nusd_attribute_get_float(stage, path, time, &value)
# Python: Returns value.value (unwrapped from ctypes)
if property_type == _lib.NUSD_TYPE_FLOAT:
    value = c_float(0.0)
    result = _lib.nusd_attribute_get_float(self._stage, property_path, time_code, byref(value))
    return value.value  # Extract from ctypes wrapper
```

#### Array Types
```python
# C: nusd_attribute_get_float_array(stage, path, time, &array_handle)
# Python: Returns custom array wrapper class
if property_type == _lib.NUSD_TYPE_FLOATARRAY:
    value = _lib.nusd_float_array_t()
    result = _lib.nusd_attribute_get_float_array(self._stage, property_path, time_code, byref(value))
    return FloatArray(value)  # Wrap in NumPy-compatible class
```

#### Vector Types
```python
# C: nusd_attribute_get_float3(stage, path, time, array_ptr)
# Python: Returns NumPy array
if property_type == _lib.NUSD_TYPE_FLOAT3:
    value = (c_float * 3)()
    result = _lib.nusd_attribute_get_float3(self._stage, property_path, time_code, value)
    return np.array(value)  # Convert to NumPy
```

#### String Types
```python
# C: nusd_attribute_get_token(stage, path, time, &char_ptr)
# Python: Returns decoded string
if property_type == _lib.NUSD_TYPE_TOKEN:
    value = c_char_p()
    result = _lib.nusd_attribute_get_token(self._stage, property_path, time_code, byref(value))
    return value.value.decode("utf-8")
```

#### Iterator Types
```python
# C: Iterator pattern with next() and destroy()
# Python: Convert to Python list
if property_type == _lib.NUSD_TYPE_TOKENARRAY:
    value = _lib.nusd_token_array_iterator_t()
    result = _lib.nusd_attribute_get_token_array(self._stage, property_path, time_code, byref(value))
    
    result = []
    tok = c_char_p()
    while _lib.nusd_token_array_iterator_next(value, byref(tok)):
        result.append(tok.value.decode("utf-8"))
    
    _lib.nusd_token_array_iterator_destroy(value)  # Cleanup
    return result
```

## Array Classes

### NumPy Integration

Custom array classes provide NumPy compatibility:

```python
class FloatArray(NDArrayOperatorsMixin):
    def __init__(self, array_handle):
        self._array = array_handle
    
    def __array__(self):
        # Enable NumPy compatibility
        size = _lib.nusd_float_array_size(self._array)
        data_ptr = _lib.nusd_float_array_data(self._array)
        return np.ctypeslib.as_array(data_ptr, shape=(size,))
    
    def __del__(self):
        # Automatic cleanup
        _lib.nusd_float_array_destroy(self._array)
```

### Array Class Patterns

All array classes follow the same pattern:
1. Wrap C array handle in constructor
2. Implement `__array__()` for NumPy compatibility
3. Implement `__del__()` for automatic cleanup
4. Inherit from `NDArrayOperatorsMixin` for mathematical operations

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

### Making Changes

1. **Modify C Headers**: Update function signatures or add new functions
2. **Regenerate Bindings**: Run `just bind` to update `ffi.py`
3. **Update Python Wrapper**: Add/modify high-level methods in `__init__.py`
4. **Write Tests**: Add comprehensive tests in `test_nanousd.py`
5. **Verify**: Run `just pytest` to ensure everything works

### Common Gotchas

1. **Encoding**: C strings need `.decode("utf-8")` in Python
2. **Memory**: Array handles must be destroyed in `__del__()`
3. **Types**: Ensure ctypes type matching between C and Python
4. **Namespaces**: Shader inputs/outputs automatically get "inputs:"/"outputs:" prefixes

### Best Practices

1. **Consistent Error Handling**: Always check `result != NUSD_RESULT_OK`
2. **Type Safety**: Validate input types before calling C functions
3. **Documentation**: Include docstrings with parameter types and examples
4. **Testing**: Test both success and failure cases comprehensively
5. **Memory Safety**: Ensure all C resources are properly cleaned up

## Extension Points

### Adding New Types

To add support for a new USD type:

1. **C API**: Add getter/setter functions in appropriate header
2. **Regenerate**: Run `just bind` to get new ctypes bindings
3. **Python Integration**: Add type handling to `get_property`/`set_property`
4. **Testing**: Add comprehensive tests for the new type

### Adding New Functionality

To add new high-level functionality:

1. **C Functions**: Implement in C API with proper error handling
2. **Python Wrapper**: Create high-level method in `Stage` class
3. **Error Handling**: Map C errors to appropriate Python exceptions
4. **Documentation**: Add examples and usage patterns
5. **Testing**: Create comprehensive test coverage

This architecture provides a solid foundation for extending NanoUSD's Python capabilities while maintaining type safety and performance.