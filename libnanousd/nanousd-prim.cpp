#include "nanousd.h"

#include <pxr/base/gf/matrix4d.h>
#include <pxr/base/gf/quatf.h>
#include <pxr/base/gf/rotation.h>

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

using TypeToTypeNameMap =
    std::unordered_map<nusd_type_t, PXR_NS::SdfValueTypeName>;
extern TypeToTypeNameMap TYPE_TO_TYPENAME;
extern std::unordered_map<char const*, nusd_type_t> TYPENAME_TO_TYPE;

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

nusd_result_t nusd_prim_add_rotate_op_axis_angle(nusd_stage_t stage,
                                                  char const* xformable_path,
                                                  char const* op_suffix,
                                                  double const* axis,
                                                  double angle_degrees,
                                                  double time_code) {
    if (stage == nullptr || xformable_path == nullptr || axis == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomXformable xform =
        UsdGeomXformable(_stage->GetPrimAtPath(SdfPath(xformable_path)));
    if (!xform) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    // Create orient op (uses quaternion representation)
    UsdGeomXformOp op =
        op_suffix != nullptr
            ? xform.AddOrientOp(UsdGeomXformOp::PrecisionFloat, TfToken(op_suffix))
            : xform.AddOrientOp(UsdGeomXformOp::PrecisionFloat);

    // Convert axis-angle to quaternion using GfRotation
    GfVec3d axisVec(axis[0], axis[1], axis[2]);
    GfRotation rotation(axisVec, angle_degrees);
    GfQuaternion quat = rotation.GetQuaternion();

    // Convert GfQuaternion (double) to GfQuatf (float) for PrecisionFloat orient op
    GfQuatf quatf(static_cast<float>(quat.GetReal()),
                  GfVec3f(static_cast<float>(quat.GetImaginary()[0]),
                          static_cast<float>(quat.GetImaginary()[1]),
                          static_cast<float>(quat.GetImaginary()[2])));

    op.Set(quatf, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_add_scale_op(nusd_stage_t stage,
                                     char const* xformable_path,
                                     char const* op_suffix,
                                     double const* scale,
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
            ? xform.AddScaleOp(UsdGeomXformOp::PrecisionDouble, TfToken(op_suffix))
            : xform.AddScaleOp(UsdGeomXformOp::PrecisionDouble);

    if (scale != nullptr) {
        op.Set(GfVec3d(scale[0], scale[1], scale[2]), time_code);
    }

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_add_look_at_op(nusd_stage_t stage,
                                        char const* xformable_path,
                                        char const* op_suffix,
                                        double const* eye,
                                        double const* target,
                                        double const* up,
                                        double time_code) {
    if (stage == nullptr || xformable_path == nullptr ||
        eye == nullptr || target == nullptr || up == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomXformable xform =
        UsdGeomXformable(_stage->GetPrimAtPath(SdfPath(xformable_path)));
    if (!xform) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    // Create a transform op (uses 4x4 matrix)
    UsdGeomXformOp op =
        op_suffix != nullptr
            ? xform.AddTransformOp(UsdGeomXformOp::PrecisionDouble, TfToken(op_suffix))
            : xform.AddTransformOp(UsdGeomXformOp::PrecisionDouble);

    // Create look-at matrix using GfMatrix4d::SetLookAt
    GfVec3d eyeVec(eye[0], eye[1], eye[2]);
    GfVec3d targetVec(target[0], target[1], target[2]);
    GfVec3d upVec(up[0], up[1], up[2]);

    GfMatrix4d lookAtMatrix;
    lookAtMatrix.SetLookAt(eyeVec, targetVec, upVec);

    op.Set(lookAtMatrix, time_code);

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_prim_create_primvar(nusd_stage_t stage,
                                       char const* prim_path,
                                       char const* primvar_name,
                                       nusd_type_t primvar_type,
                                       nusd_interpolation_t primvar_interpolation) {
    if (stage == nullptr || prim_path == nullptr || primvar_name == nullptr) {
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
                                             TYPE_TO_TYPENAME[primvar_type],
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