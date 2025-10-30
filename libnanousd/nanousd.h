#ifndef NANOUSD_H
#define NANOUSD_H

/// @file nanousd.h
///
/// @brief C API for nanousd

#include "nanousd-array.h"
#include "nanousd-iterator.h"
#include "nanousd-mesh.h"
#include "nanousd-property.h"
#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup StageFunctions Stage Functions
///
/// @brief Functions related to stage management
///
/// @{

/// Opens an existing USD stage from a file.
///
/// @param filename Path to the USD file to open. Must be a valid path to an
/// existing file.
/// @param stage Output pointer that will contain the opened stage handle on
/// success.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_OPEN_STAGE_FAILED if the file cannot be opened (file not
/// found, invalid format, permission denied, etc.)
///
/// @note The returned stage handle must be released with nusd_stage_destroy()
/// when no longer needed.
/// @note filename must not be null.
/// @note stage must not be null.
NANOUSD_API
nusd_result_t nusd_stage_open(char const* filename, nusd_stage_t* stage);

/// Creates a new USD stage with a root layer at the specified file path.
///
/// @param identifier File path where the root layer will be created. Any
/// existing file at this path will be destroyed.
/// @param stage Output pointer that will contain the created stage handle on
/// success.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_CREATE_STAGE_FAILED if stage creation fails (invalid
/// path, permission denied, existing open layer with same identifier, out of
/// memory, etc.)
///
/// @note The returned stage handle must be released with nusd_stage_destroy()
/// when no longer needed.
/// @note identifier must not be null and should be a valid file path.
/// @note stage must not be null.
/// @note On failure, stage is set to nullptr.
/// @note This creates actual files on disk, unlike
/// nusd_stage_create_in_memory().
NANOUSD_API
nusd_result_t nusd_stage_create_new(char const* identifier,
                                    nusd_stage_t* stage);

/// Creates a new USD stage entirely in memory without creating any files.
///
/// @param identifier A unique identifier for the stage. Used for internal
/// tracking and debugging.
/// @param stage Output pointer that will contain the created stage handle on
/// success.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_CREATE_STAGE_FAILED if stage creation fails (out of
/// memory, internal USD error, etc.)
///
/// @note The returned stage handle must be released with nusd_stage_destroy()
/// when no longer needed.
/// @note identifier must not be null.
/// @note stage must not be null.
/// @note On failure, stage is set to nullptr.
/// @note This creates no files on disk, unlike nusd_stage_create_new().
NANOUSD_API
nusd_result_t nusd_stage_create_in_memory(char const* identifier,
                                          nusd_stage_t* stage);

/// Saves the stage to its associated file.
///
/// @param stage Valid stage handle created with nusd_stage_open() or
/// nusd_stage_create_new().
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK as the underlying USD
/// Save() method does not report errors.
/// @note For in-memory stages created with nusd_stage_create_in_memory(), this
/// function has no effect but still returns success.
/// @note stage must not be null.
NANOUSD_API
nusd_result_t nusd_stage_save(nusd_stage_t stage);

/// Exports the stage's root layer to the specified filename.
///
/// @param stage Valid stage handle.
/// @param filename Path where the root layer should be exported.
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK as the underlying USD
/// Export() method does not report errors.
/// @note stage must not be null.
/// @note filename must not be null.
NANOUSD_API
nusd_result_t nusd_stage_save_as(nusd_stage_t stage, char const* filename);

/// Destroys a stage handle and releases associated resources.
///
/// @param stage Valid stage handle to destroy. Can be null (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the stage handle becomes invalid and must
/// not be used.
/// @note It is safe to call this function with a null stage handle.
NANOUSD_API
nusd_result_t nusd_stage_destroy(nusd_stage_t stage);

