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
    assert clipping_range[0] == near
    assert clipping_range[1] == far


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
