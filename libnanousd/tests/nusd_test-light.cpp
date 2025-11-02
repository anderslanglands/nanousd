#include <gtest/gtest.h>

#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>

#include <cmath>

TEST(nusd, rect_light_define_basic) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-rect-light-basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a rectangular light with basic parameters
    float color[] = {1.0f, 1.0f, 1.0f};  // White light
    
    result = nusd_rect_light_define(stage, "/World/RectLight", 
                                   2.0f, 1.0f,  // width, height
                                   1000.0f,     // intensity
                                   color);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the light prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/RectLight"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, rect_light_define_colored) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-rect-light-colored", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a rectangular light with colored light (warm orange)
    float color[] = {1.0f, 0.7f, 0.3f};  // Warm orange light
    
    result = nusd_rect_light_define(stage, "/World/WarmLight", 
                                   4.0f, 2.0f,  // larger dimensions
                                   500.0f,      // moderate intensity
                                   color);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the light prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/WarmLight"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, rect_light_define_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-rect-light-null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    float color[] = {1.0f, 1.0f, 1.0f};

    // Test null stage
    EXPECT_EQ(nusd_rect_light_define(nullptr, "/World/Light", 
                                    1.0f, 1.0f, 1000.0f, color), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null light_path
    EXPECT_EQ(nusd_rect_light_define(stage, nullptr, 
                                    1.0f, 1.0f, 1000.0f, color), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null color
    EXPECT_EQ(nusd_rect_light_define(stage, "/World/Light", 
                                    1.0f, 1.0f, 1000.0f, nullptr), 
              NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, disk_light_define_basic) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-disk-light-basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a disk light with basic parameters
    float color[] = {1.0f, 1.0f, 1.0f};  // White light
    
    result = nusd_disk_light_define(stage, "/World/DiskLight", 
                                   1.5f,        // radius
                                   800.0f,      // intensity
                                   color);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the light prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/DiskLight"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, disk_light_define_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-disk-light-null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    float color[] = {1.0f, 1.0f, 1.0f};

    // Test null stage
    EXPECT_EQ(nusd_disk_light_define(nullptr, "/World/Light", 
                                    1.0f, 1000.0f, color), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null light_path
    EXPECT_EQ(nusd_disk_light_define(stage, nullptr, 
                                    1.0f, 1000.0f, color), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null color
    EXPECT_EQ(nusd_disk_light_define(stage, "/World/Light", 
                                    1.0f, 1000.0f, nullptr), 
              NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, sphere_light_define_basic) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-sphere-light-basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a sphere light with basic parameters
    float color[] = {0.9f, 0.8f, 0.7f};  // Warm light
    
    result = nusd_sphere_light_define(stage, "/World/SphereLight", 
                                     2.0f,        // radius
                                     1200.0f,     // intensity
                                     color);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the light prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/SphereLight"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, sphere_light_define_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-sphere-light-null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    float color[] = {1.0f, 1.0f, 1.0f};

    // Test null stage
    EXPECT_EQ(nusd_sphere_light_define(nullptr, "/World/Light", 
                                      1.0f, 1000.0f, color), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null light_path
    EXPECT_EQ(nusd_sphere_light_define(stage, nullptr, 
                                      1.0f, 1000.0f, color), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null color
    EXPECT_EQ(nusd_sphere_light_define(stage, "/World/Light", 
                                      1.0f, 1000.0f, nullptr), 
              NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}