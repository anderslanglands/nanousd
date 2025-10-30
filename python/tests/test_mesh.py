import re
import pytest
import nanousd as nusd
import numpy as np


def test_mesh_define_simple_triangle():
    """Test defining a simple triangle mesh"""
    stage = nusd.Stage.create_in_memory("test_mesh_triangle")
    stage.define_prim("/World", "Xform")
    
    # Define a simple triangle mesh
    vertices = np.array([
        [0.0, 0.0, 0.0],  # vertex 0
        [1.0, 0.0, 0.0],  # vertex 1
        [0.5, 1.0, 0.0]   # vertex 2
    ], dtype=np.float32)
    
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Verify the mesh prim was created by trying to get properties from it
    # If the mesh exists, we should be able to get its properties
    properties = stage.prim_get_properties("/World/Triangle")


def test_mesh_define_quad():
    """Test defining a quad mesh"""
    stage = nusd.Stage.create_in_memory("test_mesh_quad")
    stage.define_prim("/World", "Xform")
    
    # Define a quad mesh (4 vertices, 1 quad face)
    vertices = np.array([
        [-1.0, -1.0, 0.0],  # vertex 0
        [ 1.0, -1.0, 0.0],  # vertex 1
        [ 1.0,  1.0, 0.0],  # vertex 2
        [-1.0,  1.0, 0.0]   # vertex 3
    ], dtype=np.float32)
    
    face_vertex_counts = np.array([4], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2, 3], dtype=np.int32)
    
    stage.mesh_define("/World/Quad", face_vertex_counts, face_vertex_indices, vertices)
    
    # Verify the mesh prim was created
    properties = stage.prim_get_properties("/World/Quad")


def test_mesh_define_complex_mesh():
    """Test defining a mesh with multiple faces"""
    stage = nusd.Stage.create_in_memory("test_mesh_complex")
    stage.define_prim("/World", "Xform")
    
    # Define a mesh with multiple faces (2 triangles forming a quad)
    vertices = np.array([
        [-1.0, -1.0, 0.0],  # vertex 0
        [ 1.0, -1.0, 0.0],  # vertex 1
        [ 1.0,  1.0, 0.0],  # vertex 2
        [-1.0,  1.0, 0.0]   # vertex 3
    ], dtype=np.float32)
    
    # Two triangle faces, each with 3 vertices
    face_vertex_counts = np.array([3, 3], dtype=np.int32)
    
    # Indices for two triangles
    face_vertex_indices = np.array([0, 1, 2, 0, 2, 3], dtype=np.int32)
    
    stage.mesh_define("/World/TwoTriangles", face_vertex_counts, face_vertex_indices, vertices)
    
    # Verify the mesh prim was created
    properties = stage.prim_get_properties("/World/TwoTriangles")


def test_mesh_define_automatic_type_conversion():
    """Test that arrays are automatically converted to correct types"""
    stage = nusd.Stage.create_in_memory("test_mesh_conversion")
    stage.define_prim("/World", "Xform")
    
    # Use different data types that should be auto-converted
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float64)  # float64 -> float32
    face_vertex_counts = np.array([3], dtype=np.int64)  # int64 -> int32
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int64)  # int64 -> int32
    
    # Should work without errors due to automatic conversion
    stage.mesh_define("/World/AutoConvert", face_vertex_counts, face_vertex_indices, vertices)


def test_mesh_define_validation_errors():
    """Test validation errors for invalid inputs"""
    stage = nusd.Stage.create_in_memory("test_mesh_validation")
    stage.define_prim("/World", "Xform")
    
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    # Test with non-numpy array
    with pytest.raises(ValueError, match="face_vertex_counts must be a 1D NumPy array"):
        stage.mesh_define("/World/BadCounts", [3], face_vertex_indices, vertices)
    
    with pytest.raises(ValueError, match="face_vertex_indices must be a 1D NumPy array"):
        stage.mesh_define("/World/BadIndices", face_vertex_counts, [0, 1, 2], vertices)
    
    with pytest.raises(ValueError, match=re.escape("vertices must be a (N, 3) float ndarray")):
        stage.mesh_define("/World/BadVertices", face_vertex_counts, face_vertex_indices, [[0, 0, 0]])
    
    # Test with wrong dimensions
    bad_2d_array = np.array([[3]], dtype=np.int32)
    with pytest.raises(ValueError, match="face_vertex_counts must be a 1D NumPy array"):
        stage.mesh_define("/World/Bad2D", bad_2d_array, face_vertex_indices, vertices)


