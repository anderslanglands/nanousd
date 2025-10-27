#ifndef NANOUSD_H
#define NANOUSD_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define NANOUSD_API

#ifdef __cplusplus
extern "C" {
#endif

enum nusd_result_e {
    NUSD_RESULT_OK = 0,
    NUSD_RESULT_INVALID_ATTRIBUTE_PATH,
    NUSD_RESULT_INVALID_RELATIONSHIP_PATH,
    NUSD_RESULT_INVALID_PRIM_PATH,
    NUSD_RESULT_WRONG_TYPE,
    NUSD_RESULT_CREATE_STAGE_FAILED,
    NUSD_RESULT_OPEN_STAGE_FAILED,
    NUSD_RESULT_DEFINE_PRIM_FAILED,
    NUSD_RESULT_INVALID_PROPERTY_PATH,
    NUSD_RESULT_INVALID_PROPERTY_TYPE,
    NUSD_RESULT_CREATE_RELATIONSHIP_FAILED,
    NUSD_RESULT_CREATE_ATTRIBUTE_FAILED,
};

typedef int nusd_result_t;

typedef void* nusd_stage_t;

typedef struct nusd_prim_iterator_s* nusd_prim_iterator_t;
typedef struct nusd_property_iterator_s* nusd_property_iterator_t;
typedef struct nusd_attribute_iterator_s* nusd_attribute_iterator_t;
typedef struct nusd_relationship_iterator_s* nusd_relationship_iterator_t;
typedef struct nusd_relationship_targets_iterator_s* nusd_relationship_targets_iterator_t;
typedef struct nusd_token_array_s* nusd_token_array_t;
typedef struct nusd_float_array_s* nusd_float_array_t;
typedef struct nusd_float2_array_s* nusd_float2_array_t;
typedef struct nusd_float3_array_s* nusd_float3_array_t;
typedef struct nusd_float4_array_s* nusd_float4_array_t;
typedef struct nusd_double_array_s* nusd_double_array_t;
typedef struct nusd_double2_array_s* nusd_double2_array_t;
typedef struct nusd_double3_array_s* nusd_double3_array_t;
typedef struct nusd_double4_array_s* nusd_double4_array_t;
typedef struct nusd_int_array_s* nusd_int_array_t;
typedef struct nusd_int2_array_s* nusd_int2_array_t;
typedef struct nusd_int3_array_s* nusd_int3_array_t;
typedef struct nusd_int4_array_s* nusd_int4_array_t;
typedef struct nusd_int64_array_s* nusd_int64_array_t;

typedef struct nusd_bool_array_s* nusd_bool_array_t;

typedef char const* nusd_type_t;

extern nusd_type_t NUSD_TYPE_ASSET;
extern nusd_type_t NUSD_TYPE_ASSETARRAY;
extern nusd_type_t NUSD_TYPE_BOOL;
extern nusd_type_t NUSD_TYPE_BOOLARRAY;
extern nusd_type_t NUSD_TYPE_COLOR3D;
extern nusd_type_t NUSD_TYPE_COLOR3DARRAY;
extern nusd_type_t NUSD_TYPE_COLOR3F;
extern nusd_type_t NUSD_TYPE_COLOR3FARRAY;
extern nusd_type_t NUSD_TYPE_COLOR3H;
extern nusd_type_t NUSD_TYPE_COLOR3HARRAY;
extern nusd_type_t NUSD_TYPE_COLOR4D;
extern nusd_type_t NUSD_TYPE_COLOR4DARRAY;
extern nusd_type_t NUSD_TYPE_COLOR4F;
extern nusd_type_t NUSD_TYPE_COLOR4FARRAY;
extern nusd_type_t NUSD_TYPE_COLOR4H;
extern nusd_type_t NUSD_TYPE_COLOR4HARRAY;
extern nusd_type_t NUSD_TYPE_DOUBLE;
extern nusd_type_t NUSD_TYPE_DOUBLE2;
extern nusd_type_t NUSD_TYPE_DOUBLE2ARRAY;
extern nusd_type_t NUSD_TYPE_DOUBLE3;
extern nusd_type_t NUSD_TYPE_DOUBLE3ARRAY;
extern nusd_type_t NUSD_TYPE_DOUBLE4;
extern nusd_type_t NUSD_TYPE_DOUBLE4ARRAY;
extern nusd_type_t NUSD_TYPE_DOUBLEARRAY;
extern nusd_type_t NUSD_TYPE_FIND;
extern nusd_type_t NUSD_TYPE_FLOAT;
extern nusd_type_t NUSD_TYPE_FLOAT2;
extern nusd_type_t NUSD_TYPE_FLOAT2ARRAY;
extern nusd_type_t NUSD_TYPE_FLOAT3;
extern nusd_type_t NUSD_TYPE_FLOAT3ARRAY;
extern nusd_type_t NUSD_TYPE_FLOAT4;
extern nusd_type_t NUSD_TYPE_FLOAT4ARRAY;
extern nusd_type_t NUSD_TYPE_FLOATARRAY;
extern nusd_type_t NUSD_TYPE_FRAME4D;
extern nusd_type_t NUSD_TYPE_FRAME4DARRAY;
extern nusd_type_t NUSD_TYPE_GROUP;
extern nusd_type_t NUSD_TYPE_HALF;
extern nusd_type_t NUSD_TYPE_HALF2;
extern nusd_type_t NUSD_TYPE_HALF2ARRAY;
extern nusd_type_t NUSD_TYPE_HALF3;
extern nusd_type_t NUSD_TYPE_HALF3ARRAY;
extern nusd_type_t NUSD_TYPE_HALF4;
extern nusd_type_t NUSD_TYPE_HALF4ARRAY;
extern nusd_type_t NUSD_TYPE_HALFARRAY;
extern nusd_type_t NUSD_TYPE_INT;
extern nusd_type_t NUSD_TYPE_INT2;
extern nusd_type_t NUSD_TYPE_INT2ARRAY;
extern nusd_type_t NUSD_TYPE_INT3;
extern nusd_type_t NUSD_TYPE_INT3ARRAY;
extern nusd_type_t NUSD_TYPE_INT4;
extern nusd_type_t NUSD_TYPE_INT4ARRAY;
extern nusd_type_t NUSD_TYPE_INT64;
extern nusd_type_t NUSD_TYPE_INT64ARRAY;
extern nusd_type_t NUSD_TYPE_INTARRAY;
extern nusd_type_t NUSD_TYPE_MATRIX2D;
extern nusd_type_t NUSD_TYPE_MATRIX2DARRAY;
extern nusd_type_t NUSD_TYPE_MATRIX3D;
extern nusd_type_t NUSD_TYPE_MATRIX3DARRAY;
extern nusd_type_t NUSD_TYPE_MATRIX4D;
extern nusd_type_t NUSD_TYPE_MATRIX4DARRAY;
extern nusd_type_t NUSD_TYPE_NORMAL3D;
extern nusd_type_t NUSD_TYPE_NORMAL3DARRAY;
extern nusd_type_t NUSD_TYPE_NORMAL3F;
extern nusd_type_t NUSD_TYPE_NORMAL3FARRAY;
extern nusd_type_t NUSD_TYPE_NORMAL3H;
extern nusd_type_t NUSD_TYPE_NORMAL3HARRAY;
extern nusd_type_t NUSD_TYPE_OPAQUE;
extern nusd_type_t NUSD_TYPE_PATHEXPRESSION;
extern nusd_type_t NUSD_TYPE_PATHEXPRESSIONARRAY;
extern nusd_type_t NUSD_TYPE_POINT3D;
extern nusd_type_t NUSD_TYPE_POINT3DARRAY;
extern nusd_type_t NUSD_TYPE_POINT3F;
extern nusd_type_t NUSD_TYPE_POINT3FARRAY;
extern nusd_type_t NUSD_TYPE_POINT3H;
extern nusd_type_t NUSD_TYPE_POINT3HARRAY;
extern nusd_type_t NUSD_TYPE_QUATD;
extern nusd_type_t NUSD_TYPE_QUATDARRAY;
extern nusd_type_t NUSD_TYPE_QUATF;
extern nusd_type_t NUSD_TYPE_QUATFARRAY;
extern nusd_type_t NUSD_TYPE_QUATH;
extern nusd_type_t NUSD_TYPE_QUATHARRAY;
extern nusd_type_t NUSD_TYPE_STRING;
extern nusd_type_t NUSD_TYPE_STRINGARRAY;
extern nusd_type_t NUSD_TYPE_TEXCOORD2D;
extern nusd_type_t NUSD_TYPE_TEXCOORD2DARRAY;
extern nusd_type_t NUSD_TYPE_TEXCOORD2F;
extern nusd_type_t NUSD_TYPE_TEXCOORD2FARRAY;
extern nusd_type_t NUSD_TYPE_TEXCOORD2H;
extern nusd_type_t NUSD_TYPE_TEXCOORD2HARRAY;
extern nusd_type_t NUSD_TYPE_TEXCOORD3D;
extern nusd_type_t NUSD_TYPE_TEXCOORD3DARRAY;
extern nusd_type_t NUSD_TYPE_TEXCOORD3F;
extern nusd_type_t NUSD_TYPE_TEXCOORD3FARRAY;
extern nusd_type_t NUSD_TYPE_TEXCOORD3H;
extern nusd_type_t NUSD_TYPE_TEXCOORD3HARRAY;
extern nusd_type_t NUSD_TYPE_TIMECODE;
extern nusd_type_t NUSD_TYPE_TIMECODEARRAY;
extern nusd_type_t NUSD_TYPE_TOKEN;
extern nusd_type_t NUSD_TYPE_TOKENARRAY;
extern nusd_type_t NUSD_TYPE_UCHAR;
extern nusd_type_t NUSD_TYPE_UCHARARRAY;
extern nusd_type_t NUSD_TYPE_UINT;
extern nusd_type_t NUSD_TYPE_UINT64;
extern nusd_type_t NUSD_TYPE_UINT64ARRAY;
extern nusd_type_t NUSD_TYPE_UINTARRAY;
extern nusd_type_t NUSD_TYPE_VECTOR3D;
extern nusd_type_t NUSD_TYPE_VECTOR3DARRAY;
extern nusd_type_t NUSD_TYPE_VECTOR3F;
extern nusd_type_t NUSD_TYPE_VECTOR3FARRAY;
extern nusd_type_t NUSD_TYPE_VECTOR3H;
extern nusd_type_t NUSD_TYPE_VECTOR3HARRAY;

extern nusd_type_t NUSD_TYPE_RELATIONSHIP;


enum nusd_property_type_e {
    NUSD_PROPERTY_TYPE_ATTRIBUTE,
    NUSD_PROPERTY_TYPE_RELATIONSHIP,
};
typedef int nusd_property_type_t;

/// Opens an existing USD stage from a file.
/// 
/// @param filename Path to the USD file to open. Must be a valid path to an existing file.
/// @param stage Output pointer that will contain the opened stage handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_OPEN_STAGE_FAILED if the file cannot be opened (file not found, invalid format, permission denied, etc.)
/// 
/// @note The returned stage handle must be released with nusd_stage_destroy() when no longer needed.
/// @note filename must not be null.
/// @note stage must not be null.
NANOUSD_API
nusd_result_t nusd_stage_open(char const* filename, nusd_stage_t* stage);

/// Creates a new USD stage with a root layer at the specified file path.
/// 
/// @param identifier File path where the root layer will be created. Any existing file at this path will be destroyed.
/// @param stage Output pointer that will contain the created stage handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_CREATE_STAGE_FAILED if stage creation fails (invalid path, permission denied, existing open layer with same identifier, out of memory, etc.)
/// 
/// @note The returned stage handle must be released with nusd_stage_destroy() when no longer needed.
/// @note identifier must not be null and should be a valid file path.
/// @note stage must not be null.
/// @note On failure, stage is set to nullptr.
/// @note This creates actual files on disk, unlike nusd_stage_create_in_memory().
NANOUSD_API
nusd_result_t nusd_stage_create_new(char const* identifier, nusd_stage_t* stage);

/// Creates a new USD stage entirely in memory without creating any files.
/// 
/// @param identifier A unique identifier for the stage. Used for internal tracking and debugging.
/// @param stage Output pointer that will contain the created stage handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_CREATE_STAGE_FAILED if stage creation fails (out of memory, internal USD error, etc.)
/// 
/// @note The returned stage handle must be released with nusd_stage_destroy() when no longer needed.
/// @note identifier must not be null.
/// @note stage must not be null.
/// @note On failure, stage is set to nullptr.
/// @note This creates no files on disk, unlike nusd_stage_create_new().
NANOUSD_API
nusd_result_t nusd_stage_create_in_memory(char const* identifier, nusd_stage_t* stage);

/// Saves the stage to its associated file.
/// 
/// @param stage Valid stage handle created with nusd_stage_open() or nusd_stage_create_new().
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK as the underlying USD Save() method does not report errors.
/// @note For in-memory stages created with nusd_stage_create_in_memory(), this function has no effect but still returns success.
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
/// @note This function always returns NUSD_RESULT_OK as the underlying USD Export() method does not report errors.
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
/// @note After calling this function, the stage handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null stage handle.
NANOUSD_API
nusd_result_t nusd_stage_destroy(nusd_stage_t stage);

/// Defines a new prim of the specified type at the given path on the stage.
/// 
/// @param stage Valid stage handle.
/// @param prim_path USD path where the prim should be defined (e.g., "/World/Geometry").
/// @param prim_type Type token for the prim (e.g., "Xform", "Mesh", "Sphere").
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if prim creation fails (invalid path, invalid type, stage issues, etc.)
/// 
/// @note stage must not be null.
/// @note prim_path must not be null and should be a valid USD path.
/// @note prim_type must not be null and should be a valid USD prim type token.
/// @note This function uses UsdStage::DefinePrim() internally.
NANOUSD_API
nusd_result_t nusd_stage_define_prim(nusd_stage_t stage, char const* prim_path, char const* prim_type);

/// Checks if the specified path refers to a valid prim on the stage.
/// 
/// @param stage Valid stage handle.
/// @param prim_path USD path to check for prim existence.
/// 
/// @return true if a valid prim exists at the path, false otherwise
/// 
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note This function uses UsdStage::GetPrimAtPath() internally and checks prim validity.
NANOUSD_API
bool nusd_stage_path_is_valid_prim(nusd_stage_t stage, char const* prim_path);

/// Creates an iterator to traverse all prims in the stage hierarchy.
/// 
/// @param stage Valid stage handle.
/// @param iterator Output pointer that will contain the prim iterator handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK as iterator creation does not fail.
/// @note The returned iterator must be released with nusd_prim_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note iterator must not be null.
/// @note Traversal starts from the stage's pseudo root and includes all descendant prims.
NANOUSD_API
nusd_result_t nusd_stage_traverse(nusd_stage_t stage, nusd_prim_iterator_t* iterator);

/// Advances the prim iterator to the next prim and returns its path.
/// 
/// @param iterator Valid prim iterator handle.
/// @param prim_path Output pointer that will contain the current prim's path if available.
/// 
/// @return true if a prim is available and prim_path was set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note prim_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_prim_iterator_next(nusd_prim_iterator_t iterator, char const** prim_path);

/// Destroys a prim iterator and releases associated resources.
/// 
/// @param iterator Valid prim iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_prim_iterator_destroy(nusd_prim_iterator_t iterator);

/// Creates an iterator for all properties (attributes and relationships) of a prim.
/// 
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim whose properties to iterate.
/// @param iterator Output pointer that will contain the property iterator handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified path
/// 
/// @note The returned iterator must be released with nusd_property_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note iterator must not be null.
NANOUSD_API
nusd_result_t nusd_prim_get_properties(nusd_stage_t stage, char const* prim_path, nusd_property_iterator_t* iterator);

/// Creates a new property (attribute or relationship) on a prim.
/// 
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim where the property should be created.
/// @param property_name Name of the property to create.
/// @param property_type Type of the property (use NUSD_TYPE_RELATIONSHIP for relationships, or any attribute type).
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified path
/// @return NUSD_RESULT_INVALID_PROPERTY_TYPE if the property type is not recognized
/// @return NUSD_RESULT_CREATE_RELATIONSHIP_FAILED if relationship creation fails
/// @return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED if attribute creation fails
/// 
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note property_name must not be null.
/// @note property_type must not be null and should be a valid USD type token.
NANOUSD_API
nusd_result_t nusd_prim_create_property(nusd_stage_t stage, char const* prim_path, char const* property_name, nusd_type_t property_type);

/// Advances the property iterator to the next property and returns its path and type.
/// 
/// @param iterator Valid property iterator handle.
/// @param property_path Output pointer that will contain the current property's path if available.
/// @param property_type Output pointer that will contain the current property's type if available.
/// 
/// @return true if a property is available and outputs were set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note property_path must not be null.
/// @note property_type must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
/// @note For relationships, property_type will be set to NUSD_TYPE_RELATIONSHIP.
NANOUSD_API
bool nusd_property_iterator_next(nusd_property_iterator_t iterator, char const** property_path, nusd_type_t* property_type);

/// Destroys a property iterator and releases associated resources.
/// 
/// @param iterator Valid property iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_property_iterator_destroy(nusd_property_iterator_t iterator);

/// Gets the type of a property at the specified path.
/// 
/// @param stage Valid stage handle.
/// @param property_path USD path to the property.
/// @param property_type Output pointer that will contain the property's type on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PROPERTY_PATH if no property exists at the specified path
/// 
/// @note stage must not be null.
/// @note property_path must not be null.
/// @note property_type must not be null.
/// @note For relationships, property_type will be set to NUSD_TYPE_RELATIONSHIP.
NANOUSD_API
nusd_result_t nusd_property_get_type(nusd_stage_t stage, char const* property_path, nusd_type_t* property_type);

/// Creates an iterator for all attributes of a prim.
/// 
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim whose attributes to iterate.
/// @param iterator Output pointer that will contain the attribute iterator handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified path
/// 
/// @note The returned iterator must be released with nusd_attribute_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note iterator must not be null.
NANOUSD_API
nusd_result_t nusd_prim_get_attributes(nusd_stage_t stage, char const* prim_path, nusd_attribute_iterator_t* iterator);

/// Advances the attribute iterator to the next attribute and returns its path.
/// 
/// @param iterator Valid attribute iterator handle.
/// @param attribute_path Output pointer that will contain the current attribute's path if available.
/// 
/// @return true if an attribute is available and attribute_path was set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note attribute_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_attribute_iterator_next(nusd_attribute_iterator_t iterator, char const** attribute_path);

/// Destroys an attribute iterator and releases associated resources.
/// 
/// @param iterator Valid attribute iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_attribute_iterator_destroy(nusd_attribute_iterator_t iterator);

/// Gets the value of the given attribute as a token, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param token Output pointer that will contain the token value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of token type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note token must not be null.
/// @note The returned token pointer is valid until the stage is destroyed.
NANOUSD_API
nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, char const** token);

