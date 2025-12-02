#include "nanousd.h"

#include <pxr/usd/sdf/assetPath.h>

#include <pxr/usd/sdf/types.h>

#include <pxr/usd/usd/property.h>

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/usd/usdGeom/xformable.h>

#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>

#include <pxr/base/tf/refPtr.h>
#include <pxr/base/vt/array.h>
#include <pxr/base/vt/value.h>

#include <pxr/base/gf/colorSpace.h>
#include <pxr/base/gf/matrix2d.h>
#include <pxr/base/gf/matrix3d.h>
#include <pxr/base/gf/matrix4d.h>

#include <mutex>
#include <unordered_map>

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

double NUSD_TIMECODE_DEFAULT = NAN;

using TokenTypeNameMap =
    std::unordered_map<char const*, PXR_NS::SdfValueTypeName>;
TokenTypeNameMap TOKEN_TO_TYPENAME;

using namespace PXR_NS;

using StageMap = std::unordered_map<UsdStage*, UsdStageRefPtr>;
StageMap STAGES;

float C_PI = 3.141592653589793f;

static float radians(float degrees) { return degrees * C_PI / 180.0f; }

static void initialize_tokens() {
    std::lock_guard<std::mutex> lock(MTX_TOKEN_INIT);
    if (TOKENS_INITIALIZED == false) {
        NUSD_TYPE_ASSET = SdfValueTypeNames->Asset.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_ASSET] = SdfValueTypeNames->Asset;
        NUSD_TYPE_ASSETARRAY =
            SdfValueTypeNames->AssetArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_ASSETARRAY] = SdfValueTypeNames->AssetArray;
        NUSD_TYPE_BOOL = SdfValueTypeNames->Bool.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_BOOL] = SdfValueTypeNames->Bool;
        NUSD_TYPE_BOOLARRAY =
            SdfValueTypeNames->BoolArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_BOOLARRAY] = SdfValueTypeNames->BoolArray;
        NUSD_TYPE_COLOR3D = SdfValueTypeNames->Color3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3D] = SdfValueTypeNames->Color3d;
        NUSD_TYPE_COLOR3DARRAY =
            SdfValueTypeNames->Color3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3DARRAY] =
            SdfValueTypeNames->Color3dArray;
        NUSD_TYPE_COLOR3F = SdfValueTypeNames->Color3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3F] = SdfValueTypeNames->Color3f;
        NUSD_TYPE_COLOR3FARRAY =
            SdfValueTypeNames->Color3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3FARRAY] =
            SdfValueTypeNames->Color3fArray;
        NUSD_TYPE_COLOR3H = SdfValueTypeNames->Color3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3H] = SdfValueTypeNames->Color3h;
        NUSD_TYPE_COLOR3HARRAY =
            SdfValueTypeNames->Color3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR3HARRAY] =
            SdfValueTypeNames->Color3hArray;
        NUSD_TYPE_COLOR4D = SdfValueTypeNames->Color4d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4D] = SdfValueTypeNames->Color4d;
        NUSD_TYPE_COLOR4DARRAY =
            SdfValueTypeNames->Color4dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4DARRAY] =
            SdfValueTypeNames->Color4dArray;
        NUSD_TYPE_COLOR4F = SdfValueTypeNames->Color4f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4F] = SdfValueTypeNames->Color4f;
        NUSD_TYPE_COLOR4FARRAY =
            SdfValueTypeNames->Color4fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4FARRAY] =
            SdfValueTypeNames->Color4fArray;
        NUSD_TYPE_COLOR4H = SdfValueTypeNames->Color4h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4H] = SdfValueTypeNames->Color4h;
        NUSD_TYPE_COLOR4HARRAY =
            SdfValueTypeNames->Color4hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_COLOR4HARRAY] =
            SdfValueTypeNames->Color4hArray;
        NUSD_TYPE_DOUBLE = SdfValueTypeNames->Double.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE] = SdfValueTypeNames->Double;
        NUSD_TYPE_DOUBLEARRAY =
            SdfValueTypeNames->DoubleArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLEARRAY] =
            SdfValueTypeNames->DoubleArray;
        NUSD_TYPE_DOUBLE2 = SdfValueTypeNames->Double2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE2] = SdfValueTypeNames->Double2;
        NUSD_TYPE_DOUBLE2ARRAY =
            SdfValueTypeNames->Double2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE2ARRAY] =
            SdfValueTypeNames->Double2Array;
        NUSD_TYPE_DOUBLE3 = SdfValueTypeNames->Double3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE3] = SdfValueTypeNames->Double3;
        NUSD_TYPE_DOUBLE3ARRAY =
            SdfValueTypeNames->Double3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE3ARRAY] =
            SdfValueTypeNames->Double3Array;
        NUSD_TYPE_DOUBLE4 = SdfValueTypeNames->Double4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE4] = SdfValueTypeNames->Double4;
        NUSD_TYPE_DOUBLE4ARRAY =
            SdfValueTypeNames->Double4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_DOUBLE4ARRAY] =
            SdfValueTypeNames->Double4Array;
        NUSD_TYPE_FLOAT = SdfValueTypeNames->Float.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT] = SdfValueTypeNames->Float;
        NUSD_TYPE_FLOATARRAY =
            SdfValueTypeNames->FloatArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOATARRAY] = SdfValueTypeNames->FloatArray;
        NUSD_TYPE_FLOAT2 = SdfValueTypeNames->Float2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT2] = SdfValueTypeNames->Float2;
        NUSD_TYPE_FLOAT2ARRAY =
            SdfValueTypeNames->Float2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT2ARRAY] =
            SdfValueTypeNames->Float2Array;
        NUSD_TYPE_FLOAT3 = SdfValueTypeNames->Float3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT3] = SdfValueTypeNames->Float3;
        NUSD_TYPE_FLOAT3ARRAY =
            SdfValueTypeNames->Float3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT3ARRAY] =
            SdfValueTypeNames->Float3Array;
        NUSD_TYPE_FLOAT4 = SdfValueTypeNames->Float4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT4] = SdfValueTypeNames->Float4;
        NUSD_TYPE_FLOAT4ARRAY =
            SdfValueTypeNames->Float4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_FLOAT4ARRAY] =
            SdfValueTypeNames->Float4Array;
        NUSD_TYPE_HALF = SdfValueTypeNames->Half.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF] = SdfValueTypeNames->Half;
        NUSD_TYPE_HALFARRAY =
            SdfValueTypeNames->HalfArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALFARRAY] = SdfValueTypeNames->HalfArray;
        NUSD_TYPE_HALF2 = SdfValueTypeNames->Half2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF2] = SdfValueTypeNames->Half2;
        NUSD_TYPE_HALF2ARRAY =
            SdfValueTypeNames->Half2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF2ARRAY] = SdfValueTypeNames->Half2Array;
        NUSD_TYPE_HALF3 = SdfValueTypeNames->Half3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF3] = SdfValueTypeNames->Half3;
        NUSD_TYPE_HALF3ARRAY =
            SdfValueTypeNames->Half3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF3ARRAY] = SdfValueTypeNames->Half3Array;
        NUSD_TYPE_HALF4 = SdfValueTypeNames->Half4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF4] = SdfValueTypeNames->Half4;
        NUSD_TYPE_HALF4ARRAY =
            SdfValueTypeNames->Half4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_HALF4ARRAY] = SdfValueTypeNames->Half4Array;
        NUSD_TYPE_INT = SdfValueTypeNames->Int.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT] = SdfValueTypeNames->Int;
        NUSD_TYPE_INTARRAY = SdfValueTypeNames->IntArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INTARRAY] = SdfValueTypeNames->IntArray;
        NUSD_TYPE_INT2 = SdfValueTypeNames->Int2.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT2] = SdfValueTypeNames->Int2;
        NUSD_TYPE_INT2ARRAY =
            SdfValueTypeNames->Int2Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT2ARRAY] = SdfValueTypeNames->Int2Array;
        NUSD_TYPE_INT3 = SdfValueTypeNames->Int3.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT3] = SdfValueTypeNames->Int3;
        NUSD_TYPE_INT3ARRAY =
            SdfValueTypeNames->Int3Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT3ARRAY] = SdfValueTypeNames->Int3Array;
        NUSD_TYPE_INT4 = SdfValueTypeNames->Int4.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT4] = SdfValueTypeNames->Int4;
        NUSD_TYPE_INT4ARRAY =
            SdfValueTypeNames->Int4Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT4ARRAY] = SdfValueTypeNames->Int4Array;
        NUSD_TYPE_INT64 = SdfValueTypeNames->Int64.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT64] = SdfValueTypeNames->Int64;
        NUSD_TYPE_INT64ARRAY =
            SdfValueTypeNames->Int64Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_INT64ARRAY] = SdfValueTypeNames->Int64Array;
        NUSD_TYPE_MATRIX2D = SdfValueTypeNames->Matrix2d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX2D] = SdfValueTypeNames->Matrix2d;
        NUSD_TYPE_MATRIX2DARRAY =
            SdfValueTypeNames->Matrix2dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX2DARRAY] =
            SdfValueTypeNames->Matrix2dArray;
        NUSD_TYPE_MATRIX3D = SdfValueTypeNames->Matrix3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX3D] = SdfValueTypeNames->Matrix3d;
        NUSD_TYPE_MATRIX3DARRAY =
            SdfValueTypeNames->Matrix3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX3DARRAY] =
            SdfValueTypeNames->Matrix3dArray;
        NUSD_TYPE_MATRIX4D = SdfValueTypeNames->Matrix4d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX4D] = SdfValueTypeNames->Matrix4d;
        NUSD_TYPE_MATRIX4DARRAY =
            SdfValueTypeNames->Matrix4dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_MATRIX4DARRAY] =
            SdfValueTypeNames->Matrix4dArray;
        NUSD_TYPE_NORMAL3D = SdfValueTypeNames->Normal3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3D] = SdfValueTypeNames->Normal3d;
        NUSD_TYPE_NORMAL3DARRAY =
            SdfValueTypeNames->Normal3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3DARRAY] =
            SdfValueTypeNames->Normal3dArray;
        NUSD_TYPE_NORMAL3F = SdfValueTypeNames->Normal3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3F] = SdfValueTypeNames->Normal3f;
        NUSD_TYPE_NORMAL3FARRAY =
            SdfValueTypeNames->Normal3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3FARRAY] =
            SdfValueTypeNames->Normal3fArray;
        NUSD_TYPE_NORMAL3H = SdfValueTypeNames->Normal3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3H] = SdfValueTypeNames->Normal3h;
        NUSD_TYPE_NORMAL3HARRAY =
            SdfValueTypeNames->Normal3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_NORMAL3HARRAY] =
            SdfValueTypeNames->Normal3hArray;
        NUSD_TYPE_POINT3D = SdfValueTypeNames->Point3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3D] = SdfValueTypeNames->Point3d;
        NUSD_TYPE_POINT3DARRAY =
            SdfValueTypeNames->Point3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3DARRAY] =
            SdfValueTypeNames->Point3dArray;
        NUSD_TYPE_POINT3F = SdfValueTypeNames->Point3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3F] = SdfValueTypeNames->Point3f;
        NUSD_TYPE_POINT3FARRAY =
            SdfValueTypeNames->Point3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3FARRAY] =
            SdfValueTypeNames->Point3fArray;
        NUSD_TYPE_POINT3H = SdfValueTypeNames->Point3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3H] = SdfValueTypeNames->Point3h;
        NUSD_TYPE_POINT3HARRAY =
            SdfValueTypeNames->Point3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_POINT3HARRAY] =
            SdfValueTypeNames->Point3hArray;
        NUSD_TYPE_QUATD = SdfValueTypeNames->Quatd.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATD] = SdfValueTypeNames->Quatd;
        NUSD_TYPE_QUATDARRAY =
            SdfValueTypeNames->QuatdArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATDARRAY] = SdfValueTypeNames->QuatdArray;
        NUSD_TYPE_QUATF = SdfValueTypeNames->Quatf.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATF] = SdfValueTypeNames->Quatf;
        NUSD_TYPE_QUATFARRAY =
            SdfValueTypeNames->QuatfArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATFARRAY] = SdfValueTypeNames->QuatfArray;
        NUSD_TYPE_QUATH = SdfValueTypeNames->Quath.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATH] = SdfValueTypeNames->Quath;
        NUSD_TYPE_QUATHARRAY =
            SdfValueTypeNames->QuathArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_QUATHARRAY] = SdfValueTypeNames->QuathArray;
        NUSD_TYPE_STRING =
            SdfValueTypeNames->String.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_STRING] = SdfValueTypeNames->String;
        NUSD_TYPE_STRINGARRAY =
            SdfValueTypeNames->StringArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_STRINGARRAY] = SdfValueTypeNames->StringArray;
        NUSD_TYPE_TEXCOORD2D =
            SdfValueTypeNames->TexCoord2d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2D] = SdfValueTypeNames->TexCoord2d;
        NUSD_TYPE_TEXCOORD2DARRAY =
            SdfValueTypeNames->TexCoord2dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2DARRAY] =
            SdfValueTypeNames->TexCoord2dArray;
        NUSD_TYPE_TEXCOORD2F =
            SdfValueTypeNames->TexCoord2f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2F] = SdfValueTypeNames->TexCoord2f;
        NUSD_TYPE_TEXCOORD2FARRAY =
            SdfValueTypeNames->TexCoord2fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2FARRAY] =
            SdfValueTypeNames->TexCoord2fArray;
        NUSD_TYPE_TEXCOORD2H =
            SdfValueTypeNames->TexCoord2h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2H] = SdfValueTypeNames->TexCoord2h;
        NUSD_TYPE_TEXCOORD2HARRAY =
            SdfValueTypeNames->TexCoord2hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD2HARRAY] =
            SdfValueTypeNames->TexCoord2hArray;
        NUSD_TYPE_TEXCOORD3D =
            SdfValueTypeNames->TexCoord3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3D] = SdfValueTypeNames->TexCoord3d;
        NUSD_TYPE_TEXCOORD3DARRAY =
            SdfValueTypeNames->TexCoord3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3DARRAY] =
            SdfValueTypeNames->TexCoord3dArray;
        NUSD_TYPE_TEXCOORD3F =
            SdfValueTypeNames->TexCoord3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3F] = SdfValueTypeNames->TexCoord3f;
        NUSD_TYPE_TEXCOORD3FARRAY =
            SdfValueTypeNames->TexCoord3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3FARRAY] =
            SdfValueTypeNames->TexCoord3fArray;
        NUSD_TYPE_TEXCOORD3H =
            SdfValueTypeNames->TexCoord3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3H] = SdfValueTypeNames->TexCoord3h;
        NUSD_TYPE_TEXCOORD3HARRAY =
            SdfValueTypeNames->TexCoord3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TEXCOORD3HARRAY] =
            SdfValueTypeNames->TexCoord3hArray;
        NUSD_TYPE_TIMECODE = SdfValueTypeNames->TimeCode.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TIMECODE] = SdfValueTypeNames->TimeCode;
        NUSD_TYPE_TIMECODEARRAY =
            SdfValueTypeNames->TimeCodeArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TIMECODEARRAY] =
            SdfValueTypeNames->TimeCodeArray;
        NUSD_TYPE_TOKEN = SdfValueTypeNames->Token.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TOKEN] = SdfValueTypeNames->Token;
        NUSD_TYPE_TOKENARRAY =
            SdfValueTypeNames->TokenArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_TOKENARRAY] = SdfValueTypeNames->TokenArray;
        NUSD_TYPE_UCHAR = SdfValueTypeNames->UChar.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UCHAR] = SdfValueTypeNames->UChar;
        NUSD_TYPE_UCHARARRAY =
            SdfValueTypeNames->UCharArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UCHARARRAY] = SdfValueTypeNames->UCharArray;
        NUSD_TYPE_UINT = SdfValueTypeNames->UInt.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINT] = SdfValueTypeNames->UInt;
        NUSD_TYPE_UINTARRAY =
            SdfValueTypeNames->UIntArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINTARRAY] = SdfValueTypeNames->UIntArray;
        NUSD_TYPE_UINT64 = SdfValueTypeNames->UInt64.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINT64] = SdfValueTypeNames->UInt64;
        NUSD_TYPE_UINT64ARRAY =
            SdfValueTypeNames->UInt64Array.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_UINT64ARRAY] =
            SdfValueTypeNames->UInt64Array;
        NUSD_TYPE_VECTOR3D = SdfValueTypeNames->Vector3d.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3D] = SdfValueTypeNames->Vector3d;
        NUSD_TYPE_VECTOR3DARRAY =
            SdfValueTypeNames->Vector3dArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3DARRAY] =
            SdfValueTypeNames->Vector3dArray;
        NUSD_TYPE_VECTOR3F = SdfValueTypeNames->Vector3f.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3F] = SdfValueTypeNames->Vector3f;
        NUSD_TYPE_VECTOR3FARRAY =
            SdfValueTypeNames->Vector3fArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3FARRAY] =
            SdfValueTypeNames->Vector3fArray;
        NUSD_TYPE_VECTOR3H = SdfValueTypeNames->Vector3h.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3H] = SdfValueTypeNames->Vector3h;
        NUSD_TYPE_VECTOR3HARRAY =
            SdfValueTypeNames->Vector3hArray.GetAsToken().GetText();
        TOKEN_TO_TYPENAME[NUSD_TYPE_VECTOR3HARRAY] =
            SdfValueTypeNames->Vector3hArray;

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

