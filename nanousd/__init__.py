import ctypes
from ctypes import c_void_p, c_bool, c_int, c_char_p, POINTER, byref
from enum import Enum
import os
_lib = ctypes.CDLL(f"{os.path.dirname(os.path.abspath(__file__))}/../build/libnanousd.so")      

nusd_stage_t = c_void_p
nusd_prim_iterator_t = c_void_p
nusd_property_iterator_t = c_void_p
nusd_attribute_iterator_t = c_void_p
nusd_relationship_iterator_t = c_void_p
nusd_relationship_targets_iterator_t = c_void_p
nusd_token_array_t = c_void_p
nusd_float_array_t = c_void_p
nusd_float2_array_t = c_void_p
nusd_float3_array_t = c_void_p
nusd_float4_array_t = c_void_p
nusd_double_array_t = c_void_p
nusd_double2_array_t = c_void_p
nusd_double3_array_t = c_void_p
nusd_double4_array_t = c_void_p
nusd_int_array_t = c_void_p
nusd_int2_array_t = c_void_p
nusd_int3_array_t = c_void_p
nusd_int4_array_t = c_void_p
nusd_bool_array_t = c_void_p

nusd_type_t = c_char_p

NUSD_TYPE_ASSET = c_char_p.in_dll(_lib, "NUSD_TYPE_ASSET")
NUSD_TYPE_ASSETARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_ASSETARRAY")
NUSD_TYPE_BOOL = c_char_p.in_dll(_lib, "NUSD_TYPE_BOOL")
NUSD_TYPE_BOOLARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_BOOLARRAY")
NUSD_TYPE_COLOR3D = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR3D")
NUSD_TYPE_COLOR3DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR3DARRAY")
NUSD_TYPE_COLOR3F = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR3F")
NUSD_TYPE_COLOR3FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR3FARRAY")
NUSD_TYPE_COLOR3H = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR3H")
NUSD_TYPE_COLOR3HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR3HARRAY")
NUSD_TYPE_COLOR4D = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR4D")
NUSD_TYPE_COLOR4DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR4DARRAY")
NUSD_TYPE_COLOR4F = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR4F")
NUSD_TYPE_COLOR4FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR4FARRAY")
NUSD_TYPE_COLOR4H = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR4H")
NUSD_TYPE_COLOR4HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_COLOR4HARRAY")
NUSD_TYPE_DOUBLE = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE")
NUSD_TYPE_DOUBLE2 = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE2")
NUSD_TYPE_DOUBLE2ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE2ARRAY")
NUSD_TYPE_DOUBLE3 = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE3")
NUSD_TYPE_DOUBLE3ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE3ARRAY")
NUSD_TYPE_DOUBLE4 = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE4")
NUSD_TYPE_DOUBLE4ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLE4ARRAY")
NUSD_TYPE_DOUBLEARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_DOUBLEARRAY")
NUSD_TYPE_FIND = c_char_p.in_dll(_lib, "NUSD_TYPE_FIND")
NUSD_TYPE_FLOAT = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT")
NUSD_TYPE_FLOAT2 = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT2")
NUSD_TYPE_FLOAT2ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT2ARRAY")
NUSD_TYPE_FLOAT3 = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT3")
NUSD_TYPE_FLOAT3ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT3ARRAY")
NUSD_TYPE_FLOAT4 = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT4")
NUSD_TYPE_FLOAT4ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOAT4ARRAY")
NUSD_TYPE_FLOATARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_FLOATARRAY")
NUSD_TYPE_FRAME4D = c_char_p.in_dll(_lib, "NUSD_TYPE_FRAME4D")
NUSD_TYPE_FRAME4DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_FRAME4DARRAY")
NUSD_TYPE_GROUP = c_char_p.in_dll(_lib, "NUSD_TYPE_GROUP")
NUSD_TYPE_HALF = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF")
NUSD_TYPE_HALF2 = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF2")
NUSD_TYPE_HALF2ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF2ARRAY")
NUSD_TYPE_HALF3 = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF3")
NUSD_TYPE_HALF3ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF3ARRAY")
NUSD_TYPE_HALF4 = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF4")
NUSD_TYPE_HALF4ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_HALF4ARRAY")
NUSD_TYPE_HALFARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_HALFARRAY")
NUSD_TYPE_INT = c_char_p.in_dll(_lib, "NUSD_TYPE_INT")
NUSD_TYPE_INT2 = c_char_p.in_dll(_lib, "NUSD_TYPE_INT2")
NUSD_TYPE_INT2ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_INT2ARRAY")
NUSD_TYPE_INT3 = c_char_p.in_dll(_lib, "NUSD_TYPE_INT3")
NUSD_TYPE_INT3ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_INT3ARRAY")
NUSD_TYPE_INT4 = c_char_p.in_dll(_lib, "NUSD_TYPE_INT4")
NUSD_TYPE_INT4ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_INT4ARRAY")
NUSD_TYPE_INT64 = c_char_p.in_dll(_lib, "NUSD_TYPE_INT64")
NUSD_TYPE_INT64ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_INT64ARRAY")
NUSD_TYPE_INTARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_INTARRAY")
NUSD_TYPE_MATRIX2D = c_char_p.in_dll(_lib, "NUSD_TYPE_MATRIX2D")
NUSD_TYPE_MATRIX2DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_MATRIX2DARRAY")
NUSD_TYPE_MATRIX3D = c_char_p.in_dll(_lib, "NUSD_TYPE_MATRIX3D")
NUSD_TYPE_MATRIX3DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_MATRIX3DARRAY")
NUSD_TYPE_MATRIX4D = c_char_p.in_dll(_lib, "NUSD_TYPE_MATRIX4D")
NUSD_TYPE_MATRIX4DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_MATRIX4DARRAY")
NUSD_TYPE_NORMAL3D = c_char_p.in_dll(_lib, "NUSD_TYPE_NORMAL3D")
NUSD_TYPE_NORMAL3DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_NORMAL3DARRAY")
NUSD_TYPE_NORMAL3F = c_char_p.in_dll(_lib, "NUSD_TYPE_NORMAL3F")
NUSD_TYPE_NORMAL3FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_NORMAL3FARRAY")
NUSD_TYPE_NORMAL3H = c_char_p.in_dll(_lib, "NUSD_TYPE_NORMAL3H")
NUSD_TYPE_NORMAL3HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_NORMAL3HARRAY")
NUSD_TYPE_OPAQUE = c_char_p.in_dll(_lib, "NUSD_TYPE_OPAQUE")
NUSD_TYPE_PATHEXPRESSION = c_char_p.in_dll(_lib, "NUSD_TYPE_PATHEXPRESSION")
NUSD_TYPE_PATHEXPRESSIONARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_PATHEXPRESSIONARRAY")
NUSD_TYPE_POINT3D = c_char_p.in_dll(_lib, "NUSD_TYPE_POINT3D")
NUSD_TYPE_POINT3DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_POINT3DARRAY")
NUSD_TYPE_POINT3F = c_char_p.in_dll(_lib, "NUSD_TYPE_POINT3F")
NUSD_TYPE_POINT3FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_POINT3FARRAY")
NUSD_TYPE_POINT3H = c_char_p.in_dll(_lib, "NUSD_TYPE_POINT3H")
NUSD_TYPE_POINT3HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_POINT3HARRAY")
NUSD_TYPE_QUATD = c_char_p.in_dll(_lib, "NUSD_TYPE_QUATD")
NUSD_TYPE_QUATDARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_QUATDARRAY")
NUSD_TYPE_QUATF = c_char_p.in_dll(_lib, "NUSD_TYPE_QUATF")
NUSD_TYPE_QUATFARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_QUATFARRAY")
NUSD_TYPE_QUATH = c_char_p.in_dll(_lib, "NUSD_TYPE_QUATH")
NUSD_TYPE_QUATHARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_QUATHARRAY")
NUSD_TYPE_STRING = c_char_p.in_dll(_lib, "NUSD_TYPE_STRING")
NUSD_TYPE_STRINGARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_STRINGARRAY")
NUSD_TYPE_TEXCOORD2D = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD2D")
NUSD_TYPE_TEXCOORD2DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD2DARRAY")
NUSD_TYPE_TEXCOORD2F = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD2F")
NUSD_TYPE_TEXCOORD2FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD2FARRAY")
NUSD_TYPE_TEXCOORD2H = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD2H")
NUSD_TYPE_TEXCOORD2HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD2HARRAY")
NUSD_TYPE_TEXCOORD3D = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD3D")
NUSD_TYPE_TEXCOORD3DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD3DARRAY")
NUSD_TYPE_TEXCOORD3F = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD3F")
NUSD_TYPE_TEXCOORD3FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD3FARRAY")
NUSD_TYPE_TEXCOORD3H = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD3H")
NUSD_TYPE_TEXCOORD3HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TEXCOORD3HARRAY")
NUSD_TYPE_TIMECODE = c_char_p.in_dll(_lib, "NUSD_TYPE_TIMECODE")
NUSD_TYPE_TIMECODEARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TIMECODEARRAY")
NUSD_TYPE_TOKEN = c_char_p.in_dll(_lib, "NUSD_TYPE_TOKEN")
NUSD_TYPE_TOKENARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_TOKENARRAY")
NUSD_TYPE_UCHAR = c_char_p.in_dll(_lib, "NUSD_TYPE_UCHAR")
NUSD_TYPE_UCHARARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_UCHARARRAY")
NUSD_TYPE_UINT = c_char_p.in_dll(_lib, "NUSD_TYPE_UINT")
NUSD_TYPE_UINT64 = c_char_p.in_dll(_lib, "NUSD_TYPE_UINT64")
NUSD_TYPE_UINT64ARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_UINT64ARRAY")
NUSD_TYPE_UINTARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_UINTARRAY")
NUSD_TYPE_VECTOR3D = c_char_p.in_dll(_lib, "NUSD_TYPE_VECTOR3D")
NUSD_TYPE_VECTOR3DARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_VECTOR3DARRAY")
NUSD_TYPE_VECTOR3F = c_char_p.in_dll(_lib, "NUSD_TYPE_VECTOR3F")
NUSD_TYPE_VECTOR3FARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_VECTOR3FARRAY")
NUSD_TYPE_VECTOR3H = c_char_p.in_dll(_lib, "NUSD_TYPE_VECTOR3H")
NUSD_TYPE_VECTOR3HARRAY = c_char_p.in_dll(_lib, "NUSD_TYPE_VECTOR3HARRAY")

