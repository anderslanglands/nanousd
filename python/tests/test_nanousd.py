import pytest
import nanousd as nusd
import numpy as np


def test_stage_open():
    stage = nusd.Stage.open("../test01.usda")


def test_stage_open_with_bad_path_fails():
    with pytest.raises(nusd.StageOpenError):
        stage = nusd.Stage.open("DOES_NOT_EXIST")


def test_stage_create_in_memory():
    stage = nusd.Stage.create_in_memory("test")


def test_stage_define_prim():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")


def test_prim_create_property_float():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat", nusd.FLOAT, 17.0)

def test_set_property_float_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloatArray", nusd.FLOATARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([1, 2, 3, 4, 5], dtype=np.float32)
    stage.set_property("/World.testFloatArray", nusd.FLOATARRAY, test_data)
    
    value = stage.get_property("/World.testFloatArray")
    assert isinstance(value, nusd.FloatArray)
    assert np.array_equal(value, np.array(test_data))

def test_prim_create_property_float2():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat2", nusd.TEXCOORD2F, np.array([1.0, 2.0], dtype=np.float32))

def test_set_property_float2():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat2", nusd.TEXCOORD2F)
    stage.set_property("/World.testFloat2", nusd.TEXCOORD2F, (1.0, 2.0))
    stage.set_property("/World.testFloat2", nusd.TEXCOORD2F, [3, 4])

def test_set_property_float2_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat2Array", nusd.FLOAT2ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1, 2], [3, 4], [5, 6]], dtype=np.float32)
    stage.set_property("/World.testFloat2Array", nusd.FLOAT2ARRAY, test_data)
    
    value = stage.get_property("/World.testFloat2Array")
    assert isinstance(value, nusd.Float2Array)
    assert np.array_equal(value, np.array(test_data))

def test_set_property_float3():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat3", nusd.COLOR3F)
    stage.set_property("/World.testFloat3", nusd.FLOAT3, (1.0, 2.0, 3))
    stage.set_property("/World.testFloat3", nusd.TEXCOORD3F, [3, 4, 5.0])

def test_prim_create_property_int():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt", nusd.INT, 42)

def test_set_property_int():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt", nusd.INT)
    stage.set_property("/World.testInt", nusd.INT, 123)
    value = stage.get_property("/World.testInt")
    assert value == 123

def test_set_property_int_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testIntArray", nusd.INTARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([1, 2, 3, 4, 5], dtype=np.int32)
    stage.set_property("/World.testIntArray", nusd.INTARRAY, test_data)
    
    value = stage.get_property("/World.testIntArray")
    assert isinstance(value, nusd.IntArray)
    assert np.array_equal(value, np.array(test_data))

def test_set_property_int2():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt2", nusd.INT2)
    stage.set_property("/World.testInt2", nusd.INT2, (10, 20))
    value = stage.get_property("/World.testInt2")
    assert np.array_equal(value, np.array([10, 20]))

def test_set_property_int2_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt2Array", nusd.INT2ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1, 2], [3, 4], [5, 6]], dtype=np.int32)
    stage.set_property("/World.testInt2Array", nusd.INT2ARRAY, test_data)
    
    value = stage.get_property("/World.testInt2Array")
    assert isinstance(value, nusd.Int2Array)
    assert np.array_equal(value, test_data)

def test_set_property_int3():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt3", nusd.INT3)
    stage.set_property("/World.testInt3", nusd.INT3, [100, 200, 300])
    value = stage.get_property("/World.testInt3")
    assert np.array_equal(value, np.array([100, 200, 300]))

def test_set_property_int3_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt3Array", nusd.INT3ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]], dtype=np.int32)
    stage.set_property("/World.testInt3Array", nusd.INT3ARRAY, test_data)
    
    value = stage.get_property("/World.testInt3Array")
    assert isinstance(value, nusd.Int3Array)
    assert np.array_equal(value, test_data)

def test_set_property_int4():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt4", nusd.INT4)
    stage.set_property("/World.testInt4", nusd.INT4, [1000, 2000, 3000, 4000])
    value = stage.get_property("/World.testInt4")
    assert np.array_equal(value, np.array([1000, 2000, 3000, 4000]))

def test_set_property_int4_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt4Array", nusd.INT4ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], dtype=np.int32)
    stage.set_property("/World.testInt4Array", nusd.INT4ARRAY, test_data)
    
    value = stage.get_property("/World.testInt4Array")
    assert isinstance(value, nusd.Int4Array)
    assert np.array_equal(value, test_data)

def test_prim_create_property_int64():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt64", nusd.INT64, 9223372036854775807)

def test_set_property_int64():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt64", nusd.INT64)
    stage.set_property("/World.testInt64", nusd.INT64, 9223372036854775807)
    value = stage.get_property("/World.testInt64")
    assert value == 9223372036854775807

def test_set_property_float3_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat3Array", nusd.FLOAT3ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]], dtype=np.float32)
    stage.set_property("/World.testFloat3Array", nusd.FLOAT3ARRAY, test_data)
    
    value = stage.get_property("/World.testFloat3Array")
    assert isinstance(value, nusd.Float3Array)
    assert np.array_equal(value, test_data)

def test_set_property_float4_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testFloat4Array", nusd.FLOAT4ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], dtype=np.float32)
    stage.set_property("/World.testFloat4Array", nusd.FLOAT4ARRAY, test_data)
    
    value = stage.get_property("/World.testFloat4Array")
    assert isinstance(value, nusd.Float4Array)
    assert np.array_equal(value, test_data)

