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
- `nanousd.h` - Main C API header that aggregates all modular headers
- `nanousd.cpp` - Implementation of the C wrapper around USD C++ APIs
- `nanousd-types.h` - Core type definitions, constants, and error codes
- `nanousd-array.h` - Array type definitions and functions (float, int, matrix, bool, uint arrays)
- `nanousd-iterator.h` - Iterator definitions for traversing collections (prims, properties, tokens, assets)
- `nanousd-property.h` - Property and attribute access functions with comprehensive USD type support
- `nanousd-camera.h` - Camera-specific functionality (FOV, exposure, aperture, clipping, transforms)
- `nanousd-material.h` - Material and shader system functions for building shader networks
- `example01.cpp` - Example application demonstrating basic USD file reading and property inspection
- `tests/nusd_test.cpp` - GoogleTest-based unit tests (57 tests total)
- `test01.usda` - Sample USD file for testing and examples

### Python Bindings
- `python/` - Python package directory
  - `pyproject.toml` - Python package configuration with uv management
  - `nanousd/` - Python package module
    - `__init__.py` - Main module aggregating all submodules
    - `ffi.py` - Auto-generated ctypes bindings (do not edit manually)
    - `tokens.py` - USD type constants and enumerations
    - `array.py` - NumPy-compatible array wrapper classes
    - `_get_property.py` - Property retrieval logic with type detection
    - `_set_property.py` - Property setting logic with validation
  - `example01.py` - Python example demonstrating USD file operations
  - `tests/test_nanousd.py` - Main Python unit tests using pytest
  - `tests/test_color_space.py` - Color space functionality tests
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
- Type-safe getters for various USD data types (float, double, int, bool, vectors, matrices, arrays)
- Comprehensive error handling with `nusd_result_t` return codes
- Full support for USD materials and shader networks
- Asset path handling for external file references
- Token support for shader identifiers and metadata
- Camera functionality with exposure, aperture, and transform controls
- Comprehensive null parameter validation throughout API

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
- **Material System**: Material definition, shader creation, and shader network connections
- **Camera Controls**: Camera definition, transform setting, FOV, exposure, and aperture controls
- **Asset Management**: Asset path handling for textures and external file references
- **Token Support**: String token handling for shader IDs and metadata

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
- **NOTE**: ctypesgen syntax errors from system headers (e.g. `/usr/include/x86_64-linux-gnu/sys/cdefs.h`) can be safely ignored - they're due to ctypesgen parser limitations, not actual code errors

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

### File Organization
The codebase is well-organized with modular headers that provide clear functional separation:

**Core Headers:**
- `nanousd.h` - Main API aggregation header that includes all modular headers
- `nanousd-types.h` - Core type definitions, constants, error codes, and stage functions

**Functional Domain Headers:**
- `nanousd-array.h` - Array type definitions and functions (bool, float, double, int, uint, matrix arrays)
- `nanousd-iterator.h` - Iterator patterns for traversing collections (prims, properties, tokens, assets)
- `nanousd-property.h` - Property and attribute access with comprehensive USD type support including color space metadata
- `nanousd-camera.h` - Camera-specific functionality (FOV, exposure, aperture, clipping, transforms)
- `nanousd-material.h` - Material and shader system functions for building shader networks

**Implementation:**
- `nanousd.cpp` - Complete implementation of all C API functions

**Function Groups:**
The API is organized into logical function groups using Doxygen `@defgroup`:
- **Stage Functions** - Stage creation, opening, saving, and management
- **Prim Functions** - Prim definition, validation, and hierarchy operations
- **Property Functions** - Attribute and relationship access with type-safe getters/setters
- **Camera Functions** - Camera definition and parameter control
- **Material Functions** - Material and shader network creation
- **Iterators** - Collection traversal patterns

This modular approach makes the codebase maintainable, allows easy extension of specific functionality areas, and provides clear API organization for both C and Python consumers.