#include <gtest/gtest.h>

#include <nanousd-camera.h>
#include <nanousd-light.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-prim.h>
#include <nanousd.h>

#include <cmath>

TEST(nusd, define_prim) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
}

TEST(nusd, define_prim_and_check_valid) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);
}

TEST(nusd, invalid_prim_path_fails_validity_check) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/Worldx"), false);
}

TEST(nusd, prim_set_transform) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_set_transform", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set up a test transformation matrix (camera looking down negative Z with
    // some translation)
    double local_to_parent_matrix[16] = {
        1.0,
        0.0,
        0.0,
        0.0, // X axis (right)
        0.0,
        1.0,
        0.0,
        0.0, // Y axis (up)
        0.0,
        0.0,
        1.0,
        0.0, // Z axis (forward)
        5.0,
        3.0,
        10.0,
        1.0 // Translation (position)
    };

    // Set the camera transform
    result = nusd_prim_set_transform(
        stage, "/World/Camera", local_to_parent_matrix, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Use nusd_prim_compute_local_to_world_transform to verify the resulting
    // world transform
    double world_transform[16];
    result = nusd_prim_compute_local_to_world_transform(
        stage, "/World/Camera", NUSD_TIMECODE_DEFAULT, world_transform);
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
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_set_extent_basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a cube (which is a boundable prim)
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Cube", "Cube"),
              NUSD_RESULT_OK);

    // Set extent for the cube: bounding box from (-1,-1,-1) to (1,1,1)
    float extent[] = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f};
    result = nusd_prim_set_extent(stage, "/World/Cube", extent);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_set_extent_mesh) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_set_extent_mesh", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a simple triangle mesh
    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f};
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage,
                              "/World/Mesh",
                              face_vertex_counts,
                              1,
                              face_vertex_indices,
                              3,
                              vertices,
                              3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set extent that encompasses the triangle vertices
    float extent[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f};
    result = nusd_prim_set_extent(stage, "/World/Mesh", extent);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_set_extent_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_set_extent_null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Cube", "Cube"),
              NUSD_RESULT_OK);

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
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_set_extent_invalid", &stage);
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

