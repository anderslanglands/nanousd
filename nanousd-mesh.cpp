#include "nanousd.h"

#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/property.h>
#include <pxr/usd/usd/relationship.h>
#include <pxr/usd/usd/stage.h>

#include <pxr/usd/usdGeom/mesh.h>

using namespace PXR_NS;

extern "C" {

nusd_result_t nusd_mesh_define(nusd_stage_t stage,
                               char const* mesh_path,
                               int* face_vertex_counts,
                               size_t num_faces,
                               int* face_vertex_indices,
                               size_t num_face_vertex_indices,
                               float* vertices,
                               size_t num_vertices) {
    
    if (stage == nullptr || mesh_path == nullptr || face_vertex_counts == nullptr || face_vertex_indices == nullptr || vertices == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);

    UsdGeomMesh mesh = UsdGeomMesh::Define(UsdStageWeakPtr(_stage), SdfPath(mesh_path));
    if (!mesh) {
        return NUSD_RESULT_DEFINE_PRIM_FAILED;
    }

    GfVec3f* _vertices = reinterpret_cast<GfVec3f*>(vertices);
    VtVec3fArray points(_vertices, _vertices+num_vertices);
    mesh.GetPointsAttr().Set(points);

    VtIntArray _face_vertex_counts(face_vertex_counts, face_vertex_counts+num_faces);
    mesh.GetFaceVertexCountsAttr().Set(_face_vertex_counts);

    VtIntArray _face_vertex_indices(face_vertex_indices, face_vertex_indices+num_face_vertex_indices);
    mesh.GetFaceVertexIndicesAttr().Set(_face_vertex_indices);
}


nusd_result_t nusd_mesh_set_normals(nusd_stage_t stage,
                                    char const* mesh_path,
                                    float* normals,
                                    size_t num_normals,
                                    char const* interpolation) {
    if (stage == nullptr || mesh_path == nullptr || normals == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomMesh mesh(_stage->GetPrimAtPath(SdfPath(mesh_path)));
    if (!mesh) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    GfVec3f* _normals = reinterpret_cast<GfVec3f*>(normals);
    VtVec3fArray points(_normals, _normals+num_normals);
    mesh.GetNormalsAttr().Set(normals);
    mesh.SetNormalsInterpolation(TfToken(interpolation));

    return NUSD_RESULT_OK;
}

}