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

TEST(nusd, prim_set_extent_basic) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-prim_set_extent_basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a cube (which is a boundable prim)
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Cube", "Cube"), NUSD_RESULT_OK);

    // Set extent for the cube: bounding box from (-1,-1,-1) to (1,1,1)
    float extent[] = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f};
    result = nusd_prim_set_extent(stage, "/World/Cube", extent);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_set_extent_mesh) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-prim_set_extent_mesh", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a simple triangle mesh
    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f};
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Mesh",
                              face_vertex_counts, 1,
                              face_vertex_indices, 3,
                              vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set extent that encompasses the triangle vertices
    float extent[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f};
    result = nusd_prim_set_extent(stage, "/World/Mesh", extent);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_set_extent_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-prim_set_extent_null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Cube", "Cube"), NUSD_RESULT_OK);

    float extent[] = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f};

    // Test null stage
    EXPECT_EQ(nusd_prim_set_extent(nullptr, "/World/Cube", extent), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null prim_path
    EXPECT_EQ(nusd_prim_set_extent(stage, nullptr, extent), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null extent
    EXPECT_EQ(nusd_prim_set_extent(stage, "/World/Cube", nullptr), 
              NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_set_extent_invalid_prim_path) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-prim_set_extent_invalid", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    float extent[] = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f};

    // Test non-existent prim
    EXPECT_EQ(nusd_prim_set_extent(stage, "/NonExistent/Prim", extent), 
              NUSD_RESULT_INVALID_PRIM_PATH);

    // Test non-boundable prim (Xform is not boundable)
    EXPECT_EQ(nusd_prim_set_extent(stage, "/World", extent), 
              NUSD_RESULT_INVALID_PRIM_PATH);

    nusd_stage_destroy(stage);
}
