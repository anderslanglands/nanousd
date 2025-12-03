#include "nanousd.h"
#include "nanousd-types.h"

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

nusd_colorspace_t NUSD_COLORSPACE_LINEAR_AP1;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_AP0;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_REC709;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_P3D65;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_REC2020;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_ADOBERGB;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_CIEXYZD65;
nusd_colorspace_t NUSD_COLORSPACE_LINEAR_DISPLAYP3;
nusd_colorspace_t NUSD_COLORSPACE_SRGB_REC709;
nusd_colorspace_t NUSD_COLORSPACE_G22_REC709;
nusd_colorspace_t NUSD_COLORSPACE_G18_REC709;
nusd_colorspace_t NUSD_COLORSPACE_SRGB_AP1;
nusd_colorspace_t NUSD_COLORSPACE_G22_AP1;
nusd_colorspace_t NUSD_COLORSPACE_G22_ADOBERGB;
nusd_colorspace_t NUSD_COLORSPACE_IDENTITY;
nusd_colorspace_t NUSD_COLORSPACE_DATA;
nusd_colorspace_t NUSD_COLORSPACE_RAW;
nusd_colorspace_t NUSD_COLORSPACE_SRGB;
nusd_colorspace_t NUSD_COLORSPACE_UNKNOWN;
nusd_colorspace_t NUSD_COLORSPACE_CIEXYZ;

double NUSD_TIMECODE_DEFAULT = NAN;

using TypeToTypeNameMap =
    std::unordered_map<nusd_type_t, PXR_NS::SdfValueTypeName>;
TypeToTypeNameMap TYPE_TO_TYPENAME;
std::unordered_map<char const*, nusd_type_t> TYPENAME_TO_TYPE;
std::unordered_map<nusd_type_t, char const*> TYPE_TO_STRING;


char const* nusd_type_to_string(nusd_type_t type) {
    if (type < 0 || type > NUSD_TYPE_RELATIONSHIP) {
        return "INVALID";
    }

    if (type == NUSD_TYPE_RELATIONSHIP) {
        return "rel";
    }

    return TYPE_TO_STRING[type];
}

using namespace PXR_NS;

using StageMap = std::unordered_map<UsdStage*, UsdStageRefPtr>;
StageMap STAGES;

float C_PI = 3.141592653589793f;

static float radians(float degrees) { return degrees * C_PI / 180.0f; }