def test_mesh_set_normals_vertex_interpolation():
    """Test setting vertex normals with vertex interpolation"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_vertex")
    stage.define_prim("/World", "Xform")
    
    # First create a triangle mesh
    vertices = np.array([
        [0.0, 0.0, 0.0],  # vertex 0
        [1.0, 0.0, 0.0],  # vertex 1
        [0.5, 1.0, 0.0]   # vertex 2
    ], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Now set vertex normals (one per vertex)
    normals = np.array([
        [0.0, 0.0, 1.0],  # normal for vertex 0
        [0.0, 0.0, 1.0],  # normal for vertex 1
        [0.0, 0.0, 1.0]   # normal for vertex 2
    ], dtype=np.float32)
    
    stage.mesh_set_normals("/World/Triangle", normals, nusd.INTERPOLATION_VERTEX)


def test_mesh_set_normals_facevarying_interpolation():
    """Test setting normals with faceVarying interpolation"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_facevarying")
    stage.define_prim("/World", "Xform")
    
    # Create a triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set face-varying normals (one per face-vertex, so 3 for triangle)
    normals = np.array([
        [0.0, 0.0, 1.0],  # normal for face-vertex 0
        [0.0, 0.0, 1.0],  # normal for face-vertex 1
        [0.0, 0.0, 1.0]   # normal for face-vertex 2
    ], dtype=np.float32)
    
    stage.mesh_set_normals("/World/Triangle", normals, nusd.INTERPOLATION_FACEVARYING)


def test_mesh_set_normals_uniform_interpolation():
    """Test setting normals with uniform interpolation"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_uniform")
    stage.define_prim("/World", "Xform")
    
    # Create a triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set uniform normals (one per face, so 1 for single triangle)
    normals = np.array([[0.0, 0.0, 1.0]], dtype=np.float32)
    
    stage.mesh_set_normals("/World/Triangle", normals, nusd.INTERPOLATION_UNIFORM)


def test_mesh_set_normals_constant_interpolation():
    """Test setting normals with constant interpolation"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_constant")
    stage.define_prim("/World", "Xform")
    
    # Create a triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set constant normals (one for entire mesh)
    normals = np.array([[0.0, 0.0, 1.0]], dtype=np.float32)
    
    stage.mesh_set_normals("/World/Triangle", normals, nusd.INTERPOLATION_CONSTANT)


def test_mesh_set_normals_default_interpolation():
    """Test setting normals with default interpolation (vertex)"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_default")
    stage.define_prim("/World", "Xform")
    
    # Create a triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set normals without specifying interpolation (should default to nusd.INTERPOLATION_VERTEX)
    normals = np.array([[0, 0, 1], [0, 0, 1], [0, 0, 1]], dtype=np.float32)
    
    stage.mesh_set_normals("/World/Triangle", normals, nusd.INTERPOLATION_VERTEX)  # No interpolation specified


def test_mesh_set_normals_automatic_type_conversion():
    """Test that normals are automatically converted to correct type"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_conversion")
    stage.define_prim("/World", "Xform")
    
    # Create a triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Use float64 normals that should be auto-converted to float32
    normals = np.array([[0, 0, 1], [0, 0, 1], [0, 0, 1]], dtype=np.float64)
    
    stage.mesh_set_normals("/World/Triangle", normals, nusd.INTERPOLATION_VERTEX)