/// Gets the value of the given attribute as a token array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param token_array Output pointer that will contain the token array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of token array type
/// 
/// @note The returned token array must be released with nusd_token_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note token_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_token_array(nusd_stage_t stage, char const* attribute_path, nusd_token_array_t* token_array);

// float
/// Gets the value of the given attribute as a float, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output pointer that will contain the float value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float(nusd_stage_t stage, char const* attribute_path, float* value);

/// Gets the value of the given attribute as a float array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param float_array Output pointer that will contain the float array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float array type
/// 
/// @note The returned float array must be released with nusd_float_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float_array(nusd_stage_t stage, char const* attribute_path, nusd_float_array_t* float_array);

/// Returns the number of elements in a float array.
/// 
/// @param float_array Valid float array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note float_array must not be null.
NANOUSD_API
size_t nusd_float_array_size(nusd_float_array_t float_array);

/// Returns a pointer to the raw data of a float array.
/// 
/// @param float_array Valid float array handle.
/// 
/// @return Pointer to the float data
/// 
/// @note float_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_float_array_size() elements.
NANOUSD_API
float* nusd_float_array_data(nusd_float_array_t float_array);

/// Destroys a float array and releases associated resources.
/// 
/// @param float_array Valid float array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float_array_destroy(nusd_float_array_t float_array);

