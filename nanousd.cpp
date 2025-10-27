#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/base/tf/refPtr.h>
#include <pxr/base/vt/value.h>
#include <pxr/base/vt/array.h>

#include <unordered_map>
#include <mutex>

#include <string.h>

#include <iostream>

struct nusd_prim_iterator_s {
    // TODO - do we need to hold the range here for iterator to be valid?
    PXR_NS::UsdPrimRange range;
    PXR_NS::UsdPrimRange::iterator current;
};

struct nusd_property_iterator_s {
    std::vector<PXR_NS::UsdProperty> properties;
    std::vector<PXR_NS::UsdProperty>::iterator current;
};

struct nusd_attribute_iterator_s {
    std::vector<PXR_NS::UsdAttribute> attributes;
    std::vector<PXR_NS::UsdAttribute>::iterator current;
};

struct nusd_relationship_iterator_s {
    std::vector<PXR_NS::UsdRelationship> relationships;
    std::vector<PXR_NS::UsdRelationship>::iterator current;
};

struct nusd_relationship_targets_iterator_s {
    PXR_NS::SdfPathVector paths;
    PXR_NS::SdfPathVector::iterator current;
};

struct nusd_token_array_s {
    PXR_NS::VtTokenArray value;
};

struct nusd_float_array_s {
    PXR_NS::VtFloatArray value;
};

struct nusd_float2_array_s {
    PXR_NS::VtVec2fArray value;
};

struct nusd_float3_array_s {
    PXR_NS::VtVec3fArray value;
};

struct nusd_float4_array_s {
    PXR_NS::VtVec4fArray value;
};

struct nusd_double_array_s {
    PXR_NS::VtDoubleArray value;
};

struct nusd_double2_array_s {
    PXR_NS::VtVec2dArray value;
};

struct nusd_double3_array_s {
    PXR_NS::VtVec3dArray value;
};

struct nusd_double4_array_s {
    PXR_NS::VtVec4dArray value;
};

struct nusd_int_array_s {
    PXR_NS::VtIntArray value;
};

struct nusd_int2_array_s {
    PXR_NS::VtVec2iArray value;
};

struct nusd_int3_array_s {
    PXR_NS::VtVec3iArray value;
};

struct nusd_int4_array_s {
    PXR_NS::VtVec4iArray value;
};

struct nusd_bool_array_s {
    PXR_NS::VtBoolArray value;
};

std::mutex MTX_TOKEN_INIT;
bool TOKENS_INITIALIZED = false;

