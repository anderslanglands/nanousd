#include <gtest/gtest.h>
#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>
#include <cmath>


TEST(nusd, material_define) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-material_define", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material at the specified path
    result = nusd_material_define(stage, "/World/Materials/MyMaterial");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify the material was created as a valid prim
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Materials/MyMaterial"), true);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_define) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_define", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a shader with UsdPreviewSurface identifier
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify the shader was created as a valid prim
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Materials/Mat/Surface"), true);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_create_input) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_create_input", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a shader first
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create a diffuseColor input of type COLOR3F
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "diffuseColor", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create a roughness input of type FLOAT
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "roughness", NUSD_TYPE_FLOAT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_create_output) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_create_output", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a shader first
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create a surface output of type TOKEN
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Surface", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a texture shader
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create an rgb output of type COLOR3F
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Texture", "rgb", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material and two shaders
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create inputs and outputs
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "diffuseColor", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Texture", "rgb", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Connect the texture output to the surface input
    result = nusd_shader_connect(stage, 
                                "/World/Materials/Mat/Texture.outputs:rgb", 
                                "/World/Materials/Mat/Surface.inputs:diffuseColor");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect_null_parameters) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect_null", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test null stage
    EXPECT_EQ(nusd_shader_connect(nullptr, 
                                 "/World/Materials/Mat/Texture.outputs:rgb", 
                                 "/World/Materials/Mat/Surface.inputs:diffuseColor"), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null source_output_path
    EXPECT_EQ(nusd_shader_connect(stage, nullptr, 
                                 "/World/Materials/Mat/Surface.inputs:diffuseColor"), 
              NUSD_RESULT_NULL_PARAMETER);

    // Test null destination_input_path
    EXPECT_EQ(nusd_shader_connect(stage, "/World/Materials/Mat/Texture.outputs:rgb", nullptr), 
              NUSD_RESULT_NULL_PARAMETER);

    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect_invalid_attribute_paths) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect_invalid_attrs", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test invalid source attribute path (non-existent prim)
    EXPECT_EQ(nusd_shader_connect(stage, 
                                 "/NonExistent/Shader.outputs:rgb", 
                                 "/World/Materials/Mat/Surface.inputs:diffuseColor"), 
              NUSD_RESULT_INVALID_ATTRIBUTE_PATH);

    // Test invalid destination attribute path (non-existent prim)
    EXPECT_EQ(nusd_shader_connect(stage, 
                                 "/World/Materials/Mat/Texture.outputs:rgb", 
                                 "/NonExistent/Shader.inputs:diffuseColor"), 
              NUSD_RESULT_INVALID_ATTRIBUTE_PATH);

    // Create a valid shader but test invalid attribute names
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Test invalid attribute name on valid prim
    EXPECT_EQ(nusd_shader_connect(stage, 
                                 "/World/Materials/Mat/Texture.outputs:nonexistent", 
                                 "/World/Materials/Mat/Texture.inputs:diffuseColor"), 
              NUSD_RESULT_INVALID_ATTRIBUTE_PATH);

    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect_invalid_shader_output) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect_invalid_output", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Create a material and shader
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Create a regular attribute (not a shader output)
    result = nusd_prim_create_property(stage, "/World/Materials/Mat/Texture", "regularAttr", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Create a valid input
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "diffuseColor", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Try to connect from regular attribute (not a shader output) - should fail
    EXPECT_EQ(nusd_shader_connect(stage, 
                                 "/World/Materials/Mat/Texture.regularAttr", 
                                 "/World/Materials/Mat/Surface.inputs:diffuseColor"), 
              NUSD_RESULT_INVALID_SHADER_OUTPUT);

    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect_invalid_shader_input) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect_invalid_input", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Create a material and shader
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Create two valid shader outputs
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Texture", "rgb", NUSD_TYPE_FLOAT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Surface", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Try to connect shader output to shader output (not a shader input) - should fail
    EXPECT_EQ(nusd_shader_connect(stage, 
                                 "/World/Materials/Mat/Texture.outputs:rgb", 
                                 "/World/Materials/Mat/Surface.outputs:surface"), 
              NUSD_RESULT_INVALID_SHADER_INPUT);

    nusd_stage_destroy(stage);
}

TEST(nusd, material_create_input) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-material_create_input", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create material input
    result = nusd_material_create_input(stage, "/World/Materials/Mat", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, material_create_output) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-material_create_output", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create material output
    result = nusd_material_create_output(stage, "/World/Materials/Mat", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, material_bind_basic) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-material_bind_basic", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material and a geometry prim
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_stage_define_prim(stage, "/World", "Xform");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_stage_define_prim(stage, "/World/Geometry", "Xform");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_stage_define_prim(stage, "/World/Geometry/Mesh", "Mesh");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Bind the material to the mesh
    result = nusd_material_bind(stage, "/World/Geometry/Mesh", "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, material_bind_invalid_paths) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-material_bind_invalid", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material and a geometry prim
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_stage_define_prim(stage, "/World", "Xform");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_stage_define_prim(stage, "/World/Geometry", "Xform");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_stage_define_prim(stage, "/World/Geometry/Mesh", "Mesh");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Test binding to non-existent prim
    result = nusd_material_bind(stage, "/NonExistent/Prim", "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_INVALID_PRIM_PATH);
    
    // Test binding non-existent material
    result = nusd_material_bind(stage, "/World/Geometry/Mesh", "/NonExistent/Material");
    EXPECT_EQ(result, NUSD_RESULT_INVALID_PRIM_PATH);
    
    // Test null parameters
    result = nusd_material_bind(nullptr, "/World/Geometry/Mesh", "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);
    
    result = nusd_material_bind(stage, nullptr, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);
    
    result = nusd_material_bind(stage, "/World/Geometry/Mesh", nullptr);
    EXPECT_EQ(result, NUSD_RESULT_NULL_PARAMETER);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect_outputs) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect_outputs", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material and shader
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create shader output
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Surface", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create material output using the new function
    result = nusd_material_create_output(stage, "/World/Materials/Mat", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Connect the shader output to the material output
    result = nusd_shader_connect_outputs(stage, 
                                        "/World/Materials/Mat/Surface.outputs:surface", 
                                        "/World/Materials/Mat.outputs:surface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}