/// Gets the value of the given attribute as a 2-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 2) that will contain the float2 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 floats.
NANOUSD_API
nusd_result_t nusd_attribute_get_float2(nusd_stage_t stage, char const* attribute_path, float* value);

/// Gets the value of the given attribute as a float2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param float2_array Output pointer that will contain the float2 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 array type
/// 
/// @note The returned float2 array must be released with nusd_float2_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float2_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float2_array(nusd_stage_t stage, char const* attribute_path, nusd_float2_array_t* float2_array);

/// Returns the number of float2 elements in a float2 array.
/// 
/// @param float2_array Valid float2 array handle.
/// 
/// @return Number of float2 elements in the array
/// 
/// @note float2_array must not be null.
NANOUSD_API
size_t nusd_float2_array_size(nusd_float2_array_t float2_array);

/// Returns a pointer to the raw data of a float2 array.
/// 
/// @param float2_array Valid float2 array handle.
/// 
/// @return Pointer to the float data (interleaved as x,y,x,y,...)
/// 
/// @note float2_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_float2_array_size() * 2 float values.
NANOUSD_API
float* nusd_float2_array_data(nusd_float2_array_t float2_array);

/// Destroys a float2 array and releases associated resources.
/// 
/// @param float2_array Valid float2 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float2_array_destroy(nusd_float2_array_t float2_array);