extern "C" {

char const* NUSD_TYPE_ASSET;
char const* NUSD_TYPE_ASSETARRAY;
char const* NUSD_TYPE_BOOL;
char const* NUSD_TYPE_BOOLARRAY;
char const* NUSD_TYPE_COLOR3D;
char const* NUSD_TYPE_COLOR3DARRAY;
char const* NUSD_TYPE_COLOR3F;
char const* NUSD_TYPE_COLOR3FARRAY;
char const* NUSD_TYPE_COLOR3H;
char const* NUSD_TYPE_COLOR3HARRAY;
char const* NUSD_TYPE_COLOR4D;
char const* NUSD_TYPE_COLOR4DARRAY;
char const* NUSD_TYPE_COLOR4F;
char const* NUSD_TYPE_COLOR4FARRAY;
char const* NUSD_TYPE_COLOR4H;
char const* NUSD_TYPE_COLOR4HARRAY;
char const* NUSD_TYPE_DOUBLE;
char const* NUSD_TYPE_DOUBLE2;
char const* NUSD_TYPE_DOUBLE2ARRAY;
char const* NUSD_TYPE_DOUBLE3;
char const* NUSD_TYPE_DOUBLE3ARRAY;
char const* NUSD_TYPE_DOUBLE4;
char const* NUSD_TYPE_DOUBLE4ARRAY;
char const* NUSD_TYPE_DOUBLEARRAY;
char const* NUSD_TYPE_FIND;
char const* NUSD_TYPE_FLOAT;
char const* NUSD_TYPE_FLOAT2;
char const* NUSD_TYPE_FLOAT2ARRAY;
char const* NUSD_TYPE_FLOAT3;
char const* NUSD_TYPE_FLOAT3ARRAY;
char const* NUSD_TYPE_FLOAT4;
char const* NUSD_TYPE_FLOAT4ARRAY;
char const* NUSD_TYPE_FLOATARRAY;
char const* NUSD_TYPE_FRAME4D;
char const* NUSD_TYPE_FRAME4DARRAY;
char const* NUSD_TYPE_GROUP;
char const* NUSD_TYPE_HALF;
char const* NUSD_TYPE_HALF2;
char const* NUSD_TYPE_HALF2ARRAY;
char const* NUSD_TYPE_HALF3;
char const* NUSD_TYPE_HALF3ARRAY;
char const* NUSD_TYPE_HALF4;
char const* NUSD_TYPE_HALF4ARRAY;
char const* NUSD_TYPE_HALFARRAY;
char const* NUSD_TYPE_INT;
char const* NUSD_TYPE_INT2;
char const* NUSD_TYPE_INT2ARRAY;
char const* NUSD_TYPE_INT3;
char const* NUSD_TYPE_INT3ARRAY;
char const* NUSD_TYPE_INT4;
char const* NUSD_TYPE_INT4ARRAY;
char const* NUSD_TYPE_INT64;
char const* NUSD_TYPE_INT64ARRAY;
char const* NUSD_TYPE_INTARRAY;
char const* NUSD_TYPE_MATRIX2D;
char const* NUSD_TYPE_MATRIX2DARRAY;
char const* NUSD_TYPE_MATRIX3D;
char const* NUSD_TYPE_MATRIX3DARRAY;
char const* NUSD_TYPE_MATRIX4D;
char const* NUSD_TYPE_MATRIX4DARRAY;
char const* NUSD_TYPE_NORMAL3D;
char const* NUSD_TYPE_NORMAL3DARRAY;
char const* NUSD_TYPE_NORMAL3F;
char const* NUSD_TYPE_NORMAL3FARRAY;
char const* NUSD_TYPE_NORMAL3H;
char const* NUSD_TYPE_NORMAL3HARRAY;
char const* NUSD_TYPE_OPAQUE;
char const* NUSD_TYPE_PATHEXPRESSION;
char const* NUSD_TYPE_PATHEXPRESSIONARRAY;
char const* NUSD_TYPE_POINT3D;
char const* NUSD_TYPE_POINT3DARRAY;
char const* NUSD_TYPE_POINT3F;
char const* NUSD_TYPE_POINT3FARRAY;
char const* NUSD_TYPE_POINT3H;
char const* NUSD_TYPE_POINT3HARRAY;
char const* NUSD_TYPE_QUATD;
char const* NUSD_TYPE_QUATDARRAY;
char const* NUSD_TYPE_QUATF;
char const* NUSD_TYPE_QUATFARRAY;
char const* NUSD_TYPE_QUATH;
char const* NUSD_TYPE_QUATHARRAY;
char const* NUSD_TYPE_STRING;
char const* NUSD_TYPE_STRINGARRAY;
char const* NUSD_TYPE_TEXCOORD2D;
char const* NUSD_TYPE_TEXCOORD2DARRAY;
char const* NUSD_TYPE_TEXCOORD2F;
char const* NUSD_TYPE_TEXCOORD2FARRAY;
char const* NUSD_TYPE_TEXCOORD2H;
char const* NUSD_TYPE_TEXCOORD2HARRAY;
char const* NUSD_TYPE_TEXCOORD3D;
char const* NUSD_TYPE_TEXCOORD3DARRAY;
char const* NUSD_TYPE_TEXCOORD3F;
char const* NUSD_TYPE_TEXCOORD3FARRAY;
char const* NUSD_TYPE_TEXCOORD3H;
char const* NUSD_TYPE_TEXCOORD3HARRAY;
char const* NUSD_TYPE_TIMECODE;
char const* NUSD_TYPE_TIMECODEARRAY;
char const* NUSD_TYPE_TOKEN;
char const* NUSD_TYPE_TOKENARRAY;
char const* NUSD_TYPE_UCHAR;
char const* NUSD_TYPE_UCHARARRAY;
char const* NUSD_TYPE_UINT;
char const* NUSD_TYPE_UINT64;
char const* NUSD_TYPE_UINT64ARRAY;
char const* NUSD_TYPE_UINTARRAY;
char const* NUSD_TYPE_VECTOR3D;
char const* NUSD_TYPE_VECTOR3DARRAY;
char const* NUSD_TYPE_VECTOR3F;
char const* NUSD_TYPE_VECTOR3FARRAY;
char const* NUSD_TYPE_VECTOR3H;
char const* NUSD_TYPE_VECTOR3HARRAY;

char const* NUSD_TYPE_RELATIONSHIP = "rel";

using TokenTypeNameMap = std::unordered_map<char const*, PXR_NS::SdfValueTypeName>;
TokenTypeNameMap TOKEN_TO_TYPENAME;

using namespace PXR_NS;

using StageMap = std::unordered_map<UsdStage*, UsdStageRefPtr>;
StageMap STAGES;

static void initialize_tokens() {
    std::lock_guard<std::mutex> lock(MTX_TOKEN_INIT);
    if (TOKENS_INITIALIZED == false) {
        NUSD_TYPE_ASSET = SdfValueTypeNames->Asset.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_ASSET] = SdfValueTypeNames->Asset;
        NUSD_TYPE_ASSETARRAY = SdfValueTypeNames->AssetArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_ASSETARRAY] = SdfValueTypeNames->AssetArray;
        NUSD_TYPE_BOOL = SdfValueTypeNames->Bool.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_BOOL] = SdfValueTypeNames->Bool;
        NUSD_TYPE_BOOLARRAY = SdfValueTypeNames->BoolArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_BOOLARRAY] = SdfValueTypeNames->BoolArray;
        NUSD_TYPE_COLOR3D = SdfValueTypeNames->Color3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3D] = SdfValueTypeNames->Color3d;
        NUSD_TYPE_COLOR3DARRAY = SdfValueTypeNames->Color3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3DARRAY] = SdfValueTypeNames->Color3dArray;
        NUSD_TYPE_COLOR3F = SdfValueTypeNames->Color3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3F] = SdfValueTypeNames->Color3f;
        NUSD_TYPE_COLOR3FARRAY = SdfValueTypeNames->Color3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3FARRAY] = SdfValueTypeNames->Color3fArray;
        NUSD_TYPE_COLOR3H = SdfValueTypeNames->Color3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3H] = SdfValueTypeNames->Color3h;
        NUSD_TYPE_COLOR3HARRAY = SdfValueTypeNames->Color3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3HARRAY] = SdfValueTypeNames->Color3hArray;
        NUSD_TYPE_COLOR4D = SdfValueTypeNames->Color4d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4D] = SdfValueTypeNames->Color4d;
        NUSD_TYPE_COLOR4DARRAY = SdfValueTypeNames->Color4dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4DARRAY] = SdfValueTypeNames->Color4dArray;
        NUSD_TYPE_COLOR4F = SdfValueTypeNames->Color4f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4F] = SdfValueTypeNames->Color4f;
        NUSD_TYPE_COLOR4FARRAY = SdfValueTypeNames->Color4fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4FARRAY] = SdfValueTypeNames->Color4fArray;
        NUSD_TYPE_COLOR4H = SdfValueTypeNames->Color4h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4H] = SdfValueTypeNames->Color4h;
        NUSD_TYPE_COLOR4HARRAY = SdfValueTypeNames->Color4hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4HARRAY] = SdfValueTypeNames->Color4hArray;
        NUSD_TYPE_DOUBLE = SdfValueTypeNames->Double.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE] = SdfValueTypeNames->Double;
        NUSD_TYPE_DOUBLEARRAY = SdfValueTypeNames->DoubleArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLEARRAY] = SdfValueTypeNames->DoubleArray;
        NUSD_TYPE_DOUBLE2 = SdfValueTypeNames->Double2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE2] = SdfValueTypeNames->Double2;
        NUSD_TYPE_DOUBLE2ARRAY = SdfValueTypeNames->Double2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE2ARRAY] = SdfValueTypeNames->Double2Array;
        NUSD_TYPE_DOUBLE3 = SdfValueTypeNames->Double3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE3] = SdfValueTypeNames->Double3;
        NUSD_TYPE_DOUBLE3ARRAY = SdfValueTypeNames->Double3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE3ARRAY] = SdfValueTypeNames->Double3Array;
        NUSD_TYPE_DOUBLE4 = SdfValueTypeNames->Double4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE4] = SdfValueTypeNames->Double4;
        NUSD_TYPE_DOUBLE4ARRAY = SdfValueTypeNames->Double4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE4ARRAY] = SdfValueTypeNames->Double4Array;
        NUSD_TYPE_FLOAT = SdfValueTypeNames->Float.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT] = SdfValueTypeNames->Float;
        NUSD_TYPE_FLOATARRAY = SdfValueTypeNames->FloatArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOATARRAY] = SdfValueTypeNames->FloatArray;
        NUSD_TYPE_FLOAT2 = SdfValueTypeNames->Float2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT2] = SdfValueTypeNames->Float2;
        NUSD_TYPE_FLOAT2ARRAY = SdfValueTypeNames->Float2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT2ARRAY] = SdfValueTypeNames->Float2Array;
        NUSD_TYPE_FLOAT3 = SdfValueTypeNames->Float3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT3] = SdfValueTypeNames->Float3;
        NUSD_TYPE_FLOAT3ARRAY = SdfValueTypeNames->Float3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT3ARRAY] = SdfValueTypeNames->Float3Array;
        NUSD_TYPE_FLOAT4 = SdfValueTypeNames->Float4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT4] = SdfValueTypeNames->Float4;
        NUSD_TYPE_FLOAT4ARRAY = SdfValueTypeNames->Float4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT4ARRAY] = SdfValueTypeNames->Float4Array;
        NUSD_TYPE_HALF = SdfValueTypeNames->Half.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF] = SdfValueTypeNames->Half;
        NUSD_TYPE_HALFARRAY = SdfValueTypeNames->HalfArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALFARRAY] = SdfValueTypeNames->HalfArray;
        NUSD_TYPE_HALF2 = SdfValueTypeNames->Half2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF2] = SdfValueTypeNames->Half2;
        NUSD_TYPE_HALF2ARRAY = SdfValueTypeNames->Half2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF2ARRAY] = SdfValueTypeNames->Half2Array;
        NUSD_TYPE_HALF3 = SdfValueTypeNames->Half3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF3] = SdfValueTypeNames->Half3;
        NUSD_TYPE_HALF3ARRAY = SdfValueTypeNames->Half3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF3ARRAY] = SdfValueTypeNames->Half3Array;
        NUSD_TYPE_HALF4 = SdfValueTypeNames->Half4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF4] = SdfValueTypeNames->Half4;
        NUSD_TYPE_HALF4ARRAY = SdfValueTypeNames->Half4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF4ARRAY] = SdfValueTypeNames->Half4Array;
        NUSD_TYPE_INT = SdfValueTypeNames->Int.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT] = SdfValueTypeNames->Int;
        NUSD_TYPE_INTARRAY = SdfValueTypeNames->IntArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INTARRAY] = SdfValueTypeNames->IntArray;
        NUSD_TYPE_INT2 = SdfValueTypeNames->Int2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT2] = SdfValueTypeNames->Int2;
        NUSD_TYPE_INT2ARRAY = SdfValueTypeNames->Int2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT2ARRAY] = SdfValueTypeNames->Int2Array;
        NUSD_TYPE_INT3 = SdfValueTypeNames->Int3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT3] = SdfValueTypeNames->Int3;
        NUSD_TYPE_INT3ARRAY = SdfValueTypeNames->Int3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT3ARRAY] = SdfValueTypeNames->Int3Array;
        NUSD_TYPE_INT4 = SdfValueTypeNames->Int4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT4] = SdfValueTypeNames->Int4;
        NUSD_TYPE_INT4ARRAY = SdfValueTypeNames->Int4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT4ARRAY] = SdfValueTypeNames->Int4Array;
        NUSD_TYPE_INT64 = SdfValueTypeNames->Int64.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT64] = SdfValueTypeNames->Int64;
        NUSD_TYPE_INT64ARRAY = SdfValueTypeNames->Int64Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT64ARRAY] = SdfValueTypeNames->Int64Array;
        NUSD_TYPE_MATRIX2D = SdfValueTypeNames->Matrix2d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX2D] = SdfValueTypeNames->Matrix2d;
        NUSD_TYPE_MATRIX2DARRAY = SdfValueTypeNames->Matrix2dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX2DARRAY] = SdfValueTypeNames->Matrix2dArray;
        NUSD_TYPE_MATRIX3D = SdfValueTypeNames->Matrix3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX3D] = SdfValueTypeNames->Matrix3d;
        NUSD_TYPE_MATRIX3DARRAY = SdfValueTypeNames->Matrix3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX3DARRAY] = SdfValueTypeNames->Matrix3dArray;
        NUSD_TYPE_MATRIX4D = SdfValueTypeNames->Matrix4d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX4D] = SdfValueTypeNames->Matrix4d;
        NUSD_TYPE_MATRIX4DARRAY = SdfValueTypeNames->Matrix4dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX4DARRAY] = SdfValueTypeNames->Matrix4dArray;
        NUSD_TYPE_NORMAL3D = SdfValueTypeNames->Normal3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3D] = SdfValueTypeNames->Normal3d;
        NUSD_TYPE_NORMAL3DARRAY = SdfValueTypeNames->Normal3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3DARRAY] = SdfValueTypeNames->Normal3dArray;
        NUSD_TYPE_NORMAL3F = SdfValueTypeNames->Normal3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3F] = SdfValueTypeNames->Normal3f;
        NUSD_TYPE_NORMAL3FARRAY = SdfValueTypeNames->Normal3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3FARRAY] = SdfValueTypeNames->Normal3fArray;
        NUSD_TYPE_NORMAL3H = SdfValueTypeNames->Normal3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3H] = SdfValueTypeNames->Normal3h;
        NUSD_TYPE_NORMAL3HARRAY = SdfValueTypeNames->Normal3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3HARRAY] = SdfValueTypeNames->Normal3hArray;
        NUSD_TYPE_POINT3D = SdfValueTypeNames->Point3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3D] = SdfValueTypeNames->Point3d;
        NUSD_TYPE_POINT3DARRAY = SdfValueTypeNames->Point3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3DARRAY] = SdfValueTypeNames->Point3dArray;
        NUSD_TYPE_POINT3F = SdfValueTypeNames->Point3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3F] = SdfValueTypeNames->Point3f;
        NUSD_TYPE_POINT3FARRAY = SdfValueTypeNames->Point3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3FARRAY] = SdfValueTypeNames->Point3fArray;
        NUSD_TYPE_POINT3H = SdfValueTypeNames->Point3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3H] = SdfValueTypeNames->Point3h;
        NUSD_TYPE_POINT3HARRAY = SdfValueTypeNames->Point3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3HARRAY] = SdfValueTypeNames->Point3hArray;
        NUSD_TYPE_QUATD = SdfValueTypeNames->Quatd.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATD] = SdfValueTypeNames->Quatd;
        NUSD_TYPE_QUATDARRAY = SdfValueTypeNames->QuatdArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATDARRAY] = SdfValueTypeNames->QuatdArray;
        NUSD_TYPE_QUATF = SdfValueTypeNames->Quatf.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATF] = SdfValueTypeNames->Quatf;
        NUSD_TYPE_QUATFARRAY = SdfValueTypeNames->QuatfArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATFARRAY] = SdfValueTypeNames->QuatfArray;
        NUSD_TYPE_QUATH = SdfValueTypeNames->Quath.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATH] = SdfValueTypeNames->Quath;
        NUSD_TYPE_QUATHARRAY = SdfValueTypeNames->QuathArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATHARRAY] = SdfValueTypeNames->QuathArray;
        NUSD_TYPE_TEXCOORD2D = SdfValueTypeNames->TexCoord2d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2D] = SdfValueTypeNames->TexCoord2d;
        NUSD_TYPE_TEXCOORD2DARRAY = SdfValueTypeNames->TexCoord2dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2DARRAY] = SdfValueTypeNames->TexCoord2dArray;
        NUSD_TYPE_TEXCOORD2F = SdfValueTypeNames->TexCoord2f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2F] = SdfValueTypeNames->TexCoord2f;
        NUSD_TYPE_TEXCOORD2FARRAY = SdfValueTypeNames->TexCoord2fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2FARRAY] = SdfValueTypeNames->TexCoord2fArray;
        NUSD_TYPE_TEXCOORD2H = SdfValueTypeNames->TexCoord2h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2H] = SdfValueTypeNames->TexCoord2h;
        NUSD_TYPE_TEXCOORD2HARRAY = SdfValueTypeNames->TexCoord2hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2HARRAY] = SdfValueTypeNames->TexCoord2hArray;
        NUSD_TYPE_TEXCOORD3D = SdfValueTypeNames->TexCoord3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3D] = SdfValueTypeNames->TexCoord3d;
        NUSD_TYPE_TEXCOORD3DARRAY = SdfValueTypeNames->TexCoord3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3DARRAY] = SdfValueTypeNames->TexCoord3dArray;
        NUSD_TYPE_TEXCOORD3F = SdfValueTypeNames->TexCoord3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3F] = SdfValueTypeNames->TexCoord3f;
        NUSD_TYPE_TEXCOORD3FARRAY = SdfValueTypeNames->TexCoord3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3FARRAY] = SdfValueTypeNames->TexCoord3fArray;
        NUSD_TYPE_TEXCOORD3H = SdfValueTypeNames->TexCoord3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3H] = SdfValueTypeNames->TexCoord3h;
        NUSD_TYPE_TEXCOORD3HARRAY = SdfValueTypeNames->TexCoord3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3HARRAY] = SdfValueTypeNames->TexCoord3hArray;
        NUSD_TYPE_TIMECODE = SdfValueTypeNames->TimeCode.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TIMECODE] = SdfValueTypeNames->TimeCode;
        NUSD_TYPE_TIMECODEARRAY = SdfValueTypeNames->TimeCodeArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TIMECODEARRAY] = SdfValueTypeNames->TimeCodeArray;
        NUSD_TYPE_TOKEN = SdfValueTypeNames->Token.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TOKEN] = SdfValueTypeNames->Token;
        NUSD_TYPE_TOKENARRAY = SdfValueTypeNames->TokenArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TOKENARRAY] = SdfValueTypeNames->TokenArray;
        NUSD_TYPE_UCHAR = SdfValueTypeNames->UChar.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UCHAR] = SdfValueTypeNames->UChar;
        NUSD_TYPE_UCHARARRAY = SdfValueTypeNames->UCharArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UCHARARRAY] = SdfValueTypeNames->UCharArray;
        NUSD_TYPE_UINT = SdfValueTypeNames->UInt.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINT] = SdfValueTypeNames->UInt;
        NUSD_TYPE_UINTARRAY = SdfValueTypeNames->UIntArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINTARRAY] = SdfValueTypeNames->UIntArray;
        NUSD_TYPE_UINT64 = SdfValueTypeNames->UInt64.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINT64] = SdfValueTypeNames->UInt64;
        NUSD_TYPE_UINT64ARRAY = SdfValueTypeNames->UInt64Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINT64ARRAY] = SdfValueTypeNames->UInt64Array;
        NUSD_TYPE_VECTOR3D = SdfValueTypeNames->Vector3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3D] = SdfValueTypeNames->Vector3d;
        NUSD_TYPE_VECTOR3DARRAY = SdfValueTypeNames->Vector3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3DARRAY] = SdfValueTypeNames->Vector3dArray;
        NUSD_TYPE_VECTOR3F = SdfValueTypeNames->Vector3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3F] = SdfValueTypeNames->Vector3f;
        NUSD_TYPE_VECTOR3FARRAY = SdfValueTypeNames->Vector3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3FARRAY] = SdfValueTypeNames->Vector3fArray;
        NUSD_TYPE_VECTOR3H = SdfValueTypeNames->Vector3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3H] = SdfValueTypeNames->Vector3h;
        NUSD_TYPE_VECTOR3HARRAY = SdfValueTypeNames->Vector3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3HARRAY] = SdfValueTypeNames->Vector3hArray;

        TOKENS_INITIALIZED = true;
    }
}

