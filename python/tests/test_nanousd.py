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