/// Gets the value of the given attribute as a 3-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 3) that will contain the float3 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 floats.
NANOUSD_API
nusd_result_t nusd_attribute_get_float3(nusd_stage_t stage, char const* attribute_path, float* value);

/// Gets the value of the given attribute as a float3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param float3_array Output pointer that will contain the float3 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 array type
/// 
/// @note The returned float3 array must be released with nusd_float3_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float3_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float3_array(nusd_stage_t stage, char const* attribute_path, nusd_float3_array_t* float3_array);

/// Returns the number of float3 elements in a float3 array.
/// 
/// @param float3_array Valid float3 array handle.
/// 
/// @return Number of float3 elements in the array
/// 
/// @note float3_array must not be null.
NANOUSD_API
size_t nusd_float3_array_size(nusd_float3_array_t float3_array);

/// Returns a pointer to the raw data of a float3 array.
/// 
/// @param float3_array Valid float3 array handle.
/// 
/// @return Pointer to the float data (interleaved as x,y,z,x,y,z,...)
/// 
/// @note float3_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_float3_array_size() * 3 float values.
NANOUSD_API
float* nusd_float3_array_data(nusd_float3_array_t float3_array);

/// Destroys a float3 array and releases associated resources.
/// 
/// @param float3_array Valid float3 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float3_array_destroy(nusd_float3_array_t float3_array);

