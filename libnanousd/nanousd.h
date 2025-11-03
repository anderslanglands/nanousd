#ifndef NANOUSD_H
#define NANOUSD_H

/// @file nanousd.h
///
/// @brief C API for nanousd

#include "nanousd-array.h"
#include "nanousd-iterator.h"
#include "nanousd-mesh.h"
#include "nanousd-prim.h"
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

/// Sets the stage's linear measurement scale by authoring the metersPerUnit metadata.
///
/// @param stage Valid stage handle.
/// @param meters_per_unit The linear unit scale, representing how many meters are 
/// equivalent to one unit in the stage. For example:
///                        - 1.0 = meters (1 stage unit = 1 meter)
///                        - 0.01 = centimeters (1 stage unit = 1 centimeter)  
///                        - 0.001 = millimeters (1 stage unit = 1 millimeter)
///                        - 0.3048 = feet (1 stage unit = 1 foot)
///                        - 0.0254 = inches (1 stage unit = 1 inch)
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage is null
/// @return NUSD_RESULT_SET_METADATA_FAILED if the metadata cannot be set (e.g., 
/// edit target is not root layer or session layer)
///
/// @note stage must not be null.
/// @note The stage's edit target must be either its root layer or session layer 
/// for this operation to succeed.
/// @note This sets stage-wide linear unit metadata that affects all geometry and 
/// measurements on the stage.
/// @note USD defaults to centimeters (0.01) if no metersPerUnit is explicitly set.
/// @note This function uses UsdGeomSetStageMetersPerUnit() internally.
/// @note All existing geometry and measurements on the stage are conceptually 
/// scaled by this value - changing this does not modify existing data but changes 
/// how it is interpreted.
/// @note Common values: 1.0 (meters), 0.01 (centimeters), 0.001 (millimeters), 
/// 0.3048 (feet), 0.0254 (inches).
NANOUSD_API
nusd_result_t nusd_stage_set_meters_per_unit(nusd_stage_t stage, double meters_per_unit);

/// Gets the stage's linear measurement scale from the metersPerUnit metadata.
///
/// @param stage Valid stage handle.
/// @param meters_per_unit Output pointer that will receive the linear unit scale, 
/// representing how many meters are equivalent to one unit in the stage. Common values:
///                        - 1.0 = meters (1 stage unit = 1 meter)
///                        - 0.01 = centimeters (1 stage unit = 1 centimeter)  
///                        - 0.001 = millimeters (1 stage unit = 1 millimeter)
///                        - 0.3048 = feet (1 stage unit = 1 foot)
///                        - 0.0254 = inches (1 stage unit = 1 inch)
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage or meters_per_unit is null
/// @return NUSD_RESULT_GET_METADATA_FAILED if the metadata cannot be retrieved
///
/// @note stage must not be null.
/// @note meters_per_unit must not be null.
/// @note If no metersPerUnit metadata has been explicitly set, USD defaults to 
/// centimeters (0.01).
/// @note This function uses UsdGeomGetStageMetersPerUnit() internally.
/// @note The returned value represents the linear scale factor that converts stage 
/// units to meters - smaller values indicate smaller base units.
/// @note This is the inverse operation of nusd_stage_set_meters_per_unit().
/// @note Common values: 1.0 (meters), 0.01 (centimeters), 0.001 (millimeters), 
/// 0.3048 (feet), 0.0254 (inches).
NANOUSD_API
nusd_result_t nusd_stage_get_meters_per_unit(nusd_stage_t stage, double* meters_per_unit);

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