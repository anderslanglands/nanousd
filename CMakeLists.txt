cmake_minimum_required(VERSION 3.15)
project(nanousd VERSION 0.1.0)

option(ENABLE_DOCS "Enable buliding the API docs using Doxygen and Sphinx" ON)
option(ENABLE_TESTS "Enable the ctest-based tests" ON)

find_package(pxr REQUIRED)
find_package(OpenGL REQUIRED)

add_library(nanousd SHARED nanousd.cpp)
target_link_libraries(nanousd PUBLIC ${PXR_LIBRARIES})
target_include_directories(nanousd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(example01 example01.cpp)
target_link_libraries(example01 PUBLIC nanousd)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(ENABLE_DOCS)
    include(FetchContent)
    FetchContent_Declare(
        doxygen-awesome-css
        GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
        GIT_TAG v2.4.1
        GIT_SHALLOW TRUE  # optional, to save download time & space
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)

    # Save the location the files were cloned into
    FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

    # Generate the Doxyfile
    find_package(Doxygen)
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/python/docs/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/python/docs/Doxyfile)
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