/// Gets the value of the given attribute as a 4-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 4) that will contain the float4 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 floats.
NANOUSD_API
nusd_result_t nusd_attribute_get_float4(nusd_stage_t stage, char const* attribute_path, float* value);

/// Gets the value of the given attribute as a float4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param float4_array Output pointer that will contain the float4 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 array type
/// 
/// @note The returned float4 array must be released with nusd_float4_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float4_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float4_array(nusd_stage_t stage, char const* attribute_path, nusd_float4_array_t* float4_array);

/// Returns the number of float4 elements in a float4 array.
/// 
/// @param float4_array Valid float4 array handle.
/// 
/// @return Number of float4 elements in the array
/// 
/// @note float4_array must not be null.
NANOUSD_API
size_t nusd_float4_array_size(nusd_float4_array_t float4_array);

/// Returns a pointer to the raw data of a float4 array.
/// 
/// @param float4_array Valid float4 array handle.
/// 
/// @return Pointer to the float data (interleaved as x,y,z,w,x,y,z,w,...)
/// 
/// @note float4_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_float4_array_size() * 4 float values.
NANOUSD_API
float* nusd_float4_array_data(nusd_float4_array_t float4_array);

/// Destroys a float4 array and releases associated resources.
/// 
/// @param float4_array Valid float4 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float4_array_destroy(nusd_float4_array_t float4_array);

/// Sets the value of the given attribute to a float, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Float value to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_float(nusd_stage_t stage, char const* attribute_path, float value);

/// Sets the value of the given attribute to a float array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float data to set.
/// @param num_elements Number of float elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

/// Sets the value of the given attribute to a 2-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 2 float values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 floats.
NANOUSD_API
nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage, char const* attribute_path, float* value);

/// Sets the value of the given attribute to a float2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float2 data to set (interleaved as x,y,x,y,...).
/// @param num_elements Number of float2 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 2 float values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float2_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

/// Sets the value of the given attribute to a 3-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 3 float values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 floats.
NANOUSD_API
nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage, char const* attribute_path, float* value);

/// Sets the value of the given attribute to a float3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float3 data to set (interleaved as x,y,z,x,y,z,...).
/// @param num_elements Number of float3 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 3 float values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float3_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

/// Sets the value of the given attribute to a 4-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 float values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 floats.
NANOUSD_API
nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage, char const* attribute_path, float* value);

/// Sets the value of the given attribute to a float4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float4 data to set (interleaved as x,y,z,w,x,y,z,w,...).
/// @param num_elements Number of float4 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 4 float values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float4_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

// double
/// Gets the value of the given attribute as a double, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output pointer that will contain the double value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double(nusd_stage_t stage, char const* attribute_path, double* value);

/// Gets the value of the given attribute as a double array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param double_array Output pointer that will contain the double array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double array type
/// 
/// @note The returned double array must be released with nusd_double_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double_array(nusd_stage_t stage, char const* attribute_path, nusd_double_array_t* double_array);

/// Returns the number of elements in a double array.
/// 
/// @param double_array Valid double array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note double_array must not be null.
NANOUSD_API
size_t nusd_double_array_size(nusd_double_array_t double_array);

/// Returns a pointer to the raw data of a double array.
/// 
/// @param double_array Valid double array handle.
/// 
/// @return Pointer to the double data
/// 
/// @note double_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_double_array_size() elements.
NANOUSD_API
double* nusd_double_array_data(nusd_double_array_t double_array);

/// Destroys a double array and releases associated resources.
/// 
/// @param double_array Valid double array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double_array_destroy(nusd_double_array_t double_array);

/// Gets the value of the given attribute as a 2-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 2) that will contain the double2 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_double2(nusd_stage_t stage, char const* attribute_path, double* value);

/// Gets the value of the given attribute as a double2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param double2_array Output pointer that will contain the double2 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 array type
/// 
/// @note The returned double2 array must be released with nusd_double2_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double2_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double2_array(nusd_stage_t stage, char const* attribute_path, nusd_double2_array_t* double2_array);

/// Returns the number of double2 elements in a double2 array.
/// 
/// @param double2_array Valid double2 array handle.
/// 
/// @return Number of double2 elements in the array
/// 
/// @note double2_array must not be null.
NANOUSD_API
size_t nusd_double2_array_size(nusd_double2_array_t double2_array);

/// Returns a pointer to the raw data of a double2 array.
/// 
/// @param double2_array Valid double2 array handle.
/// 
/// @return Pointer to the double data (interleaved as x,y,x,y,...)
/// 
/// @note double2_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_double2_array_size() * 2 double values.
NANOUSD_API
double* nusd_double2_array_data(nusd_double2_array_t double2_array);

