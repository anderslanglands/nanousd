cmake_minimum_required(VERSION 3.15)
project(nanousd VERSION 0.1.0)

find_package(pxr REQUIRED)
find_package(OpenGL REQUIRED)

add_library(nanousd SHARED nanousd.cpp)
target_link_libraries(nanousd PUBLIC ${PXR_LIBRARIES})
target_include_directories(nanousd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(example01 example01.cpp)
target_link_libraries(example01 PUBLIC nanousd)

enable_testing()
add_subdirectory(tests)