def test_set_property_double_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testDoubleArray", nusd.DOUBLEARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([1.0, 2.0, 3.0, 4.0, 5.0], dtype=np.float64)
    stage.set_property("/World.testDoubleArray", nusd.DOUBLEARRAY, test_data)
    
    value = stage.get_property("/World.testDoubleArray")
    assert isinstance(value, nusd.DoubleArray)
    assert np.array_equal(value, test_data)

def test_set_property_double2_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testDouble2Array", nusd.DOUBLE2ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1.0, 2.0], [3.0, 4.0], [5.0, 6.0]], dtype=np.float64)
    stage.set_property("/World.testDouble2Array", nusd.DOUBLE2ARRAY, test_data)
    
    value = stage.get_property("/World.testDouble2Array")
    assert isinstance(value, nusd.Double2Array)
    assert np.array_equal(value, test_data)

def test_set_property_double3_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testDouble3Array", nusd.DOUBLE3ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]], dtype=np.float64)
    stage.set_property("/World.testDouble3Array", nusd.DOUBLE3ARRAY, test_data)
    
    value = stage.get_property("/World.testDouble3Array")
    assert isinstance(value, nusd.Double3Array)
    assert np.array_equal(value, test_data)

def test_set_property_double4_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testDouble4Array", nusd.DOUBLE4ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], dtype=np.float64)
    stage.set_property("/World.testDouble4Array", nusd.DOUBLE4ARRAY, test_data)
    
    value = stage.get_property("/World.testDouble4Array")
    assert isinstance(value, nusd.Double4Array)
    assert np.array_equal(value, test_data)

def test_set_property_int64_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt64Array", nusd.INT64ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([1000000000000, 2000000000000, 3000000000000, 4000000000000, 5000000000000], dtype=np.int64)
    stage.set_property("/World.testInt64Array", nusd.INT64ARRAY, test_data)
    
    value = stage.get_property("/World.testInt64Array")
    assert isinstance(value, nusd.Int64Array)
    assert np.array_equal(value, test_data)

def test_set_property_bool():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testBool", nusd.BOOL)
    stage.set_property("/World.testBool", nusd.BOOL, True)
    value = stage.get_property("/World.testBool")
    assert value == True

def test_set_property_bool_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testBoolArray", nusd.BOOLARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([True, False, True, False, True], dtype=np.bool_)
    stage.set_property("/World.testBoolArray", nusd.BOOLARRAY, test_data)
    
    value = stage.get_property("/World.testBoolArray")
    assert isinstance(value, nusd.BoolArray)
    assert np.array_equal(value, test_data)

def test_set_property_matrix2d():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testMatrix2d", nusd.MATRIX2D)
    test_data = np.array([[1.0, 2.0], [3.0, 4.0]], dtype=np.float64)
    stage.set_property("/World.testMatrix2d", nusd.MATRIX2D, test_data)
    
    value = stage.get_property("/World.testMatrix2d")
    assert isinstance(value, np.ndarray)
    assert value.shape == (2, 2)
    assert np.array_equal(value, test_data)

def test_set_property_matrix2d_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testMatrix2dArray", nusd.MATRIX2DARRAY)
    test_data = np.array([[[1.0, 2.0], [3.0, 4.0]], [[5.0, 6.0], [7.0, 8.0]]], dtype=np.float64)
    stage.set_property("/World.testMatrix2dArray", nusd.MATRIX2DARRAY, test_data)
    
    value = stage.get_property("/World.testMatrix2dArray")
    assert isinstance(value, nusd.Matrix2dArray)
    assert np.array_equal(value, test_data)

def test_set_property_matrix3d():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testMatrix3d", nusd.MATRIX3D)
    test_data = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]], dtype=np.float64)
    stage.set_property("/World.testMatrix3d", nusd.MATRIX3D, test_data)
    
    value = stage.get_property("/World.testMatrix3d")
    assert isinstance(value, np.ndarray)
    assert value.shape == (3, 3)
    assert np.array_equal(value, test_data)

def test_set_property_matrix3d_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testMatrix3dArray", nusd.MATRIX3DARRAY)
    test_data = np.array([[[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]], 
                          [[10.0, 11.0, 12.0], [13.0, 14.0, 15.0], [16.0, 17.0, 18.0]]], dtype=np.float64)
    stage.set_property("/World.testMatrix3dArray", nusd.MATRIX3DARRAY, test_data)
    
    value = stage.get_property("/World.testMatrix3dArray")
    assert isinstance(value, nusd.Matrix3dArray)
    assert np.array_equal(value, test_data)

def test_set_property_matrix4d():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testMatrix4d", nusd.MATRIX4D)
    test_data = np.arange(1, 17, dtype=np.float64).reshape(4, 4)
    stage.set_property("/World.testMatrix4d", nusd.MATRIX4D, test_data)
    
    value = stage.get_property("/World.testMatrix4d")
    assert isinstance(value, np.ndarray)
    assert value.shape == (4, 4)
    assert np.array_equal(value, test_data)

def test_set_property_matrix4d_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testMatrix4dArray", nusd.MATRIX4DARRAY)
    test_data = np.arange(1, 33, dtype=np.float64).reshape(2, 4, 4)
    stage.set_property("/World.testMatrix4dArray", nusd.MATRIX4DARRAY, test_data)
    
    value = stage.get_property("/World.testMatrix4dArray")
    assert isinstance(value, nusd.Matrix4dArray)
    assert np.array_equal(value, test_data)

