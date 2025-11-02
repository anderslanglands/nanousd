#include <gtest/gtest.h>
#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>
#include <cmath>

TEST(nusd, define_prim) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
}

TEST(nusd, define_prim_and_check_valid) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);
}

TEST(nusd, invalid_prim_path_fails_validity_check) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/Worldx"), false);
}

TEST(nusd, prim_set_transform) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-prim_set_transform", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Set up a test transformation matrix (camera looking down negative Z with some translation)
    double local_to_parent_matrix[16] = {
        1.0, 0.0, 0.0, 0.0,  // X axis (right)
        0.0, 1.0, 0.0, 0.0,  // Y axis (up)
        0.0, 0.0, 1.0, 0.0,  // Z axis (forward)
        5.0, 3.0, 10.0, 1.0  // Translation (position)
    };
    
    // Set the camera transform
    result = nusd_prim_set_transform(stage, "/World/Camera", local_to_parent_matrix, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Use nusd_prim_compute_local_to_world_transform to verify the resulting world transform
    double world_transform[16];
    result = nusd_prim_compute_local_to_world_transform(stage, "/World/Camera", NUSD_TIMECODE_DEFAULT, world_transform);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Since camera is a direct child of World and World has identity transform,
    // the world transform should match our local_to_parent_matrix
    for (int i = 0; i < 16; i++) {
        EXPECT_DOUBLE_EQ(world_transform[i], local_to_parent_matrix[i]);
    }
    
    nusd_stage_destroy(stage);
}
