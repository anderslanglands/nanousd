#include "nanousd.h"

#include <pxr/usd/sdf/assetPath.h>

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformable.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdShade/material.h>

#include <pxr/base/tf/refPtr.h>
#include <pxr/base/vt/value.h>
#include <pxr/base/vt/array.h>

#include <pxr/base/gf/colorSpace.h>
#include <pxr/base/gf/matrix2d.h>
#include <pxr/base/gf/matrix3d.h>
#include <pxr/base/gf/matrix4d.h>

#include <unordered_map>
#include <mutex>

#include <string.h>

#include <math.h>

#include <stdio.h>

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

struct nusd_token_array_iterator_s {
    PXR_NS::VtTokenArray tokens;
    PXR_NS::VtTokenArray::iterator current;
};

struct nusd_asset_path_s {
    PXR_NS::SdfAssetPath path;
};

struct nusd_asset_path_array_iterator_s {
    PXR_NS::VtArray<PXR_NS::SdfAssetPath> paths;
    PXR_NS::VtArray<PXR_NS::SdfAssetPath>::iterator current;
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
struct nusd_uint_array_s {
    PXR_NS::VtUIntArray value;
};
struct nusd_uint64_array_s {
    PXR_NS::VtUInt64Array value;
};
struct nusd_uchar_array_s {
    PXR_NS::VtUCharArray value;
};

struct nusd_int64_array_s {
    PXR_NS::VtArray<int64_t> value;
};

struct nusd_bool_array_s {
    PXR_NS::VtBoolArray value;
};

struct nusd_matrix2d_array_s {
    PXR_NS::VtArray<PXR_NS::GfMatrix2d> value;
};

struct nusd_matrix3d_array_s {
    PXR_NS::VtArray<PXR_NS::GfMatrix3d> value;
};

struct nusd_matrix4d_array_s {
    PXR_NS::VtArray<PXR_NS::GfMatrix4d> value;
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

char const* NUSD_COLORSPACE_SRGB;
char const* NUSD_COLORSPACE_LINEAR_AP1;
char const* NUSD_COLORSPACE_LINEAR_AP0;
char const* NUSD_COLORSPACE_SRGB_AP1;

using TokenTypeNameMap = std::unordered_map<char const*, PXR_NS::SdfValueTypeName>;
TokenTypeNameMap TOKEN_TO_TYPENAME;

using namespace PXR_NS;

using StageMap = std::unordered_map<UsdStage*, UsdStageRefPtr>;
StageMap STAGES;


float C_PI = 3.141592653589793f;

static float radians(float degrees) {
    return degrees * C_PI / 180.0f;
}

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

        NUSD_COLORSPACE_SRGB = "sRGB";
        NUSD_COLORSPACE_LINEAR_AP1 = GfColorSpaceNames->LinearAP1.GetText();
        NUSD_COLORSPACE_LINEAR_AP0 = GfColorSpaceNames->LinearAP0.GetText();
        NUSD_COLORSPACE_SRGB_AP1 = GfColorSpaceNames->SRGBAP1.GetText();

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

    UsdStageRefPtr _stage = UsdStage::CreateNew(identifier);

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

nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, double time_code, char const** token) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKEN) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    TfToken tok;
    attr.Get(&tok, time_code);
    *token = tok.GetText();

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_token_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_token_array_iterator_t* token_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *token_array = new nusd_token_array_iterator_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKENARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*token_array)->tokens, time_code);
    (*token_array)->current = (*token_array)->tokens.begin();

    return NUSD_RESULT_OK;
}

bool nusd_token_array_iterator_next(nusd_token_array_iterator_t iterator, char const** token) {
    if (iterator->current == iterator->tokens.end()) {
        return false;
    }

    *token = iterator->current->GetText();
    iterator->current++;

    return true;
}

size_t nusd_token_array_iterator_size(nusd_token_array_iterator_t iterator) {
    return iterator->tokens.size();
}