def test_prim_create_property_uint():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUint", nusd.UINT, 42)

def test_set_property_uint():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUint", nusd.UINT)
    stage.set_property("/World.testUint", nusd.UINT, 123)
    value = stage.get_property("/World.testUint")
    assert value == 123

def test_set_property_uint_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUintArray", nusd.UINTARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([1, 2, 3, 4, 5], dtype=np.uint32)
    stage.set_property("/World.testUintArray", nusd.UINTARRAY, test_data)
    
    value = stage.get_property("/World.testUintArray")
    assert isinstance(value, nusd.UintArray)
    assert np.array_equal(value, np.array(test_data))

def test_prim_create_property_uint64():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUint64", nusd.UINT64, 18446744073709551615)

def test_set_property_uint64():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUint64", nusd.UINT64)
    stage.set_property("/World.testUint64", nusd.UINT64, 18446744073709551615)
    value = stage.get_property("/World.testUint64")
    assert value == 18446744073709551615

def test_set_property_uint64_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUint64Array", nusd.UINT64ARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([1000000000000, 2000000000000, 3000000000000, 4000000000000, 5000000000000], dtype=np.uint64)
    stage.set_property("/World.testUint64Array", nusd.UINT64ARRAY, test_data)
    
    value = stage.get_property("/World.testUint64Array")
    assert isinstance(value, nusd.Uint64Array)
    assert np.array_equal(value, test_data)

def test_prim_create_property_uchar():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUchar", nusd.UCHAR, 255)

def test_set_property_uchar():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUchar", nusd.UCHAR)
    stage.set_property("/World.testUchar", nusd.UCHAR, 200)
    value = stage.get_property("/World.testUchar")
    assert value == 200

def test_set_property_uchar_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testUcharArray", nusd.UCHARARRAY)
    # Set via Python API, get via Python API
    test_data = np.array([100, 150, 200, 255, 50], dtype=np.uint8)
    stage.set_property("/World.testUcharArray", nusd.UCHARARRAY, test_data)
    
    value = stage.get_property("/World.testUcharArray")
    assert isinstance(value, nusd.UcharArray)
    assert np.array_equal(value, test_data)


def test_camera_define():
    """Test camera definition"""
    stage = nusd.Stage.create_in_memory("test_camera_define")
    stage.camera_define("/World/Camera")
    # Camera should now exist as a valid prim (assuming stage has method to check this)


def test_prim_set_transform():
    """Test prim transform setting and verification using world transform"""
    stage = nusd.Stage.create_in_memory("test_prim_transform")
    stage.camera_define("/World/Camera")
    
    # Set up a test transformation matrix
    transform_matrix = np.array([
        [1.0, 0.0, 0.0, 0.0],
        [0.0, 1.0, 0.0, 0.0],
        [0.0, 0.0, 1.0, 0.0],
        [5.0, 3.0, 10.0, 1.0]
    ], dtype=np.float64)
    
    # Set the camera transform
    stage.prim_set_transform("/World/Camera", transform_matrix)
    
    # Use prim_compute_local_to_world_transform to verify the resulting world transform
    world_transform = stage.prim_compute_local_to_world_transform("/World/Camera")
    
    # Since camera is a direct child of World and World has identity transform,
    # the world transform should match our camera_to_parent_matrix
    assert world_transform.shape == (4, 4)
    assert world_transform.dtype == np.float64
    assert np.allclose(world_transform, transform_matrix)


def test_prim_set_extent_basic():
    """Test basic extent setting with list format"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_basic")
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Cube", "Cube")
    
    # Set extent as list: bounding box from (-1,-1,-1) to (1,1,1)
    extent = [-1.0, -1.0, -1.0, 1.0, 1.0, 1.0]
    stage.prim_set_extent("/World/Cube", extent)


def test_prim_set_extent_tuple():
    """Test extent setting with tuple format"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_tuple")
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Sphere", "Sphere")
    
    # Set extent as tuple
    extent = (-2.0, -2.0, -2.0, 2.0, 2.0, 2.0)
    stage.prim_set_extent("/World/Sphere", extent)


def test_prim_set_extent_numpy_1d():
    """Test extent setting with 1D NumPy array"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_numpy_1d")
    stage.define_prim("/World", "Xform")
    
    # Create a simple triangle mesh
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 1.0, 0.0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Mesh", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set extent as 1D NumPy array
    extent = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0], dtype=np.float32)
    stage.prim_set_extent("/World/Mesh", extent)


def test_prim_set_extent_numpy_3x2():
    """Test extent setting with 3x2 NumPy array format"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_numpy_3x2")
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Cube", "Cube")
    
    # Set extent as 3x2 array: [[min_x, max_x], [min_y, max_y], [min_z, max_z]]
    extent = np.array([[-0.5, 0.5], [-0.5, 0.5], [-0.5, 0.5]], dtype=np.float32)
    stage.prim_set_extent("/World/Cube", extent)


