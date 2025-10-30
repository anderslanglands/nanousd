import pytest
import nanousd as nusd
import numpy as np


def test_prim_create_primvar_basic():
    """Test basic primvar creation and value setting."""
    stage = nusd.Stage.create_in_memory("test-primvar")
    
    # Create a mesh prim to add primvars to
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Create a basic primvar
    stage.prim_create_primvar("/World/Mesh", "testFloat3", nusd.FLOAT3, nusd.INTERPOLATION_VERTEX)
    
    # Set a value on the created primvar
    test_value = np.array([1.0, 0.5, 0.0], dtype=np.float32)
    stage.set_property("/World/Mesh.primvars:testFloat3", nusd.FLOAT3, test_value)
    
    # Verify we can read the value back
    retrieved_value = stage.get_property("/World/Mesh.primvars:testFloat3")
    np.testing.assert_array_equal(retrieved_value, test_value)


def test_prim_create_primvar_with_value():
    """Test primvar creation with immediate value setting."""
    stage = nusd.Stage.create_in_memory("test-primvar-value")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Create primvar with immediate value setting
    test_value = np.array([0.8, 0.4, 0.2], dtype=np.float32)
    stage.prim_create_primvar(
        "/World/Mesh", 
        "testColor", 
        nusd.FLOAT3, 
        nusd.INTERPOLATION_VERTEX,
        value=test_value
    )
    
    # Verify the value was set correctly
    retrieved_value = stage.get_property("/World/Mesh.primvars:testColor")
    np.testing.assert_array_equal(retrieved_value, test_value)


def test_prim_create_primvar_different_types():
    """Test primvar creation with different USD data types."""
    stage = nusd.Stage.create_in_memory("test-primvar-types")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Test FLOAT3 primvar
    stage.prim_create_primvar("/World/Mesh", "testFloat3", nusd.FLOAT3, nusd.INTERPOLATION_VERTEX)
    float3_value = np.array([1.0, 0.5, 0.0], dtype=np.float32)
    stage.set_property("/World/Mesh.primvars:testFloat3", nusd.FLOAT3, float3_value)
    retrieved_float3 = stage.get_property("/World/Mesh.primvars:testFloat3")
    np.testing.assert_array_equal(retrieved_float3, float3_value)
    
    # Test FLOAT2 primvar for UV coordinates
    stage.prim_create_primvar("/World/Mesh", "testFloat2", nusd.FLOAT2, nusd.INTERPOLATION_FACEVARYING)
    float2_value = np.array([0.5, 0.75], dtype=np.float32)
    stage.set_property("/World/Mesh.primvars:testFloat2", nusd.FLOAT2, float2_value)
    retrieved_float2 = stage.get_property("/World/Mesh.primvars:testFloat2")
    np.testing.assert_array_equal(retrieved_float2, float2_value)
    
    # Test FLOAT primvar for opacity
    stage.prim_create_primvar("/World/Mesh", "opacity", nusd.FLOAT, nusd.INTERPOLATION_CONSTANT)
    opacity_value = 0.8
    stage.set_property("/World/Mesh.primvars:opacity", nusd.FLOAT, opacity_value)
    retrieved_opacity = stage.get_property("/World/Mesh.primvars:opacity")
    assert abs(retrieved_opacity - opacity_value) < 1e-6
    
    # Test COLOR3F primvar
    stage.prim_create_primvar("/World/Mesh", "testColor3F", nusd.COLOR3F, nusd.INTERPOLATION_VERTEX)
    color_value = np.array([0.2, 0.8, 0.4], dtype=np.float32)
    stage.set_property("/World/Mesh.primvars:testColor3F", nusd.COLOR3F, color_value)
    retrieved_color = stage.get_property("/World/Mesh.primvars:testColor3F")
    np.testing.assert_array_equal(retrieved_color, color_value)


def test_prim_create_primvar_different_interpolations():
    """Test primvar creation with all interpolation modes."""
    stage = nusd.Stage.create_in_memory("test-primvar-interp")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    test_color = np.array([1.0, 0.0, 0.0], dtype=np.float32)
    
    # Test all interpolation modes
    interpolations = [
        ("constant_color", nusd.INTERPOLATION_CONSTANT),
        ("uniform_color", nusd.INTERPOLATION_UNIFORM),
        ("varying_color", nusd.INTERPOLATION_VARYING),
        ("vertex_color", nusd.INTERPOLATION_VERTEX),
        ("facevarying_color", nusd.INTERPOLATION_FACEVARYING),
    ]
    
    for primvar_name, interpolation in interpolations:
        stage.prim_create_primvar("/World/Mesh", primvar_name, nusd.FLOAT3, interpolation)
        primvar_path = f"/World/Mesh.primvars:{primvar_name}"
        stage.set_property(primvar_path, nusd.FLOAT3, test_color)
        retrieved_color = stage.get_property(primvar_path)
        np.testing.assert_array_equal(retrieved_color, test_color)