nusd_result_t nusd_token_array_iterator_destroy(nusd_token_array_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_asset(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_asset_path_t* asset_path) {
    if (stage == nullptr || attribute_path == nullptr || asset_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_ASSET) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    *asset_path = new nusd_asset_path_s();
    attr.Get(&(*asset_path)->path, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_asset_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_asset_path_array_iterator_t* asset_path_array) {
    if (stage == nullptr || attribute_path == nullptr || asset_path_array == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *asset_path_array = new nusd_asset_path_array_iterator_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_ASSETARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*asset_path_array)->paths, time_code);
    (*asset_path_array)->current = (*asset_path_array)->paths.begin();

    return NUSD_RESULT_OK;
}

// float
nusd_result_t nusd_attribute_get_float(nusd_stage_t stage, char const* attribute_path, double time_code, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float_array_t* float_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *float_array = new nusd_float_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOATARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_float2(nusd_stage_t stage, char const* attribute_path, double time_code, float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT2 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD2F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2f*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float2_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float2_array_t* float2_array) {
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

    attr.Get(&(*float2_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_float3(nusd_stage_t stage, char const* attribute_path, double time_code, float* value) {
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

    attr.Get(reinterpret_cast<GfVec3f*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float3_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float3_array_t* float3_array) {
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

    attr.Get(&(*float3_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_float4(nusd_stage_t stage, char const* attribute_path, double time_code, float* value) {
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

    attr.Get(reinterpret_cast<GfVec4f*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float4_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float4_array_t* float4_array) {
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

    attr.Get(&(*float4_array)->value, time_code);

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
nusd_result_t nusd_attribute_get_double(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double_array_t* double_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *double_array = new nusd_double_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLEARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_double2(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE2 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TEXCOORD2D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2d*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double2_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double2_array_t* double2_array) {
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

    attr.Get(&(*double2_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_double3(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
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

    attr.Get(reinterpret_cast<GfVec3d*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double3_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double3_array_t* double3_array) {
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

    attr.Get(&(*double3_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_double4(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
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

    attr.Get(reinterpret_cast<GfVec4d*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double4_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double4_array_t* double4_array) {
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

    attr.Get(&(*double4_array)->value, time_code);

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
nusd_result_t nusd_attribute_get_int(nusd_stage_t stage, char const* attribute_path, double time_code, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int_array_t* int_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int_array = new nusd_int_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_int2(nusd_stage_t stage, char const* attribute_path, double time_code, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2i*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int2_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int2_array_t* int2_array) {
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

    attr.Get(&(*int2_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_int3(nusd_stage_t stage, char const* attribute_path, double time_code, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3i*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int3_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int3_array_t* int3_array) {
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

    attr.Get(&(*int3_array)->value, time_code);

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

nusd_result_t nusd_attribute_get_int4(nusd_stage_t stage, char const* attribute_path, double time_code, int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4
    ) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4i*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int4_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int4_array_t* int4_array) {
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

    attr.Get(&(*int4_array)->value, time_code);

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
nusd_result_t nusd_attribute_get_bool(nusd_stage_t stage, char const* attribute_path, double time_code, bool* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_BOOL) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_bool_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_bool_array_t* bool_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *bool_array = new nusd_bool_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_BOOLARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*bool_array)->value, time_code);

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

// Bool setters
nusd_result_t nusd_attribute_set_bool(nusd_stage_t stage, char const* attribute_path, bool value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_BOOL) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_bool_array(nusd_stage_t stage, char const* attribute_path, bool* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_BOOLARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    VtArray<bool> vt_array(data, data + num_elements);
    attr.Set(vt_array, time_code);
    return NUSD_RESULT_OK;
}

// matrix2d getters
nusd_result_t nusd_attribute_get_matrix2d(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX2D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfMatrix2d matrix;
    attr.Get(&matrix, time_code);
    
    // Copy matrix data in row-major order
    const double* data = matrix.GetArray();
    for (int i = 0; i < 4; i++) {
        value[i] = data[i];
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_matrix2d_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_matrix2d_array_t* matrix2d_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *matrix2d_array = new nusd_matrix2d_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX2DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&((*matrix2d_array)->value), time_code);

    return NUSD_RESULT_OK;
}

size_t nusd_matrix2d_array_size(nusd_matrix2d_array_t matrix2d_array) {
    return matrix2d_array->value.size();
}

double* nusd_matrix2d_array_data(nusd_matrix2d_array_t matrix2d_array) {
    return reinterpret_cast<double*>(matrix2d_array->value.data());
}

void nusd_matrix2d_array_destroy(nusd_matrix2d_array_t matrix2d_array) {
    delete matrix2d_array;
}

// matrix3d getters
nusd_result_t nusd_attribute_get_matrix3d(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX3D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfMatrix3d matrix;
    attr.Get(&matrix, time_code);
    
    // Copy matrix data in row-major order
    const double* data = matrix.GetArray();
    for (int i = 0; i < 9; i++) {
        value[i] = data[i];
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_matrix3d_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_matrix3d_array_t* matrix3d_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *matrix3d_array = new nusd_matrix3d_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX3DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&((*matrix3d_array)->value), time_code);

    return NUSD_RESULT_OK;
}

size_t nusd_matrix3d_array_size(nusd_matrix3d_array_t matrix3d_array) {
    return matrix3d_array->value.size();
}

double* nusd_matrix3d_array_data(nusd_matrix3d_array_t matrix3d_array) {
    return reinterpret_cast<double*>(matrix3d_array->value.data());
}

void nusd_matrix3d_array_destroy(nusd_matrix3d_array_t matrix3d_array) {
    delete matrix3d_array;
}

// matrix4d getters
nusd_result_t nusd_attribute_get_matrix4d(nusd_stage_t stage, char const* attribute_path, double time_code, double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX4D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfMatrix4d matrix;
    attr.Get(&matrix, time_code);
    
    // Copy matrix data in row-major order
    const double* data = matrix.GetArray();
    for (int i = 0; i < 16; i++) {
        value[i] = data[i];
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_matrix4d_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_matrix4d_array_t* matrix4d_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *matrix4d_array = new nusd_matrix4d_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX4DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&((*matrix4d_array)->value), time_code);

    return NUSD_RESULT_OK;
}

size_t nusd_matrix4d_array_size(nusd_matrix4d_array_t matrix4d_array) {
    return matrix4d_array->value.size();
}

double* nusd_matrix4d_array_data(nusd_matrix4d_array_t matrix4d_array) {
    return reinterpret_cast<double*>(matrix4d_array->value.data());
}

void nusd_matrix4d_array_destroy(nusd_matrix4d_array_t matrix4d_array) {
    delete matrix4d_array;
}

// matrix2d setters
nusd_result_t nusd_attribute_set_matrix2d(nusd_stage_t stage, char const* attribute_path, double* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX2D) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    GfMatrix2d matrix(value[0], value[1], value[2], value[3]);
    attr.Set(matrix, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_matrix2d_array(nusd_stage_t stage, char const* attribute_path, double* _data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX2DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    
    GfMatrix2d* data = reinterpret_cast<GfMatrix2d*>(_data);
    VtArray<GfMatrix2d> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

// matrix3d setters
nusd_result_t nusd_attribute_set_matrix3d(nusd_stage_t stage, char const* attribute_path, double* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX3D) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    GfMatrix3d matrix(value[0], value[1], value[2], 
                      value[3], value[4], value[5], 
                      value[6], value[7], value[8]);
    attr.Set(matrix, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_matrix3d_array(nusd_stage_t stage, char const* attribute_path, double* _data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX3DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    
    GfMatrix3d* data = reinterpret_cast<GfMatrix3d*>(_data);
    VtArray<GfMatrix3d> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

// matrix4d setters
nusd_result_t nusd_attribute_set_matrix4d(nusd_stage_t stage, char const* attribute_path, double* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX4D) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    GfMatrix4d matrix(value[0], value[1], value[2], value[3],
                      value[4], value[5], value[6], value[7],
                      value[8], value[9], value[10], value[11],
                      value[12], value[13], value[14], value[15]);
    attr.Set(matrix, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_matrix4d_array(nusd_stage_t stage, char const* attribute_path, double* _data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX4DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    
    GfMatrix4d* data = reinterpret_cast<GfMatrix4d*>(_data);
    VtArray<GfMatrix4d> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
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

char const* nusd_asset_path_get_asset_path(nusd_asset_path_t asset_path) {
    if (!asset_path) {
        return nullptr;
    }
    
    return asset_path->path.GetAssetPath().c_str();
}

void nusd_asset_path_destroy(nusd_asset_path_t asset_path) {
    if (asset_path) {
        delete asset_path;
    }
}

bool nusd_asset_path_array_iterator_next(nusd_asset_path_array_iterator_t asset_paths, char const** asset_path) {
    if (!asset_paths || !asset_path) {
        return false;
    }
    
    if (asset_paths->current == asset_paths->paths.end()) {
        return false;
    }
    
    *asset_path = asset_paths->current->GetAssetPath().c_str();
    
    ++asset_paths->current;
    return true;
}

size_t nusd_asset_path_array_iterator_size(nusd_asset_path_array_iterator_t iterator) {
    if (!iterator) {
        return 0;
    }
    
    return iterator->paths.size();
}

nusd_result_t nusd_asset_path_array_iterator_destroy(nusd_asset_path_array_iterator_t asset_paths) {
    if (asset_paths) {
        delete asset_paths;
    }
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float(nusd_stage_t stage, char const* attribute_path, float value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOATARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtFloatArray value(data, data+num_elements);

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage, char const* attribute_path, float* value, double time_code) {
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

    attr.Set(GfVec2f(value[0], value[1]), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float2_array(nusd_stage_t stage, char const* attribute_path, float* _data, size_t num_elements, double time_code) {
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

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage, char const* attribute_path, float* value, double time_code) {
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

    attr.Set(GfVec3f(value[0], value[1], value[2]), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float3_array(nusd_stage_t stage, char const* attribute_path, float* _data, size_t num_elements, double time_code) {
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

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage, char const* attribute_path, float* value, double time_code) {
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

    attr.Set(GfVec4f(value[0], value[1], value[2], value[3]), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float4_array(nusd_stage_t stage, char const* attribute_path, float* _data, size_t num_elements, double time_code) {
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

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}

// Int setters
nusd_result_t nusd_attribute_set_int(nusd_stage_t stage, char const* attribute_path, int value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtArray<int> vt_array(data, data + num_elements);
    attr.Set(vt_array, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int2(nusd_stage_t stage, char const* attribute_path, int* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2i vec(value[0], value[1]);
    attr.Set(vec, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int2_array(nusd_stage_t stage, char const* attribute_path, int* _data, size_t num_elements, double time_code) {
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
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int3(nusd_stage_t stage, char const* attribute_path, int* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3i vec(value[0], value[1], value[2]);
    attr.Set(vec, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int3_array(nusd_stage_t stage, char const* attribute_path, int* _data, size_t num_elements, double time_code) {
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
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int4(nusd_stage_t stage, char const* attribute_path, int* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4i vec(value[0], value[1], value[2], value[3]);
    attr.Set(vec, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int4_array(nusd_stage_t stage, char const* attribute_path, int* _data, size_t num_elements, double time_code) {
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
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

// Int64 getters
nusd_result_t nusd_attribute_get_int64(nusd_stage_t stage, char const* attribute_path, double time_code, int64_t* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT64) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int64_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int64_array_t* int64_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *int64_array = new nusd_int64_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT64ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int64_array)->value, time_code);

    return NUSD_RESULT_OK;
}

size_t nusd_int64_array_size(nusd_int64_array_t int64_array) {
    return int64_array->value.size();
}

int64_t* nusd_int64_array_data(nusd_int64_array_t int64_array) {
    return int64_array->value.data();
}

void nusd_int64_array_destroy(nusd_int64_array_t int64_array) {
    delete int64_array;
}

// Unsigned integer getters
nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, double time_code, unsigned int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_uint_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_uint_array_t* uint_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *uint_array = new nusd_uint_array_s();
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(&(*uint_array)->value, time_code);
    return NUSD_RESULT_OK;
}

size_t nusd_uint_array_size(nusd_uint_array_t uint_array) {
    return uint_array->value.size();
}

unsigned int* nusd_uint_array_data(nusd_uint_array_t uint_array) {
    return uint_array->value.data();
}

void nusd_uint_array_destroy(nusd_uint_array_t uint_array) {
    delete uint_array;
}

nusd_result_t nusd_attribute_get_uint64(nusd_stage_t stage, char const* attribute_path, double time_code, uint64_t* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT64) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_uint64_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_uint64_array_t* uint64_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *uint64_array = new nusd_uint64_array_s();
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT64ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(&(*uint64_array)->value, time_code);
    return NUSD_RESULT_OK;
}

size_t nusd_uint64_array_size(nusd_uint64_array_t uint64_array) {
    return uint64_array->value.size();
}

uint64_t* nusd_uint64_array_data(nusd_uint64_array_t uint64_array) {
    return uint64_array->value.data();
}

void nusd_uint64_array_destroy(nusd_uint64_array_t uint64_array) {
    delete uint64_array;
}

nusd_result_t nusd_attribute_get_uchar(nusd_stage_t stage, char const* attribute_path, double time_code, unsigned char* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UCHAR) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_uchar_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_uchar_array_t* uchar_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    
    *uchar_array = new nusd_uchar_array_s();
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UCHARARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Get(&(*uchar_array)->value, time_code);
    return NUSD_RESULT_OK;
}

size_t nusd_uchar_array_size(nusd_uchar_array_t uchar_array) {
    return uchar_array->value.size();
}

unsigned char* nusd_uchar_array_data(nusd_uchar_array_t uchar_array) {
    return uchar_array->value.data();
}

void nusd_uchar_array_destroy(nusd_uchar_array_t uchar_array) {
    delete uchar_array;
}

// Int64 setters
nusd_result_t nusd_attribute_set_int64(nusd_stage_t stage, char const* attribute_path, int64_t value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT64) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int64_array(nusd_stage_t stage, char const* attribute_path, int64_t* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT64ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtArray<int64_t> vt_array(data, data + num_elements);
    attr.Set(vt_array, time_code);
    return NUSD_RESULT_OK;
}

// Unsigned integer setters
nusd_result_t nusd_attribute_set_uint(nusd_stage_t stage, char const* attribute_path, unsigned int value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_uint_array(nusd_stage_t stage, char const* attribute_path, unsigned int* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINTARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    VtArray<unsigned int> vt_array(data, data + num_elements);
    attr.Set(vt_array, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_uint64(nusd_stage_t stage, char const* attribute_path, uint64_t value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT64) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_uint64_array(nusd_stage_t stage, char const* attribute_path, uint64_t* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UINT64ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    VtArray<uint64_t> vt_array(data, data + num_elements);
    attr.Set(vt_array, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_uchar(nusd_stage_t stage, char const* attribute_path, unsigned char value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UCHAR) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_uchar_array(nusd_stage_t stage, char const* attribute_path, unsigned char* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_UCHARARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    VtArray<unsigned char> vt_array(data, data + num_elements);
    attr.Set(vt_array, time_code);
    return NUSD_RESULT_OK;
}

// Double setters
nusd_result_t nusd_attribute_set_double(nusd_stage_t stage, char const* attribute_path, double value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(value, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLEARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtArray<double> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double2(nusd_stage_t stage, char const* attribute_path, double* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE2) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2d vec(value[0], value[1]);
    attr.Set(vec, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double2_array(nusd_stage_t stage, char const* attribute_path, double* _data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE2ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2d* data = reinterpret_cast<GfVec2d*>(_data);
    VtArray<GfVec2d> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double3(nusd_stage_t stage, char const* attribute_path, double* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE3) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3d vec(value[0], value[1], value[2]);
    attr.Set(vec, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double3_array(nusd_stage_t stage, char const* attribute_path, double* _data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE3ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3d* data = reinterpret_cast<GfVec3d*>(_data);
    VtArray<GfVec3d> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double4(nusd_stage_t stage, char const* attribute_path, double* value, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE4) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4d vec(value[0], value[1], value[2], value[3]);
    attr.Set(vec, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_double4_array(nusd_stage_t stage, char const* attribute_path, double* _data, size_t num_elements, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE4ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4d* data = reinterpret_cast<GfVec4d*>(_data);
    VtArray<GfVec4d> value(data, data + num_elements);
    attr.Set(std::move(value), time_code);
    return NUSD_RESULT_OK;
}


nusd_result_t nusd_camera_define(nusd_stage_t stage, char const* camera_path) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera = UsdGeomCamera::Define(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_set_transform(nusd_stage_t stage, char const* xformable_path, double* local_to_parent_matrix, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomXformable xformable = UsdGeomXformable::Get(UsdStageWeakPtr(_stage), SdfPath(xformable_path));
    if (!xformable) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    if (local_to_parent_matrix) {
        UsdGeomXformOp op = xformable.AddTransformOp();
        op.Set(*reinterpret_cast<GfMatrix4d*>(local_to_parent_matrix), time_code);
    } else {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_camera_set_fov_w(nusd_stage_t stage, char const* camera_path, float fov_w, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera = UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    float w;
    camera.GetHorizontalApertureAttr().Get(&w);
    float f = w / (2.0f * tanf(radians(fov_w) / 2.0f));

    camera.GetFocalLengthAttr().Set(f, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_camera_set_exposure(nusd_stage_t stage, char const* camera_path, float iso, float time, float f_stop, float compensation, float responsivity, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera = UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    camera.GetExposureIsoAttr().Set(iso, time_code);
    camera.GetExposureTimeAttr().Set(time, time_code);
    camera.GetExposureFStopAttr().Set(f_stop, time_code);
    camera.GetExposureAttr().Set(compensation, time_code);
    camera.GetExposureResponsivityAttr().Set(responsivity, time_code);

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_camera_set_clipping_range(nusd_stage_t stage, char const* camera_path, float near, float far, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera = UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    camera.GetClippingRangeAttr().Set(GfVec2f(near, far), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_compute_local_to_world_transform(nusd_stage_t stage, char const* xformable_path, double time_code, double* transform) {
    if (stage == nullptr || xformable_path == nullptr || transform == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomXformable xformable = UsdGeomXformable::Get(UsdStageWeakPtr(_stage), SdfPath(xformable_path));
    if (!xformable) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    GfMatrix4d matrix = xformable.ComputeLocalToWorldTransform(time_code);
    memcpy(transform, matrix.data(), sizeof(double) * 16);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_camera_set_aperture(nusd_stage_t stage, char const* camera_path, float width, float height, double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera = UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    camera.GetHorizontalApertureAttr().Set(width, time_code);
    camera.GetVerticalApertureAttr().Set(height, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_material_define(nusd_stage_t stage, char const* material_path) {
    if (stage == nullptr || material_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdShadeMaterial material = UsdShadeMaterial::Define(UsdStageWeakPtr(_stage), SdfPath(material_path));
    if (!material) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_define(nusd_stage_t stage, char const* shader_path, char const* shader_id) {
    if (stage == nullptr || shader_path == nullptr || shader_id == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdShadeShader shader = UsdShadeShader::Define(UsdStageWeakPtr(_stage), SdfPath(shader_path));
    if (!shader) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    shader.SetShaderId(TfToken(shader_id));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_create_input(nusd_stage_t stage, char const* shader_path, char const* input_name, nusd_type_t input_type) {
    if (stage == nullptr || shader_path == nullptr || input_name == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    if (input_type == NUSD_TYPE_RELATIONSHIP) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeShader shader = UsdShadeShader(_stage->GetPrimAtPath(SdfPath(shader_path)));
    if (!shader) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeInput input = shader.CreateInput(TfToken(input_name), TOKEN_TO_TYPENAME[input_type]);
    if (!input) {
        return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_create_output(nusd_stage_t stage, char const* shader_path, char const* output_name, nusd_type_t output_type) {
    if (stage == nullptr || shader_path == nullptr || output_name == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    if (output_type == NUSD_TYPE_RELATIONSHIP) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeShader shader = UsdShadeShader(_stage->GetPrimAtPath(SdfPath(shader_path)));
    if (!shader) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeOutput output = shader.CreateOutput(TfToken(output_name), TOKEN_TO_TYPENAME[output_type]);
    if (!output) {
        return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_connect(nusd_stage_t stage, char const* source_output_path, char const* destination_input_path) {
    if (stage == nullptr || source_output_path== nullptr || destination_input_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeOutput source = UsdShadeOutput(_stage->GetAttributeAtPath(SdfPath(source_output_path)));
    UsdShadeInput destination = UsdShadeInput(_stage->GetAttributeAtPath(SdfPath(destination_input_path)));
    if (!source || !destination) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (!destination.ConnectToSource(SdfPath(source_output_path))) {
        return NUSD_RESULT_CONNECTION_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_token(nusd_stage_t stage, char const* attribute_path, char const* value, double time_code) {
    if (stage == nullptr || attribute_path== nullptr || value == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKEN) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Set(TfToken(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_token_array(nusd_stage_t stage, char const* attribute_path, char const** value, size_t num_elements, double time_code) {
    if (stage == nullptr || attribute_path== nullptr || value == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_TOKENARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtTokenArray arr;
    for (size_t i = 0; i < num_elements; ++i) {
        arr.push_back(TfToken(value[i]));
    }

    attr.Set(arr, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_asset(nusd_stage_t stage, char const* attribute_path, char const* value, double time_code) {
    if (stage == nullptr || attribute_path== nullptr || value == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_ASSET) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    attr.Set(SdfAssetPath(value), time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_asset_array(nusd_stage_t stage, char const* attribute_path, char const** value, size_t num_elements, double time_code) {
    if (stage == nullptr || attribute_path== nullptr || value == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_ASSETARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtArray<SdfAssetPath> arr;
    for (size_t i = 0; i < num_elements; ++i) {
        arr.push_back(SdfAssetPath(value[i]));
    }

    attr.Set(arr, time_code);
    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_color_space(nusd_stage_t stage, char const* attribute_path, nusd_colorspace_t color_space) {
    if (stage == nullptr || attribute_path== nullptr || color_space == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    attr.SetColorSpace(TfToken(color_space));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_color_space(nusd_stage_t stage, char const* attribute_path, nusd_colorspace_t* color_space) {
    if (stage == nullptr || attribute_path== nullptr || color_space == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    *color_space = attr.GetColorSpace().GetText();

    return NUSD_RESULT_OK;
}

}