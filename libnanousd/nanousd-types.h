#ifndef NANOUSD_TYPES_H
#define NANOUSD_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
    NUSD_RESULT_NULL_PARAMETER,
    NUSD_RESULT_CONNECTION_FAILED,
    NUSD_RESULT_INVALID_SHADER_INPUT,
    NUSD_RESULT_INVALID_SHADER_OUTPUT,
    NUSD_RESULT_CREATE_INPUT_FAILED,
    NUSD_RESULT_CREATE_OUTPUT_FAILED,
    NUSD_RESULT_INVALID_MATERIAL_PATH,
    NUSD_RESULT_APPLY_BINDING_API_FAILED,
    NUSD_RESULT_CREATE_BINDING_FAILED,
    NUSD_RESULT_SET_METADATA_FAILED,
};
typedef int nusd_result_t;

typedef char const* nusd_type_t;
typedef char const* nusd_colorspace_t;
typedef void* nusd_stage_t;
typedef struct nusd_asset_path_s* nusd_asset_path_t;
typedef struct nusd_string_s* nusd_string_t;

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

extern nusd_type_t NUSD_COLORSPACE_LINEAR_AP1;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_AP0;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_REC709;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_P3D65;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_REC2020;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_ADOBERGB;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_CIEXYZD65;
extern nusd_type_t NUSD_COLORSPACE_LINEAR_DISPLAYP3;
extern nusd_type_t NUSD_COLORSPACE_SRGB_REC709;
extern nusd_type_t NUSD_COLORSPACE_G22_REC709;
extern nusd_type_t NUSD_COLORSPACE_G18_REC709;
extern nusd_type_t NUSD_COLORSPACE_SRGB_AP1;
extern nusd_type_t NUSD_COLORSPACE_G22_AP1;
extern nusd_type_t NUSD_COLORSPACE_G22_ADOBERGB;
extern nusd_type_t NUSD_COLORSPACE_IDENTITY;
extern nusd_type_t NUSD_COLORSPACE_DATA;
extern nusd_type_t NUSD_COLORSPACE_RAW;
extern nusd_type_t NUSD_COLORSPACE_SRGB;
extern nusd_type_t NUSD_COLORSPACE_UNKNOWN;
extern nusd_type_t NUSD_COLORSPACE_CIEXYZ;

extern nusd_type_t NUSD_INTERPOLATION_CONSTANT;
extern nusd_type_t NUSD_INTERPOLATION_UNIFORM;
extern nusd_type_t NUSD_INTERPOLATION_VERTEX;
extern nusd_type_t NUSD_INTERPOLATION_VARYING;
extern nusd_type_t NUSD_INTERPOLATION_FACEVARYING;

extern double NUSD_TIMECODE_DEFAULT;

#define NUSD_UNIT_METERS 1.0
#define NUSD_UNIT_DECIMETERS 0.1
#define NUSD_UNIT_CENTIMETERS 0.01

#ifdef __cplusplus
}
#endif

#endif