static void initialize_tokens() {
    std::lock_guard<std::mutex> lock(MTX_TOKEN_INIT);
    if (TOKENS_INITIALIZED == false) {

#define REGISTER_TYPE(NUSD_TYPE, SDF_TYPE) \
    TYPE_TO_TYPENAME[NUSD_TYPE] = SdfValueTypeNames->SDF_TYPE; \
    TYPENAME_TO_TYPE[SdfValueTypeNames->SDF_TYPE.GetAsToken().GetText()] = NUSD_TYPE; \
    TYPE_TO_STRING[NUSD_TYPE] = SdfValueTypeNames->SDF_TYPE.GetAsToken().GetText();

    REGISTER_TYPE(NUSD_TYPE_ASSET, Asset);
    REGISTER_TYPE(NUSD_TYPE_ASSETARRAY, AssetArray);
    REGISTER_TYPE(NUSD_TYPE_BOOL, Bool);
    REGISTER_TYPE(NUSD_TYPE_BOOLARRAY, BoolArray);
    REGISTER_TYPE(NUSD_TYPE_COLOR3D, Color3d);
    REGISTER_TYPE(NUSD_TYPE_COLOR3DARRAY, Color3dArray);
    REGISTER_TYPE(NUSD_TYPE_COLOR3F, Color3f);
    REGISTER_TYPE(NUSD_TYPE_COLOR3FARRAY, Color3fArray);
    REGISTER_TYPE(NUSD_TYPE_COLOR3H, Color3h);
    REGISTER_TYPE(NUSD_TYPE_COLOR3HARRAY, Color3hArray);
    REGISTER_TYPE(NUSD_TYPE_COLOR4D, Color4d);
    REGISTER_TYPE(NUSD_TYPE_COLOR4DARRAY, Color4dArray);
    REGISTER_TYPE(NUSD_TYPE_COLOR4F, Color4f);
    REGISTER_TYPE(NUSD_TYPE_COLOR4FARRAY, Color4fArray);
    REGISTER_TYPE(NUSD_TYPE_COLOR4H, Color4h);
    REGISTER_TYPE(NUSD_TYPE_COLOR4HARRAY, Color4hArray);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE, Double);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE2, Double2);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE2ARRAY, Double2Array);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE3, Double3);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE3ARRAY, Double3Array);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE4, Double4);
    REGISTER_TYPE(NUSD_TYPE_DOUBLE4ARRAY, Double4Array);
    REGISTER_TYPE(NUSD_TYPE_DOUBLEARRAY, DoubleArray);
    REGISTER_TYPE(NUSD_TYPE_FLOAT, Float);
    REGISTER_TYPE(NUSD_TYPE_FLOAT2, Float2);
    REGISTER_TYPE(NUSD_TYPE_FLOAT2ARRAY, Float2Array);
    REGISTER_TYPE(NUSD_TYPE_FLOAT3, Float3);
    REGISTER_TYPE(NUSD_TYPE_FLOAT3ARRAY, Float3Array);
    REGISTER_TYPE(NUSD_TYPE_FLOAT4, Float4);
    REGISTER_TYPE(NUSD_TYPE_FLOAT4ARRAY, Float4Array);
    REGISTER_TYPE(NUSD_TYPE_FLOATARRAY, FloatArray);
    REGISTER_TYPE(NUSD_TYPE_FRAME4D, Frame4d);
    REGISTER_TYPE(NUSD_TYPE_FRAME4DARRAY, Frame4dArray);
    REGISTER_TYPE(NUSD_TYPE_GROUP, Group);
    REGISTER_TYPE(NUSD_TYPE_HALF, Half);
    REGISTER_TYPE(NUSD_TYPE_HALF2, Half2);
    REGISTER_TYPE(NUSD_TYPE_HALF2ARRAY, Half2Array);
    REGISTER_TYPE(NUSD_TYPE_HALF3, Half3);
    REGISTER_TYPE(NUSD_TYPE_HALF3ARRAY, Half3Array);
    REGISTER_TYPE(NUSD_TYPE_HALF4, Half4);
    REGISTER_TYPE(NUSD_TYPE_HALF4ARRAY, Half4Array);
    REGISTER_TYPE(NUSD_TYPE_HALFARRAY, HalfArray);
    REGISTER_TYPE(NUSD_TYPE_INT, Int);
    REGISTER_TYPE(NUSD_TYPE_INT2, Int2);
    REGISTER_TYPE(NUSD_TYPE_INT2ARRAY, Int2Array);
    REGISTER_TYPE(NUSD_TYPE_INT3, Int3);
    REGISTER_TYPE(NUSD_TYPE_INT3ARRAY, Int3Array);
    REGISTER_TYPE(NUSD_TYPE_INT4, Int4);
    REGISTER_TYPE(NUSD_TYPE_INT4ARRAY, Int4Array);
    REGISTER_TYPE(NUSD_TYPE_INT64, Int64);
    REGISTER_TYPE(NUSD_TYPE_INT64ARRAY, Int64Array);
    REGISTER_TYPE(NUSD_TYPE_INTARRAY, IntArray);
    REGISTER_TYPE(NUSD_TYPE_MATRIX2D, Matrix2d);
    REGISTER_TYPE(NUSD_TYPE_MATRIX2DARRAY, Matrix2dArray);
    REGISTER_TYPE(NUSD_TYPE_MATRIX3D, Matrix3d);
    REGISTER_TYPE(NUSD_TYPE_MATRIX3DARRAY, Matrix3dArray);
    REGISTER_TYPE(NUSD_TYPE_MATRIX4D, Matrix4d);
    REGISTER_TYPE(NUSD_TYPE_MATRIX4DARRAY, Matrix4dArray);
    REGISTER_TYPE(NUSD_TYPE_NORMAL3D, Normal3d);
    REGISTER_TYPE(NUSD_TYPE_NORMAL3DARRAY, Normal3dArray);
    REGISTER_TYPE(NUSD_TYPE_NORMAL3F, Normal3f);
    REGISTER_TYPE(NUSD_TYPE_NORMAL3FARRAY, Normal3fArray);
    REGISTER_TYPE(NUSD_TYPE_NORMAL3H, Normal3h);
    REGISTER_TYPE(NUSD_TYPE_NORMAL3HARRAY, Normal3hArray);
    REGISTER_TYPE(NUSD_TYPE_OPAQUE, Opaque);
    REGISTER_TYPE(NUSD_TYPE_PATHEXPRESSION, PathExpression);
    REGISTER_TYPE(NUSD_TYPE_PATHEXPRESSIONARRAY, PathExpressionArray);
    REGISTER_TYPE(NUSD_TYPE_POINT3D, Point3d);
    REGISTER_TYPE(NUSD_TYPE_POINT3DARRAY, Point3dArray);
    REGISTER_TYPE(NUSD_TYPE_POINT3F, Point3f);
    REGISTER_TYPE(NUSD_TYPE_POINT3FARRAY, Point3fArray);
    REGISTER_TYPE(NUSD_TYPE_POINT3H, Point3h);
    REGISTER_TYPE(NUSD_TYPE_POINT3HARRAY, Point3hArray);
    REGISTER_TYPE(NUSD_TYPE_QUATD, Quatd);
    REGISTER_TYPE(NUSD_TYPE_QUATDARRAY, QuatdArray);
    REGISTER_TYPE(NUSD_TYPE_QUATF, Quatf);
    REGISTER_TYPE(NUSD_TYPE_QUATFARRAY, QuatfArray);
    REGISTER_TYPE(NUSD_TYPE_QUATH, Quath);
    REGISTER_TYPE(NUSD_TYPE_QUATHARRAY, QuathArray);
    REGISTER_TYPE(NUSD_TYPE_STRING, String);
    REGISTER_TYPE(NUSD_TYPE_STRINGARRAY, StringArray);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD2D, TexCoord2d);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD2DARRAY, TexCoord2dArray);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD2F, TexCoord2f);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD2FARRAY, TexCoord2fArray);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD2H, TexCoord2h);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD2HARRAY, TexCoord2hArray);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD3D, TexCoord3d);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD3DARRAY, TexCoord3dArray);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD3F, TexCoord3f);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD3FARRAY, TexCoord3fArray);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD3H, TexCoord3h);
    REGISTER_TYPE(NUSD_TYPE_TEXCOORD3HARRAY, TexCoord3hArray);
    REGISTER_TYPE(NUSD_TYPE_TIMECODE, TimeCode);
    REGISTER_TYPE(NUSD_TYPE_TIMECODEARRAY, TimeCodeArray);
    REGISTER_TYPE(NUSD_TYPE_TOKEN, Token);
    REGISTER_TYPE(NUSD_TYPE_TOKENARRAY, TokenArray);
    REGISTER_TYPE(NUSD_TYPE_UCHAR, UChar);
    REGISTER_TYPE(NUSD_TYPE_UCHARARRAY, UCharArray);
    REGISTER_TYPE(NUSD_TYPE_UINT, UInt);
    REGISTER_TYPE(NUSD_TYPE_UINT64, UInt64);
    REGISTER_TYPE(NUSD_TYPE_UINT64ARRAY, UInt64Array);
    REGISTER_TYPE(NUSD_TYPE_UINTARRAY, UIntArray);
    REGISTER_TYPE(NUSD_TYPE_VECTOR3D, Vector3d);
    REGISTER_TYPE(NUSD_TYPE_VECTOR3DARRAY, Vector3dArray);
    REGISTER_TYPE(NUSD_TYPE_VECTOR3F, Vector3f);
    REGISTER_TYPE(NUSD_TYPE_VECTOR3FARRAY, Vector3fArray);
    REGISTER_TYPE(NUSD_TYPE_VECTOR3H, Vector3h);
    REGISTER_TYPE(NUSD_TYPE_VECTOR3HARRAY, Vector3hArray);

#undef REGISTER_TYPE

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
        if (property_type < 0 || property_type > NUSD_TYPE_RELATIONSHIP) {
            return NUSD_RESULT_INVALID_PROPERTY_TYPE;
        }

        UsdAttribute attr = prim.CreateAttribute(
            TfToken(property_name), TYPE_TO_TYPENAME[property_type]);
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
        *property_type = TYPENAME_TO_TYPE[type_name.GetAsToken().GetText()];
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
        shader.CreateInput(TfToken(input_name), TYPE_TO_TYPENAME[input_type]);
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
                                                TYPE_TO_TYPENAME[output_type]);
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
                                              TYPE_TO_TYPENAME[input_type]);
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
                                                 TYPE_TO_TYPENAME[output_type]);
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