nusd_result_t nusd_stage_create_new(char const* identifier,
                                    nusd_stage_t* stage) {
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

nusd_result_t nusd_stage_create_in_memory(char const* identifier,
                                          nusd_stage_t* stage) {
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

nusd_result_t nusd_stage_define_prim(nusd_stage_t stage,
                                     char const* prim_path,
                                     char const* prim_type) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdPrim prim = _stage->DefinePrim(SdfPath(prim_path), TfToken(prim_type));
    if (!prim) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    return NUSD_RESULT_OK;
}

bool nusd_stage_path_is_valid_prim(nusd_stage_t stage, char const* prim_path) {
    if (stage == nullptr || prim_path == nullptr) {
        return false;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));

    return bool(prim);
}


nusd_result_t nusd_stage_set_meters_per_unit(nusd_stage_t stage, double meters_per_unit) {
    if (stage == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    if (!UsdGeomSetStageMetersPerUnit(UsdStageWeakPtr(_stage), meters_per_unit)) {
        return NUSD_RESULT_SET_METADATA_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_get_meters_per_unit(nusd_stage_t stage, double* meters_per_unit) {
    if (stage == nullptr || meters_per_unit == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    *meters_per_unit = UsdGeomGetStageMetersPerUnit(UsdStageWeakPtr(_stage));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_stage_traverse(nusd_stage_t stage,
                                  nusd_prim_iterator_t* iterator) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdPrim pseudo_root = _stage->GetPseudoRoot();

    nusd_prim_iterator_s* it = new nusd_prim_iterator_s();
    it->range = UsdPrimRange(pseudo_root);
    it->current = it->range.begin();

    *iterator = std::move(it);

    return NUSD_RESULT_OK;
}

bool nusd_prim_iterator_next(nusd_prim_iterator_t iterator,
                             char const** prim_path) {
    if (iterator->current == iterator->range.end()) {
        return false;
    }

    *prim_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_prim_iterator_is_done(nusd_prim_iterator_t iterator,
                                         bool* is_done) {
    *is_done = iterator->current == iterator->range.end();

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_iterator_destroy(nusd_prim_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_get_properties(nusd_stage_t stage,
                                       char const* prim_path,
                                       nusd_property_iterator_t* iterator) {
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

nusd_result_t nusd_prim_create_property(nusd_stage_t stage,
                                        char const* prim_path,
                                        char const* property_name,
                                        nusd_type_t property_type) {
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

        UsdAttribute attr = prim.CreateAttribute(
            TfToken(property_name), TOKEN_TO_TYPENAME[property_type]);
        if (!attr) {
            return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
        } else {
            return NUSD_RESULT_OK;
        }
    }
}

bool nusd_property_iterator_next(nusd_property_iterator_t iterator,
                                 char const** property_path,
                                 nusd_type_t* property_type) {
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

nusd_result_t
nusd_property_iterator_destroy(nusd_property_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_get_attributes(nusd_stage_t stage,
                                       char const* prim_path,
                                       nusd_attribute_iterator_t* iterator) {
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

bool nusd_attribute_iterator_next(nusd_attribute_iterator_t iterator,
                                  char const** attribute_path) {
    if (iterator->current == iterator->attributes.end()) {
        return false;
    }

    *attribute_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t
nusd_attribute_iterator_destroy(nusd_attribute_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

char const* nusd_path_get_name(char const* path) {
    return strstr(path, ".") + 1;
}

nusd_result_t nusd_camera_define(nusd_stage_t stage, char const* camera_path) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera =
        UsdGeomCamera::Define(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_set_transform(nusd_stage_t stage,
                                      char const* xformable_path,
                                      double const* local_to_parent_matrix,
                                      double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomXformable xformable =
        UsdGeomXformable::Get(UsdStageWeakPtr(_stage), SdfPath(xformable_path));
    if (!xformable) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    if (local_to_parent_matrix) {
        UsdGeomXformOp op = xformable.AddTransformOp();
        op.Set(*reinterpret_cast<GfMatrix4d const*>(local_to_parent_matrix),
               time_code);
    } else {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_camera_set_fov_w(nusd_stage_t stage,
                                    char const* camera_path,
                                    float fov_w,
                                    double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera =
        UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    float w;
    camera.GetHorizontalApertureAttr().Get(&w);
    float f = w / (2.0f * tanf(radians(fov_w) / 2.0f));

    camera.GetFocalLengthAttr().Set(f, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_camera_set_exposure(nusd_stage_t stage,
                                       char const* camera_path,
                                       float iso,
                                       float time,
                                       float f_stop,
                                       float compensation,
                                       float responsivity,
                                       double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera =
        UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
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

nusd_result_t nusd_camera_set_clipping_range(nusd_stage_t stage,
                                             char const* camera_path,
                                             float near,
                                             float far,
                                             double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera =
        UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    camera.GetClippingRangeAttr().Set(GfVec2f(near, far), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_prim_compute_local_to_world_transform(nusd_stage_t stage,
                                           char const* xformable_path,
                                           double time_code,
                                           double* transform) {
    if (stage == nullptr || xformable_path == nullptr || transform == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomXformable xformable =
        UsdGeomXformable::Get(UsdStageWeakPtr(_stage), SdfPath(xformable_path));
    if (!xformable) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    GfMatrix4d matrix = xformable.ComputeLocalToWorldTransform(time_code);
    memcpy(transform, matrix.data(), sizeof(double) * 16);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_camera_set_aperture(nusd_stage_t stage,
                                       char const* camera_path,
                                       float width,
                                       float height,
                                       double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomCamera camera =
        UsdGeomCamera::Get(UsdStageWeakPtr(_stage), SdfPath(camera_path));
    if (!camera) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    camera.GetHorizontalApertureAttr().Set(width, time_code);
    camera.GetVerticalApertureAttr().Set(height, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_material_define(nusd_stage_t stage,
                                   char const* material_path) {
    if (stage == nullptr || material_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdShadeMaterial material = UsdShadeMaterial::Define(
        UsdStageWeakPtr(_stage), SdfPath(material_path));
    if (!material) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_define(nusd_stage_t stage,
                                 char const* shader_path,
                                 char const* shader_id) {
    if (stage == nullptr || shader_path == nullptr || shader_id == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdShadeShader shader =
        UsdShadeShader::Define(UsdStageWeakPtr(_stage), SdfPath(shader_path));
    if (!shader) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    shader.SetShaderId(TfToken(shader_id));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_create_input(nusd_stage_t stage,
                                       char const* shader_path,
                                       char const* input_name,
                                       nusd_type_t input_type) {
    if (stage == nullptr || shader_path == nullptr || input_name == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    if (input_type == NUSD_TYPE_RELATIONSHIP) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeShader shader =
        UsdShadeShader(_stage->GetPrimAtPath(SdfPath(shader_path)));
    if (!shader) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeInput input =
        shader.CreateInput(TfToken(input_name), TOKEN_TO_TYPENAME[input_type]);
    if (!input) {
        return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_create_output(nusd_stage_t stage,
                                        char const* shader_path,
                                        char const* output_name,
                                        nusd_type_t output_type) {
    if (stage == nullptr || shader_path == nullptr || output_name == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    if (output_type == NUSD_TYPE_RELATIONSHIP) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeShader shader =
        UsdShadeShader(_stage->GetPrimAtPath(SdfPath(shader_path)));
    if (!shader) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeOutput output = shader.CreateOutput(TfToken(output_name),
                                                TOKEN_TO_TYPENAME[output_type]);
    if (!output) {
        return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_connect(nusd_stage_t stage,
                                  char const* source_output_path,
                                  char const* destination_input_path) {
    if (stage == nullptr || source_output_path == nullptr ||
        destination_input_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr_source =
        _stage->GetAttributeAtPath(SdfPath(source_output_path));
    UsdAttribute attr_dest =
        _stage->GetAttributeAtPath(SdfPath(destination_input_path));

    if (!attr_source || !attr_dest) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    UsdShadeOutput source = UsdShadeOutput(attr_source);
    UsdShadeInput destination = UsdShadeInput(attr_dest);

    if (!source) {
        return NUSD_RESULT_INVALID_SHADER_OUTPUT;
    }
    if (!destination) {
        return NUSD_RESULT_INVALID_SHADER_INPUT;
    }

    if (!destination.ConnectToSource(SdfPath(source_output_path))) {
        return NUSD_RESULT_CONNECTION_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_material_create_input(nusd_stage_t stage,
                                         char const* material_path,
                                         char const* input_name,
                                         nusd_type_t input_type) {
    if (stage == nullptr || material_path == nullptr || input_name == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    if (input_type == NUSD_TYPE_RELATIONSHIP) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeMaterial material =
        UsdShadeMaterial(_stage->GetPrimAtPath(SdfPath(material_path)));
    if (!material) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeInput input = material.CreateInput(TfToken(input_name),
                                              TOKEN_TO_TYPENAME[input_type]);
    if (!input) {
        return NUSD_RESULT_CREATE_INPUT_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_material_create_output(nusd_stage_t stage,
                                          char const* material_path,
                                          char const* output_name,
                                          nusd_type_t output_type) {
    if (stage == nullptr || material_path == nullptr || output_name == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    if (output_type == NUSD_TYPE_RELATIONSHIP) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdShadeMaterial material =
        UsdShadeMaterial(_stage->GetPrimAtPath(SdfPath(material_path)));
    if (!material) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeOutput output = material.CreateOutput(TfToken(output_name),
                                                 TOKEN_TO_TYPENAME[output_type]);
    if (!output) {
        return NUSD_RESULT_CREATE_OUTPUT_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_shader_connect_outputs(nusd_stage_t stage,
                                          char const* source_output_path,
                                          char const* destination_output_path) {
    if (stage == nullptr || source_output_path == nullptr ||
        destination_output_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr_source =
        _stage->GetAttributeAtPath(SdfPath(source_output_path));
    UsdAttribute attr_dest =
        _stage->GetAttributeAtPath(SdfPath(destination_output_path));

    if (!attr_source || !attr_dest) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    UsdShadeOutput source = UsdShadeOutput(attr_source);
    UsdShadeOutput destination = UsdShadeOutput(attr_dest);

    if (!source) {
        return NUSD_RESULT_INVALID_SHADER_OUTPUT;
    }
    if (!destination) {
        return NUSD_RESULT_INVALID_SHADER_OUTPUT;
    }

    if (!destination.ConnectToSource(SdfPath(source_output_path))) {
        return NUSD_RESULT_CONNECTION_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_material_bind(nusd_stage_t stage,
                                 char const* prim_path,
                                 char const* material_path) {
    if (stage == nullptr || prim_path == nullptr || material_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdPrim prim = _stage->GetPrimAtPath(SdfPath(prim_path));
    if (!prim) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdPrim prim_material = _stage->GetPrimAtPath(SdfPath(material_path));
    if (!prim_material) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdShadeMaterial material(prim_material);
    if (!material) {
        return NUSD_RESULT_INVALID_MATERIAL_PATH;
    }

    UsdShadeMaterialBindingAPI binding = UsdShadeMaterialBindingAPI::Apply(prim);
    if (!binding) {
        return NUSD_RESULT_APPLY_BINDING_API_FAILED;
    }

    if (!binding.Bind(material)) {
        return NUSD_RESULT_CREATE_BINDING_FAILED;
    }
    
    return NUSD_RESULT_OK;
}
}