NUSD_TYPE_RELATIONSHIP = c_char_p.in_dll(_lib, "NUSD_TYPE_RELATIONSHIP")

class nusd_result_t(Enum):
    NUSD_RESULT_OK = 0
    NUSD_RESULT_INVALID_ATTRIBUTE_PATH = 1
    NUSD_RESULT_INVALID_RELATIONSHIP_PATH = 2
    NUSD_RESULT_INVALID_PRIM_PATH = 3
    NUSD_RESULT_WRONG_TYPE = 4
    NUSD_RESULT_CREATE_STAGE_FAILED = 5
    NUSD_RESULT_DEFINE_PRIM_FAILED = 6

_lib.nusd_prim_iterator_next.argtypes = [nusd_prim_iterator_t, POINTER(c_char_p)]
_lib.nusd_prim_iterator_next.restype = c_bool

class PrimIterator:
    def __init__(self, iterator: nusd_prim_iterator_t):
        self._iterator = iterator

    def __iter__(self) -> "PrimIterator":
        return self

    def __next__(self) -> str:
        path = c_char_p(0)
        has_next: c_bool = _lib.nusd_prim_iterator_next(self._iterator, byref(path))
        if not has_next:
            raise StopIteration
        
        return path.value.decode("utf-8")

_lib.nusd_stage_open.argtypes = [c_char_p, POINTER(nusd_stage_t)]
_lib.nusd_stage_destroy.argtypes = [nusd_stage_t]

class StageOpenError(RuntimeError):
    pass

class Stage:
    def __init__(self, stage: nusd_stage_t):
        self._stage = stage

    def __del__(self):
        _lib.nusd_stage_destroy(self._stage)

    @classmethod
    def Open(cls, filename: str) -> "Stage":
        stage = nusd_stage_t(0)
        result = _lib.nusd_stage_open(filename.encode("ascii"), byref(stage))
        if result != nusd_result_t.NUSD_RESULT_OK.value:
            raise StageOpenError(f'failed to open stage "{filename}": {result}')
        return cls(stage)

    def Traverse(self) -> PrimIterator:
        it = nusd_prim_iterator_t(0)
        _lib.nusd_stage_traverse(self._stage, byref(it))
        return PrimIterator(it)

    def __iter__(self) -> PrimIterator:
        return self.Traverse()


stage = Stage.Open("test01.usda")
for prim in stage.Traverse():
    print(prim)

