#include <gtest/gtest.h>

#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>

#include <cmath>

TEST(nusd, create_stage) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_stage", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
}

TEST(nusd, mesh_set_subdivision_scheme) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh_set_subdivision_scheme", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Create a simple triangle mesh
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};
    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f};
    result = nusd_mesh_define(stage, "/World/Mesh", face_vertex_counts, 1, face_vertex_indices, 3, vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting subdivision scheme to Catmull-Clark
    result = nusd_mesh_set_subdivision_scheme(stage, "/World/Mesh", 
        NUSD_SUBDIVISION_SCHEME_CATMULL_CLARK, 
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting subdivision scheme to None (polygonal mesh)
    result = nusd_mesh_set_subdivision_scheme(stage, "/World/Mesh",
        NUSD_SUBDIVISION_SCHEME_NONE,
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting subdivision scheme to Loop
    result = nusd_mesh_set_subdivision_scheme(stage, "/World/Mesh",
        NUSD_SUBDIVISION_SCHEME_LOOP,
        NUSD_TRIANGLE_SUBDIVISION_RULE_SMOOTH);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test setting subdivision scheme to Bilinear
    result = nusd_mesh_set_subdivision_scheme(stage, "/World/Mesh",
        NUSD_SUBDIVISION_SCHEME_BILINEAR,
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test invalid mesh path
    result = nusd_mesh_set_subdivision_scheme(stage, "/NonExistent/Mesh",
        NUSD_SUBDIVISION_SCHEME_NONE,
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_INVALID_PRIM_PATH);

    // Test invalid subdivision scheme
    result = nusd_mesh_set_subdivision_scheme(stage, "/World/Mesh",
        (nusd_subdivision_scheme_e)99,
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_INVALID_SUBDIVISION_SCHEME);

    // Test invalid triangle subdivision rule
    result = nusd_mesh_set_subdivision_scheme(stage, "/World/Mesh",
        NUSD_SUBDIVISION_SCHEME_CATMULL_CLARK,
        (nusd_triangle_subdivision_rule_e)99);
    EXPECT_EQ(result, NUSD_RESULT_INVALID_TRIANGLE_SUBDIVISION_RULE);

    // Test null stage
    result = nusd_mesh_set_subdivision_scheme(nullptr, "/World/Mesh",
        NUSD_SUBDIVISION_SCHEME_NONE,
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);

    // Test null mesh path
    result = nusd_mesh_set_subdivision_scheme(stage, nullptr,
        NUSD_SUBDIVISION_SCHEME_NONE,
        NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);
}
