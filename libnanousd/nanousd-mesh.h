#ifndef NANOUSD_MESH_H
#define NANOUSD_MESH_H

#include "nanousd-array.h"
#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup MeshFunctions Mesh Functions
///
/// @brief Functions related to managing mesh geometry
///
/// @{

/// Defines a new USD mesh prim at the specified path with geometry data.
///
/// @param stage Valid stage handle.
/// @param mesh_path USD path where the mesh should be created (e.g., 
/// "/World/Geometry/MyMesh").
/// @param face_vertex_counts Array of integers specifying the number of vertices 
/// for each face.
/// @param num_faces Number of faces in the mesh (length of face_vertex_counts array).
/// @param face_vertex_indices Array of integers specifying vertex indices for each 
/// face (flattened).
/// @param num_face_vertex_indices Total number of vertex indices 
/// (length of face_vertex_indices array).
/// @param vertices Array of vertex positions as packed float triplets (x, y, z).
/// @param num_vertices Number of vertices in the mesh (length of vertices array / 3).
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if any pointer parameter is null
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the mesh cannot be defined at the 
/// specified path
///
/// @note stage must not be null.
/// @note mesh_path must not be null and should be a valid USD prim path.
/// @note face_vertex_counts must not be null and should contain num_faces elements.
/// @note face_vertex_indices must not be null and should contain num_face_vertex_indices elements.
/// @note vertices must not be null and should contain num_vertices * 3 float values 
/// (x, y, z triplets).
/// @note Creates a UsdGeomMesh prim with the specified topology and vertex positions.
/// @note The function sets the mesh's points, faceVertexCounts, and faceVertexIndices 
/// attributes.
/// @note Vertex positions are expected as consecutive float triplets representing 
/// 3D coordinates.
NANOUSD_API
nusd_result_t nusd_mesh_define(nusd_stage_t stage,
                               char const* mesh_path,
                               int* face_vertex_counts,
                               size_t num_faces,
                               int* face_vertex_indices,
                               size_t num_face_vertex_indices,
                               float* vertices,
                               size_t num_vertices);

/// Sets vertex normals for an existing mesh with specified interpolation mode.
///
/// @param stage Valid stage handle.
/// @param mesh_path USD path to an existing mesh prim.
/// @param normals Array of normal vectors as packed float triplets (x, y, z).
/// @param num_normals Number of normal vectors in the array (length of normals array / 3).
/// @param interpolation Interpolation mode for the normals (e.g., "vertex", "faceVarying", 
/// "uniform", "constant").
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage, mesh_path, or normals is null
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no mesh exists at the specified path
///
/// @note stage must not be null.
/// @note mesh_path must not be null and should point to an existing UsdGeomMesh prim.
/// @note normals must not be null and should contain num_normals * 3 float values 
/// (x, y, z triplets).
/// @note interpolation must not be null and should specify a valid USD interpolation 
/// mode.
/// @note Sets the mesh's normals attribute and normalsInterpolation metadata.
/// @note Normal vectors should be unit length for proper shading results.
/// @note Common interpolation modes: "vertex" (one normal per vertex), 
/// "faceVarying" (one normal per face-vertex), "uniform" (one normal per face), 
/// "constant" (one normal for entire mesh).
NANOUSD_API
nusd_result_t nusd_mesh_set_normals(nusd_stage_t stage,
                                    char const* mesh_path,
                                    float* normals,
                                    size_t num_normals,
                                    char const* interpolation);

/// @}

#ifdef __cplusplus
}
#endif

#endif
