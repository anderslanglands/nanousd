#ifndef NANOUSD_MATERIALS_H
#define NANOUSD_MATERIALS_H

#include "nanousd-array.h"
#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup MeshFunctions Mesh Functions
///
/// @brief Functions related to managing meshes
///
/// @{

NANOUSD_API
nusd_result_t nusd_mesh_define(nusd_stage_t stage,
                               char const* mesh_path,
                               int* face_vertex_counts,
                               size_t num_faces,
                               int* face_vertex_indices,
                               size_t num_face_vertex_indices,
                               float* vertices,
                               size_t num_vertices);

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
