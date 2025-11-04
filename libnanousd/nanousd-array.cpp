#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/stage.h>

using namespace PXR_NS;

struct nusd_token_array_iterator_s {
    PXR_NS::VtTokenArray tokens;
    PXR_NS::VtTokenArray::iterator current;
};

struct nusd_asset_path_array_iterator_s {
    PXR_NS::VtArray<PXR_NS::SdfAssetPath> paths;
    PXR_NS::VtArray<PXR_NS::SdfAssetPath>::iterator current;
};

struct nusd_string_array_iterator_s {
    PXR_NS::VtArray<std::string> strings;
    PXR_NS::VtArray<std::string>::iterator current;
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

extern "C" {

bool nusd_asset_path_array_iterator_next(
    nusd_asset_path_array_iterator_t asset_paths, char const** asset_path) {
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

size_t
nusd_asset_path_array_iterator_size(nusd_asset_path_array_iterator_t iterator) {
    if (!iterator) {
        return 0;
    }

    return iterator->paths.size();
}

nusd_result_t nusd_asset_path_array_iterator_destroy(
    nusd_asset_path_array_iterator_t asset_paths) {
    if (asset_paths) {
        delete asset_paths;
    }
    return NUSD_RESULT_OK;
}

bool nusd_string_array_iterator_next(
    nusd_string_array_iterator_t strings, char const** string_value) {
    if (!strings || !string_value) {
        return false;
    }

    if (strings->current == strings->strings.end()) {
        return false;
    }

    *string_value = strings->current->c_str();

    ++strings->current;
    return true;
}

size_t
nusd_string_array_iterator_size(nusd_string_array_iterator_t iterator) {
    if (!iterator) {
        return 0;
    }

    return iterator->strings.size();
}

nusd_result_t nusd_string_array_iterator_destroy(
    nusd_string_array_iterator_t strings) {
    if (strings) {
        delete strings;
    }
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

size_t nusd_uint_array_size(nusd_uint_array_t uint_array) {
    return uint_array->value.size();
}

unsigned int* nusd_uint_array_data(nusd_uint_array_t uint_array) {
    return uint_array->value.data();
}

void nusd_uint_array_destroy(nusd_uint_array_t uint_array) {
    delete uint_array;
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

size_t nusd_uchar_array_size(nusd_uchar_array_t uchar_array) {
    return uchar_array->value.size();
}

unsigned char* nusd_uchar_array_data(nusd_uchar_array_t uchar_array) {
    return uchar_array->value.data();
}

void nusd_uchar_array_destroy(nusd_uchar_array_t uchar_array) {
    delete uchar_array;
}

bool nusd_token_array_iterator_next(nusd_token_array_iterator_t iterator,
                                    char const** token) {
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

nusd_result_t
nusd_token_array_iterator_destroy(nusd_token_array_iterator_t iterator) {
    delete iterator;

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

size_t nusd_float2_array_size(nusd_float2_array_t float2_array) {
    return float2_array->value.size();
}

float* nusd_float2_array_data(nusd_float2_array_t float2_array) {
    return reinterpret_cast<float*>(float2_array->value.data());
}

void nusd_float2_array_destroy(nusd_float2_array_t float2_array) {
    delete float2_array;
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

size_t nusd_float4_array_size(nusd_float4_array_t float4_array) {
    return float4_array->value.size();
}

float* nusd_float4_array_data(nusd_float4_array_t float4_array) {
    return reinterpret_cast<float*>(float4_array->value.data());
}

void nusd_float4_array_destroy(nusd_float4_array_t float4_array) {
    delete float4_array;
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

size_t nusd_double2_array_size(nusd_double2_array_t double2_array) {
    return double2_array->value.size();
}

double* nusd_double2_array_data(nusd_double2_array_t double2_array) {
    return reinterpret_cast<double*>(double2_array->value.data());
}

void nusd_double2_array_destroy(nusd_double2_array_t double2_array) {
    delete double2_array;
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

size_t nusd_double4_array_size(nusd_double4_array_t double4_array) {
    return double4_array->value.size();
}

double* nusd_double4_array_data(nusd_double4_array_t double4_array) {
    return reinterpret_cast<double*>(double4_array->value.data());
}

void nusd_double4_array_destroy(nusd_double4_array_t double4_array) {
    delete double4_array;
}

size_t nusd_int_array_size(nusd_int_array_t int_array) {
    return int_array->value.size();
}

int* nusd_int_array_data(nusd_int_array_t int_array) {
    return int_array->value.data();
}

void nusd_int_array_destroy(nusd_int_array_t int_array) { delete int_array; }

size_t nusd_int2_array_size(nusd_int2_array_t int2_array) {
    return int2_array->value.size();
}

int* nusd_int2_array_data(nusd_int2_array_t int2_array) {
    return reinterpret_cast<int*>(int2_array->value.data());
}

void nusd_int2_array_destroy(nusd_int2_array_t int2_array) {
    delete int2_array;
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

size_t nusd_int4_array_size(nusd_int4_array_t int4_array) {
    return int4_array->value.size();
}

int* nusd_int4_array_data(nusd_int4_array_t int4_array) {
    return reinterpret_cast<int*>(int4_array->value.data());
}

void nusd_int4_array_destroy(nusd_int4_array_t int4_array) {
    delete int4_array;
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

size_t nusd_matrix2d_array_size(nusd_matrix2d_array_t matrix2d_array) {
    return matrix2d_array->value.size();
}

double* nusd_matrix2d_array_data(nusd_matrix2d_array_t matrix2d_array) {
    return reinterpret_cast<double*>(matrix2d_array->value.data());
}

void nusd_matrix2d_array_destroy(nusd_matrix2d_array_t matrix2d_array) {
    delete matrix2d_array;
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

size_t nusd_matrix4d_array_size(nusd_matrix4d_array_t matrix4d_array) {
    return matrix4d_array->value.size();
}

double* nusd_matrix4d_array_data(nusd_matrix4d_array_t matrix4d_array) {
    return reinterpret_cast<double*>(matrix4d_array->value.data());
}

void nusd_matrix4d_array_destroy(nusd_matrix4d_array_t matrix4d_array) {
    delete matrix4d_array;
}

nusd_result_t
nusd_attribute_get_token_array(nusd_stage_t stage,
                               char const* attribute_path,
                               double time_code,
                               nusd_token_array_iterator_t* token_array) {
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

nusd_result_t nusd_attribute_get_asset_array(
    nusd_stage_t stage,
    char const* attribute_path,
    double time_code,
    nusd_asset_path_array_iterator_t* asset_path_array) {
    if (stage == nullptr || attribute_path == nullptr ||
        asset_path_array == nullptr) {
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

nusd_result_t nusd_attribute_get_string_array(
    nusd_stage_t stage,
    char const* attribute_path,
    double time_code,
    nusd_string_array_iterator_t* string_array) {
    if (stage == nullptr || attribute_path == nullptr ||
        string_array == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *string_array = new nusd_string_array_iterator_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_STRINGARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*string_array)->strings, time_code);
    (*string_array)->current = (*string_array)->strings.begin();

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_float_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             double time_code,
                                             nusd_float_array_t* float_array) {
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

nusd_result_t
nusd_attribute_get_float2_array(nusd_stage_t stage,
                                char const* attribute_path,
                                double time_code,
                                nusd_float2_array_t* float2_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *float2_array = new nusd_float2_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT2ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() !=
            NUSD_TYPE_TEXCOORD2FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float2_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_attribute_get_float3_array(nusd_stage_t stage,
                                char const* attribute_path,
                                double time_code,
                                nusd_float3_array_t* float3_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *float3_array = new nusd_float3_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT3ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() !=
            NUSD_TYPE_TEXCOORD3FARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_VECTOR3FARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_POINT3FARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_NORMAL3FARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float3_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_attribute_get_float4_array(nusd_stage_t stage,
                                char const* attribute_path,
                                double time_code,
                                nusd_float4_array_t* float4_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *float4_array = new nusd_float4_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOAT4ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*float4_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_attribute_get_double_array(nusd_stage_t stage,
                                char const* attribute_path,
                                double time_code,
                                nusd_double_array_t* double_array) {
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

nusd_result_t
nusd_attribute_get_double2_array(nusd_stage_t stage,
                                 char const* attribute_path,
                                 double time_code,
                                 nusd_double2_array_t* double2_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *double2_array = new nusd_double2_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE2ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() !=
            NUSD_TYPE_TEXCOORD2DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double2_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_attribute_get_double3_array(nusd_stage_t stage,
                                 char const* attribute_path,
                                 double time_code,
                                 nusd_double3_array_t* double3_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *double3_array = new nusd_double3_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE3ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() !=
            NUSD_TYPE_TEXCOORD3DARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_VECTOR3DARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_POINT3DARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_NORMAL3DARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR3DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double3_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_attribute_get_double4_array(nusd_stage_t stage,
                                 char const* attribute_path,
                                 double time_code,
                                 nusd_double4_array_t* double4_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *double4_array = new nusd_double4_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_DOUBLE4ARRAY &&
        attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_COLOR4DARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*double4_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int_array(nusd_stage_t stage,
                                           char const* attribute_path,
                                           double time_code,
                                           nusd_int_array_t* int_array) {
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

nusd_result_t nusd_attribute_get_int2_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            double time_code,
                                            nusd_int2_array_t* int2_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *int2_array = new nusd_int2_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT2ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int2_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int3_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            double time_code,
                                            nusd_int3_array_t* int3_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *int3_array = new nusd_int3_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT3ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int3_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_int4_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            double time_code,
                                            nusd_int4_array_t* int4_array) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    *int4_array = new nusd_int4_array_s();

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_INT4ARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    attr.Get(&(*int4_array)->value, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_get_bool_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            double time_code,
                                            nusd_bool_array_t* bool_array) {
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

nusd_result_t nusd_attribute_set_bool_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            bool* data,
                                            size_t num_elements,
                                            double time_code) {
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

nusd_result_t
nusd_attribute_get_matrix2d_array(nusd_stage_t stage,
                                  char const* attribute_path,
                                  double time_code,
                                  nusd_matrix2d_array_t* matrix2d_array) {
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

nusd_result_t
nusd_attribute_get_matrix3d_array(nusd_stage_t stage,
                                  char const* attribute_path,
                                  double time_code,
                                  nusd_matrix3d_array_t* matrix3d_array) {
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

nusd_result_t
nusd_attribute_get_matrix4d_array(nusd_stage_t stage,
                                  char const* attribute_path,
                                  double time_code,
                                  nusd_matrix4d_array_t* matrix4d_array) {
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

nusd_result_t nusd_attribute_set_matrix2d_array(nusd_stage_t stage,
                                                char const* attribute_path,
                                                double* _data,
                                                size_t num_elements,
                                                double time_code) {
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

nusd_result_t nusd_attribute_set_matrix3d_array(nusd_stage_t stage,
                                                char const* attribute_path,
                                                double* _data,
                                                size_t num_elements,
                                                double time_code) {
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

nusd_result_t nusd_attribute_set_matrix4d_array(nusd_stage_t stage,
                                                char const* attribute_path,
                                                double* _data,
                                                size_t num_elements,
                                                double time_code) {
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

nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             float* data,
                                             size_t num_elements,
                                             double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    if (attr.GetTypeName().GetAsToken().GetText() != NUSD_TYPE_FLOATARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    VtFloatArray value(data, data + num_elements);

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float2_array(nusd_stage_t stage,
                                              char const* attribute_path,
                                              float* _data,
                                              size_t num_elements,
                                              double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT2ARRAY &&
        attr_type != NUSD_TYPE_TEXCOORD2FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec2f* data = reinterpret_cast<GfVec2f*>(_data);
    VtArray<GfVec2f> value(data, data + num_elements);

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float3_array(nusd_stage_t stage,
                                              char const* attribute_path,
                                              float* _data,
                                              size_t num_elements,
                                              double time_code) {
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
        attr_type != NUSD_TYPE_TEXCOORD3FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec3f* data = reinterpret_cast<GfVec3f*>(_data);
    VtArray<GfVec3f> value(data, data + num_elements);

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_float4_array(nusd_stage_t stage,
                                              char const* attribute_path,
                                              float* _data,
                                              size_t num_elements,
                                              double time_code) {
    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdAttribute attr = _stage->GetAttributeAtPath(SdfPath(attribute_path));

    if (!attr) {
        return NUSD_RESULT_INVALID_ATTRIBUTE_PATH;
    }

    char const* attr_type = attr.GetTypeName().GetAsToken().GetText();
    if (attr_type != NUSD_TYPE_FLOAT4ARRAY &&
        attr_type != NUSD_TYPE_COLOR4FARRAY) {
        return NUSD_RESULT_WRONG_TYPE;
    }

    GfVec4f* data = reinterpret_cast<GfVec4f*>(_data);
    VtArray<GfVec4f> value(data, data + num_elements);

    attr.Set(std::move(value), time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_attribute_set_int_array(nusd_stage_t stage,
                                           char const* attribute_path,
                                           int* data,
                                           size_t num_elements,
                                           double time_code) {
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

nusd_result_t nusd_attribute_set_int2_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            int* _data,
                                            size_t num_elements,
                                            double time_code) {
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

nusd_result_t nusd_attribute_set_int3_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            int* _data,
                                            size_t num_elements,
                                            double time_code) {
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

nusd_result_t nusd_attribute_set_int4_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            int* _data,
                                            size_t num_elements,
                                            double time_code) {
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

nusd_result_t nusd_attribute_get_int64_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             double time_code,
                                             nusd_int64_array_t* int64_array) {
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

nusd_result_t nusd_attribute_get_uint_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            double time_code,
                                            nusd_uint_array_t* uint_array) {
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

nusd_result_t
nusd_attribute_get_uint64_array(nusd_stage_t stage,
                                char const* attribute_path,
                                double time_code,
                                nusd_uint64_array_t* uint64_array) {
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

nusd_result_t nusd_attribute_get_uchar_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             double time_code,
                                             nusd_uchar_array_t* uchar_array) {
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

nusd_result_t nusd_attribute_set_int64_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             int64_t* data,
                                             size_t num_elements,
                                             double time_code) {
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

nusd_result_t nusd_attribute_set_uint_array(nusd_stage_t stage,
                                            char const* attribute_path,
                                            unsigned int* data,
                                            size_t num_elements,
                                            double time_code) {
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

nusd_result_t nusd_attribute_set_uint64_array(nusd_stage_t stage,
                                              char const* attribute_path,
                                              uint64_t* data,
                                              size_t num_elements,
                                              double time_code) {
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

nusd_result_t nusd_attribute_set_uchar_array(nusd_stage_t stage,
                                             char const* attribute_path,
                                             unsigned char* data,
                                             size_t num_elements,
                                             double time_code) {
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

nusd_result_t nusd_attribute_set_double_array(nusd_stage_t stage,
                                              char const* attribute_path,
                                              double* data,
                                              size_t num_elements,
                                              double time_code) {
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

nusd_result_t nusd_attribute_set_double2_array(nusd_stage_t stage,
                                               char const* attribute_path,
                                               double* _data,
                                               size_t num_elements,
                                               double time_code) {
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

nusd_result_t nusd_attribute_set_double3_array(nusd_stage_t stage,
                                               char const* attribute_path,
                                               double* _data,
                                               size_t num_elements,
                                               double time_code) {
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

nusd_result_t nusd_attribute_set_double4_array(nusd_stage_t stage,
                                               char const* attribute_path,
                                               double* _data,
                                               size_t num_elements,
                                               double time_code) {
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
}