def test_prim_create_primvar_array_types():
    """Test primvar creation with array types."""
    stage = nusd.Stage.create_in_memory("test-primvar-arrays")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Test FLOAT3ARRAY primvar for multiple colors
    stage.prim_create_primvar("/World/Mesh", "colorArray", nusd.FLOAT3ARRAY, nusd.INTERPOLATION_VERTEX)
    color_array = np.array([
        [1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0], 
        [0.0, 0.0, 1.0]
    ], dtype=np.float32)
    stage.set_property("/World/Mesh.primvars:colorArray", nusd.FLOAT3ARRAY, color_array)
    retrieved_colors = stage.get_property("/World/Mesh.primvars:colorArray")
    np.testing.assert_array_equal(retrieved_colors, color_array)
    
    # Test FLOATARRAY primvar
    stage.prim_create_primvar("/World/Mesh", "weightArray", nusd.FLOATARRAY, nusd.INTERPOLATION_VERTEX)
    weight_array = np.array([0.1, 0.5, 0.8, 1.0], dtype=np.float32)
    stage.set_property("/World/Mesh.primvars:weightArray", nusd.FLOATARRAY, weight_array)
    retrieved_weights = stage.get_property("/World/Mesh.primvars:weightArray")
    np.testing.assert_array_equal(retrieved_weights, weight_array)


def test_prim_create_primvar_numpy_integration():
    """Test primvar NumPy array integration and operations."""
    stage = nusd.Stage.create_in_memory("test-primvar-numpy")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Create primvar with array value
    stage.prim_create_primvar("/World/Mesh", "testColors", nusd.FLOAT3ARRAY, nusd.INTERPOLATION_VERTEX)
    original_colors = np.array([
        [1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 0.0, 1.0],
        [1.0, 1.0, 0.0]
    ], dtype=np.float32)
    
    stage.set_property("/World/Mesh.primvars:testColors", nusd.FLOAT3ARRAY, original_colors)
    
    # Get the array and test NumPy operations
    color_array = stage.get_property("/World/Mesh.primvars:testColors")
    
    # Test basic array operations
    assert isinstance(color_array, nusd.Float3Array)
    assert color_array.shape == (4, 3)
    
    # Test NumPy compatibility
    dimmed_colors = color_array * 0.5
    expected_dimmed = original_colors * 0.5
    np.testing.assert_array_equal(dimmed_colors, expected_dimmed)
    
    # Test mean calculation
    mean_color = np.mean(color_array, axis=0)
    expected_mean = np.mean(original_colors, axis=0)
    np.testing.assert_array_equal(mean_color, expected_mean)


def test_prim_create_primvar_with_time_coding():
    """Test primvar creation with time-coded values."""
    stage = nusd.Stage.create_in_memory("test-primvar-time")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Create primvar
    stage.prim_create_primvar("/World/Mesh", "animatedColor", nusd.FLOAT3, nusd.INTERPOLATION_VERTEX)
    
    # Set values at different times
    time_0_color = np.array([1.0, 0.0, 0.0], dtype=np.float32)
    time_1_color = np.array([0.0, 1.0, 0.0], dtype=np.float32)
    time_2_color = np.array([0.0, 0.0, 1.0], dtype=np.float32)
    
    stage.set_property("/World/Mesh.primvars:animatedColor", nusd.FLOAT3, time_0_color, time_code=0.0)
    stage.set_property("/World/Mesh.primvars:animatedColor", nusd.FLOAT3, time_1_color, time_code=1.0)
    stage.set_property("/World/Mesh.primvars:animatedColor", nusd.FLOAT3, time_2_color, time_code=2.0)
    
    # Verify values at different times
    retrieved_0 = stage.get_property("/World/Mesh.primvars:animatedColor", time_code=0.0)
    retrieved_1 = stage.get_property("/World/Mesh.primvars:animatedColor", time_code=1.0)
    retrieved_2 = stage.get_property("/World/Mesh.primvars:animatedColor", time_code=2.0)
    
    np.testing.assert_array_equal(retrieved_0, time_0_color)
    np.testing.assert_array_equal(retrieved_1, time_1_color)
    np.testing.assert_array_equal(retrieved_2, time_2_color)