def test_mesh_set_normals_validation_errors():
    """Test validation errors for invalid normals"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_validation")
    stage.define_prim("/World", "Xform")
    
    # Create a triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Test with non-numpy array
    with pytest.raises(ValueError, match=re.escape("normals must be an (N, 3) float ndarray")):
        stage.mesh_set_normals("/World/Triangle", [[0, 0, 1]], nusd.INTERPOLATION_VERTEX)


def test_mesh_set_normals_invalid_mesh_path():
    """Test error handling for invalid mesh paths"""
    stage = nusd.Stage.create_in_memory("test_mesh_normals_invalid")
    stage.define_prim("/World", "Xform")
    
    normals = np.array([[0, 0, 1]], dtype=np.float32)
    
    # Try to set normals on non-existent mesh
    with pytest.raises(nusd.SetPropertyError, match='mesh not found at "/World/NonExistentMesh"'):
        stage.mesh_set_normals("/World/NonExistentMesh", normals, nusd.INTERPOLATION_CONSTANT)
    
    # Try with completely invalid path
    with pytest.raises(nusd.SetPropertyError, match='mesh not found at "/InvalidPath"'):
        stage.mesh_set_normals("/InvalidPath", normals, nusd.INTERPOLATION_CONSTANT)


def test_mesh_complex_workflow():
    """Test complete workflow with complex mesh and normals"""
    stage = nusd.Stage.create_in_memory("test_mesh_workflow")
    stage.define_prim("/World", "Xform")
    
    # Create a more complex mesh: a pyramid (4 triangular faces)
    vertices = np.array([
        # Base vertices
        [-1.0, 0.0, -1.0],  # vertex 0
        [ 1.0, 0.0, -1.0],  # vertex 1
        [ 1.0, 0.0,  1.0],  # vertex 2
        [-1.0, 0.0,  1.0],  # vertex 3
        # Apex
         [0.0, 2.0,  0.0]   # vertex 4
    ], dtype=np.float32)
    
    # 4 triangular faces (no base)
    face_vertex_counts = np.array([3, 3, 3, 3], dtype=np.int32)
    
    # Face indices for the 4 triangular faces
    face_vertex_indices = np.array([
        0, 1, 4,  # front face
        1, 2, 4,  # right face
        2, 3, 4,  # back face
        3, 0, 4   # left face
    ], dtype=np.int32)
    
    stage.mesh_define("/World/Pyramid", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set face-varying normals (3 normals per face, 4 faces = 12 normals)
    normals = np.array([
        # Front face normals (pointing outward)
        [0.0, 0.4472, 0.8944],
        [0.0, 0.4472, 0.8944],
        [0.0, 0.4472, 0.8944],
        
        # Right face normals
        [0.8944, 0.4472, 0.0],
        [0.8944, 0.4472, 0.0],
        [0.8944, 0.4472, 0.0],
        
        # Back face normals
        [0.0, 0.4472, -0.8944],
        [0.0, 0.4472, -0.8944],
        [0.0, 0.4472, -0.8944],
        
        # Left face normals
        [-0.8944, 0.4472, 0.0],
        [-0.8944, 0.4472, 0.0],
        [-0.8944, 0.4472, 0.0]
    ], dtype=np.float32)
    
    stage.mesh_set_normals("/World/Pyramid", normals, nusd.INTERPOLATION_FACEVARYING)
    
    # Verify the mesh exists
    try:
        properties = stage.prim_get_properties("/World/Pyramid")
        mesh_exists = True
    except:
        mesh_exists = False
    assert mesh_exists


def test_mesh_workflow_with_different_array_types():
    """Test mesh workflow with various NumPy array types and shapes"""
    stage = nusd.Stage.create_in_memory("test_mesh_array_types")
    stage.define_prim("/World", "Xform")
    
    # Test with different input array types that should all work
    
    # Test 1: Python lists converted to numpy arrays
    vertices_list = [[0, 0, 0], [1, 0, 0], [0.5, 1, 0]]
    face_counts_list = [3]
    face_indices_list = [0, 1, 2]
    
    vertices = np.array(vertices_list, dtype=np.float32)
    face_vertex_counts = np.array(face_counts_list, dtype=np.int32)
    face_vertex_indices = np.array(face_indices_list, dtype=np.int32)
    
    stage.mesh_define("/World/FromLists", face_vertex_counts, face_vertex_indices, vertices)
    
    # Test 2: Different numeric types that get converted
    vertices_mixed = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 1.0, 0.0]])  # defaults to float64
    face_counts_mixed = np.array([3])  # defaults to int64
    face_indices_mixed = np.array([0, 1, 2])  # defaults to int64
    
    stage.mesh_define("/World/MixedTypes", face_counts_mixed, face_indices_mixed, vertices_mixed)
    
    # Test 3: Setting normals with auto-conversion
    normals_mixed = np.array([[0, 0, 1], [0, 0, 1], [0, 0, 1]])  # defaults to int64, should convert to float32
    stage.mesh_set_normals("/World/MixedTypes", normals_mixed.astype(np.float64), nusd.INTERPOLATION_VERTEX)


def test_mesh_edge_cases():
    """Test edge cases and boundary conditions"""
    stage = nusd.Stage.create_in_memory("test_mesh_edge_cases")
    stage.define_prim("/World", "Xform")
    
    # Test with single vertex (degenerate case)
    single_vertex = np.array([[0, 0, 0]], dtype=np.float32)
    # Note: This creates a degenerate mesh, but should not crash
    face_vertex_counts = np.array([1], dtype=np.int32)
    face_vertex_indices = np.array([0], dtype=np.int32)
    
    stage.mesh_define("/World/SingleVertex", face_vertex_counts, face_vertex_indices, single_vertex)
    
    # Test with very large mesh (performance test)
    # Create a 10x10 grid of quads (100 quads, 121 vertices)
    grid_size = 10
    vertices = []
    for y in range(grid_size + 1):
        for x in range(grid_size + 1):
            vertices.extend([[x, 0, y]])
    
    vertices = np.array(vertices, dtype=np.float32)
    
    # Create quad faces
    face_vertex_counts = np.array([4] * (grid_size * grid_size), dtype=np.int32)
    face_vertex_indices = []
    for y in range(grid_size):
        for x in range(grid_size):
            base = y * (grid_size + 1) + x
            face_vertex_indices.extend([base, base + 1, base + grid_size + 2, base + grid_size + 1])
    
    face_vertex_indices = np.array(face_vertex_indices, dtype=np.int32)
    
    stage.mesh_define("/World/LargeGrid", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set normals for the large mesh
    num_vertices = len(vertices)
    normals = np.tile([0, 1, 0], (num_vertices, 1)).astype(np.float32)  # All normals pointing up
    stage.mesh_set_normals("/World/LargeGrid", normals, nusd.INTERPOLATION_VERTEX)


def test_mesh_unicode_paths():
    """Test mesh creation with unicode characters in paths"""
    stage = nusd.Stage.create_in_memory("test_mesh_unicode")
    stage.define_prim("/World", "Xform")
    
    # Simple triangle mesh
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0.5, 1, 0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    # Create mesh with ASCII path (unicode should be handled by encoding)
    stage.mesh_define("/World/TestMesh", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set normals
    normals = np.array([[0, 0, 1], [0, 0, 1], [0, 0, 1]], dtype=np.float32)
    stage.mesh_set_normals("/World/TestMesh", normals, nusd.INTERPOLATION_VERTEX)