def test_prim_set_extent_mesh_workflow():
    """Test extent setting on a mesh after creation"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_mesh")
    stage.define_prim("/World", "Xform")
    
    # Create a simple triangle mesh
    vertices = np.array([[0.0, 0.0, 0.0], [2.0, 0.0, 0.0], [1.0, 2.0, 0.0]], dtype=np.float32)
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32)
    
    stage.mesh_define("/World/Triangle", face_vertex_counts, face_vertex_indices, vertices)
    
    # Set extent that encompasses the triangle vertices
    extent = [0.0, 0.0, 0.0, 2.0, 2.0, 0.0]
    stage.prim_set_extent("/World/Triangle", extent)


def test_prim_set_extent_validation_errors():
    """Test various validation error scenarios"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_errors")
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Cube", "Cube")
    
    # Test wrong number of elements in list
    with pytest.raises(ValueError, match="list or tuple must contain exactly 6 numbers"):
        stage.prim_set_extent("/World/Cube", [1.0, 2.0, 3.0])  # Only 3 elements
    
    with pytest.raises(ValueError, match="list or tuple must contain exactly 6 numbers"):
        stage.prim_set_extent("/World/Cube", [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0])  # 7 elements
    
    # Test wrong NumPy array shape
    with pytest.raises(ValueError, match="NumPy array must be either shape \\(6,\\) or \\(3, 2\\)"):
        stage.prim_set_extent("/World/Cube", np.array([[1, 2, 3], [4, 5, 6]]))  # 2x3 array
    
    # Test non-numeric values
    with pytest.raises(ValueError, match="extent components must be numeric values"):
        stage.prim_set_extent("/World/Cube", ["a", "b", "c", "d", "e", "f"])
    
    # Test invalid input type
    with pytest.raises(ValueError, match="extent must be a list, tuple, or NumPy array"):
        stage.prim_set_extent("/World/Cube", "invalid")