TEST(nusd, prim_add_translate_op_basic) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_add_translate_op_basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a camera (which is xformable)
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Add translate operation with initial translation
    double translation[] = {5.0, 3.0, 10.0};
    result = nusd_prim_add_translate_op(
        stage, "/World/Camera", nullptr, translation, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_add_translate_op_with_suffix) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory(
        "test-prim_add_translate_op_suffix", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a mesh (which is xformable)
    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f};
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage,
                              "/World/Mesh",
                              face_vertex_counts,
                              1,
                              face_vertex_indices,
                              3,
                              vertices,
                              3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Add translate operation with custom suffix
    double translation[] = {2.0, 1.0, 0.0};
    result = nusd_prim_add_translate_op(
        stage, "/World/Mesh", "pivot", translation, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_add_translate_op_no_initial_value) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory(
        "test-prim_add_translate_op_no_value", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Cube", "Cube"),
              NUSD_RESULT_OK);

    // Add translate operation without initial value
    result = nusd_prim_add_translate_op(
        stage, "/World/Cube", "offset", nullptr, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_add_translate_op_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-prim_add_translate_op_null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    double translation[] = {1.0, 2.0, 3.0};

    // Test null stage
    EXPECT_EQ(
        nusd_prim_add_translate_op(
            nullptr, "/World", nullptr, translation, NUSD_TIMECODE_DEFAULT),
        NUSD_RESULT_NULL_PARAMETER);

    // Test null xformable_path
    EXPECT_EQ(nusd_prim_add_translate_op(
                  stage, nullptr, nullptr, translation, NUSD_TIMECODE_DEFAULT),
              NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_add_translate_op_invalid_prim_path) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory(
        "test-prim_add_translate_op_invalid", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double translation[] = {1.0, 2.0, 3.0};

    // Test non-existent prim
    EXPECT_EQ(nusd_prim_add_translate_op(stage,
                                         "/NonExistent/Prim",
                                         nullptr,
                                         translation,
                                         NUSD_TIMECODE_DEFAULT),
              NUSD_RESULT_INVALID_PRIM_PATH);

    nusd_stage_destroy(stage);
}

TEST(nusd, prim_add_translate_op_multiple_operations) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory(
        "test-prim_add_translate_op_multiple", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Add multiple translate operations with different suffixes
    double translation1[] = {1.0, 0.0, 0.0};
    result = nusd_prim_add_translate_op(
        stage, "/World", "offset1", translation1, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double translation2[] = {0.0, 2.0, 0.0};
    result = nusd_prim_add_translate_op(
        stage, "/World", "offset2", translation2, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double translation3[] = {0.0, 0.0, 3.0};
    result = nusd_prim_add_translate_op(
        stage, "/World", "offset3", translation3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_path_is_valid_prim_comprehensive) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_path_is_valid_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test root path validity (USD root "/" is always valid)
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/"), true);

    // Create basic hierarchy
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Geometry", "Xform"),
              NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Geometry/Mesh", "Mesh"),
              NUSD_RESULT_OK);

    // Test valid paths
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Geometry"), true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Geometry/Mesh"),
              true);

    // Test invalid paths
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/NonExistent"), false);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/NonExistent"),
              false);
    EXPECT_EQ(
        nusd_stage_path_is_valid_prim(stage, "/World/Geometry/NonExistent"),
        false);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_path_is_valid_prim_edge_cases) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_path_edge_cases", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Test empty string (should be false)
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, ""), false);

    // Test partial path matches (should be false)
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/Worl"), false);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/Worldx"), false);

    // Test case sensitivity
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/world"), false);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/WORLD"), false);

    // Test paths with trailing characters
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/"), false);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World "), false);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_path_is_valid_prim_different_prim_types) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_path_prim_types", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create different types of prims
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_material_define(stage, "/World/Materials/MyMaterial");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_shader_define(
        stage, "/World/Materials/MyMaterial/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Geometry/Cube", "Cube"),
              NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World/Geometry/Sphere", "Sphere"),
              NUSD_RESULT_OK);

    // Test all created prims are valid
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Camera"), true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Materials"), true);
    EXPECT_EQ(
        nusd_stage_path_is_valid_prim(stage, "/World/Materials/MyMaterial"),
        true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(
                  stage, "/World/Materials/MyMaterial/Surface"),
              true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Geometry"), true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Geometry/Cube"),
              true);
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Geometry/Sphere"),
              true);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_path_is_valid_prim_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_path_null_params", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Test null prim_path - function should handle gracefully
    // Note: Since this returns bool, it should return false for null path
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, nullptr), false);

    // Test null stage - function should handle gracefully
    // Note: This might crash, but we're testing the boundary condition
    // In production, calling with null stage would be a programming error
    EXPECT_EQ(nusd_stage_path_is_valid_prim(nullptr, "/World"), false);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_set_meters_per_unit) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_set_meters_per_unit", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting meters per unit (default USD units are centimeters = 0.01)
    result = nusd_stage_set_meters_per_unit(stage, 0.01);  // centimeters
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting different unit scales
    result = nusd_stage_set_meters_per_unit(stage, 1.0);   // meters
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_stage_set_meters_per_unit(stage, 0.001); // millimeters
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_stage_set_meters_per_unit(stage, 0.3048); // feet
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_stage_set_meters_per_unit(stage, 0.0254); // inches
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test null stage parameter
    result = nusd_stage_set_meters_per_unit(nullptr, 1.0);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_get_meters_per_unit) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_get_meters_per_unit", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting and getting meters per unit
    double set_value = 0.01;  // centimeters
    result = nusd_stage_set_meters_per_unit(stage, set_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double get_value = 0.0;
    result = nusd_stage_get_meters_per_unit(stage, &get_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(get_value, set_value);

    // Test different values
    set_value = 1.0;  // meters
    result = nusd_stage_set_meters_per_unit(stage, set_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_stage_get_meters_per_unit(stage, &get_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(get_value, set_value);

    // Test engineering units
    set_value = 0.3048;  // feet
    result = nusd_stage_set_meters_per_unit(stage, set_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_stage_get_meters_per_unit(stage, &get_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(get_value, set_value);

    // Test null stage parameter
    result = nusd_stage_get_meters_per_unit(nullptr, &get_value);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    // Test null output parameter
    result = nusd_stage_get_meters_per_unit(stage, nullptr);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_set_up_axis) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_set_up_axis", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting Y-up axis
    result = nusd_stage_set_up_axis(stage, NUSD_UP_AXIS_Y);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting Z-up axis
    result = nusd_stage_set_up_axis(stage, NUSD_UP_AXIS_Z);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test null stage parameter
    result = nusd_stage_set_up_axis(nullptr, NUSD_UP_AXIS_Y);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    // Test invalid up axis value
    result = nusd_stage_set_up_axis(stage, (nusd_up_axis_t)99);
    EXPECT_EQ(result, NUSD_RESULT_INVALID_UP_AXIS);

    nusd_stage_destroy(stage);
}

TEST(nusd, stage_get_up_axis) {
    nusd_stage_t stage;
    nusd_result_t result =
        nusd_stage_create_in_memory("test-stage_get_up_axis", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting and getting Y-up axis
    result = nusd_stage_set_up_axis(stage, NUSD_UP_AXIS_Y);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_up_axis_t up_axis;
    result = nusd_stage_get_up_axis(stage, &up_axis);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(up_axis, NUSD_UP_AXIS_Y);

    // Test setting and getting Z-up axis
    result = nusd_stage_set_up_axis(stage, NUSD_UP_AXIS_Z);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_stage_get_up_axis(stage, &up_axis);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(up_axis, NUSD_UP_AXIS_Z);

    // Test null stage parameter
    result = nusd_stage_get_up_axis(nullptr, &up_axis);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    // Test null output parameter
    result = nusd_stage_get_up_axis(stage, nullptr);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}