nusd_result_t nusd_stage_open(char const* filename, nusd_stage_t* stage) {
    initialize_tokens();

    UsdStageRefPtr _stage = UsdStage::Open(filename);
    if (!_stage) {
        return NUSD_RESULT_OPEN_STAGE_FAILED;
    }

    UsdStage* raw_ptr = TfTypeFunctions<UsdStageRefPtr>::GetRawPtr(_stage);
    STAGES.emplace(raw_ptr, std::move(_stage));
    *stage = reinterpret_cast<nusd_stage_t>(raw_ptr);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_create_new(char const* identifier, nusd_stage_t* stage) {
    initialize_tokens();

    UsdStageRefPtr _stage = UsdStage::CreateInMemory(identifier);

    if (!_stage) {
        *stage = nullptr;
        return NUSD_RESULT_CREATE_STAGE_FAILED;
    }

    UsdStage* raw_ptr = TfTypeFunctions<UsdStageRefPtr>::GetRawPtr(_stage);
    STAGES.emplace(raw_ptr, std::move(_stage));
    *stage = reinterpret_cast<nusd_stage_t>(raw_ptr);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_create_in_memory(char const* identifier, nusd_stage_t* stage) {
    initialize_tokens();

    UsdStageRefPtr _stage = UsdStage::CreateInMemory(identifier);

    if (!_stage) {
        *stage = nullptr;
        return NUSD_RESULT_CREATE_STAGE_FAILED;
    }

    UsdStage* raw_ptr = TfTypeFunctions<UsdStageRefPtr>::GetRawPtr(_stage);
    STAGES.emplace(raw_ptr, std::move(_stage));
    *stage = reinterpret_cast<nusd_stage_t>(raw_ptr);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_save(nusd_stage_t stage) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    _stage->Save();

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_save_as(nusd_stage_t stage, char const* filename) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    _stage->GetRootLayer()->Export(filename);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_destroy(nusd_stage_t stage) {
    StageMap::iterator it = STAGES.find(reinterpret_cast<UsdStage*>(stage));   
    if (it != STAGES.end()) {
        STAGES.erase(it);
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_define_prim(nusd_stage_t stage, char const* prim_path, char const* prim_type) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdPrim prim = _stage->DefinePrim(SdfPath(prim_path), TfToken(prim_type));
    if (!prim) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    return NUSD_RESULT_OK;
}

bool nusd_stage_path_is_valid_prim(nusd_stage_t stage, char const* prim_path) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));

    return bool(prim);
}

nusd_result_t nusd_stage_traverse(nusd_stage_t stage, nusd_prim_iterator_t* iterator) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdPrim pseudo_root = _stage->GetPseudoRoot();
    
    nusd_prim_iterator_s* it = new nusd_prim_iterator_s();
    it->range = UsdPrimRange(pseudo_root);
    it->current = it->range.begin();

    *iterator = std::move(it);

    return NUSD_RESULT_OK;
}