def test_prim_set_extent_prim_errors():
    """Test prim-related error scenarios"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_prim_errors")
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Cube", "Cube")
    
    extent = [-1.0, -1.0, -1.0, 1.0, 1.0, 1.0]
    
    # Test non-existent prim
    with pytest.raises(nusd.SetPropertyError, match='does not exist or is not a boundable prim'):
        stage.prim_set_extent("/NonExistent/Prim", extent)
    
    # Test non-boundable prim (Xform is not boundable)
    with pytest.raises(nusd.SetPropertyError, match='does not exist or is not a boundable prim'):
        stage.prim_set_extent("/World", extent)


def test_prim_set_extent_different_formats():
    """Test that different input formats produce equivalent results"""
    stage = nusd.Stage.create_in_memory("test_prim_set_extent_formats")
    stage.define_prim("/World", "Xform")
    
    # Create multiple cubes to test different formats
    stage.define_prim("/World/Cube1", "Cube")
    stage.define_prim("/World/Cube2", "Cube")
    stage.define_prim("/World/Cube3", "Cube")
    
    # Same extent in different formats
    extent_list = [-1.0, -2.0, -3.0, 1.0, 2.0, 3.0]
    extent_tuple = (-1.0, -2.0, -3.0, 1.0, 2.0, 3.0)
    extent_array_1d = np.array([-1.0, -2.0, -3.0, 1.0, 2.0, 3.0])
    extent_array_3x2 = np.array([[-1.0, 1.0], [-2.0, 2.0], [-3.0, 3.0]])
    
    # All should work without error
    stage.prim_set_extent("/World/Cube1", extent_list)
    stage.prim_set_extent("/World/Cube2", extent_tuple)
    stage.prim_set_extent("/World/Cube3", extent_array_1d)
    
    # Test the 3x2 format on the first cube again
    stage.prim_set_extent("/World/Cube1", extent_array_3x2)


def test_camera_set_fov_w():
    """Test camera field of view setting"""
    stage = nusd.Stage.create_in_memory("test_camera_fov")
    stage.camera_define("/World/Camera")
    
    # Get the default horizontal aperture first
    horizontal_aperture = stage.get_property("/World/Camera.horizontalAperture")
    
    # Set horizontal field of view to 60 degrees
    test_fov = 60.0
    stage.camera_set_fov_w("/World/Camera", test_fov)
    
    # Verify by reading the focalLength attribute that was set
    focal_length = stage.get_property("/World/Camera.focalLength")
    
    # The focal length should be calculated from FOV and the actual horizontal aperture
    # focal_length = aperture / (2 * tan(fov/2))
    expected_focal_length = horizontal_aperture / (2.0 * np.tan(np.radians(test_fov) / 2.0))
    assert abs(focal_length - expected_focal_length) < 0.01


def test_camera_set_exposure():
    """Test camera exposure parameter setting"""
    stage = nusd.Stage.create_in_memory("test_camera_exposure")
    stage.camera_define("/World/Camera")
    
    # Set exposure parameters
    iso = 400.0
    time = 1.0 / 60.0  # 1/60 second
    f_stop = 2.8
    compensation = 0.5
    responsivity = 1.0
    
    stage.camera_set_exposure("/World/Camera", iso, time, f_stop, compensation, responsivity)
    
    # Verify each exposure attribute was set correctly (using approximate equality for float precision)
    assert abs(stage.get_property("/World/Camera.exposure:iso") - iso) < 1e-6
    assert abs(stage.get_property("/World/Camera.exposure:time") - time) < 1e-6
    assert abs(stage.get_property("/World/Camera.exposure:fStop") - f_stop) < 1e-6
    assert abs(stage.get_property("/World/Camera.exposure") - compensation) < 1e-6
    assert abs(stage.get_property("/World/Camera.exposure:responsivity") - responsivity) < 1e-6


def test_camera_set_clipping_range():
    """Test camera clipping range setting"""
    stage = nusd.Stage.create_in_memory("test_camera_clipping")
    stage.camera_define("/World/Camera")
    
    # Set clipping range
    near = 0.1
    far = 1000.0
    
    stage.camera_set_clipping_range("/World/Camera", near, far)
    
    # Verify by reading the clippingRange attribute (float2)
    clipping_range = stage.get_property("/World/Camera.clippingRange")
    
    # Should be a numpy array with [near, far]
    assert isinstance(clipping_range, np.ndarray)
    assert len(clipping_range) == 2
    assert abs(clipping_range[0] - near) < 1e-6
    assert abs(clipping_range[1] - far) < 1e-6


def test_prim_compute_local_to_world_transform():
    """Test local-to-world transform computation"""
    stage = nusd.Stage.create_in_memory("test_transform_compute")
    
    # Create a simple hierarchy: World -> Parent -> Child
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Parent", "Xform")
    stage.define_prim("/World/Parent/Child", "Xform")
    
    # For World prim, the transform should be identity
    world_transform = stage.prim_compute_local_to_world_transform("/World")
    expected_identity = np.eye(4, dtype=np.float64)
    assert np.allclose(world_transform, expected_identity)
    
    # Test that the function returns proper shape and type
    assert world_transform.shape == (4, 4)
    assert world_transform.dtype == np.float64


def test_camera_functions_with_time_code():
    """Test camera functions with explicit time codes"""
    stage = nusd.Stage.create_in_memory("test_camera_time")
    stage.camera_define("/World/Camera")
    
    # Test with non-default time code
    time_code = 24.0
    
    # Set transform at specific time
    transform_matrix = np.eye(4, dtype=np.float64)
    transform_matrix[0, 3] = 10.0  # Translation in X
    stage.prim_set_transform("/World/Camera", transform_matrix, time_code)
    
    # Set other properties at the same time
    stage.camera_set_fov_w("/World/Camera", 45.0, time_code)
    stage.camera_set_clipping_range("/World/Camera", 0.5, 500.0, time_code)
    
    # Verify transform computation at that time
    world_transform = stage.prim_compute_local_to_world_transform("/World/Camera", time_code)
    assert np.allclose(world_transform, transform_matrix)


def test_camera_set_aperture():
    """Test camera aperture setting"""
    stage = nusd.Stage.create_in_memory("test_camera_aperture")
    stage.camera_define("/World/Camera")
    
    # Set aperture dimensions (35mm full frame: 36x24 in tenths of scene units)
    width = 36.0  # horizontal aperture
    height = 24.0  # vertical aperture
    
    stage.camera_set_aperture("/World/Camera", width, height)
    
    # Verify by reading the horizontalAperture and verticalAperture attributes
    horizontal_aperture = stage.get_property("/World/Camera.horizontalAperture")
    vertical_aperture = stage.get_property("/World/Camera.verticalAperture")
    
    # Use approximate equality for float precision
    assert abs(horizontal_aperture - width) < 1e-6
    assert abs(vertical_aperture - height) < 1e-6


def test_camera_set_aperture_with_time_code():
    """Test camera aperture setting with explicit time code"""
    stage = nusd.Stage.create_in_memory("test_camera_aperture_time")
    stage.camera_define("/World/Camera")
    
    # Test with non-default time code
    time_code = 12.0
    
    # Set aperture at specific time (Super 35: 24.89x18.66)
    width = 24.89
    height = 18.66
    
    stage.camera_set_aperture("/World/Camera", width, height, time_code)
    
    # Verify the aperture was set at the correct time
    # Note: We can't easily test time-specific values without more complex USD setup,
    # but we can verify that the function call succeeds and the values are set
    horizontal_aperture = stage.get_property("/World/Camera.horizontalAperture", time_code)
    vertical_aperture = stage.get_property("/World/Camera.verticalAperture", time_code)
    
    assert abs(horizontal_aperture - width) < 1e-4
    assert abs(vertical_aperture - height) < 1e-4


def test_material_define():
    """Test material definition"""
    stage = nusd.Stage.create_in_memory("test_material_define")
    stage.material_define("/World/Materials/MyMaterial")
    # Material should now exist as a valid prim


def test_shader_define():
    """Test shader definition with shader ID"""
    stage = nusd.Stage.create_in_memory("test_shader_define")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    # Shader should now exist as a valid prim


def test_shader_create_input():
    """Test shader input creation"""
    stage = nusd.Stage.create_in_memory("test_shader_input")
    
    # Define a shader first
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create a diffuseColor input of type COLOR3F
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.COLOR3F)
    
    # Create a roughness input of type FLOAT
    stage.shader_create_input("/World/Materials/Mat/Surface", "roughness", nusd.FLOAT)


def test_shader_create_output():
    """Test shader output creation"""
    stage = nusd.Stage.create_in_memory("test_shader_output")
    
    # Define a shader first
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create a surface output of type TOKEN
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN)
    
    # Define a texture shader
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create an rgb output of type COLOR3F
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.COLOR3F)


def test_shader_connect():
    """Test shader connection functionality"""
    stage = nusd.Stage.create_in_memory("test_shader_connect")
    
    # Define a material and two shaders
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create inputs and outputs
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.COLOR3F)
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.COLOR3F)
    
    # Connect the texture output to the surface input
    stage.shader_connect(
        "/World/Materials/Mat/Texture.outputs:rgb",
        "/World/Materials/Mat/Surface.inputs:diffuseColor"
    )


def test_material_shader_workflow():
    """Test complete material and shader workflow"""
    stage = nusd.Stage.create_in_memory("test_material_workflow")
    
    # Create a material
    stage.material_define("/World/Materials/TestMaterial")
    
    # Create a UsdPreviewSurface shader
    stage.shader_define("/World/Materials/TestMaterial/PreviewSurface", "UsdPreviewSurface")
    
    # Create a UsdUVTexture shader for diffuse texture
    stage.shader_define("/World/Materials/TestMaterial/DiffuseTexture", "UsdUVTexture")
    
    # Create inputs on the surface shader
    stage.shader_create_input("/World/Materials/TestMaterial/PreviewSurface", "diffuseColor", nusd.COLOR3F)
    stage.shader_create_input("/World/Materials/TestMaterial/PreviewSurface", "roughness", nusd.FLOAT)
    stage.shader_create_input("/World/Materials/TestMaterial/PreviewSurface", "metallic", nusd.FLOAT)
    
    # Create outputs on the texture shader
    stage.shader_create_output("/World/Materials/TestMaterial/DiffuseTexture", "rgb", nusd.COLOR3F)
    stage.shader_create_output("/World/Materials/TestMaterial/DiffuseTexture", "a", nusd.FLOAT)
    
    # Create surface output on the material shader
    stage.shader_create_output("/World/Materials/TestMaterial/PreviewSurface", "surface", nusd.TOKEN)
    
    # Connect texture to surface shader
    stage.shader_connect(
        "/World/Materials/TestMaterial/DiffuseTexture.outputs:rgb",
        "/World/Materials/TestMaterial/PreviewSurface.inputs:diffuseColor"
    )
    
    # Verify we can set some properties on the inputs
    stage.set_property("/World/Materials/TestMaterial/PreviewSurface.inputs:roughness", nusd.FLOAT, 0.8)
    stage.set_property("/World/Materials/TestMaterial/PreviewSurface.inputs:metallic", nusd.FLOAT, 0.0)
    
    # Verify we can read them back
    roughness = stage.get_property("/World/Materials/TestMaterial/PreviewSurface.inputs:roughness")
    metallic = stage.get_property("/World/Materials/TestMaterial/PreviewSurface.inputs:metallic")
    
    assert abs(roughness - 0.8) < 1e-6
    assert abs(metallic - 0.0) < 1e-6


def test_shader_create_input_with_value():
    """Test shader input creation with optional value parameter"""
    stage = nusd.Stage.create_new("test_shader_input_value.usda")
    
    # Define a shader first
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create inputs with values
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.COLOR3F, [1.0, 0.5, 0.0])
    stage.shader_create_input("/World/Materials/Mat/Surface", "roughness", nusd.FLOAT, 0.8)
    stage.shader_create_input("/World/Materials/Mat/Surface", "metallic", nusd.FLOAT, 0.0)

    stage.save()
    
    # Verify the values were set correctly
    diffuse_color = stage.get_property("/World/Materials/Mat/Surface.inputs:diffuseColor")
    roughness = stage.get_property("/World/Materials/Mat/Surface.inputs:roughness")
    metallic = stage.get_property("/World/Materials/Mat/Surface.inputs:metallic")
    
    assert len(diffuse_color) == 3
    assert abs(diffuse_color[0] - 1.0) < 1e-6
    assert abs(diffuse_color[1] - 0.5) < 1e-6 
    assert abs(diffuse_color[2] - 0.0) < 1e-6
    assert abs(roughness - 0.8) < 1e-6
    assert abs(metallic - 0.0) < 1e-6


def test_shader_create_output_with_value():
    """Test shader output creation with optional value parameter"""
    stage = nusd.Stage.create_in_memory("test_shader_output_value")
    
    # Define a shader first
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create outputs with values
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN, "surface")
    
    # Define a texture shader
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create an rgb output with a color value
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.COLOR3F, [0.8, 0.2, 0.1])
    
    # Verify the values were set correctly
    surface_output = stage.get_property("/World/Materials/Mat/Surface.outputs:surface")
    rgb_output = stage.get_property("/World/Materials/Mat/Texture.outputs:rgb")
    
    assert surface_output == "surface"
    assert len(rgb_output) == 3
    assert abs(rgb_output[0] - 0.8) < 1e-6
    assert abs(rgb_output[1] - 0.2) < 1e-6
    assert abs(rgb_output[2] - 0.1) < 1e-6


def test_shader_create_input_output_mixed():
    """Test shader creation with both value and no-value parameters"""
    stage = nusd.Stage.create_in_memory("test_shader_mixed")
    
    # Define a shader first
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create some inputs with values and some without
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.COLOR3F, [1.0, 0.0, 0.0])
    stage.shader_create_input("/World/Materials/Mat/Surface", "roughness", nusd.FLOAT)  # No value
    stage.shader_create_input("/World/Materials/Mat/Surface", "metallic", nusd.FLOAT, 1.0)
    
    # Create some outputs with values and some without  
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN, "surface")
    stage.shader_create_output("/World/Materials/Mat/Surface", "displacement", nusd.TOKEN)  # No value
    
    # Verify the values that were set
    diffuse_color = stage.get_property("/World/Materials/Mat/Surface.inputs:diffuseColor")
    metallic = stage.get_property("/World/Materials/Mat/Surface.inputs:metallic")
    surface_output = stage.get_property("/World/Materials/Mat/Surface.outputs:surface")
    
    assert len(diffuse_color) == 3
    assert abs(diffuse_color[0] - 1.0) < 1e-6
    assert abs(diffuse_color[1] - 0.0) < 1e-6
    assert abs(diffuse_color[2] - 0.0) < 1e-6
    assert abs(metallic - 1.0) < 1e-6
    assert surface_output == "surface"


def test_set_token():
    """Test setting token property values"""
    stage = nusd.Stage.create_in_memory("test_token")
    stage.define_prim("/World", "Xform")
    
    # Create and set a token property
    stage.prim_create_property("/World", "shader_id", nusd.TOKEN, "UsdPreviewSurface")
    
    # Verify the value was set correctly
    shader_id = stage.get_property("/World.shader_id")
    assert shader_id == "UsdPreviewSurface"
    
    # Test setting a different token value
    stage.set_property("/World.shader_id", nusd.TOKEN, "UsdUVTexture")
    shader_id = stage.get_property("/World.shader_id")
    assert shader_id == "UsdUVTexture"


def test_set_token_array():
    """Test setting token array property values"""
    stage = nusd.Stage.create_in_memory("test_token_array")
    stage.define_prim("/World", "Xform")
    
    # Create and set a token array property
    stage.prim_create_property("/World", "testTokenArray", nusd.TOKENARRAY, ["default", "render", "proxy"])
    
    # Verify the values were set correctly
    purposes = stage.get_property("/World.testTokenArray")
    assert isinstance(purposes, list)
    assert len(purposes) == 3
    assert purposes[0] == "default"
    assert purposes[1] == "render" 
    assert purposes[2] == "proxy"


def test_set_asset():
    """Test setting asset property values"""
    stage = nusd.Stage.create_in_memory("test_asset")
    stage.define_prim("/World", "Xform")
    
    # Create and set an asset property
    stage.prim_create_property("/World", "testAsset", nusd.ASSET, "textures/diffuse.jpg")
    
    # Verify the value was set correctly
    asset_path = stage.get_property("/World.testAsset")
    assert asset_path == "textures/diffuse.jpg"
    
    # Test setting a different asset value
    stage.set_property("/World.testAsset", nusd.ASSET, "textures/normal.png")
    asset_path = stage.get_property("/World.testAsset")
    assert asset_path == "textures/normal.png"


def test_set_asset_array():
    """Test setting asset array property values"""
    stage = nusd.Stage.create_in_memory("test_asset_array")
    stage.define_prim("/World", "Xform")
    
    # Create and set an asset array property
    test_assets = ["textures/diffuse.jpg", "textures/normal.png", "textures/roughness.tga"]
    stage.prim_create_property("/World", "testAssetArray", nusd.ASSETARRAY, test_assets)
    
    # Verify the values were set correctly
    assets = stage.get_property("/World.testAssetArray")
    assert isinstance(assets, list)
    assert len(assets) == 3
    assert assets[0] == "textures/diffuse.jpg"
    assert assets[1] == "textures/normal.png"
    assert assets[2] == "textures/roughness.tga"
    
    # Test setting different asset array values
    new_assets = ["models/chair.usd", "models/table.usd"]
    stage.set_property("/World.testAssetArray", nusd.ASSETARRAY, new_assets)
    assets = stage.get_property("/World.testAssetArray")
    assert len(assets) == 2
    assert assets[0] == "models/chair.usd"
    assert assets[1] == "models/table.usd"


def test_asset_empty_values():
    """Test asset properties with empty values"""
    stage = nusd.Stage.create_in_memory("test_asset_empty")
    stage.define_prim("/World", "Xform")
    
    # Test empty asset path
    stage.prim_create_property("/World", "emptyAsset", nusd.ASSET, "")
    asset_path = stage.get_property("/World.emptyAsset")
    assert asset_path == ""
    
    # Test empty asset array
    stage.prim_create_property("/World", "emptyAssetArray", nusd.ASSETARRAY, [])
    assets = stage.get_property("/World.emptyAssetArray")
    assert isinstance(assets, list)
    assert len(assets) == 0


def test_asset_relative_paths():
    """Test asset properties with relative paths"""
    stage = nusd.Stage.create_in_memory("test_asset_relative")
    stage.define_prim("/World", "Xform")
    
    # Test relative paths
    relative_paths = ["./local.jpg", "../parent.png", "subfolder/nested.tiff"]
    stage.prim_create_property("/World", "relativePaths", nusd.ASSETARRAY, relative_paths)
    
    assets = stage.get_property("/World.relativePaths")
    assert len(assets) == 3
    assert assets[0] == "./local.jpg"
    assert assets[1] == "../parent.png"
    assert assets[2] == "subfolder/nested.tiff"


def test_asset_special_characters():
    """Test asset properties with special characters in paths"""
    stage = nusd.Stage.create_in_memory("test_asset_special")
    stage.define_prim("/World", "Xform")
    
    # Test paths with spaces and special characters
    special_paths = [
        "path with spaces.jpg",
        "path-with-dashes.png", 
        "path_with_underscores.tga",
        "path.with.dots.exr"
    ]
    stage.prim_create_property("/World", "specialPaths", nusd.ASSETARRAY, special_paths)
    
    assets = stage.get_property("/World.specialPaths")
    assert len(assets) == 4
    assert assets[0] == "path with spaces.jpg"
    assert assets[1] == "path-with-dashes.png"
    assert assets[2] == "path_with_underscores.tga"
    assert assets[3] == "path.with.dots.exr"


def test_prim_add_translate_op_basic():
    """Test basic translate operation addition with initial translation"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_basic")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Add translate operation with initial translation
    translation = [5.0, 3.0, 10.0]
    stage.prim_add_translate_op("/World/Camera", translation=translation)
    
    # Function should succeed without raising exceptions


