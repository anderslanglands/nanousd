# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NanoUSD is a C wrapper library for Pixar's USD (Universal Scene Description) library. It provides a simplified C API for working with USD files, making it easier to integrate USD functionality into C-based applications.

## Build System

This project uses CMake as its build system. Key build commands:

```bash
# Configure and build the project
# Requires OpenUSD to be discoverable via CMAKE_PREFIX_PATH
cmake -B build -G Ninja
cmake --build build
```

## Dependencies

- **Pixar USD**: The core USD library (required)
- **OpenGL**: Graphics library dependency
- **GoogleTest**: For unit testing (automatically downloaded via FetchContent)

## Project Structure

- `nanousd.h` - Main C API header file with comprehensive USD type definitions and function declarations
- `nanousd.cpp` - Implementation of the C wrapper around USD C++ APIs
- `example01.cpp` - Example application demonstrating basic USD file reading and property inspection
- `tests/nusd_test.cpp` - GoogleTest-based unit tests
- `test01.usda` - Sample USD file for testing and examples

## Core Architecture

The library follows a C wrapper pattern:
- C++ USD objects are wrapped in opaque C handles (e.g., `nusd_stage_t`, `nusd_prim_iterator_t`)
- Iterator pattern for traversing prims, properties, and relationships
- Type-safe getters for various USD data types (float, double, int, bool, vectors, arrays)
- Comprehensive error handling with `nusd_result_t` return codes

Key components:
- **Stage Management**: Creating, opening, saving USD stages
- **Prim Operations**: Defining and validating prims on stages
- **Property Access**: Reading attributes and relationships with type checking
- **Iterator Interface**: Traversing scene hierarchy and properties
- **Memory Management**: Proper cleanup of allocated resources

## Testing

Run tests using CTest:
```bash
ctest --test-dir build --output-on-failure
```

## Example Usage

See `example01.cpp` for a complete example that:
1. Opens a USD file
2. Traverses all prims in the scene
3. Inspects properties and their values
4. Handles different USD data types properly

## Development Notes

- The library maintains a global stage registry (`STAGES`) to manage USD stage lifecycles
- Token initialization is thread-safe using mutex protection
- All array types provide size and data access functions with proper memory management
- The C API closely mirrors USD's C++ patterns while remaining C-compatible