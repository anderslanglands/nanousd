cmake_minimum_required(VERSION 3.24)
project(nanousd VERSION 0.1.0)

option(ENABLE_DOCS "Enable buliding the API docs using Doxygen and Sphinx" OFF)
option(ENABLE_TESTS "Enable the ctest-based tests" ON)

set(USD_BUILD_TYPE "release" CACHE STRING "Choose debug or release for USD dependency")

set(LOCAL_USD_BUILD OFF)
set(STATIC_USD_BUILD OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(USD_MINIMAL_VERSION 25.11.17)
if(LOCAL_USD_BUILD)
    set(usd_minimal_SOURCE_DIR /home/anders/code/openusd-minimal-build/build/openusd-minimal-${USD_MINIMAL_VERSION})
else()
    FetchContent_Declare(
      usd_minimal
      URL "https://github.com/anderslanglands/openusd-minimal-build/releases/download/v${USD_MINIMAL_VERSION}/openusd-minimal-${USD_BUILD_TYPE}-v${USD_MINIMAL_VERSION}.tar.gz"
      DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(usd_minimal)
endif()

set(CMAKE_PREFIX_PATH ${usd_minimal_SOURCE_DIR})

set(PXR_BUILD_MONOLITHIC ON)
find_package(pxr REQUIRED)
find_package(TBB REQUIRED)
find_package(OpenSubdiv REQUIRED)

add_library(nanousd 
    nanousd.cpp
    nanousd-property.cpp
    nanousd-array.cpp
    nanousd-prim.cpp
    nanousd-mesh.cpp
    nanousd-light.cpp
)

if(STATIC_USD_BUILD)
    target_link_libraries(nanousd PUBLIC "$<LINK_LIBRARY:WHOLE_ARCHIVE,usd_m>" "$<LINK_LIBRARY:WHOLE_ARCHIVE,OpenSubdiv::osdCPU_static>")
else()
    target_link_libraries(nanousd PUBLIC usd_ms)
endif()

target_include_directories(nanousd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# set(CMAKE_INSTALL_RPATH "$ORIGIN")
set_target_properties(nanousd PROPERTIES INSTALL_RPATH "$ORIGIN")

get_target_property(TBB_LIBRARY_PATH TBB::tbb LOCATION)
message("TBB: ${TBB_LIBRARY_PATH}")
file(REAL_PATH "${TBB_LIBRARY_PATH}" TBB_RESOLVED_PATH)
message("TBB_RESOLVED_PATH: ${TBB_RESOLVED_PATH}")

get_target_property(USD_LIBRARY_PATH usd_ms LOCATION)
message("USD: ${USD_LIBRARY_PATH}")

set(HEADERS
    nanousd-array.h
    nanousd-camera.h
    nanousd-iterator.h
    nanousd-light.h
    nanousd-material.h
    nanousd-mesh.h
    nanousd-prim.h
    nanousd-property.h
    nanousd-types.h
    nanousd.h
)

target_sources(nanousd 
    PUBLIC FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        nanousd-array.h
        nanousd-camera.h
        nanousd-iterator.h
        nanousd-light.h
        nanousd-material.h
        nanousd-mesh.h
        nanousd-prim.h
        nanousd-property.h
        nanousd-types.h
        nanousd.h
)

install(TARGETS nanousd
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/nanousd"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/nanousd"
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/nanousd"
        FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_PREFIX}/nanousd"
)

message("INSTALL PATH ${CMAKE_INSTALL_PREFIX}/nanousd")
install(FILES ${TBB_LIBRARY_PATH} ${TBB_RESOLVED_PATH} ${USD_LIBRARY_PATH} DESTINATION "${CMAKE_INSTALL_PREFIX}/nanousd")

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
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/../python/docs/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/python/docs/Doxyfile)
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