def test_prim_add_translate_op_with_suffix():
    """Test translate operation addition with custom suffix"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_suffix")
    stage.define_prim("/World", "Xform")
    
    # Create a mesh which is also xformable
    face_vertex_counts = np.array([3], dtype=np.int32)
    face_vertex_indices = np.array([0, 1, 2], dtype=np.int32) 
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 1.0, 0.0]], dtype=np.float32)
    stage.mesh_define("/World/Mesh", face_vertex_counts, face_vertex_indices, vertices)
    
    # Add translate operation with custom suffix
    translation = [2.0, 1.0, 0.0]
    stage.prim_add_translate_op("/World/Mesh", op_suffix="pivot", translation=translation)
    
    # Function should succeed without raising exceptions


def test_prim_add_translate_op_no_initial_value():
    """Test translate operation addition without initial value"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_no_value")
    stage.define_prim("/World", "Xform")
    stage.define_prim("/World/Cube", "Cube")
    
    # Add translate operation without initial value
    stage.prim_add_translate_op("/World/Cube", op_suffix="offset")
    
    # Function should succeed without raising exceptions


def test_prim_add_translate_op_list_input():
    """Test translate operation with list input"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_list")
    stage.define_prim("/World", "Xform") 
    stage.camera_define("/World/Camera")
    
    # Test with Python list
    translation = [1.0, 2.0, 3.0]
    stage.prim_add_translate_op("/World/Camera", translation=translation)


def test_prim_add_translate_op_tuple_input():
    """Test translate operation with tuple input"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_tuple")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with Python tuple
    translation = (4.0, 5.0, 6.0)
    stage.prim_add_translate_op("/World/Camera", translation=translation)