bool nusd_prim_iterator_next(nusd_prim_iterator_t iterator, char const** prim_path) {
    if (iterator->current == iterator->range.end()) {
        return false;
    }

    *prim_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_prim_iterator_is_done(nusd_prim_iterator_t iterator, bool* is_done) {
    *is_done = iterator->current == iterator->range.end();

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_iterator_destroy(nusd_prim_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_get_properties(nusd_stage_t stage, char const* prim_path, nusd_property_iterator_t* iterator) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));
    if (!prim) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    nusd_property_iterator_t it = new nusd_property_iterator_s();
    it->properties = prim.GetProperties();
    it->current = it->properties.begin();

    *iterator = it;

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_prim_create_property(nusd_stage_t stage, char const* prim_path, char const* property_name, nusd_type_t property_type) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));
    if (!prim) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    if (property_type == NUSD_TYPE_RELATIONSHIP) {
        UsdRelationship rel = prim.CreateRelationship(TfToken(property_name));
        if (!rel) {
            return NUSD_RESULT_CREATE_RELATIONSHIP_FAILED;
        } else {
            return NUSD_RESULT_OK;
        }

    } else {
        if (TOKEN_TO_TYPENAME.find(property_type) == TOKEN_TO_TYPENAME.end()) {
            return NUSD_RESULT_INVALID_PROPERTY_TYPE;
        }

        UsdAttribute attr = prim.CreateAttribute(TfToken(property_name), TOKEN_TO_TYPENAME[property_type]);
        if (!attr) {
            return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
        } else {
            return NUSD_RESULT_OK;
        }
    }
}

