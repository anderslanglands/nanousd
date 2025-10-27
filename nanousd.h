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

NANOUSD_API
nusd_result_t nusd_stage_open(char const* filename, nusd_stage_t* stage);

NANOUSD_API
nusd_result_t nusd_stage_create_new(char const* identifier, nusd_stage_t* stage);

NANOUSD_API
nusd_result_t nusd_stage_create_in_memory(char const* identifier, nusd_stage_t* stage);

NANOUSD_API
nusd_result_t nusd_stage_save(nusd_stage_t stage);

/// Exports the stage's root layer to `filename`
NANOUSD_API
nusd_result_t nusd_stage_save_as(nusd_stage_t stage, char const* filename);

NANOUSD_API
nusd_result_t nusd_stage_destroy(nusd_stage_t stage);

/// Define a prim of type @p prim_type at path @p prim_path on the stage
NANOUSD_API
nusd_result_t nusd_stage_define_prim(nusd_stage_t stage, char const* prim_path, char const* prim_type);

/// Returns true if @p prim_path refers to a valid prim on @p stage, false otherwise
NANOUSD_API
bool nusd_stage_path_is_valid_prim(nusd_stage_t stage, char const* prim_path);

NANOUSD_API
nusd_result_t nusd_stage_traverse(nusd_stage_t stage, nusd_prim_iterator_t* iterator);

NANOUSD_API
bool nusd_prim_iterator_next(nusd_prim_iterator_t iterator, char const** prim_path);

NANOUSD_API
nusd_result_t nusd_prim_iterator_destroy(nusd_prim_iterator_t iterator);

NANOUSD_API
nusd_result_t nusd_prim_get_properties(nusd_stage_t stage, char const* prim_path, nusd_property_iterator_t* iterator);

NANOUSD_API
nusd_result_t nusd_prim_create_property(nusd_stage_t stage, char const* prim_path, char const* property_name, nusd_type_t property_type);

NANOUSD_API
bool nusd_property_iterator_next(nusd_property_iterator_t iterator, char const** property_path, nusd_type_t* property_type);

NANOUSD_API
nusd_result_t nusd_property_iterator_destroy(nusd_property_iterator_t iterator);

NANOUSD_API
nusd_result_t nusd_property_get_type(nusd_stage_t stage, char const* property_path, nusd_type_t* property_type);

NANOUSD_API
nusd_result_t nusd_prim_get_attributes(nusd_stage_t stage, char const* prim_path, nusd_attribute_iterator_t* iterator);

NANOUSD_API
bool nusd_attribute_iterator_next(nusd_attribute_iterator_t iterator, char const** attribute_path);

NANOUSD_API
nusd_result_t nusd_attribute_iterator_destroy(nusd_attribute_iterator_t iterator);

NANOUSD_API
nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, char const** token);

NANOUSD_API
nusd_result_t nusd_attribute_get_token_array(nusd_stage_t stage, char const* attribute_path, nusd_token_array_t* token_array);