/// Destroys a double2 array and releases associated resources.
/// 
/// @param double2_array Valid double2 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double2_array_destroy(nusd_double2_array_t double2_array);

/// Gets the value of the given attribute as a 3-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 3) that will contain the double3 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_double3(nusd_stage_t stage, char const* attribute_path, double* value);

/// Gets the value of the given attribute as a double3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param double3_array Output pointer that will contain the double3 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 array type
/// 
/// @note The returned double3 array must be released with nusd_double3_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double3_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double3_array(nusd_stage_t stage, char const* attribute_path, nusd_double3_array_t* double3_array);

/// Returns the number of double3 elements in a double3 array.
/// 
/// @param double3_array Valid double3 array handle.
/// 
/// @return Number of double3 elements in the array
/// 
/// @note double3_array must not be null.
NANOUSD_API
size_t nusd_double3_array_size(nusd_double3_array_t double3_array);

/// Returns a pointer to the raw data of a double3 array.
/// 
/// @param double3_array Valid double3 array handle.
/// 
/// @return Pointer to the double data (interleaved as x,y,z,x,y,z,...)
/// 
/// @note double3_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_double3_array_size() * 3 double values.
NANOUSD_API
double* nusd_double3_array_data(nusd_double3_array_t double3_array);

/// Destroys a double3 array and releases associated resources.
/// 
/// @param double3_array Valid double3 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double3_array_destroy(nusd_double3_array_t double3_array);

/// Gets the value of the given attribute as a 4-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 4) that will contain the double4 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_double4(nusd_stage_t stage, char const* attribute_path, double* value);

/// Gets the value of the given attribute as a double4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param double4_array Output pointer that will contain the double4 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 array type
/// 
/// @note The returned double4 array must be released with nusd_double4_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double4_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double4_array(nusd_stage_t stage, char const* attribute_path, nusd_double4_array_t* double4_array);

/// Returns the number of double4 elements in a double4 array.
/// 
/// @param double4_array Valid double4 array handle.
/// 
/// @return Number of double4 elements in the array
/// 
/// @note double4_array must not be null.
NANOUSD_API
size_t nusd_double4_array_size(nusd_double4_array_t double4_array);

/// Returns a pointer to the raw data of a double4 array.
/// 
/// @param double4_array Valid double4 array handle.
/// 
/// @return Pointer to the double data (interleaved as x,y,z,w,x,y,z,w,...)
/// 
/// @note double4_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_double4_array_size() * 4 double values.
NANOUSD_API
double* nusd_double4_array_data(nusd_double4_array_t double4_array);

/// Destroys a double4 array and releases associated resources.
/// 
/// @param double4_array Valid double4 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double4_array_destroy(nusd_double4_array_t double4_array);

// double setters
/// Sets the value of the given attribute to a double, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Double value to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_double(nusd_stage_t stage, char const* attribute_path, double value);

/// Sets the value of the given attribute to a double array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double data to set.
/// @param num_elements Number of double elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

/// Sets the value of the given attribute to a 2-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 2 double values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_double2(nusd_stage_t stage, char const* attribute_path, double* value);

/// Sets the value of the given attribute to a double2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double2 data to set (interleaved as x,y,x,y,...).
/// @param num_elements Number of double2 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 2 double values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double2_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

/// Sets the value of the given attribute to a 3-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 3 double values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_double3(nusd_stage_t stage, char const* attribute_path, double* value);

/// Sets the value of the given attribute to a double3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double3 data to set (interleaved as x,y,z,x,y,z,...).
/// @param num_elements Number of double3 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 3 double values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double3_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

/// Sets the value of the given attribute to a 4-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 double values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_double4(nusd_stage_t stage, char const* attribute_path, double* value);

/// Sets the value of the given attribute to a double4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double4 data to set (interleaved as x,y,z,w,x,y,z,w,...).
/// @param num_elements Number of double4 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 4 double values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double4_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

// int
/// Gets the value of the given attribute as an int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output pointer that will contain the int value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int(nusd_stage_t stage, char const* attribute_path, int* value);

/// Gets the value of the given attribute as an int array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param int_array Output pointer that will contain the int array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int array type
/// 
/// @note The returned int array must be released with nusd_int_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int_array(nusd_stage_t stage, char const* attribute_path, nusd_int_array_t* int_array);

/// Returns the number of elements in an int array.
/// 
/// @param int_array Valid int array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note int_array must not be null.
NANOUSD_API
size_t nusd_int_array_size(nusd_int_array_t int_array);

/// Returns a pointer to the raw data of an int array.
/// 
/// @param int_array Valid int array handle.
/// 
/// @return Pointer to the int data
/// 
/// @note int_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_int_array_size() elements.
NANOUSD_API
int* nusd_int_array_data(nusd_int_array_t int_array);

/// Destroys an int array and releases associated resources.
/// 
/// @param int_array Valid int array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int_array_destroy(nusd_int_array_t int_array);

/// Gets the value of the given attribute as a 2-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 2) that will contain the int2 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 ints.
NANOUSD_API
nusd_result_t nusd_attribute_get_int2(nusd_stage_t stage, char const* attribute_path, int* value);

/// Gets the value of the given attribute as an int2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param int2_array Output pointer that will contain the int2 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 array type
/// 
/// @note The returned int2 array must be released with nusd_int2_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int2_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int2_array(nusd_stage_t stage, char const* attribute_path, nusd_int2_array_t* int2_array);

/// Returns the number of int2 elements in an int2 array.
/// 
/// @param int2_array Valid int2 array handle.
/// 
/// @return Number of int2 elements in the array
/// 
/// @note int2_array must not be null.
NANOUSD_API
size_t nusd_int2_array_size(nusd_int2_array_t int2_array);

