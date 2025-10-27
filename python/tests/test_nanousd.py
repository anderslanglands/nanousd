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
    test_data = [1, 2, 3, 4, 5]
    from ctypes import c_int
    c_data = (c_int * len(test_data))(*test_data)
    result = nusd._lib.nusd_attribute_set_int_array(stage._stage, b"/World.testIntArray", c_data, len(test_data))
    assert result == nusd._lib.NUSD_RESULT_OK
    
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
    test_data = [1, 2, 3, 4, 5, 6]  # 3 int2 values
    from ctypes import c_int
    c_data = (c_int * len(test_data))(*test_data)
    result = nusd._lib.nusd_attribute_set_int2_array(stage._stage, b"/World.testInt2Array", c_data, 3)
    assert result == nusd._lib.NUSD_RESULT_OK
    
    value = stage.get_property("/World.testInt2Array")
    assert isinstance(value, nusd.Int2Array)
    expected = np.array([[1, 2], [3, 4], [5, 6]])
    assert np.array_equal(value, expected)

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
    test_data = [1, 2, 3, 4, 5, 6, 7, 8, 9]  # 3 int3 values
    from ctypes import c_int
    c_data = (c_int * len(test_data))(*test_data)
    result = nusd._lib.nusd_attribute_set_int3_array(stage._stage, b"/World.testInt3Array", c_data, 3)
    assert result == nusd._lib.NUSD_RESULT_OK
    
    value = stage.get_property("/World.testInt3Array")
    assert isinstance(value, nusd.Int3Array)
    expected = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    assert np.array_equal(value, expected)

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
    test_data = [1, 2, 3, 4, 5, 6, 7, 8]  # 2 int4 values
    from ctypes import c_int
    c_data = (c_int * len(test_data))(*test_data)
    result = nusd._lib.nusd_attribute_set_int4_array(stage._stage, b"/World.testInt4Array", c_data, 2)
    assert result == nusd._lib.NUSD_RESULT_OK
    
    value = stage.get_property("/World.testInt4Array")
    assert isinstance(value, nusd.Int4Array)
    expected = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])
    assert np.array_equal(value, expected)

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

def test_set_property_int64_array():
    stage = nusd.Stage.create_in_memory("test")
    stage.define_prim("/World", "Xform")
    stage.prim_create_property("/World", "testInt64Array", nusd.INT64ARRAY)
    # Set via C API, get via Python API
    test_data = [1000000000000, 2000000000000, 3000000000000, 4000000000000, 5000000000000]
    from ctypes import c_longlong
    c_data = (c_longlong * len(test_data))(*test_data)
    result = nusd._lib.nusd_attribute_set_int64_array(stage._stage, b"/World.testInt64Array", c_data, len(test_data))
    assert result == nusd._lib.NUSD_RESULT_OK
    
    value = stage.get_property("/World.testInt64Array")
    assert isinstance(value, nusd.Int64Array)
    assert np.array_equal(value, np.array(test_data))
