#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdLux/rectLight.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdLux/domeLight.h>

using namespace PXR_NS;

extern "C" {

nusd_result_t nusd_rect_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     float width,
                                     float height,
                                     float intensity,
                                     float const* color) {
    if (stage == nullptr || light_path == nullptr || color == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdLuxRectLight light =
        UsdLuxRectLight::Define(UsdStageWeakPtr(_stage), SdfPath(light_path));
    if (!light) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    light.GetWidthAttr().Set(width);
    light.GetHeightAttr().Set(height);
    light.GetIntensityAttr().Set(intensity);
    light.GetColorAttr().Set(GfVec3f(color[0], color[1], color[2]));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_disk_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     float radius,
                                     float intensity,
                                     float const* color) {
    if (stage == nullptr || light_path == nullptr || color == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdLuxDiskLight light =
        UsdLuxDiskLight::Define(UsdStageWeakPtr(_stage), SdfPath(light_path));
    if (!light) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    light.GetRadiusAttr().Set(radius);
    light.GetIntensityAttr().Set(intensity);
    light.GetColorAttr().Set(GfVec3f(color[0], color[1], color[2]));

    return NUSD_RESULT_OK;
}

nusd_result_t nusd_sphere_light_define(nusd_stage_t stage,
                                       char const* light_path,
                                       float radius,
                                       float intensity,
                                       float const* color) {
    if (stage == nullptr || light_path == nullptr || color == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdLuxSphereLight light =
        UsdLuxSphereLight::Define(UsdStageWeakPtr(_stage), SdfPath(light_path));
    if (!light) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    light.GetRadiusAttr().Set(radius);
    light.GetIntensityAttr().Set(intensity);
    light.GetColorAttr().Set(GfVec3f(color[0], color[1], color[2]));

    return NUSD_RESULT_OK;
}


nusd_result_t nusd_dome_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     char const* texture_file,
                                     float intensity,
                                     float const* color) {
    if (stage == nullptr || light_path == nullptr || color == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdLuxDomeLight light = UsdLuxDomeLight::Define(UsdStageWeakPtr(_stage), SdfPath(light_path));
    
    if (!light) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    light.GetIntensityAttr().Set(intensity);
    light.GetColorAttr().Set(GfVec3f(color[0], color[1], color[2]));

    if (texture_file != nullptr) {
        light.GetTextureFileAttr().Set(SdfAssetPath(texture_file));
    }

    return NUSD_RESULT_OK;
}

}