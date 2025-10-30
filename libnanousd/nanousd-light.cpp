#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/usd/usdLux/rectLight.h>

using namespace PXR_NS;

extern "C" {

nusd_result_t nusd_rect_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     float width,
                                     float height,
                                     float intensity,
                                     float* color) {
    if (stage == nullptr || light_path == nullptr || color == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdLuxRectLight light = UsdLuxRectLight::Define(UsdStageWeakPtr(_stage), SdfPath(light_path));
    if (!light) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    light.GetWidthAttr().Set(width);
    light.GetHeightAttr().Set(height);
    light.GetIntensityAttr().Set(intensity);
    light.GetColorAttr().Set(GfVec3f(color[0], color[1], color[2]));

    return NUSD_RESULT_OK;
}

}