// float
NANOUSD_API
nusd_result_t nusd_attribute_get_float(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_float_array(nusd_stage_t stage, char const* attribute_path, nusd_float_array_t* float_array);

NANOUSD_API
size_t nusd_float_array_size(nusd_float_array_t float_array);

NANOUSD_API
float* nusd_float_array_data(nusd_float_array_t float_array);

NANOUSD_API
void nusd_float_array_destroy(nusd_float_array_t float_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_float2(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_float2_array(nusd_stage_t stage, char const* attribute_path, nusd_float2_array_t* float2_array);

NANOUSD_API
size_t nusd_float2_array_size(nusd_float2_array_t float2_array);

NANOUSD_API
float* nusd_float2_array_data(nusd_float2_array_t float2_array);

NANOUSD_API
void nusd_float2_array_destroy(nusd_float2_array_t float2_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_float3(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_float3_array(nusd_stage_t stage, char const* attribute_path, nusd_float3_array_t* float3_array);

NANOUSD_API
size_t nusd_float3_array_size(nusd_float3_array_t float3_array);

NANOUSD_API
float* nusd_float3_array_data(nusd_float3_array_t float3_array);

NANOUSD_API
void nusd_float3_array_destroy(nusd_float3_array_t float3_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_float4(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_float4_array(nusd_stage_t stage, char const* attribute_path, nusd_float4_array_t* float4_array);

NANOUSD_API
size_t nusd_float4_array_size(nusd_float4_array_t float4_array);

NANOUSD_API
float* nusd_float4_array_data(nusd_float4_array_t float4_array);

NANOUSD_API
void nusd_float4_array_destroy(nusd_float4_array_t float4_array);

NANOUSD_API
nusd_result_t nusd_attribute_set_float(nusd_stage_t stage, char const* attribute_path, float value);

NANOUSD_API
nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_float2_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_float3_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage, char const* attribute_path, float* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_float4_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements);

// double
NANOUSD_API
nusd_result_t nusd_attribute_get_double(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_double_array(nusd_stage_t stage, char const* attribute_path, nusd_double_array_t* double_array);

NANOUSD_API
size_t nusd_double_array_size(nusd_double_array_t double_array);

NANOUSD_API
double* nusd_double_array_data(nusd_double_array_t double_array);

NANOUSD_API
void nusd_double_array_destroy(nusd_double_array_t double_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_double2(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_double2_array(nusd_stage_t stage, char const* attribute_path, nusd_double2_array_t* double2_array);

NANOUSD_API
size_t nusd_double2_array_size(nusd_double2_array_t double2_array);

NANOUSD_API
double* nusd_double2_array_data(nusd_double2_array_t double2_array);

NANOUSD_API
void nusd_double2_array_destroy(nusd_double2_array_t double2_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_double3(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_double3_array(nusd_stage_t stage, char const* attribute_path, nusd_double3_array_t* double3_array);

NANOUSD_API
size_t nusd_double3_array_size(nusd_double3_array_t double3_array);

NANOUSD_API
double* nusd_double3_array_data(nusd_double3_array_t double3_array);

NANOUSD_API
void nusd_double3_array_destroy(nusd_double3_array_t double3_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_double4(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_double4_array(nusd_stage_t stage, char const* attribute_path, nusd_double4_array_t* double4_array);

NANOUSD_API
size_t nusd_double4_array_size(nusd_double4_array_t double4_array);

NANOUSD_API
double* nusd_double4_array_data(nusd_double4_array_t double4_array);

NANOUSD_API
void nusd_double4_array_destroy(nusd_double4_array_t double4_array);

// double setters
NANOUSD_API
nusd_result_t nusd_attribute_set_double(nusd_stage_t stage, char const* attribute_path, double value);

NANOUSD_API
nusd_result_t nusd_attribute_set_double_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_double2(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_double2_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_double3(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_double3_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_double4(nusd_stage_t stage, char const* attribute_path, double* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_double4_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements);

// int
NANOUSD_API
nusd_result_t nusd_attribute_get_int(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_int_array(nusd_stage_t stage, char const* attribute_path, nusd_int_array_t* int_array);

NANOUSD_API
size_t nusd_int_array_size(nusd_int_array_t int_array);

NANOUSD_API
int* nusd_int_array_data(nusd_int_array_t int_array);

NANOUSD_API
void nusd_int_array_destroy(nusd_int_array_t int_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_int2(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_int2_array(nusd_stage_t stage, char const* attribute_path, nusd_int2_array_t* int2_array);

NANOUSD_API
size_t nusd_int2_array_size(nusd_int2_array_t int2_array);

NANOUSD_API
int* nusd_int2_array_data(nusd_int2_array_t int2_array);

NANOUSD_API
void nusd_int2_array_destroy(nusd_int2_array_t int2_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_int3(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_int3_array(nusd_stage_t stage, char const* attribute_path, nusd_int3_array_t* int3_array);

NANOUSD_API
size_t nusd_int3_array_size(nusd_int3_array_t int3_array);

NANOUSD_API
int* nusd_int3_array_data(nusd_int3_array_t int3_array);

NANOUSD_API
void nusd_int3_array_destroy(nusd_int3_array_t int3_array);

NANOUSD_API
nusd_result_t nusd_attribute_get_int4(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_int4_array(nusd_stage_t stage, char const* attribute_path, nusd_int4_array_t* int4_array);

NANOUSD_API
size_t nusd_int4_array_size(nusd_int4_array_t int4_array);

NANOUSD_API
int* nusd_int4_array_data(nusd_int4_array_t int4_array);

NANOUSD_API
void nusd_int4_array_destroy(nusd_int4_array_t int4_array);

// int64
NANOUSD_API
nusd_result_t nusd_attribute_get_int64(nusd_stage_t stage, char const* attribute_path, int64_t* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_int64_array(nusd_stage_t stage, char const* attribute_path, nusd_int64_array_t* int64_array);

NANOUSD_API
size_t nusd_int64_array_size(nusd_int64_array_t int64_array);

NANOUSD_API
int64_t* nusd_int64_array_data(nusd_int64_array_t int64_array);

NANOUSD_API
void nusd_int64_array_destroy(nusd_int64_array_t int64_array);

// int setters
NANOUSD_API
nusd_result_t nusd_attribute_set_int(nusd_stage_t stage, char const* attribute_path, int value);

NANOUSD_API
nusd_result_t nusd_attribute_set_int_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_int2(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_int2_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_int3(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_int3_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

NANOUSD_API
nusd_result_t nusd_attribute_set_int4(nusd_stage_t stage, char const* attribute_path, int* value);

NANOUSD_API
nusd_result_t nusd_attribute_set_int4_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements);

// int64 setters
NANOUSD_API
nusd_result_t nusd_attribute_set_int64(nusd_stage_t stage, char const* attribute_path, int64_t value);

NANOUSD_API
nusd_result_t nusd_attribute_set_int64_array(nusd_stage_t stage, char const* attribute_path, int64_t* data, size_t num_elements);

// bool
NANOUSD_API
nusd_result_t nusd_attribute_get_bool(nusd_stage_t stage, char const* attribute_path, bool* value);

NANOUSD_API
nusd_result_t nusd_attribute_get_bool_array(nusd_stage_t stage, char const* attribute_path, nusd_bool_array_t* bool_array);

NANOUSD_API
size_t nusd_bool_array_size(nusd_bool_array_t bool_array);

NANOUSD_API
bool* nusd_bool_array_data(nusd_bool_array_t bool_array);

NANOUSD_API
void nusd_bool_array_destroy(nusd_bool_array_t bool_array);


// token
NANOUSD_API
size_t nusd_token_array_size(nusd_token_array_t token_array);

NANOUSD_API
char const* nusd_token_array_index(nusd_token_array_t token_array, size_t index);

NANOUSD_API
void nusd_token_array_destroy(nusd_token_array_t token_array);

NANOUSD_API
nusd_result_t nusd_prim_get_relationships(nusd_stage_t stage, char const* prim_path, nusd_relationship_iterator_t* iterator);

NANOUSD_API
bool nusd_relationship_iterator_next(nusd_relationship_iterator_t iterator, char const** relationship_path);

NANOUSD_API
nusd_result_t nusd_relationship_iterator_destroy(nusd_relationship_iterator_t iterator);

NANOUSD_API
nusd_result_t nusd_relationship_get_targets(nusd_stage_t stage, char const* relationship_path, nusd_relationship_targets_iterator_t* targets, size_t* num_targets);

NANOUSD_API
bool nusd_relationship_targets_iterator_next(nusd_relationship_targets_iterator_t targets, char const** target_path);

NANOUSD_API
nusd_result_t nusd_relationship_targets_iterator_destroy(nusd_relationship_targets_iterator_t targets);

NANOUSD_API
char const* nusd_path_get_name(char const* path);

#ifdef __cplusplus
}
#endif

#endif