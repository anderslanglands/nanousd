#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/primvarsAPI.h>

using namespace PXR_NS;

using TokenTypeNameMap =
    std::unordered_map<char const*, PXR_NS::SdfValueTypeName>;
extern TokenTypeNameMap TOKEN_TO_TYPENAME;

extern "C" {

nusd_result_t nusd_prim_create_primvar(nusd_stage_t stage,
                                       char const* prim_path,
                                       char const* primvar_name,
                                       nusd_type_t primvar_type,
                                       char const* primvar_interpolation) {
    if (stage == nullptr || prim_path == nullptr || primvar_name == nullptr ||
        primvar_type == nullptr || primvar_interpolation == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomPrimvarsAPI pv_api =
        UsdGeomPrimvarsAPI(_stage->GetPrimAtPath(SdfPath(prim_path)));
    if (!pv_api) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    UsdGeomPrimvar pv = pv_api.CreatePrimvar(TfToken(primvar_name),
                                             TOKEN_TO_TYPENAME[primvar_type],
                                             TfToken(primvar_interpolation));
    if (!pv) {
        return NUSD_RESULT_CREATE_ATTRIBUTE_FAILED;
    }

    return NUSD_RESULT_OK;
}
}