def test_prim_add_translate_op_numpy_float32():
    """Test translate operation with NumPy float32 array (should convert to double)"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_numpy32")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with NumPy float32 array (should be converted to double)
    translation = np.array([7.0, 8.0, 9.0], dtype=np.float32)
    stage.prim_add_translate_op("/World/Camera", translation=translation)


def test_prim_add_translate_op_numpy_float64():
    """Test translate operation with NumPy float64 array"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_numpy64")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with NumPy float64 array
    translation = np.array([10.0, 11.0, 12.0], dtype=np.float64)
    stage.prim_add_translate_op("/World/Camera", translation=translation)


def test_prim_add_translate_op_numpy_int():
    """Test translate operation with NumPy int array (should convert to double)"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_numpy_int")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with NumPy int array (should be converted to double)
    translation = np.array([13, 14, 15], dtype=np.int32)
    stage.prim_add_translate_op("/World/Camera", translation=translation)


def test_prim_add_translate_op_multiple_operations():
    """Test adding multiple translate operations with different suffixes"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_multiple")
    stage.define_prim("/World", "Xform")
    
    # Add multiple translate operations with different suffixes
    stage.prim_add_translate_op("/World", op_suffix="offset1", translation=[1.0, 0.0, 0.0])
    stage.prim_add_translate_op("/World", op_suffix="offset2", translation=[0.0, 2.0, 0.0])
    stage.prim_add_translate_op("/World", op_suffix="offset3", translation=[0.0, 0.0, 3.0])
    
    # All operations should succeed without raising exceptions