/// Returns a pointer to the raw data of an int2 array.
/// 
/// @param int2_array Valid int2 array handle.
/// 
/// @return Pointer to the int data (interleaved as x,y,x,y,...)
/// 
/// @note int2_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_int2_array_size() * 2 int values.
NANOUSD_API
int* nusd_int2_array_data(nusd_int2_array_t int2_array);

/// Destroys an int2 array and releases associated resources.
/// 
/// @param int2_array Valid int2 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int2_array_destroy(nusd_int2_array_t int2_array);

/// Gets the value of the given attribute as a 3-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 3) that will contain the int3 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 ints.
NANOUSD_API
nusd_result_t nusd_attribute_get_int3(nusd_stage_t stage, char const* attribute_path, int* value);

/// Gets the value of the given attribute as an int3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param int3_array Output pointer that will contain the int3 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 array type
/// 
/// @note The returned int3 array must be released with nusd_int3_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int3_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int3_array(nusd_stage_t stage, char const* attribute_path, nusd_int3_array_t* int3_array);

/// Returns the number of int3 elements in an int3 array.
/// 
/// @param int3_array Valid int3 array handle.
/// 
/// @return Number of int3 elements in the array
/// 
/// @note int3_array must not be null.
NANOUSD_API
size_t nusd_int3_array_size(nusd_int3_array_t int3_array);

/// Returns a pointer to the raw data of an int3 array.
/// 
/// @param int3_array Valid int3 array handle.
/// 
/// @return Pointer to the int data (interleaved as x,y,z,x,y,z,...)
/// 
/// @note int3_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_int3_array_size() * 3 int values.
NANOUSD_API
int* nusd_int3_array_data(nusd_int3_array_t int3_array);

/// Destroys an int3 array and releases associated resources.
/// 
/// @param int3_array Valid int3 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int3_array_destroy(nusd_int3_array_t int3_array);

/// Gets the value of the given attribute as a 4-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output array (size 4) that will contain the int4 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 ints.
NANOUSD_API
nusd_result_t nusd_attribute_get_int4(nusd_stage_t stage, char const* attribute_path, int* value);

/// Gets the value of the given attribute as an int4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param int4_array Output pointer that will contain the int4 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 array type
/// 
/// @note The returned int4 array must be released with nusd_int4_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int4_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int4_array(nusd_stage_t stage, char const* attribute_path, nusd_int4_array_t* int4_array);

/// Returns the number of int4 elements in an int4 array.
/// 
/// @param int4_array Valid int4 array handle.
/// 
/// @return Number of int4 elements in the array
/// 
/// @note int4_array must not be null.
NANOUSD_API
size_t nusd_int4_array_size(nusd_int4_array_t int4_array);

/// Returns a pointer to the raw data of an int4 array.
/// 
/// @param int4_array Valid int4 array handle.
/// 
/// @return Pointer to the int data (interleaved as x,y,z,w,x,y,z,w,...)
/// 
/// @note int4_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_int4_array_size() * 4 int values.
NANOUSD_API
int* nusd_int4_array_data(nusd_int4_array_t int4_array);

/// Destroys an int4 array and releases associated resources.
/// 
/// @param int4_array Valid int4 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int4_array_destroy(nusd_int4_array_t int4_array);

// int64
/// Gets the value of the given attribute as an int64, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output pointer that will contain the int64 value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int64(nusd_stage_t stage, char const* attribute_path, int64_t* value);

/// Gets the value of the given attribute as an int64 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param int64_array Output pointer that will contain the int64 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 array type
/// 
/// @note The returned int64 array must be released with nusd_int64_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int64_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int64_array(nusd_stage_t stage, char const* attribute_path, nusd_int64_array_t* int64_array);

/// Returns the number of elements in an int64 array.
/// 
/// @param int64_array Valid int64 array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note int64_array must not be null.
NANOUSD_API
size_t nusd_int64_array_size(nusd_int64_array_t int64_array);

/// Returns a pointer to the raw data of an int64 array.
/// 
/// @param int64_array Valid int64 array handle.
/// 
/// @return Pointer to the int64 data
/// 
/// @note int64_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_int64_array_size() elements.
NANOUSD_API
int64_t* nusd_int64_array_data(nusd_int64_array_t int64_array);

/// Destroys an int64 array and releases associated resources.
/// 
/// @param int64_array Valid int64 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int64_array_destroy(nusd_int64_array_t int64_array);

// int setters
/// Sets the value of the given attribute to an int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Int value to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_int(nusd_stage_t stage, char const* attribute_path, int value);

/// Sets the value of the given attribute to an int array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int data to set.
/// @param num_elements Number of int elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

/// Sets the value of the given attribute to a 2-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 2 int values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 ints.
NANOUSD_API
nusd_result_t nusd_attribute_set_int2(nusd_stage_t stage, char const* attribute_path, int* value);

/// Sets the value of the given attribute to an int2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int2 data to set (interleaved as x,y,x,y,...).
/// @param num_elements Number of int2 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 2 int values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int2_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

/// Sets the value of the given attribute to a 3-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 3 int values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 ints.
NANOUSD_API
nusd_result_t nusd_attribute_set_int3(nusd_stage_t stage, char const* attribute_path, int* value);

/// Sets the value of the given attribute to an int3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int3 data to set (interleaved as x,y,z,x,y,z,...).
/// @param num_elements Number of int3 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 3 int values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int3_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

/// Sets the value of the given attribute to a 4-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 int values to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 ints.
NANOUSD_API
nusd_result_t nusd_attribute_set_int4(nusd_stage_t stage, char const* attribute_path, int* value);

