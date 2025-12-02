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

    VtVec3fArray extent;
    mesh.ComputeExtent(points, &extent);
    mesh.GetExtentAttr().Set(extent);

    return NUSD_RESULT_OK;
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
    VtVec3fArray normal_array(_normals, _normals+num_normals);
    mesh.GetNormalsAttr().Set(normal_array);
    mesh.SetNormalsInterpolation(TfToken(interpolation));

    return NUSD_RESULT_OK;
}


NANOUSD_API
nusd_result_t nusd_mesh_set_subdivision_scheme(nusd_stage_t stage,
                                    char const* mesh_path,
                                    nusd_subdivision_scheme_t subdivision_scheme,
                                    nusd_triangle_subdivision_rule_t triangle_subdivision_rule) {
    if (stage == nullptr || mesh_path == nullptr) {
        return NUSD_RESULT_NULL_PARAMETER;
    }

    UsdStage* _stage = reinterpret_cast<UsdStage*>(stage);
    UsdGeomMesh mesh(_stage->GetPrimAtPath(SdfPath(mesh_path)));
    if (!mesh) {
        return NUSD_RESULT_INVALID_PRIM_PATH;
    }

    TfToken tok_subdivision_scheme;
    switch (subdivision_scheme) {
        case NUSD_SUBDIVISION_SCHEME_NONE:
            tok_subdivision_scheme = UsdGeomTokens->none;
            break;
        case NUSD_SUBDIVISION_SCHEME_CATMULL_CLARK:
            tok_subdivision_scheme = UsdGeomTokens->catmullClark;
            break;
        case NUSD_SUBDIVISION_SCHEME_LOOP:
            tok_subdivision_scheme = UsdGeomTokens->loop;
            break;
        case NUSD_SUBDIVISION_SCHEME_BILINEAR:
            tok_subdivision_scheme = UsdGeomTokens->bilinear;
            break;
        default:
            return NUSD_RESULT_INVALID_SUBDIVISION_SCHEME;
    }

    TfToken tok_triangle_subdivision_rule;
    switch (triangle_subdivision_rule) {
        case NUSD_TRIANGLE_SUBDIVISION_RULE_CATMULL_CLARK:
            tok_triangle_subdivision_rule = UsdGeomTokens->catmullClark;
            break;
        case NUSD_TRIANGLE_SUBDIVISION_RULE_SMOOTH:
            tok_triangle_subdivision_rule = UsdGeomTokens->smooth;
            break;
        default:
            return NUSD_RESULT_INVALID_TRIANGLE_SUBDIVISION_RULE;
    }

    mesh.GetSubdivisionSchemeAttr().Set(tok_subdivision_scheme);
    mesh.GetTriangleSubdivisionRuleAttr().Set(tok_triangle_subdivision_rule);

    return NUSD_RESULT_OK;
}

}