/// Defines a new prim of the specified type at the given path on the stage.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path where the prim should be defined (e.g.,
/// "/World/Geometry").
/// @param prim_type Type token for the prim (e.g., "Xform", "Mesh", "Sphere").
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if prim creation fails (invalid path,
/// invalid type, stage issues, etc.)
///
/// @note stage must not be null.
/// @note prim_path must not be null and should be a valid USD path.
/// @note prim_type must not be null and should be a valid USD prim type token.
/// @note This function uses UsdStage::DefinePrim() internally.
NANOUSD_API
nusd_result_t nusd_stage_define_prim(nusd_stage_t stage,
                                     char const* prim_path,
                                     char const* prim_type);

/// Checks if the specified path refers to a valid prim on the stage.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to check for prim existence.
///
/// @return true if a valid prim exists at the path, false otherwise
///
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note This function uses UsdStage::GetPrimAtPath() internally and checks
/// prim validity.
NANOUSD_API
bool nusd_stage_path_is_valid_prim(nusd_stage_t stage, char const* prim_path);

/// Creates an iterator to traverse all prims in the stage hierarchy.
///
/// @param stage Valid stage handle.
/// @param iterator Output pointer that will contain the prim iterator handle on
/// success.
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK as iterator creation does
/// not fail.
/// @note The returned iterator must be released with
/// nusd_prim_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note iterator must not be null.
/// @note Traversal starts from the stage's pseudo root and includes all
/// descendant prims.
NANOUSD_API
nusd_result_t nusd_stage_traverse(nusd_stage_t stage,
                                  nusd_prim_iterator_t* iterator);

/// @}

/// @defgroup PrimFunctions Prim Functions
///
/// @brief Functions related to managing prims
///
/// @{

/// Creates an iterator for all properties (attributes and relationships) of a
/// prim.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim whose properties to iterate.
/// @param iterator Output pointer that will contain the property iterator
/// handle on success.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified
/// path
///
/// @note The returned iterator must be released with
/// nusd_property_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note iterator must not be null.
NANOUSD_API
nusd_result_t nusd_prim_get_properties(nusd_stage_t stage,
                                       char const* prim_path,
                                       nusd_property_iterator_t* iterator);

/// Creates an iterator for all attributes of a prim.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim whose attributes to iterate.
/// @param iterator Output pointer that will contain the attribute iterator
/// handle on success.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified
/// path
///
/// @note The returned iterator must be released with
/// nusd_attribute_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note iterator must not be null.
NANOUSD_API
nusd_result_t nusd_prim_get_attributes(nusd_stage_t stage,
                                       char const* prim_path,
                                       nusd_attribute_iterator_t* iterator);

/// Creates an iterator for all relationships of a prim.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim whose relationships to iterate.
/// @param iterator Output pointer that will contain the relationship iterator
/// handle on success.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified
/// path
///
/// @note The returned iterator must be released with
/// nusd_relationship_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note iterator must not be null.
NANOUSD_API
nusd_result_t
nusd_prim_get_relationships(nusd_stage_t stage,
                            char const* prim_path,
                            nusd_relationship_iterator_t* iterator);

/// Creates a new property (attribute or relationship) on a prim.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim where the property should be created.
/// @param property_name Name of the property to create.
/// @param property_type Type of the property (use NUSD_TYPE_RELATIONSHIP for
/// relationships, or any attribute type).
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified
/// path
/// @return NUSD_RESULT_INVALID_PROPERTY_TYPE if the property type is not
/// recognized
/// @return NUSD_RESULT_CREATE_RELATIONSHIP_FAILED if relationship creation
/// fails
/// @return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED if attribute creation fails
///
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note property_name must not be null.
/// @note property_type must not be null and should be a valid USD type token.
NANOUSD_API
nusd_result_t nusd_prim_create_property(nusd_stage_t stage,
                                        char const* prim_path,
                                        char const* property_name,
                                        nusd_type_t property_type);

/// Sets the transform matrix for a prim, positioning it relative to its parent.
///
/// @param stage Valid stage handle.
/// @param xformable_path USD path to an existing Xformable prim.
/// @param camera_to_parent_matrix Pointer to 16 double values representing a
/// 4x4 transformation matrix
///                                in row-major order that transforms from local
///                                space to its parent space.
/// @param time_code The time at which to set the transform. Use
/// NUSD_TIMECODE_DEFAULT
///                  for the default time. Time samples can be set for
///                  animation.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified
/// path
/// @return NUSD_RESULT_NULL_PARAMETER if local_to_parent is null
///
/// @note stage must not be null.
/// @note xformable_path must not be null and should point to an existing
/// Xformable prim.
/// @note local_to_parent must not be null and should contain 16 valid double
/// values.
/// @note The matrix should represent the transformation from prim space to its
/// parent's coordinate space.
/// @note USD cameras use a "Y up" coordinate system regardless of stage
/// orientation.
NANOUSD_API
nusd_result_t nusd_prim_set_transform(nusd_stage_t stage,
                                      char const* xformable_path,
                                      double* local_to_parent,
                                      double time_code);

/// Computes the complete transformation matrix from a prim's local space to
/// world space.
///
/// @param stage Valid stage handle.
/// @param xformable_path USD path to a transformable prim (must inherit from
/// UsdGeomXformable).
/// @param time_code The time at which to evaluate the transformation. Use
/// NUSD_TIMECODE_DEFAULT
///                  for the default time. Different times may yield different
///                  transforms for animated objects.
/// @param transform Output pointer to a 16-element double array that will
/// receive the 4x4 transformation matrix
///                  in row-major order. The matrix transforms points from the
///                  prim's local coordinate space to world space.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any parameter is null
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no transformable prim exists at the
/// specified path
///
/// @note stage must not be null.
/// @note xformable_path must not be null and should point to a prim that
/// inherits from UsdGeomXformable.
/// @note transform must not be null and should point to a buffer capable of
/// holding 16 double values.
/// @note The computed matrix includes all transformations from the prim up to
/// the root of the scene.
/// @note This includes the prim's own local transforms as well as all inherited
/// parent transforms.
/// @note The resulting matrix can be used to position geometry or cameras in
/// world space.
/// @note For animated prims, the transformation may vary over time based on the
/// time_code parameter.
NANOUSD_API
nusd_result_t
nusd_prim_compute_local_to_world_transform(nusd_stage_t stage,
                                           char const* xformable_path,
                                           double time_code,
                                           double* transform);

/// Creates a new primvar (primitive variable) on a prim for geometry attribute
/// data.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to an existing prim (e.g., "/World/Mesh").
/// @param primvar_name Name of the primvar to create (e.g., "displayColor",
/// "st", "normals").
/// @param primvar_type USD type for the primvar data (e.g., NUSD_TYPE_COLOR3F,
/// NUSD_TYPE_FLOAT2, NUSD_TYPE_VECTOR3F).
/// @param primvar_interpolation Interpolation mode for the primvar (use
/// NUSD_INTERPOLATION_* constants).
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any parameter is null
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified
/// path
/// @return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED if the primvar cannot be created
///
/// @note stage must not be null.
/// @note prim_path must not be null and should point to an existing prim.
/// @note primvar_name must not be null and should follow USD primvar naming
/// conventions.
/// @note primvar_type must be a valid USD attribute type compatible with the
/// intended data.
/// @note primvar_interpolation must not be null and should be one of the
/// predefined constants.
/// @note Primvars store per-vertex, per-face, or per-primitive data such as
/// colors, texture coordinates, and normals.
/// @note The interpolation mode determines how the data is distributed across
/// the geometry:
///       - NUSD_INTERPOLATION_CONSTANT: One value for the entire primitive
///       - NUSD_INTERPOLATION_UNIFORM: One value per face/primitive
///       - NUSD_INTERPOLATION_VARYING: One value per vertex (same as vertex for
///       most cases)
///       - NUSD_INTERPOLATION_VERTEX: One value per vertex
///       - NUSD_INTERPOLATION_FACEVARYING: One value per face-vertex (allows
///       discontinuities)
/// @note Common primvar types include NUSD_TYPE_COLOR3F for colors,
/// NUSD_TYPE_FLOAT2 for UV coordinates, and NUSD_TYPE_VECTOR3F for normals.
/// @note The created primvar can be populated with data using standard
/// attribute setting functions.
NANOUSD_API
nusd_result_t nusd_prim_create_primvar(nusd_stage_t stage,
                                       char const* prim_path,
                                       char const* primvar_name,
                                       nusd_type_t primvar_type,
                                       char const* primvar_interpolation);

NANOUSD_API
nusd_result_t nusd_prim_set_extent(nusd_stage_t stage, char const* prim_path, float* extent);

/// @}

/// Extracts the name from a USD path.
///
/// @param path USD path (prim, property, or relationship path).
///
/// @return Pointer to the name portion of the path, or null if no delimiter
/// found
///
/// @note path must not be null.
/// @note Returns the name of the prim, property, or relational attribute
/// identified by the path.
/// @note For property paths like "/World/Mesh.points", returns "points".
/// @note For prim paths, this function's behavior depends on the presence of a
/// '.' delimiter.
NANOUSD_API
char const* nusd_path_get_name(char const* path);

/// Gets the asset path string from an asset path handle.
///
/// @param asset_path Valid asset path handle.
///
/// @return The asset path string, or null if asset_path is null.
///
/// @note asset_path must not be null for valid results.
/// @note The returned string is valid as long as the asset_path handle remains
/// valid.
/// @note Asset paths represent file system paths or URIs to external assets
/// like textures, geometry files, etc.
NANOUSD_API
char const* nusd_asset_path_get_asset_path(nusd_asset_path_t asset_path);

/// Destroys an asset path handle and releases associated resources.
///
/// @param asset_path Valid asset path handle to destroy. Can be null (no-op).
///
/// @note After calling this function, the asset_path handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null asset_path handle.
NANOUSD_API
void nusd_asset_path_destroy(nusd_asset_path_t asset_path);

#ifdef __cplusplus
}
#endif

#endif