/// Sets the value of the given attribute to an int4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int4 data to set (interleaved as x,y,z,w,x,y,z,w,...).
/// @param num_elements Number of int4 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 4 int values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int4_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

// int64 setters
/// Sets the value of the given attribute to an int64, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Int64 value to set.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_int64(nusd_stage_t stage, char const* attribute_path, int64_t value);

/// Sets the value of the given attribute to an int64 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int64 data to set.
/// @param num_elements Number of int64 elements in the data array.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int64_array(nusd_stage_t stage, char const* attribute_path, int64_t* data, size_t num_elements);

// bool
/// Gets the value of the given attribute as a bool, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Output pointer that will contain the bool value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of bool type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_bool(nusd_stage_t stage, char const* attribute_path, bool* value);

/// Gets the value of the given attribute as a bool array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param bool_array Output pointer that will contain the bool array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of bool array type
/// 
/// @note The returned bool array must be released with nusd_bool_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note bool_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_bool_array(nusd_stage_t stage, char const* attribute_path, nusd_bool_array_t* bool_array);

/// Returns the number of elements in a bool array.
/// 
/// @param bool_array Valid bool array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note bool_array must not be null.
NANOUSD_API
size_t nusd_bool_array_size(nusd_bool_array_t bool_array);

/// Returns a pointer to the raw data of a bool array.
/// 
/// @param bool_array Valid bool array handle.
/// 
/// @return Pointer to the bool data
/// 
/// @note bool_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_bool_array_size() elements.
NANOUSD_API
bool* nusd_bool_array_data(nusd_bool_array_t bool_array);

/// Destroys a bool array and releases associated resources.
/// 
/// @param bool_array Valid bool array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_bool_array_destroy(nusd_bool_array_t bool_array);


// token
/// Returns the number of tokens in a token array.
/// 
/// @param token_array Valid token array handle.
/// 
/// @return Number of tokens in the array
/// 
/// @note token_array must not be null.
NANOUSD_API
size_t nusd_token_array_size(nusd_token_array_t token_array);

/// Returns the token at the specified index in a token array.
/// 
/// @param token_array Valid token array handle.
/// @param index Index of the token to retrieve (must be < nusd_token_array_size()).
/// 
/// @return Pointer to the token string at the specified index
/// 
/// @note token_array must not be null.
/// @note index must be a valid index within the array bounds.
/// @note The returned pointer is valid until the array is destroyed.
NANOUSD_API
char const* nusd_token_array_index(nusd_token_array_t token_array, size_t index);

/// Destroys a token array and releases associated resources.
/// 
/// @param token_array Valid token array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_token_array_destroy(nusd_token_array_t token_array);

/// Creates an iterator for all relationships of a prim.
/// 
/// @param stage Valid stage handle.
/// @param prim_path USD path to the prim whose relationships to iterate.
/// @param iterator Output pointer that will contain the relationship iterator handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no prim exists at the specified path
/// 
/// @note The returned iterator must be released with nusd_relationship_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note prim_path must not be null.
/// @note iterator must not be null.
NANOUSD_API
nusd_result_t nusd_prim_get_relationships(nusd_stage_t stage, char const* prim_path, nusd_relationship_iterator_t* iterator);

/// Advances the relationship iterator to the next relationship and returns its path.
/// 
/// @param iterator Valid relationship iterator handle.
/// @param relationship_path Output pointer that will contain the current relationship's path if available.
/// 
/// @return true if a relationship is available and relationship_path was set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note relationship_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_relationship_iterator_next(nusd_relationship_iterator_t iterator, char const** relationship_path);

/// Destroys a relationship iterator and releases associated resources.
/// 
/// @param iterator Valid relationship iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_relationship_iterator_destroy(nusd_relationship_iterator_t iterator);

/// Gets an iterator for the target paths of a relationship.
/// 
/// @param stage Valid stage handle.
/// @param relationship_path USD path to the relationship.
/// @param targets Output pointer that will contain the targets iterator handle on success.
/// @param num_targets Optional output pointer that will contain the number of targets (can be null).
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_RELATIONSHIP_PATH if no relationship exists at the specified path
/// 
/// @note The returned iterator must be released with nusd_relationship_targets_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note relationship_path must not be null.
/// @note targets must not be null.
NANOUSD_API
nusd_result_t nusd_relationship_get_targets(nusd_stage_t stage, char const* relationship_path, nusd_relationship_targets_iterator_t* targets, size_t* num_targets);

/// Advances the relationship targets iterator to the next target and returns its path.
/// 
/// @param targets Valid relationship targets iterator handle.
/// @param target_path Output pointer that will contain the current target's path if available.
/// 
/// @return true if a target is available and target_path was set, false if iteration is complete
/// 
/// @note targets must not be null.
/// @note target_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_relationship_targets_iterator_next(nusd_relationship_targets_iterator_t targets, char const** target_path);

/// Destroys a relationship targets iterator and releases associated resources.
/// 
/// @param targets Valid relationship targets iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_relationship_targets_iterator_destroy(nusd_relationship_targets_iterator_t targets);

/// Extracts the name from a USD path.
/// 
/// @param path USD path (prim, property, or relationship path).
/// 
/// @return Pointer to the name portion of the path, or null if no delimiter found
/// 
/// @note path must not be null.
/// @note Returns the name of the prim, property, or relational attribute identified by the path.
/// @note For property paths like "/World/Mesh.points", returns "points".
/// @note For prim paths, this function's behavior depends on the presence of a '.' delimiter.
NANOUSD_API
char const* nusd_path_get_name(char const* path);

#ifdef __cplusplus
}
#endif

#endif