bool nusd_property_iterator_next(nusd_property_iterator_t iterator, char const** property_path, nusd_type_t* property_type) {
    if (iterator->current == iterator->properties.end()) {
        return false;
    }

    UsdProperty const& property = *iterator->current;
    if (property.Is<UsdAttribute>()) {
        UsdAttribute const& attr = property.As<UsdAttribute>();
        SdfValueTypeName type_name = attr.GetTypeName();
        *property_type = type_name.GetAsToken().GetText();
    } else {
        *property_type = NUSD_TYPE_RELATIONSHIP;
    }

    *property_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_property_iterator_destroy(nusd_property_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_get_attributes(nusd_stage_t stage, char const* prim_path, nusd_attribute_iterator_t* iterator) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));
    if (!prim) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    nusd_attribute_iterator_t it = new nusd_attribute_iterator_s();
    it->attributes = prim.GetAttributes();
    it->current = it->attributes.begin();

    *iterator = it;

    return NUSD_RESULT_OK;
}

bool nusd_attribute_iterator_next(nusd_attribute_iterator_t iterator, char const** attribute_path) {
    if (iterator->current == iterator->attributes.end()) {
        return false;
    }

    *attribute_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_attribute_iterator_destroy(nusd_attribute_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, char const** token) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKEN) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    TfToken tok;
    attr.Get(&tok);
    *token = tok.GetText();

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_token_array(nusd_stage_t stage, char const* attribute_path, nusd_token_array_t* token_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *token_array = new nusd_token_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKENARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*token_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_token_array_size(nusd_token_array_t token_array) {
    return token_array->value.size();
}

char const* nusd_token_array_index(nusd_token_array_t token_array, size_t index) {
    return token_array->value[index].GetText();
}

void nusd_token_array_destroy(nusd_token_array_t token_array) {
    delete token_array;
}

// float
nusd_result_t nusd_attribute_get_float(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float_array(nusd_stage_t stage, char const* attribute_path, nusd_float_array_t* float_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *float_array = new nusd_float_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOATARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_float_array_size(nusd_float_array_t float_array) {
    return float_array->value.size();
}

float* nusd_float_array_data(nusd_float_array_t float_array) {
    return float_array->value.data();
}

void nusd_float_array_destroy(nusd_float_array_t float_array) {
    delete float_array;
}

nusd_result_t nusd_attribute_get_float2(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT2 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD2F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2f*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float2_array(nusd_stage_t stage, char const* attribute_path, nusd_float2_array_t* float2_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *float2_array = new nusd_float2_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT2ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD2FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float2_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_float2_array_size(nusd_float2_array_t float2_array) {
    return float2_array->value.size();
}

float* nusd_float2_array_data(nusd_float2_array_t float2_array) {
    return reinterpret_cast<float*>(float2_array->value.data());
}

void nusd_float2_array_destroy(nusd_float2_array_t float2_array) {
    delete float2_array;
}

nusd_result_t nusd_attribute_get_float3(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT3 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD3F &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_VECTOR3F &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_POINT3F &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_NORMAL3F &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3F
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3f*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float3_array(nusd_stage_t stage, char const* attribute_path, nusd_float3_array_t* float3_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *float3_array = new nusd_float3_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT3ARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD3FARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_VECTOR3FARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_POINT3FARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_NORMAL3FARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3FARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float3_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_float3_array_size(nusd_float3_array_t float3_array) {
    return float3_array->value.size();
}

float* nusd_float3_array_data(nusd_float3_array_t float3_array) {
    return reinterpret_cast<float*>(float3_array->value.data());
}

void nusd_float3_array_destroy(nusd_float3_array_t float3_array) {
    delete float3_array;
}

nusd_result_t nusd_attribute_get_float4(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT4 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4F
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4f*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float4_array(nusd_stage_t stage, char const* attribute_path, nusd_float4_array_t* float4_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *float4_array = new nusd_float4_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT4ARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4FARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float4_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_float4_array_size(nusd_float4_array_t float4_array) {
    return float4_array->value.size();
}

float* nusd_float4_array_data(nusd_float4_array_t float4_array) {
    return reinterpret_cast<float*>(float4_array->value.data());
}

void nusd_float4_array_destroy(nusd_float4_array_t float4_array) {
    delete float4_array;
}


// double
nusd_result_t nusd_attribute_get_double(nusd_stage_t stage, char const* attribute_path, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double_array(nusd_stage_t stage, char const* attribute_path, nusd_double_array_t* double_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *double_array = new nusd_double_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLEARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_double_array_size(nusd_double_array_t double_array) {
    return double_array->value.size();
}

double* nusd_double_array_data(nusd_double_array_t double_array) {
    return double_array->value.data();
}

void nusd_double_array_destroy(nusd_double_array_t double_array) {
    delete double_array;
}

nusd_result_t nusd_attribute_get_double2(nusd_stage_t stage, char const* attribute_path, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE2 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD2D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2d*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double2_array(nusd_stage_t stage, char const* attribute_path, nusd_double2_array_t* double2_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *double2_array = new nusd_double2_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE2ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD2DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double2_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_double2_array_size(nusd_double2_array_t double2_array) {
    return double2_array->value.size();
}

double* nusd_double2_array_data(nusd_double2_array_t double2_array) {
    return reinterpret_cast<double*>(double2_array->value.data());
}

void nusd_double2_array_destroy(nusd_double2_array_t double2_array) {
    delete double2_array;
}

nusd_result_t nusd_attribute_get_double3(nusd_stage_t stage, char const* attribute_path, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE3 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD3D &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_VECTOR3D &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_POINT3D &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_NORMAL3D &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3D
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3d*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double3_array(nusd_stage_t stage, char const* attribute_path, nusd_double3_array_t* double3_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *double3_array = new nusd_double3_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE3ARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD3DARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_VECTOR3DARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_POINT3DARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_NORMAL3DARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3DARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double3_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_double3_array_size(nusd_double3_array_t double3_array) {
    return double3_array->value.size();
}

double* nusd_double3_array_data(nusd_double3_array_t double3_array) {
    return reinterpret_cast<double*>(double3_array->value.data());
}

void nusd_double3_array_destroy(nusd_double3_array_t double3_array) {
    delete double3_array;
}

nusd_result_t nusd_attribute_get_double4(nusd_stage_t stage, char const* attribute_path, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE4&&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4D
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4d*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double4_array(nusd_stage_t stage, char const* attribute_path, nusd_double4_array_t* double4_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *double4_array = new nusd_double4_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE4ARRAY  &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4DARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double4_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_double4_array_size(nusd_double4_array_t double4_array) {
    return double4_array->value.size();
}

double* nusd_double4_array_data(nusd_double4_array_t double4_array) {
    return reinterpret_cast<double*>(double4_array->value.data());
}

void nusd_double4_array_destroy(nusd_double4_array_t double4_array) {
    delete double4_array;
}


// int
nusd_result_t nusd_attribute_get_int(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int_array(nusd_stage_t stage, char const* attribute_path, nusd_int_array_t* int_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int_array = new nusd_int_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_int_array_size(nusd_int_array_t int_array) {
    return int_array->value.size();
}

int* nusd_int_array_data(nusd_int_array_t int_array) {
    return int_array->value.data();
}

void nusd_int_array_destroy(nusd_int_array_t int_array) {
    delete int_array;
}

nusd_result_t nusd_attribute_get_int2(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2i*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int2_array(nusd_stage_t stage, char const* attribute_path, nusd_int2_array_t* int2_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int2_array = new nusd_int2_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2ARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int2_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_int2_array_size(nusd_int2_array_t int2_array) {
    return int2_array->value.size();
}

int* nusd_int2_array_data(nusd_int2_array_t int2_array) {
    return reinterpret_cast<int*>(int2_array->value.data());
}

void nusd_int2_array_destroy(nusd_int2_array_t int2_array) {
    delete int2_array;
}

nusd_result_t nusd_attribute_get_int3(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3i*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int3_array(nusd_stage_t stage, char const* attribute_path, nusd_int3_array_t* int3_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int3_array = new nusd_int3_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3ARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int3_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_int3_array_size(nusd_int3_array_t int3_array) {
    return int3_array->value.size();
}

int* nusd_int3_array_data(nusd_int3_array_t int3_array) {
    return reinterpret_cast<int*>(int3_array->value.data());
}

void nusd_int3_array_destroy(nusd_int3_array_t int3_array) {
    delete int3_array;
}

nusd_result_t nusd_attribute_get_int4(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4i*>(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int4_array(nusd_stage_t stage, char const* attribute_path, nusd_int4_array_t* int4_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int4_array = new nusd_int4_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4ARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int4_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_int4_array_size(nusd_int4_array_t int4_array) {
    return int4_array->value.size();
}

int* nusd_int4_array_data(nusd_int4_array_t int4_array) {
    return reinterpret_cast<int*>(int4_array->value.data());
}

void nusd_int4_array_destroy(nusd_int4_array_t int4_array) {
    delete int4_array;
}


// bool
nusd_result_t nusd_attribute_get_bool(nusd_stage_t stage, char const* attribute_path, bool* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_BOOL) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_bool_array(nusd_stage_t stage, char const* attribute_path, nusd_bool_array_t* bool_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *bool_array = new nusd_bool_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_BOOLARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*bool_array)->value);

    return NUSD_RESULT_OK;
}

size_t nusd_bool_array_size(nusd_bool_array_t bool_array) {
    return bool_array->value.size();
}

bool* nusd_bool_array_data(nusd_bool_array_t bool_array) {
    return bool_array->value.data();
}

void nusd_bool_array_destroy(nusd_bool_array_t bool_array) {
    delete bool_array;
}



// relationships
nusd_result_t nusd_prim_get_relationships(nusd_stage_t stage, char const* prim_path, nusd_relationship_iterator_t* iterator) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));
    if (!prim) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    nusd_relationship_iterator_t it = new nusd_relationship_iterator_s();
    it->relationships = prim.GetRelationships();
    it->current = it->relationships.begin();

    *iterator = it;

    return NUSD_RESULT_OK;
}

bool nusd_relationship_iterator_next(nusd_relationship_iterator_t iterator, char const** relationship_path) {
    if (iterator->current == iterator->relationships.end()) {
        return false;
    }

    *relationship_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_relationship_iterator_destroy(nusd_relationship_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_property_get_type(nusd_stage_t stage, char const* property_path, nusd_type_t* property_type) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdProperty const& property = _stage->GetPropertyAtPath(SdfPath(property_path));

    if (!property) {
        return NUSD_RESULT_INVALID_PROPERTY_PATH;
    }

    if (property.Is<UsdAttribute>()) {
        UsdAttribute const& attr = property.As<UsdAttribute>();
        SdfValueTypeName type_name = attr.GetTypeName();
        *property_type = type_name.GetAsToken().GetText();
    } else {
        *property_type = NUSD_TYPE_RELATIONSHIP;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_relationship_get_targets(nusd_stage_t stage, char const* relationship_path, nusd_relationship_targets_iterator_t* targets, size_t* num_targets) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdRelationship rel = _stage->GetRelationshipAtPath(SdfPath(relationship_path));

    if (!rel) {
        return NUSD_RESULT_INVALID_RELATIONSHIP_PATH;
    }

    nusd_relationship_targets_iterator_s* it = new nusd_relationship_targets_iterator_s();
    rel.GetTargets(&it->paths);
    it->current = it->paths.begin();
    if (num_targets != nullptr) {
        *num_targets = it->paths.size();
    }

    *targets = it;

    return NUSD_RESULT_OK;
}

bool nusd_relationship_targets_iterator_next(nusd_relationship_targets_iterator_t iterator, char const** target_path) {
    if (iterator->current == iterator->paths.end()) {
        return false;
    }

    *target_path = iterator->current->GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_relationship_targets_iterator_destroy(nusd_relationship_targets_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

char const* nusd_path_get_name(char const* path) {
    return strstr(path, ".") + 1;
}

nusd_result_t nusd_attribute_set_float(nusd_stage_t stage, char const* attribute_path, float value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(value);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOATARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtFloatArray value(data, data+num_elements);

    attr.Set(std::move(value));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT2 &&
        attr_type != NUSD_TYPE_TEXCOORD2F
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(GfVec2f(value[0], value[1]));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float2_array(nusd_stage_t stage, char const* attribute_path, float* _data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT2ARRAY &&
        attr_type != NUSD_TYPE_TEXCOORD2FARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2f* data = reinterpret_cast<GfVec2f*>(_data);
    VtArray<GfVec2f> value(data, data+num_elements);

    attr.Set(std::move(value));

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT3 &&
        attr_type != NUSD_TYPE_COLOR3F &&
        attr_type != NUSD_TYPE_VECTOR3F &&
        attr_type != NUSD_TYPE_POINT3F &&
        attr_type != NUSD_TYPE_NORMAL3F &&
        attr_type != NUSD_TYPE_TEXCOORD3F
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(GfVec3f(value[0], value[1], value[2]));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float3_array(nusd_stage_t stage, char const* attribute_path, float* _data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT3ARRAY &&
        attr_type != NUSD_TYPE_COLOR3FARRAY &&
        attr_type != NUSD_TYPE_POINT3FARRAY &&
        attr_type != NUSD_TYPE_VECTOR3FARRAY &&
        attr_type != NUSD_TYPE_NORMAL3FARRAY &&
        attr_type != NUSD_TYPE_TEXCOORD3FARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3f* data = reinterpret_cast<GfVec3f*>(_data);
    VtArray<GfVec3f> value(data, data+num_elements);

    attr.Set(std::move(value));

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage, char const* attribute_path, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT4 &&
        attr_type != NUSD_TYPE_COLOR4F
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(GfVec4f(value[0], value[1], value[2], value[3]));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float4_array(nusd_stage_t stage, char const* attribute_path, float* _data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT4ARRAY &&
        attr_type != NUSD_TYPE_COLOR4FARRAY
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4f* data = reinterpret_cast<GfVec4f*>(_data);
    VtArray<GfVec4f> value(data, data+num_elements);

    attr.Set(std::move(value));

    return NUSD_RESULT_OK;
}

// Int setters
nusd_result_t nusd_attribute_set_int(nusd_stage_t stage, char const* attribute_path, int value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(value);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtArray<int> vt_array(data, data + num_elements);
    attr.Set(vt_array);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int2(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2i vec(value[0], value[1]);
    attr.Set(vec);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int2_array(nusd_stage_t stage, char const* attribute_path, int* _data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2i* data = reinterpret_cast<GfVec2i*>(_data);
    VtArray<GfVec2i> value(data, data + num_elements);
    attr.Set(std::move(value));
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int3(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3i vec(value[0], value[1], value[2]);
    attr.Set(vec);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int3_array(nusd_stage_t stage, char const* attribute_path, int* _data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3i* data = reinterpret_cast<GfVec3i*>(_data);
    VtArray<GfVec3i> value(data, data + num_elements);
    attr.Set(std::move(value));
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int4(nusd_stage_t stage, char const* attribute_path, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4i vec(value[0], value[1], value[2], value[3]);
    attr.Set(vec);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int4_array(nusd_stage_t stage, char const* attribute_path, int* _data, size_t num_elements) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4i* data = reinterpret_cast<GfVec4i*>(_data);
    VtArray<GfVec4i> value(data, data + num_elements);
    attr.Set(std::move(value));
    return NUSD_RESULT_OK;
}

}