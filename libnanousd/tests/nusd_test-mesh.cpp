#include <gtest/gtest.h>
#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>

#include <cmath>


TEST(nusd, mesh_define_simple_triangle) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-triangle", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a simple triangle mesh
    // 3 vertices forming a triangle
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  // vertex 0
        1.0f, 0.0f, 0.0f,  // vertex 1
        0.5f, 1.0f, 0.0f   // vertex 2
    };
    
    // One triangle face with 3 vertices
    int face_vertex_counts[] = {3};
    
    // Indices for the triangle
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Triangle", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 3,
                             vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the mesh prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Triangle"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_define_quad) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-quad", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a quad mesh (4 vertices, 1 quad face)
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,  // vertex 0
         1.0f, -1.0f, 0.0f,  // vertex 1
         1.0f,  1.0f, 0.0f,  // vertex 2
        -1.0f,  1.0f, 0.0f   // vertex 3
    };
    
    // One quad face with 4 vertices
    int face_vertex_counts[] = {4};
    
    // Indices for the quad
    int face_vertex_indices[] = {0, 1, 2, 3};

    result = nusd_mesh_define(stage, "/World/Quad", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 4,
                             vertices, 4);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the mesh prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Quad"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_define_complex_mesh) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-complex", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Define a mesh with multiple faces (2 triangles forming a quad)
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,  // vertex 0
         1.0f, -1.0f, 0.0f,  // vertex 1
         1.0f,  1.0f, 0.0f,  // vertex 2
        -1.0f,  1.0f, 0.0f   // vertex 3
    };
    
    // Two triangle faces, each with 3 vertices
    int face_vertex_counts[] = {3, 3};
    
    // Indices for two triangles
    int face_vertex_indices[] = {0, 1, 2, 0, 2, 3};

    result = nusd_mesh_define(stage, "/World/TwoTriangles", 
                             face_vertex_counts, 2,
                             face_vertex_indices, 6,
                             vertices, 4);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the mesh prim was created
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/TwoTriangles"), true);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_define_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f};
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    // Test null stage
    EXPECT_EQ(nusd_mesh_define(nullptr, "/World/Mesh",
                              face_vertex_counts, 1,
                              face_vertex_indices, 3,
                              vertices, 3), NUSD_RESULT_NULL_PARAMETER);

    // Test null mesh_path
    EXPECT_EQ(nusd_mesh_define(stage, nullptr,
                              face_vertex_counts, 1,
                              face_vertex_indices, 3,
                              vertices, 3), NUSD_RESULT_NULL_PARAMETER);

    // Test null face_vertex_counts
    EXPECT_EQ(nusd_mesh_define(stage, "/World/Mesh",
                              nullptr, 1,
                              face_vertex_indices, 3,
                              vertices, 3), NUSD_RESULT_NULL_PARAMETER);

    // Test null face_vertex_indices
    EXPECT_EQ(nusd_mesh_define(stage, "/World/Mesh",
                              face_vertex_counts, 1,
                              nullptr, 3,
                              vertices, 3), NUSD_RESULT_NULL_PARAMETER);

    // Test null vertices
    EXPECT_EQ(nusd_mesh_define(stage, "/World/Mesh",
                              face_vertex_counts, 1,
                              face_vertex_indices, 3,
                              nullptr, 3), NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_set_normals_vertex_interpolation) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-normals-vertex", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // First create a triangle mesh
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  // vertex 0
        1.0f, 0.0f, 0.0f,  // vertex 1
        0.5f, 1.0f, 0.0f   // vertex 2
    };
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Triangle", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 3,
                             vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Now set vertex normals (one per vertex)
    float normals[] = {
        0.0f, 0.0f, 1.0f,  // normal for vertex 0
        0.0f, 0.0f, 1.0f,  // normal for vertex 1
        0.0f, 0.0f, 1.0f   // normal for vertex 2
    };

    result = nusd_mesh_set_normals(stage, "/World/Triangle",
                                  normals, 3,
                                  NUSD_INTERPOLATION_VERTEX);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_set_normals_facevarying_interpolation) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-normals-facevarying", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a triangle mesh
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  // vertex 0
        1.0f, 0.0f, 0.0f,  // vertex 1
        0.5f, 1.0f, 0.0f   // vertex 2
    };
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Triangle", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 3,
                             vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set face-varying normals (one per face-vertex, so 3 for triangle)
    float normals[] = {
        0.0f, 0.0f, 1.0f,  // normal for face-vertex 0
        0.0f, 0.0f, 1.0f,  // normal for face-vertex 1
        0.0f, 0.0f, 1.0f   // normal for face-vertex 2
    };

    result = nusd_mesh_set_normals(stage, "/World/Triangle",
                                  normals, 3,
                                  NUSD_INTERPOLATION_FACEVARYING);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_set_normals_uniform_interpolation) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-normals-uniform", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a triangle mesh
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  // vertex 0
        1.0f, 0.0f, 0.0f,  // vertex 1
        0.5f, 1.0f, 0.0f   // vertex 2
    };
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Triangle", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 3,
                             vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set uniform normals (one per face, so 1 for single triangle)
    float normals[] = {
        0.0f, 0.0f, 1.0f   // normal for the face
    };

    result = nusd_mesh_set_normals(stage, "/World/Triangle",
                                  normals, 1,
                                  NUSD_INTERPOLATION_UNIFORM);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_set_normals_constant_interpolation) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-normals-constant", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a triangle mesh
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  // vertex 0
        1.0f, 0.0f, 0.0f,  // vertex 1
        0.5f, 1.0f, 0.0f   // vertex 2
    };
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Triangle", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 3,
                             vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set constant normals (one for entire mesh)
    float normals[] = {
        0.0f, 0.0f, 1.0f   // normal for entire mesh
    };

    result = nusd_mesh_set_normals(stage, "/World/Triangle",
                                  normals, 1,
                                  NUSD_INTERPOLATION_CONSTANT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_set_normals_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-normals-null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a mesh first
    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f};
    int face_vertex_counts[] = {3};
    int face_vertex_indices[] = {0, 1, 2};

    result = nusd_mesh_define(stage, "/World/Triangle", 
                             face_vertex_counts, 1,
                             face_vertex_indices, 3,
                             vertices, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    float normals[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    // Test null stage
    EXPECT_EQ(nusd_mesh_set_normals(nullptr, "/World/Triangle",
                                   normals, 3, NUSD_INTERPOLATION_VERTEX), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null mesh_path
    EXPECT_EQ(nusd_mesh_set_normals(stage, nullptr,
                                   normals, 3, NUSD_INTERPOLATION_VERTEX), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null normals
    EXPECT_EQ(nusd_mesh_set_normals(stage, "/World/Triangle",
                                   nullptr, 3, NUSD_INTERPOLATION_VERTEX), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test invalid interpolation
    EXPECT_EQ(nusd_mesh_set_normals(stage, "/World/Triangle",
                                   normals, 3, (nusd_interpolation_t)99), 
              NUSD_RESULT_INVALID_INTERPOLATION);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_set_normals_invalid_mesh_path) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-normals-invalid", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    float normals[] = {0.0f, 0.0f, 1.0f};

    // Try to set normals on non-existent mesh
    EXPECT_EQ(nusd_mesh_set_normals(stage, "/World/NonExistentMesh",
                                   normals, 1, NUSD_INTERPOLATION_CONSTANT), 
              NUSD_RESULT_INVALID_PRIM_PATH);

    // Try with completely invalid path
    EXPECT_EQ(nusd_mesh_set_normals(stage, "/InvalidPath",
                                   normals, 1, NUSD_INTERPOLATION_CONSTANT), 
              NUSD_RESULT_INVALID_PRIM_PATH);

    nusd_stage_destroy(stage);
}

TEST(nusd, mesh_complex_workflow) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-mesh-workflow", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    // Create a more complex mesh: a pyramid (4 triangular faces)
    float vertices[] = {
        // Base vertices
        -1.0f, 0.0f, -1.0f,  // vertex 0
         1.0f, 0.0f, -1.0f,  // vertex 1
         1.0f, 0.0f,  1.0f,  // vertex 2
        -1.0f, 0.0f,  1.0f,  // vertex 3
        // Apex
         0.0f, 2.0f,  0.0f   // vertex 4
    };
    
    // 4 triangular faces (no base)
    int face_vertex_counts[] = {3, 3, 3, 3};
    
    // Face indices for the 4 triangular faces
    int face_vertex_indices[] = {
        0, 1, 4,  // front face
        1, 2, 4,  // right face
        2, 3, 4,  // back face
        3, 0, 4   // left face
    };

    result = nusd_mesh_define(stage, "/World/Pyramid", 
                             face_vertex_counts, 4,
                             face_vertex_indices, 12,
                             vertices, 5);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set face-varying normals (3 normals per face, 4 faces = 12 normals)
    float normals[] = {
        // Front face normals (pointing outward)
        0.0f, 0.4472f, 0.8944f,
        0.0f, 0.4472f, 0.8944f,
        0.0f, 0.4472f, 0.8944f,
        
        // Right face normals
        0.8944f, 0.4472f, 0.0f,
        0.8944f, 0.4472f, 0.0f,
        0.8944f, 0.4472f, 0.0f,
        
        // Back face normals
        0.0f, 0.4472f, -0.8944f,
        0.0f, 0.4472f, -0.8944f,
        0.0f, 0.4472f, -0.8944f,
        
        // Left face normals
        -0.8944f, 0.4472f, 0.0f,
        -0.8944f, 0.4472f, 0.0f,
        -0.8944f, 0.4472f, 0.0f
    };

    result = nusd_mesh_set_normals(stage, "/World/Pyramid",
                                  normals, 12,
                                  NUSD_INTERPOLATION_FACEVARYING);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Verify the mesh exists
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Pyramid"), true);

    nusd_stage_destroy(stage);
}
