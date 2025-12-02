#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/usd/usdGeom/boundable.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/primvarsAPI.h>
#include <pxr/usd/usdGeom/xformOp.h>
#include <pxr/usd/usdGeom/xformable.h>

using namespace PXR_NS;

using TokenTypeNameMap =
    std::unordered_map<char const*, PXR_NS::SdfValueTypeName>;
extern TokenTypeNameMap TOKEN_TO_TYPENAME;

extern "C" {

nusd_result_t nusd_prim_add_translate_op(nusd_stage_t stage,
                                         char const* xformable_path,
                                         char const* op_suffix,
                                         double const* translation,
                                         double time_code) {
    if (stage == nullptr || xformable_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomXformable xform =
        UsdGeomXformable(_stage->GetPrimAtPath(SdfPath(xformable_path)));
    if (!xform) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdGeomXformOp op =
        op_suffix != nullptr
            ? xform.AddTranslateOp(UsdGeomXformOp::PrecisionDouble,
                                   TfToken(op_suffix))
            : xform.AddTranslateOp(UsdGeomXformOp::PrecisionDouble);

    if (translation != nullptr) {
        op.Set(GfVec3d(translation[0], translation[1], translation[2]), time_code);
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_create_primvar(nusd_stage_t stage,
                                       char const* prim_path,
                                       char const* primvar_name,
                                       nusd_type_t primvar_type,
                                       nusd_interpolation_t primvar_interpolation) {
    if (stage == nullptr || prim_path == nullptr || primvar_name == nullptr ||
        primvar_type == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    TfToken tok_interpolation;
    switch (primvar_interpolation) {
        case NUSD_INTERPOLATION_CONSTANT:
            tok_interpolation = UsdGeomTokens->constant;
            break;
        case NUSD_INTERPOLATION_UNIFORM:
            tok_interpolation = UsdGeomTokens->uniform;
            break;
        case NUSD_INTERPOLATION_VERTEX:
            tok_interpolation = UsdGeomTokens->vertex;
            break;
        case NUSD_INTERPOLATION_VARYING:
            tok_interpolation = UsdGeomTokens->varying;
            break;
        case NUSD_INTERPOLATION_FACEVARYING:
            tok_interpolation = UsdGeomTokens->faceVarying;
            break;
        default:
                return NUSD_RESULT_INVALID_INTERPOLATION;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomPrimvarsAPI pv_api =
        UsdGeomPrimvarsAPI(_stage->GetPrimAtPath(SdfPath(prim_path)));
    if (!pv_api) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdGeomPrimvar pv = pv_api.CreatePrimvar(TfToken(primvar_name),
                                             TOKEN_TO_TYPENAME[primvar_type],
                                             tok_interpolation);
    if (!pv) {
        return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
    }

    return NUSD_RESULT_OK;
}

nusd_result_t
nusd_prim_set_extent(nusd_stage_t stage, char const* prim_path, float const* extent) {
    if (stage == nullptr || prim_path == nullptr || extent == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomBoundable boundable =
        UsdGeomBoundable(_stage->GetPrimAtPath(SdfPath(prim_path)));

    if (!boundable) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    GfVec3f const* _extent = reinterpret_cast<GfVec3f const*>(extent);
    VtVec3fArray value(_extent, _extent + 2);
    boundable.GetExtentAttr().Set(value);

    return NUSD_RESULT_OK;
}
}