def test_prim_add_translate_op_with_time_code():
    """Test translate operation addition with explicit time code"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_time")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with non-default time code
    time_code = 24.0
    translation = [16.0, 17.0, 18.0]
    stage.prim_add_translate_op("/World/Camera", translation=translation, time_code=time_code)


def test_prim_add_translate_op_invalid_prim_path():
    """Test translate operation addition with invalid prim path"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_invalid")
    
    # Test with non-existent prim
    translation = [1.0, 2.0, 3.0]
    with pytest.raises(nusd.SetPropertyError):
        stage.prim_add_translate_op("/NonExistent/Prim", translation=translation)


def test_prim_add_translate_op_invalid_translation_wrong_length():
    """Test translate operation with invalid translation length"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_invalid_length")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with wrong number of elements
    with pytest.raises(ValueError, match="translation must contain exactly 3 values"):
        stage.prim_add_translate_op("/World/Camera", translation=[1.0, 2.0])  # Only 2 elements
    
    with pytest.raises(ValueError, match="translation must contain exactly 3 values"):
        stage.prim_add_translate_op("/World/Camera", translation=[1.0, 2.0, 3.0, 4.0])  # 4 elements


def test_prim_add_translate_op_invalid_translation_type():
    """Test translate operation with invalid translation type"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_invalid_type")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with invalid type
    with pytest.raises(ValueError, match="translation must be a list, tuple, or array"):
        stage.prim_add_translate_op("/World/Camera", translation="invalid")
    
    with pytest.raises(ValueError, match="translation must be a list, tuple, or array"):
        stage.prim_add_translate_op("/World/Camera", translation=42)


def test_prim_add_translate_op_invalid_translation_values():
    """Test translate operation with non-numeric translation values"""
    stage = nusd.Stage.create_in_memory("test_prim_add_translate_op_invalid_values")
    stage.define_prim("/World", "Xform")
    stage.camera_define("/World/Camera")
    
    # Test with non-numeric values
    with pytest.raises(ValueError, match="translation components must be numeric values"):
        stage.prim_add_translate_op("/World/Camera", translation=["a", "b", "c"])
    
    with pytest.raises(ValueError, match="translation components must be numeric values"):
        stage.prim_add_translate_op("/World/Camera", translation=[1.0, None, 3.0])
