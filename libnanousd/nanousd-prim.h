#ifndef NANOUSD_PRIM_H
#define NANOUSD_PRIM_H

#include "nanousd-array.h"
#include "nanousd-iterator.h"
#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum nusd_interpolation_e {
    NUSD_INTERPOLATION_CONSTANT = 0,
    NUSD_INTERPOLATION_UNIFORM = 1,
    NUSD_INTERPOLATION_VERTEX = 2,
    NUSD_INTERPOLATION_VARYING = 3,
    NUSD_INTERPOLATION_FACEVARYING = 4,
};
typedef int nusd_interpolation_t;

/// @defgroup PrimFunctions Prims Functions
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
                                      double const* local_to_parent,
                                      double time_code);


/// Adds a translate transform operation to a UsdGeomXformable prim.
///
/// @param stage Valid stage handle.
/// @param xformable_path USD path to an existing xformable prim (e.g., "/World/Camera", "/World/Mesh").
/// @param op_suffix Optional suffix for the operation name. If null, USD will generate a default name.
///                  If provided, the operation will be named "xformOp:translate:{op_suffix}".
/// @param translation Optional array of 3 double values representing the translation as [x, y, z].
///                   If null, the operation is created but no initial value is set.
/// @param time_code The time at which to set the translation value. Use NUSD_TIMECODE_DEFAULT for default time.
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage or xformable_path is null
/// @return NUSD_RESULT_INVALID_PRIM_PATH if the prim doesn't exist or is not xformable
///
/// @note stage must not be null.
/// @note xformable_path must not be null and should point to an existing UsdGeomXformable prim.
/// @note op_suffix is optional and can be null for auto-generated operation names.
/// @note translation is optional and can be null to create the operation without setting an initial value.
/// @note If translation is provided, it must contain exactly 3 double values for [x, y, z] coordinates.
/// @note The translate operation uses double precision for maximum accuracy.
/// @note Multiple translate operations can be added to the same prim with different suffixes.
/// @note Transform operations are evaluated in the order they appear in the xformOpOrder attribute.
/// @note The resulting transform operation will be named "xformOp:translate" or "xformOp:translate:{op_suffix}".
/// @note Translation values are in the prim's local coordinate space.
NANOUSD_API
nusd_result_t nusd_prim_add_translate_op(nusd_stage_t stage,
                                      char const* xformable_path,
                                      char const* op_suffix,
                                      double const* translation,
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
/// @return NUSD_RESULT_INVALID_INTERPOLATION if the interpolation is not a
/// member of the nusd_interpolation_e enum
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
                                       nusd_interpolation_t primvar_interpolation);

/// Sets the extent (bounding box) attribute on a UsdGeomBoundable prim.
///
/// @param stage Valid stage handle.
/// @param prim_path USD path to an existing boundable prim (e.g., "/World/Mesh", "/World/Cube").
/// @param extent Array of 6 float values representing the bounding box as [min_x, min_y, min_z, max_x, max_y, max_z].
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage, prim_path, or extent is null
/// @return NUSD_RESULT_INVALID_PRIM_PATH if the prim doesn't exist or is not a boundable prim
///
/// @note stage must not be null.
/// @note prim_path must not be null and should point to an existing UsdGeomBoundable prim.
/// @note extent must not be null and should contain exactly 6 float values.
/// @note The extent represents the axis-aligned bounding box of the prim in local coordinates.
/// @note Only prims derived from UsdGeomBoundable (like Mesh, Cube, Sphere, etc.) support extent.
/// @note The extent format is [min_x, min_y, min_z, max_x, max_y, max_z] where:
///       - (min_x, min_y, min_z) is the minimum corner of the bounding box
///       - (max_x, max_y, max_z) is the maximum corner of the bounding box
/// @note Extent is used by USD for culling and optimization during rendering and traversal.
/// @note For meshes, the extent should encompass all vertex positions.
/// @note For primitives like cubes and spheres, the extent should match their geometric bounds.
NANOUSD_API
nusd_result_t nusd_prim_set_extent(nusd_stage_t stage, char const* prim_path, float const* extent);


/// @}

#ifdef __cplusplus
}
#endif

#endif
