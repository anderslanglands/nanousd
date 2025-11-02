# Download GoogleTest automatically
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0 
)
FetchContent_MakeAvailable(googletest)

add_executable(nusd_test 
    nusd_test.cpp
    nusd_test-camera.cpp
    nusd_test-light.cpp
    nusd_test-material.cpp
    nusd_test-mesh.cpp
    nusd_test-prim.cpp
    nusd_test-property.cpp
)
target_link_libraries(nusd_test PRIVATE GTest::gtest_main nanousd)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(nusd_test)
