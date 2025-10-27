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
```

## Dependencies

- **Pixar USD**: The core USD library (required)
- **OpenGL**: Graphics library dependency
- **GoogleTest**: For unit testing (automatically downloaded via FetchContent)
- **uv**: Python package manager for managing Python dependencies and virtual environments
- **ctypesgen**: Automatically generates Python ctypes bindings from C header files
- **NumPy**: For efficient array operations in Python bindings

## Project Structure

### C Library
- `nanousd.h` - Main C API header file with comprehensive USD type definitions and function declarations
- `nanousd.cpp` - Implementation of the C wrapper around USD C++ APIs
- `example01.cpp` - Example application demonstrating basic USD file reading and property inspection
- `tests/nusd_test.cpp` - GoogleTest-based unit tests
- `test01.usda` - Sample USD file for testing and examples

### Python Bindings
- `python/` - Python package directory
  - `pyproject.toml` - Python package configuration with uv management
  - `nanousd/` - Python package module
    - `__init__.py` - High-level Python API with NumPy integration
    - `ffi.py` - Auto-generated ctypes bindings (do not edit manually)
  - `example01.py` - Python example demonstrating USD file operations
  - `tests/test_nanousd.py` - Python unit tests using pytest
  - `uv.lock` - Lock file for reproducible Python environment

### Build System
- `justfile` - Task runner configuration for orchestrating builds and tests
- `CMakeLists.txt` - CMake configuration for C library
- `build/` - CMake build output directory

## Core Architecture

### C Library
The library follows a C wrapper pattern:
- C++ USD objects are wrapped in opaque C handles (e.g., `nusd_stage_t`, `nusd_prim_iterator_t`)
- Iterator pattern for traversing prims, properties, and relationships
- Type-safe getters for various USD data types (float, double, int, bool, vectors, arrays)
- Comprehensive error handling with `nusd_result_t` return codes

### Python Bindings
The Python layer provides:
- **ctypes Integration**: Auto-generated bindings via ctypesgen from `nanousd.h`
- **NumPy Integration**: USD arrays are exposed as NumPy-compatible arrays with full operator support
- **Pythonic API**: Object-oriented interface with context managers and iterators
- **Type Safety**: USD type constants exposed as module-level constants
- **Memory Management**: Automatic cleanup of C resources via Python `__del__` methods

Key components:
- **Stage Management**: Creating, opening, saving USD stages (`Stage` class)
- **Prim Operations**: Defining and validating prims on stages
- **Property Access**: Reading attributes and relationships with automatic type conversion
- **Iterator Interface**: Pythonic iteration over scene hierarchy and properties
- **Array Types**: NumPy-compatible array classes (`FloatArray`, `Double3Array`, etc.) with mathematical operations

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
- Type-safe property getting/setting
- NumPy array integration and mathematical operations
- Error handling with custom exception types

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

## Development Notes

### C Library
- The library maintains a global stage registry (`STAGES`) to manage USD stage lifecycles
- Token initialization is thread-safe using mutex protection
- All array types provide size and data access functions with proper memory management
- The C API closely mirrors USD's C++ patterns while remaining C-compatible

### Python Bindings
- The `ffi.py` file is auto-generated by ctypesgen and should **never be edited manually**
- Regenerate Python bindings when `nanousd.h` changes using `just bind`
- Array classes inherit from `NDArrayOperatorsMixin` for full NumPy compatibility
- Memory management is handled automatically via Python's garbage collection and `__del__` methods
- Type constants (e.g., `FLOAT`, `COLOR3F`) are exposed at module level for easy access

### Workflow
- Primary development should focus on the C library (`nanousd.h`, `nanousd.cpp`)
- Python bindings are automatically generated and provide the main user interface
- **CRITICAL**: After modifying `nanousd.h`, ALWAYS run `just bind` to regenerate Python bindings before running `just pytest`
- Use `just pytest` as the primary testing method since it covers both C and Python functionality
- The Python layer handles type conversions and provides a more user-friendly API than the raw C interface