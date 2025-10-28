#ifndef NANOUSD_MATERIALS_H
#define NANOUSD_MATERIALS_H

#include "nanousd-types.h"
#include "nanousd-arrays.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @defgroup MaterialFunctions Material and Shader Functions
/// 
/// @brief Functions related to managing materials and shader graphs
///
/// @{

/// Defines a new USD material prim at the specified path.
/// 
/// @param stage Valid stage handle.
/// @param material_path USD path where the material should be created (e.g., "/World/Materials/MyMaterial").
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage or material_path is null
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the material cannot be defined at the specified path
/// 
/// @note stage must not be null.
/// @note material_path must not be null and should be a valid USD prim path.
/// @note Creates a UsdShadeMaterial prim that can contain shader networks for surface, displacement, and volume.
/// @note Materials define the appearance of geometry through shader networks that compute surface properties.
NANOUSD_API
nusd_result_t nusd_material_define(nusd_stage_t stage, char const* material_path);

/// Defines a new USD shader prim at the specified path with the given shader identifier.
/// 
/// @param stage Valid stage handle.
/// @param shader_path USD path where the shader should be created (e.g., "/World/Materials/MyMaterial/Shader").
/// @param shader_id Shader type identifier (e.g., "UsdPreviewSurface", "UsdUVTexture", "UsdPrimvarReader_float2").
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any parameter is null
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the shader cannot be defined at the specified path
/// 
/// @note stage must not be null.
/// @note shader_path must not be null and should be a valid USD prim path.
/// @note shader_id must not be null and should identify a valid shader type.
/// @note Creates a UsdShadeShader prim and sets its shader identifier for the rendering system.
/// @note Common shader_id values include "UsdPreviewSurface" for materials, "UsdUVTexture" for textures.
NANOUSD_API
nusd_result_t nusd_shader_define(nusd_stage_t stage, char const* shader_path, char const* shader_id);

/// Creates an input parameter on a shader for receiving values or connections from other shaders.
/// 
/// @param stage Valid stage handle.
/// @param shader_path USD path to an existing shader prim.
/// @param input_name Name of the input parameter to create (e.g., "diffuseColor", "roughness", "st").
/// @param input_type USD type for the input parameter (e.g., NUSD_TYPE_COLOR3F, NUSD_TYPE_FLOAT, NUSD_TYPE_FLOAT2).
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any pointer parameter is null
/// @return NUSD_RESULT_WRONG_TYPE if input_type is NUSD_TYPE_RELATIONSHIP (not supported for shader inputs)
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no shader exists at the specified path
/// @return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED if the input cannot be created
/// 
/// @note stage must not be null.
/// @note shader_path must not be null and should point to an existing shader prim.
/// @note input_name must not be null and should follow USD naming conventions.
/// @note input_type must be a valid USD attribute type, not a relationship type.
/// @note The created input will be automatically placed in the "inputs:" namespace (e.g., "inputs:diffuseColor").
/// @note Shader inputs can receive constant values or connections from other shader outputs.
NANOUSD_API
nusd_result_t nusd_shader_create_input(nusd_stage_t stage, char const* shader_path, char const* input_name, nusd_type_t input_type);

/// Creates an output parameter on a shader for providing values to other shaders or materials.
/// 
/// @param stage Valid stage handle.
/// @param shader_path USD path to an existing shader prim.
/// @param output_name Name of the output parameter to create (e.g., "surface", "rgb", "r").
/// @param output_type USD type for the output parameter (e.g., NUSD_TYPE_TOKEN, NUSD_TYPE_COLOR3F, NUSD_TYPE_FLOAT).
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any pointer parameter is null
/// @return NUSD_RESULT_WRONG_TYPE if output_type is NUSD_TYPE_RELATIONSHIP (not supported for shader outputs)
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no shader exists at the specified path
/// @return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED if the output cannot be created
/// 
/// @note stage must not be null.
/// @note shader_path must not be null and should point to an existing shader prim.
/// @note output_name must not be null and should follow USD naming conventions.
/// @note output_type must be a valid USD attribute type, not a relationship type.
/// @note The created output will be automatically placed in the "outputs:" namespace (e.g., "outputs:rgb").
/// @note Shader outputs provide computed values that can be connected to inputs of other shaders.
NANOUSD_API
nusd_result_t nusd_shader_create_output(nusd_stage_t stage, char const* shader_path, char const* output_name, nusd_type_t output_type);

/// Connects a shader output to a shader input, creating a data flow connection in the shader network.
/// 
/// @param stage Valid stage handle.
/// @param source_output_path Full USD path to the source shader output (e.g., "/World/Materials/Mat/Texture.outputs:rgb").
/// @param destination_input_path Full USD path to the destination shader input (e.g., "/World/Materials/Mat/Surface.inputs:diffuseColor").
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any parameter is null
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if either the source output or destination input cannot be found
/// @return NUSD_RESULT_CONNECTION_FAILED if the connection cannot be established
/// 
/// @note stage must not be null.
/// @note source_output_path must not be null and should point to a valid shader output attribute with "outputs:" namespace.
/// @note destination_input_path must not be null and should point to a valid shader input attribute with "inputs:" namespace.
/// @note The connection creates a data flow from the source shader's output to the destination shader's input.
/// @note Connected inputs override any authored constant values on the destination input.
/// @note Both the source and destination must exist before calling this function.
NANOUSD_API
nusd_result_t nusd_shader_connect(nusd_stage_t stage, char const* source_output_path, char const* destination_input_path);




/// @}


#ifdef __cplusplus
}
#endif

#endif