def test_prim_create_primvar_error_handling():
    """Test error handling for primvar creation."""
    stage = nusd.Stage.create_in_memory("test-primvar-errors")
    
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Mesh", "Mesh")
    
    # Test invalid prim path
    with pytest.raises(nusd.CreatePropertyError):
        stage.prim_create_primvar("/World/NonExistent", "testPrimvar", nusd.FLOAT3, nusd.INTERPOLATION_VERTEX)
    
    # Test completely invalid path
    with pytest.raises(nusd.CreatePropertyError):
        stage.prim_create_primvar("/InvalidPath", "testPrimvar", nusd.FLOAT3, nusd.INTERPOLATION_VERTEX)
    
    # Test with invalid type (should work at creation but might fail when setting value)
    stage.prim_create_primvar("/World/Mesh", "testPrimvar", nusd.FLOAT3, nusd.INTERPOLATION_VERTEX)
    
    # Test type mismatch when setting value
    with pytest.raises((nusd.SetPropertyError, ValueError, TypeError)):
        stage.set_property("/World/Mesh.primvars:testPrimvar", nusd.FLOAT3, "invalid_type")


def test_prim_create_primvar_complex_workflow():
    """Test a complete workflow with multiple primvars and operations."""
    stage = nusd.Stage.create_in_memory("test-primvar-workflow")
    
    # Create mesh hierarchy
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Geometry", "Xform")
    stage.define_prim("/World/Geometry/Mesh", "Mesh")
    
    mesh_path = "/World/Geometry/Mesh"
    
    # Create multiple primvars for a realistic mesh
    # Test colors (vertex colors) - use COLOR3FARRAY for multiple colors
    stage.prim_create_primvar(mesh_path, "testColor3", nusd.COLOR3FARRAY, nusd.INTERPOLATION_VERTEX)
    vertex_colors = np.array([
        [1.0, 0.0, 0.0],  # Red
        [0.0, 1.0, 0.0],  # Green  
        [0.0, 0.0, 1.0],  # Blue
        [1.0, 1.0, 0.0],  # Yellow
    ], dtype=np.float32)
    stage.set_property(f"{mesh_path}.primvars:testColor3", nusd.COLOR3FARRAY, vertex_colors)
    
    # UV coordinates (face-varying) - use FLOAT2ARRAY for multiple UV coords
    stage.prim_create_primvar(mesh_path, "st", nusd.FLOAT2ARRAY, nusd.INTERPOLATION_FACEVARYING)
    uv_coords = np.array([
        [0.0, 0.0],
        [1.0, 0.0],
        [1.0, 1.0],
        [0.0, 1.0],
    ], dtype=np.float32)
    stage.set_property(f"{mesh_path}.primvars:st", nusd.FLOAT2ARRAY, uv_coords)
    
    # Test vectors (vertex) - use VECTOR3FARRAY for multiple vectors
    stage.prim_create_primvar(mesh_path, "testVector3f", nusd.VECTOR3FARRAY, nusd.INTERPOLATION_VERTEX)
    test_vectors = np.array([
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 1.0],
    ], dtype=np.float32)
    stage.set_property(f"{mesh_path}.primvars:testVector3f", nusd.VECTOR3FARRAY, test_vectors)
    
    # Material ID (uniform per face)
    stage.prim_create_primvar(mesh_path, "materialId", nusd.INT, nusd.INTERPOLATION_UNIFORM)
    material_id = 1
    stage.set_property(f"{mesh_path}.primvars:materialId", nusd.INT, material_id)
    
    # Verify all primvars are accessible and correct
    retrieved_colors = stage.get_property(f"{mesh_path}.primvars:testColor3")
    retrieved_uvs = stage.get_property(f"{mesh_path}.primvars:st")
    retrieved_vectors = stage.get_property(f"{mesh_path}.primvars:testVector3f")
    retrieved_material_id = stage.get_property(f"{mesh_path}.primvars:materialId")
    
    np.testing.assert_array_equal(retrieved_colors, vertex_colors)
    np.testing.assert_array_equal(retrieved_uvs, uv_coords)
    np.testing.assert_array_equal(retrieved_vectors, test_vectors)
    assert retrieved_material_id == material_id
    
    # Test NumPy operations on the retrieved arrays
    # Brighten the colors
    brightened_colors = retrieved_colors * 1.5
    np.testing.assert_array_equal(brightened_colors, vertex_colors * 1.5)
    
    # Calculate average UV coordinate
    avg_uv = np.mean(retrieved_uvs, axis=0)
    expected_avg_uv = np.mean(uv_coords, axis=0)
    np.testing.assert_array_equal(avg_uv, expected_avg_uv)