#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

using namespace PXR_NS;

struct nusd_asset_path_s {
    PXR_NS::SdfAssetPath path;
};

struct nusd_relationship_iterator_s {
    std::vector<PXR_NS::UsdRelationship> relationships;
    std::vector<PXR_NS::UsdRelationship>::iterator current;
};

struct nusd_relationship_targets_iterator_s {
    PXR_NS::SdfPathVector paths;
    PXR_NS::SdfPathVector::iterator current;
};

extern "C" {

nusd_result_t nusd_property_get_type(nusd_stage_t stage,
                                     char const* property_path,
                                     nusd_type_t* property_type) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdProperty const& property =
        _stage->GetPropertyAtPath(SdfPath(property_path));

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

nusd_result_t nusd_attribute_get_token(nusd_stage_t stage,
                                       char const* attribute_path,
                                       double time_code,
                                       char const** token) {
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

nusd_result_t nusd_attribute_get_asset(nusd_stage_t stage,
                                       char const* attribute_path,
                                       double time_code,
                                       nusd_asset_path_t* asset_path) {
    if (stage == nullptr || attribute_path == nullptr ||
        asset_path == nullptr) {
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

// float
nusd_result_t nusd_attribute_get_float(nusd_stage_t stage,
                                       char const* attribute_path,
                                       double time_code,
                                       float* value) {
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

nusd_result_t nusd_attribute_get_float2(nusd_stage_t stage,
                                        char const* attribute_path,
                                        double time_code,
                                        float* value) {
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

nusd_result_t nusd_attribute_get_float3(nusd_stage_t stage,
                                        char const* attribute_path,
                                        double time_code,
                                        float* value) {
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
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3f*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float4(nusd_stage_t stage,
                                        char const* attribute_path,
                                        double time_code,
                                        float* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT4 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4f*>(value), time_code);

    return NUSD_RESULT_OK;
}

// double
nusd_result_t nusd_attribute_get_double(nusd_stage_t stage,
                                        char const* attribute_path,
                                        double time_code,
                                        double* value) {
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

nusd_result_t nusd_attribute_get_double2(nusd_stage_t stage,
                                         char const* attribute_path,
                                         double time_code,
                                         double* value) {
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

nusd_result_t nusd_attribute_get_double3(nusd_stage_t stage,
                                         char const* attribute_path,
                                         double time_code,
                                         double* value) {
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
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3d*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_double4(nusd_stage_t stage,
                                         char const* attribute_path,
                                         double time_code,
                                         double* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE4 &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4D) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4d*>(value), time_code);

    return NUSD_RESULT_OK;
}

// int
nusd_result_t nusd_attribute_get_int(nusd_stage_t stage,
                                     char const* attribute_path,
                                     double time_code,
                                     int* value) {
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

nusd_result_t nusd_attribute_get_int2(nusd_stage_t stage,
                                      char const* attribute_path,
                                      double time_code,
                                      int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec2i*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int3(nusd_stage_t stage,
                                      char const* attribute_path,
                                      double time_code,
                                      int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec3i*>(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int4(nusd_stage_t stage,
                                      char const* attribute_path,
                                      double time_code,
                                      int* value) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(reinterpret_cast<GfVec4i*>(value), time_code);

    return NUSD_RESULT_OK;
}

// bool
nusd_result_t nusd_attribute_get_bool(nusd_stage_t stage,
                                      char const* attribute_path,
                                      double time_code,
                                      bool* value) {
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

// Bool setters
nusd_result_t nusd_attribute_set_bool(nusd_stage_t stage,
                                      char const* attribute_path,
                                      bool value,
                                      double time_code) {
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

// matrix2d getters
nusd_result_t nusd_attribute_get_matrix2d(nusd_stage_t stage,
                                          char const* attribute_path,
                                          double time_code,
                                          double* value) {
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

// matrix3d getters
nusd_result_t nusd_attribute_get_matrix3d(nusd_stage_t stage,
                                          char const* attribute_path,
                                          double time_code,
                                          double* value) {
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

// matrix4d getters
nusd_result_t nusd_attribute_get_matrix4d(nusd_stage_t stage,
                                          char const* attribute_path,
                                          double time_code,
                                          double* value) {
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

// matrix2d setters
nusd_result_t nusd_attribute_set_matrix2d(nusd_stage_t stage,
                                          char const* attribute_path,
                                          double* value,
                                          double time_code) {
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

// matrix3d setters
nusd_result_t nusd_attribute_set_matrix3d(nusd_stage_t stage,
                                          char const* attribute_path,
                                          double* value,
                                          double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX3D) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    GfMatrix3d matrix(value[0],
                      value[1],
                      value[2],
                      value[3],
                      value[4],
                      value[5],
                      value[6],
                      value[7],
                      value[8]);
    attr.Set(matrix, time_code);
    return NUSD_RESULT_OK;
}

// matrix4d setters
nusd_result_t nusd_attribute_set_matrix4d(nusd_stage_t stage,
                                          char const* attribute_path,
                                          double* value,
                                          double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));
    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }
    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_MATRIX4D) {
        return NUSD_RESULT_WRONG_TYPE;
    }
    GfMatrix4d matrix(value[0],
                      value[1],
                      value[2],
                      value[3],
                      value[4],
                      value[5],
                      value[6],
                      value[7],
                      value[8],
                      value[9],
                      value[10],
                      value[11],
                      value[12],
                      value[13],
                      value[14],
                      value[15]);
    attr.Set(matrix, time_code);
    return NUSD_RESULT_OK;
}

// relationships
nusd_result_t
nusd_prim_get_relationships(nusd_stage_t stage,
                            char const* prim_path,
                            nusd_relationship_iterator_t* iterator) {
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

nusd_result_t nusd_attribute_set_float(nusd_stage_t stage,
                                       char const* attribute_path,
                                       float value,
                                       double time_code) {
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

nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage,
                                        char const* attribute_path,
                                        float* value,
                                        double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT2 && attr_type != NUSD_TYPE_TEXCOORD2F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(GfVec2f(value[0], value[1]), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage,
                                        char const* attribute_path,
                                        float* value,
                                        double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT3 && attr_type != NUSD_TYPE_COLOR3F &&
        attr_type != NUSD_TYPE_VECTOR3F && attr_type != NUSD_TYPE_POINT3F &&
        attr_type != NUSD_TYPE_NORMAL3F && attr_type != NUSD_TYPE_TEXCOORD3F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(GfVec3f(value[0], value[1], value[2]), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage,
                                        char const* attribute_path,
                                        float* value,
                                        double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT4 && attr_type != NUSD_TYPE_COLOR4F) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Set(GfVec4f(value[0], value[1], value[2], value[3]), time_code);

    return NUSD_RESULT_OK;
}

// Int setters
nusd_result_t nusd_attribute_set_int(nusd_stage_t stage,
                                     char const* attribute_path,
                                     int value,
                                     double time_code) {
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

nusd_result_t nusd_attribute_set_int2(nusd_stage_t stage,
                                      char const* attribute_path,
                                      int* value,
                                      double time_code) {
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

nusd_result_t nusd_attribute_set_int3(nusd_stage_t stage,
                                      char const* attribute_path,
                                      int* value,
                                      double time_code) {
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

nusd_result_t nusd_attribute_set_int4(nusd_stage_t stage,
                                      char const* attribute_path,
                                      int* value,
                                      double time_code) {
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

// Int64 getters
nusd_result_t nusd_attribute_get_int64(nusd_stage_t stage,
                                       char const* attribute_path,
                                       double time_code,
                                       int64_t* value) {
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

// Unsigned integer getters
nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage,
                                      char const* attribute_path,
                                      double time_code,
                                      unsigned int* value) {
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

nusd_result_t nusd_attribute_get_uint64(nusd_stage_t stage,
                                        char const* attribute_path,
                                        double time_code,
                                        uint64_t* value) {
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

nusd_result_t nusd_attribute_get_uchar(nusd_stage_t stage,
                                       char const* attribute_path,
                                       double time_code,
                                       unsigned char* value) {
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

// Int64 setters
nusd_result_t nusd_attribute_set_int64(nusd_stage_t stage,
                                       char const* attribute_path,
                                       int64_t value,
                                       double time_code) {
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

// Unsigned integer setters
nusd_result_t nusd_attribute_set_uint(nusd_stage_t stage,
                                      char const* attribute_path,
                                      unsigned int value,
                                      double time_code) {
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

nusd_result_t nusd_attribute_set_uint64(nusd_stage_t stage,
                                        char const* attribute_path,
                                        uint64_t value,
                                        double time_code) {
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

nusd_result_t nusd_attribute_set_uchar(nusd_stage_t stage,
                                       char const* attribute_path,
                                       unsigned char value,
                                       double time_code) {
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

// Double setters
nusd_result_t nusd_attribute_set_double(nusd_stage_t stage,
                                        char const* attribute_path,
                                        double value,
                                        double time_code) {
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

nusd_result_t nusd_attribute_set_double2(nusd_stage_t stage,
                                         char const* attribute_path,
                                         double* value,
                                         double time_code) {
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

nusd_result_t nusd_attribute_set_double3(nusd_stage_t stage,
                                         char const* attribute_path,
                                         double* value,
                                         double time_code) {
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

nusd_result_t nusd_attribute_set_double4(nusd_stage_t stage,
                                         char const* attribute_path,
                                         double* value,
                                         double time_code) {
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

bool nusd_relationship_iterator_next(nusd_relationship_iterator_t iterator,
                                     char const** relationship_path) {
    if (iterator->current == iterator->relationships.end()) {
        return false;
    }

    *relationship_path = iterator->current->GetPath().GetText();
    iterator->current++;

    return true;
}

nusd_result_t
nusd_relationship_iterator_destroy(nusd_relationship_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_relationship_get_targets(nusd_stage_t stage,
                              char const* relationship_path,
                              nusd_relationship_targets_iterator_t* targets,
                              size_t* num_targets) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdRelationship rel =
        _stage->GetRelationshipAtPath(SdfPath(relationship_path));

    if (!rel) {
        return NUSD_RESULT_INVALID_RELATIONSHIP_PATH;
    }

    nusd_relationship_targets_iterator_s* it =
        new nusd_relationship_targets_iterator_s();
    rel.GetTargets(&it->paths);
    it->current = it->paths.begin();
    if (num_targets != nullptr) {
        *num_targets = it->paths.size();
    }

    *targets = it;

    return NUSD_RESULT_OK;
}

bool nusd_relationship_targets_iterator_next(
    nusd_relationship_targets_iterator_t iterator, char const** target_path) {
    if (iterator->current == iterator->paths.end()) {
        return false;
    }

    *target_path = iterator->current->GetText();
    iterator->current++;

    return true;
}

nusd_result_t nusd_relationship_targets_iterator_destroy(
    nusd_relationship_targets_iterator_t iterator) {
    delete iterator;

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_asset(nusd_stage_t stage,
                                       char const* attribute_path,
                                       char const* value,
                                       double time_code) {
    if (stage == nullptr || attribute_path == nullptr || value == nullptr) {
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

nusd_result_t nusd_attribute_set_asset_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             char const** value,
                                             size_t num_elements,
                                             double time_code) {
    if (stage == nullptr || attribute_path == nullptr || value == nullptr) {
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

nusd_result_t nusd_attribute_set_color_space(nusd_stage_t stage,
                                             char const* attribute_path,
                                             nusd_colorspace_t color_space) {
    if (stage == nullptr || attribute_path == nullptr ||
        color_space == nullptr) {
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

nusd_result_t nusd_attribute_get_color_space(nusd_stage_t stage,
                                             char const* attribute_path,
                                             nusd_colorspace_t* color_space) {
    if (stage == nullptr || attribute_path == nullptr ||
        color_space == nullptr) {
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

nusd_result_t nusd_attribute_set_token(nusd_stage_t stage,
                                       char const* attribute_path,
                                       char const* value,
                                       double time_code) {
    if (stage == nullptr || attribute_path == nullptr || value == nullptr) {
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

nusd_result_t nusd_attribute_set_token_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             char const** value,
                                             size_t num_elements,
                                             double time_code) {
    if (stage == nullptr || attribute_path == nullptr || value == nullptr) {
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


}