from typing import Any
from . import ffi as _lib
import numpy as np
from numpy.lib.mixins import NDArrayOperatorsMixin

import ctypes
from ctypes import (
    c_char,
    c_void_p,
    c_bool,
    c_int,
    c_char_p,
    POINTER,
    byref,
    c_float,
    c_double,
    c_longlong,
    c_size_t,
)

ASSET = _lib.NUSD_TYPE_ASSET
ASSETARRAY = _lib.NUSD_TYPE_ASSETARRAY
BOOL = _lib.NUSD_TYPE_BOOL
BOOLARRAY = _lib.NUSD_TYPE_BOOLARRAY
COLOR3D = _lib.NUSD_TYPE_COLOR3D
COLOR3DARRAY = _lib.NUSD_TYPE_COLOR3DARRAY
COLOR3F = _lib.NUSD_TYPE_COLOR3F
COLOR3FARRAY = _lib.NUSD_TYPE_COLOR3FARRAY
COLOR3H = _lib.NUSD_TYPE_COLOR3H
COLOR3HARRAY = _lib.NUSD_TYPE_COLOR3HARRAY
COLOR4D = _lib.NUSD_TYPE_COLOR4D
COLOR4DARRAY = _lib.NUSD_TYPE_COLOR4DARRAY
COLOR4F = _lib.NUSD_TYPE_COLOR4F
COLOR4FARRAY = _lib.NUSD_TYPE_COLOR4FARRAY
COLOR4H = _lib.NUSD_TYPE_COLOR4H
COLOR4HARRAY = _lib.NUSD_TYPE_COLOR4HARRAY
DOUBLE = _lib.NUSD_TYPE_DOUBLE
DOUBLE2 = _lib.NUSD_TYPE_DOUBLE2
DOUBLE2ARRAY = _lib.NUSD_TYPE_DOUBLE2ARRAY
DOUBLE3 = _lib.NUSD_TYPE_DOUBLE3
DOUBLE3ARRAY = _lib.NUSD_TYPE_DOUBLE3ARRAY
DOUBLE4 = _lib.NUSD_TYPE_DOUBLE4
DOUBLE4ARRAY = _lib.NUSD_TYPE_DOUBLE4ARRAY
DOUBLEARRAY = _lib.NUSD_TYPE_DOUBLEARRAY
FIND = _lib.NUSD_TYPE_FIND
FLOAT = _lib.NUSD_TYPE_FLOAT
FLOAT2 = _lib.NUSD_TYPE_FLOAT2
FLOAT2ARRAY = _lib.NUSD_TYPE_FLOAT2ARRAY
FLOAT3 = _lib.NUSD_TYPE_FLOAT3
FLOAT3ARRAY = _lib.NUSD_TYPE_FLOAT3ARRAY
FLOAT4 = _lib.NUSD_TYPE_FLOAT4
FLOAT4ARRAY = _lib.NUSD_TYPE_FLOAT4ARRAY
FLOATARRAY = _lib.NUSD_TYPE_FLOATARRAY
FRAME4D = _lib.NUSD_TYPE_FRAME4D
FRAME4DARRAY = _lib.NUSD_TYPE_FRAME4DARRAY
GROUP = _lib.NUSD_TYPE_GROUP
HALF = _lib.NUSD_TYPE_HALF
HALF2 = _lib.NUSD_TYPE_HALF2
HALF2ARRAY = _lib.NUSD_TYPE_HALF2ARRAY
HALF3 = _lib.NUSD_TYPE_HALF3
HALF3ARRAY = _lib.NUSD_TYPE_HALF3ARRAY
HALF4 = _lib.NUSD_TYPE_HALF4
HALF4ARRAY = _lib.NUSD_TYPE_HALF4ARRAY
HALFARRAY = _lib.NUSD_TYPE_HALFARRAY
INT = _lib.NUSD_TYPE_INT
INT2 = _lib.NUSD_TYPE_INT2
INT2ARRAY = _lib.NUSD_TYPE_INT2ARRAY
INT3 = _lib.NUSD_TYPE_INT3
INT3ARRAY = _lib.NUSD_TYPE_INT3ARRAY
INT4 = _lib.NUSD_TYPE_INT4
INT4ARRAY = _lib.NUSD_TYPE_INT4ARRAY
INT64 = _lib.NUSD_TYPE_INT64
INT64ARRAY = _lib.NUSD_TYPE_INT64ARRAY
INTARRAY = _lib.NUSD_TYPE_INTARRAY
MATRIX2D = _lib.NUSD_TYPE_MATRIX2D
MATRIX2DARRAY = _lib.NUSD_TYPE_MATRIX2DARRAY
MATRIX3D = _lib.NUSD_TYPE_MATRIX3D
MATRIX3DARRAY = _lib.NUSD_TYPE_MATRIX3DARRAY
MATRIX4D = _lib.NUSD_TYPE_MATRIX4D
MATRIX4DARRAY = _lib.NUSD_TYPE_MATRIX4DARRAY
NORMAL3D = _lib.NUSD_TYPE_NORMAL3D
NORMAL3DARRAY = _lib.NUSD_TYPE_NORMAL3DARRAY
NORMAL3F = _lib.NUSD_TYPE_NORMAL3F
NORMAL3FARRAY = _lib.NUSD_TYPE_NORMAL3FARRAY
NORMAL3H = _lib.NUSD_TYPE_NORMAL3H
NORMAL3HARRAY = _lib.NUSD_TYPE_NORMAL3HARRAY
OPAQUE = _lib.NUSD_TYPE_OPAQUE
PATHEXPRESSION = _lib.NUSD_TYPE_PATHEXPRESSION
PATHEXPRESSIONARRAY = _lib.NUSD_TYPE_PATHEXPRESSIONARRAY
POINT3D = _lib.NUSD_TYPE_POINT3D
POINT3DARRAY = _lib.NUSD_TYPE_POINT3DARRAY
POINT3F = _lib.NUSD_TYPE_POINT3F
POINT3FARRAY = _lib.NUSD_TYPE_POINT3FARRAY
POINT3H = _lib.NUSD_TYPE_POINT3H
POINT3HARRAY = _lib.NUSD_TYPE_POINT3HARRAY
QUATD = _lib.NUSD_TYPE_QUATD
QUATDARRAY = _lib.NUSD_TYPE_QUATDARRAY
QUATF = _lib.NUSD_TYPE_QUATF
QUATFARRAY = _lib.NUSD_TYPE_QUATFARRAY
QUATH = _lib.NUSD_TYPE_QUATH
QUATHARRAY = _lib.NUSD_TYPE_QUATHARRAY
STRING = _lib.NUSD_TYPE_STRING
STRINGARRAY = _lib.NUSD_TYPE_STRINGARRAY
TEXCOORD2D = _lib.NUSD_TYPE_TEXCOORD2D
TEXCOORD2DARRAY = _lib.NUSD_TYPE_TEXCOORD2DARRAY
TEXCOORD2F = _lib.NUSD_TYPE_TEXCOORD2F
TEXCOORD2FARRAY = _lib.NUSD_TYPE_TEXCOORD2FARRAY
TEXCOORD2H = _lib.NUSD_TYPE_TEXCOORD2H
TEXCOORD2HARRAY = _lib.NUSD_TYPE_TEXCOORD2HARRAY
TEXCOORD3D = _lib.NUSD_TYPE_TEXCOORD3D
TEXCOORD3DARRAY = _lib.NUSD_TYPE_TEXCOORD3DARRAY
TEXCOORD3F = _lib.NUSD_TYPE_TEXCOORD3F
TEXCOORD3FARRAY = _lib.NUSD_TYPE_TEXCOORD3FARRAY
TEXCOORD3H = _lib.NUSD_TYPE_TEXCOORD3H
TEXCOORD3HARRAY = _lib.NUSD_TYPE_TEXCOORD3HARRAY
TIMECODE = _lib.NUSD_TYPE_TIMECODE
TIMECODEARRAY = _lib.NUSD_TYPE_TIMECODEARRAY
TOKEN = _lib.NUSD_TYPE_TOKEN
TOKENARRAY = _lib.NUSD_TYPE_TOKENARRAY
UCHAR = _lib.NUSD_TYPE_UCHAR
UCHARARRAY = _lib.NUSD_TYPE_UCHARARRAY
UINT = _lib.NUSD_TYPE_UINT
UINT64 = _lib.NUSD_TYPE_UINT64
UINT64ARRAY = _lib.NUSD_TYPE_UINT64ARRAY
UINTARRAY = _lib.NUSD_TYPE_UINTARRAY
VECTOR3D = _lib.NUSD_TYPE_VECTOR3D
VECTOR3DARRAY = _lib.NUSD_TYPE_VECTOR3DARRAY
VECTOR3F = _lib.NUSD_TYPE_VECTOR3F
VECTOR3FARRAY = _lib.NUSD_TYPE_VECTOR3FARRAY
VECTOR3H = _lib.NUSD_TYPE_VECTOR3H
VECTOR3HARRAY = _lib.NUSD_TYPE_VECTOR3HARRAY
RELATIONSHIP = _lib.NUSD_TYPE_RELATIONSHIP


def path_get_name(path: str) -> str:
    return _lib.nusd_path_get_name(path.encode("ascii")).decode("utf-8")


# fix up ctypesgen's sometimes wonky typing
_lib.nusd_prim_iterator_next.argtypes = [_lib.nusd_prim_iterator_t, POINTER(c_char_p)]
_lib.nusd_attribute_get_token.argtypes = [_lib.nusd_stage_t, _lib.String, c_double, POINTER(c_char_p)]
_lib.nusd_token_array_iterator_next.argtypes = [_lib.nusd_token_array_iterator_t, POINTER(c_char_p)]
_lib.nusd_asset_path_array_iterator_next.argtypes = [_lib.nusd_asset_path_array_iterator_t, POINTER(c_char_p)]


class PrimIterator:
    def __init__(self, iterator: c_void_p):
        self._iterator = iterator

    def __del__(self):
        _lib.nusd_prim_iterator_destroy(self._iterator)

    def __iter__(self) -> "PrimIterator":
        return self

    def __next__(self) -> str:
        path = c_char_p(0)
        has_next: c_bool = _lib.nusd_prim_iterator_next(self._iterator, byref(path))
        if not has_next:
            raise StopIteration

        return path.value.decode("utf-8")


_lib.nusd_property_iterator_next.argtypes = [
    _lib.nusd_property_iterator_t,
    POINTER(c_char_p),
    POINTER(_lib.nusd_type_t),
]


class PropertyIterator:
    def __init__(self, iterator: c_void_p):
        self._iterator = iterator

    def __iter__(self) -> "PropertyIterator":
        return self

    def __next__(self) -> str:
        path = c_char_p(0)
        prop_type = _lib.nusd_type_t()
        has_next = _lib.nusd_property_iterator_next(
            self._iterator, byref(path), byref(prop_type)
        )
        if not has_next:
            raise StopIteration

        return path.value.decode("utf-8")


class ArrayBase(NDArrayOperatorsMixin):
    def __array__(self, dtype=None):
        return np.asarray(self._view, dtype=dtype)

    def __str__(self):
        return str(self._view)

    def __repr__(self):
        return repr(self._view)

    def __getattr__(self, name):
        # delegate to NumPy array for properties/methods (e.g. .shape)
        return getattr(self._view, name)

    def __array_ufunc__(self, ufunc, method, *inputs, **kwargs):
        """Handle elementwise operations like arr * 2 or np.add(arr1, arr2)."""
        if method != "__call__":
            # Only handle normal elementwise calls
            return NotImplemented

        # Convert inputs into raw arrays
        new_inputs = []
        for x in inputs:
            if isinstance(x, ArrayBase):
                new_inputs.append(x._view)
            else:
                new_inputs.append(x)

        # Perform the operation using NumPy
        result = getattr(ufunc, method)(*new_inputs, **kwargs)

        return result

    def __array_function__(self, func, types, args, kwargs):
        """Delegate NumPy function calls like np.mean(self)."""
        # Only handle the call if all inputs are PyNusdArray or ndarray
        if not all(issubclass(t, (ArrayBase, np.ndarray)) for t in types):
            return NotImplemented
        # Replace any ArrayBase in args with its underlying ndarray
        new_args = [a._view if isinstance(a, ArrayBase) else a for a in args]
        result = func(*new_args, **kwargs)

        return result


class FloatArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_float_array_size(array)
        data = _lib.nusd_float_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_float_array_destroy(self._array)


class Float2Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_float2_array_size(array)
        data = _lib.nusd_float2_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 2))

    def __del__(self):
        _lib.nusd_float2_array_destroy(self._array)


class Float3Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_float3_array_size(array)
        data = _lib.nusd_float3_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 3))

    def __del__(self):
        _lib.nusd_float3_array_destroy(self._array)


class Float4Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_float4_array_size(array)
        data = _lib.nusd_float4_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 4))

    def __del__(self):
        _lib.nusd_float4_array_destroy(self._array)


class DoubleArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_double_array_size(array)
        data = _lib.nusd_double_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_double_array_destroy(self._array)


class Double2Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_double2_array_size(array)
        data = _lib.nusd_double2_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 2))

    def __del__(self):
        _lib.nusd_double2_array_destroy(self._array)


class Double3Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_double3_array_size(array)
        data = _lib.nusd_double3_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 3))

    def __del__(self):
        _lib.nusd_double3_array_destroy(self._array)


class Double4Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_double4_array_size(array)
        data = _lib.nusd_double4_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 4))

    def __del__(self):
        _lib.nusd_double4_array_destroy(self._array)


class IntArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_int_array_size(array)
        data = _lib.nusd_int_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_int_array_destroy(self._array)


class Int2Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_int2_array_size(array)
        data = _lib.nusd_int2_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 2))

    def __del__(self):
        _lib.nusd_int2_array_destroy(self._array)


class Int3Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_int3_array_size(array)
        data = _lib.nusd_int3_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 3))

    def __del__(self):
        _lib.nusd_int3_array_destroy(self._array)


class Int4Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_int4_array_size(array)
        data = _lib.nusd_int4_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 4))

    def __del__(self):
        _lib.nusd_int4_array_destroy(self._array)


class Int64Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_int64_array_size(array)
        data = _lib.nusd_int64_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_int64_array_destroy(self._array)


class BoolArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_bool_array_size(array)
        data = _lib.nusd_bool_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_bool_array_destroy(self._array)


class Matrix2dArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_matrix2d_array_size(array)
        data = _lib.nusd_matrix2d_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 2, 2))

    def __del__(self):
        _lib.nusd_matrix2d_array_destroy(self._array)


class Matrix3dArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_matrix3d_array_size(array)
        data = _lib.nusd_matrix3d_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 3, 3))

    def __del__(self):
        _lib.nusd_matrix3d_array_destroy(self._array)


class Matrix4dArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_matrix4d_array_size(array)
        data = _lib.nusd_matrix4d_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size, 4, 4))

    def __del__(self):
        _lib.nusd_matrix4d_array_destroy(self._array)


class UintArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_uint_array_size(array)
        data = _lib.nusd_uint_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_uint_array_destroy(self._array)


class Uint64Array(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_uint64_array_size(array)
        data = _lib.nusd_uint64_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_uint64_array_destroy(self._array)


class UcharArray(ArrayBase):
    def __init__(self, array: c_void_p):
        size = _lib.nusd_uchar_array_size(array)
        data = _lib.nusd_uchar_array_data(array)
        self._array = array
        self._view = np.ctypeslib.as_array(data, (size,))

    def __del__(self):
        _lib.nusd_uchar_array_destroy(self._array)


class StageOpenError(RuntimeError):
    pass


class StageCreateError(RuntimeError):
    pass


class GetPropertiesError(RuntimeError):
    pass


class GetPropertyError(RuntimeError):
    pass


class CreatePropertyError(RuntimeError):
    pass


class DefinePrimError(RuntimeError):
    pass


class SetPropertyError(RuntimeError):
    pass


class Stage:
    def __init__(self, stage: c_void_p):
        self._stage = stage

    def __del__(self):
        _lib.nusd_stage_destroy(self._stage)

    @classmethod
    def open(cls, filename: str) -> "Stage":
        stage = _lib.nusd_stage_t(0)
        result = _lib.nusd_stage_open(filename.encode("ascii"), byref(stage))
        if result != _lib.NUSD_RESULT_OK:
            raise StageOpenError(f'failed to open stage "{filename}": {result}')
        return cls(stage)

    @classmethod
    def create_in_memory(cls, identifier: str) -> "Stage":
        stage = _lib.nusd_stage_t(0)
        result = _lib.nusd_stage_create_in_memory(
            identifier.encode("ascii"), byref(stage)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise StageCreateError(f'failed to create stage "{identifier}": {result}')
        return cls(stage)

    def traverse(self) -> PrimIterator:
        it = _lib.nusd_prim_iterator_t(0)
        _lib.nusd_stage_traverse(self._stage, byref(it))
        return PrimIterator(it)

    def __iter__(self) -> PrimIterator:
        return self.traverse()

    def prim_get_properties(self, prim_path: str) -> PropertyIterator:
        it = _lib.nusd_property_iterator_t(0)
        result = _lib.nusd_prim_get_properties(
            self._stage, prim_path.encode("ascii"), byref(it)
        )

        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertiesError(
                f'failed to get properties for "{prim_path}": {result}'
            )

        return PropertyIterator(it)

    def get_property(self, property_path: str, time_code: float = 0.0):
        property_type = _lib.nusd_type_t()
        result = _lib.nusd_property_get_type(
            self._stage, property_path, byref(property_type)
        )

        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get property type for "{property_path}": {result}'
            )

        if property_type == _lib.NUSD_TYPE_FLOAT:
            value = c_float(0.0)
            result = _lib.nusd_attribute_get_float(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_FLOATARRAY:
            value = _lib.nusd_float_array_t()
            result = _lib.nusd_attribute_get_float_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return FloatArray(value)
        elif property_type in [_lib.NUSD_TYPE_FLOAT2, _lib.NUSD_TYPE_TEXCOORD2F]:
            value = (c_float * 2)()
            result = _lib.nusd_attribute_get_float2(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [
            _lib.NUSD_TYPE_FLOAT2ARRAY,
            _lib.NUSD_TYPE_TEXCOORD2FARRAY,
        ]:
            value = _lib.nusd_float2_array_t()
            result = _lib.nusd_attribute_get_float2_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Float2Array(value)
        elif property_type in [
            _lib.NUSD_TYPE_FLOAT3,
            _lib.NUSD_TYPE_TEXCOORD3F,
            _lib.NUSD_TYPE_COLOR3F,
            _lib.NUSD_TYPE_VECTOR3F,
            _lib.NUSD_TYPE_POINT3F,
            _lib.NUSD_TYPE_NORMAL3F,
        ]:
            value = (c_float * 3)()
            result = _lib.nusd_attribute_get_float3(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [
            _lib.NUSD_TYPE_FLOAT3ARRAY,
            _lib.NUSD_TYPE_TEXCOORD3FARRAY,
            _lib.NUSD_TYPE_COLOR3FARRAY,
            _lib.NUSD_TYPE_VECTOR3FARRAY,
            _lib.NUSD_TYPE_POINT3FARRAY,
            _lib.NUSD_TYPE_NORMAL3FARRAY,
        ]:
            value = _lib.nusd_float3_array_t()
            result = _lib.nusd_attribute_get_float3_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Float3Array(value)
        elif property_type in [_lib.NUSD_TYPE_FLOAT4, _lib.NUSD_TYPE_COLOR4F]:
            value = (c_float * 4)()
            result = _lib.nusd_attribute_get_float4(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [_lib.NUSD_TYPE_FLOAT4ARRAY, _lib.NUSD_TYPE_COLOR4FARRAY]:
            value = _lib.nusd_float4_array_t()
            result = _lib.nusd_attribute_get_float4_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Float4Array(value)
        elif property_type == _lib.NUSD_TYPE_DOUBLE:
            value = c_double(0.0)
            result = _lib.nusd_attribute_get_double(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_DOUBLEARRAY:
            value = _lib.nusd_double_array_t()
            result = _lib.nusd_attribute_get_double_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return DoubleArray(value)
        elif property_type in [_lib.NUSD_TYPE_DOUBLE2, _lib.NUSD_TYPE_TEXCOORD2D]:
            value = (c_double * 2)()
            result = _lib.nusd_attribute_get_double2(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [
            _lib.NUSD_TYPE_DOUBLE2ARRAY,
            _lib.NUSD_TYPE_TEXCOORD2DARRAY,
        ]:
            value = _lib.nusd_double2_array_t()
            result = _lib.nusd_attribute_get_double2_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Double2Array(value)
        elif property_type in [
            _lib.NUSD_TYPE_DOUBLE3,
            _lib.NUSD_TYPE_TEXCOORD3D,
            _lib.NUSD_TYPE_COLOR3D,
            _lib.NUSD_TYPE_VECTOR3D,
            _lib.NUSD_TYPE_POINT3D,
            _lib.NUSD_TYPE_NORMAL3D,
        ]:
            value = (c_double * 3)()
            result = _lib.nusd_attribute_get_double3(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [
            _lib.NUSD_TYPE_DOUBLE3ARRAY,
            _lib.NUSD_TYPE_TEXCOORD3DARRAY,
            _lib.NUSD_TYPE_COLOR3DARRAY,
            _lib.NUSD_TYPE_VECTOR3DARRAY,
            _lib.NUSD_TYPE_POINT3DARRAY,
            _lib.NUSD_TYPE_NORMAL3DARRAY,
        ]:
            value = _lib.nusd_double3_array_t()
            result = _lib.nusd_attribute_get_double3_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Double3Array(value)
        elif property_type in [_lib.NUSD_TYPE_DOUBLE4, _lib.NUSD_TYPE_COLOR4D]:
            value = (c_double * 4)()
            result = _lib.nusd_attribute_get_double4(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [
            _lib.NUSD_TYPE_DOUBLE4ARRAY,
            _lib.NUSD_TYPE_COLOR4DARRAY,
        ]:
            value = _lib.nusd_double4_array_t()
            result = _lib.nusd_attribute_get_double4_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Double4Array(value)
        elif property_type == _lib.NUSD_TYPE_INT:
            value = c_int(0)
            result = _lib.nusd_attribute_get_int(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_INTARRAY:
            value = _lib.nusd_int_array_t()
            result = _lib.nusd_attribute_get_int_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return IntArray(value)
        elif property_type == _lib.NUSD_TYPE_INT2:
            value = (c_int * 2)()
            result = _lib.nusd_attribute_get_int2(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type == _lib.NUSD_TYPE_INT2ARRAY:
            value = _lib.nusd_int2_array_t()
            result = _lib.nusd_attribute_get_int2_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int2Array(value)
        elif property_type == _lib.NUSD_TYPE_INT3:
            value = (c_int * 3)()
            result = _lib.nusd_attribute_get_int3(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type == _lib.NUSD_TYPE_INT3ARRAY:
            value = _lib.nusd_int3_array_t()
            result = _lib.nusd_attribute_get_int3_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int3Array(value)
        elif property_type == _lib.NUSD_TYPE_INT4:
            value = (c_int * 4)()
            result = _lib.nusd_attribute_get_int4(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type == _lib.NUSD_TYPE_INT4ARRAY:
            value = _lib.nusd_int4_array_t()
            result = _lib.nusd_attribute_get_int4_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int4Array(value)
        elif property_type == _lib.NUSD_TYPE_INT64:
            value = c_longlong(0)
            result = _lib.nusd_attribute_get_int64(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_INT64ARRAY:
            value = _lib.nusd_int64_array_t()
            result = _lib.nusd_attribute_get_int64_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int64Array(value)
        elif property_type == _lib.NUSD_TYPE_BOOL:
            value = c_bool(False)
            result = _lib.nusd_attribute_get_bool(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_BOOLARRAY:
            value = _lib.nusd_bool_array_t()
            result = _lib.nusd_attribute_get_bool_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return BoolArray(value)
        elif property_type == _lib.NUSD_TYPE_MATRIX2D:
            value = (c_double * 4)()
            result = _lib.nusd_attribute_get_matrix2d(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value).reshape(2, 2)
        elif property_type == _lib.NUSD_TYPE_MATRIX2DARRAY:
            value = _lib.nusd_matrix2d_array_t()
            result = _lib.nusd_attribute_get_matrix2d_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Matrix2dArray(value)
        elif property_type == _lib.NUSD_TYPE_MATRIX3D:
            value = (c_double * 9)()
            result = _lib.nusd_attribute_get_matrix3d(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value).reshape(3, 3)
        elif property_type == _lib.NUSD_TYPE_MATRIX3DARRAY:
            value = _lib.nusd_matrix3d_array_t()
            result = _lib.nusd_attribute_get_matrix3d_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Matrix3dArray(value)
        elif property_type == _lib.NUSD_TYPE_MATRIX4D:
            value = (c_double * 16)()
            result = _lib.nusd_attribute_get_matrix4d(
                self._stage, property_path, time_code, value
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value).reshape(4, 4)
        elif property_type == _lib.NUSD_TYPE_MATRIX4DARRAY:
            value = _lib.nusd_matrix4d_array_t()
            result = _lib.nusd_attribute_get_matrix4d_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Matrix4dArray(value)
        elif property_type == _lib.NUSD_TYPE_UINT:
            from ctypes import c_uint

            value = c_uint(0)
            result = _lib.nusd_attribute_get_uint(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_UINTARRAY:
            value = _lib.nusd_uint_array_t()
            result = _lib.nusd_attribute_get_uint_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return UintArray(value)
        elif property_type == _lib.NUSD_TYPE_UINT64:
            from ctypes import c_ulonglong

            value = c_ulonglong(0)
            result = _lib.nusd_attribute_get_uint64(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_UINT64ARRAY:
            value = _lib.nusd_uint64_array_t()
            result = _lib.nusd_attribute_get_uint64_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Uint64Array(value)
        elif property_type == _lib.NUSD_TYPE_UCHAR:
            from ctypes import c_ubyte

            value = c_ubyte(0)
            result = _lib.nusd_attribute_get_uchar(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_UCHARARRAY:
            value = _lib.nusd_uchar_array_t()
            result = _lib.nusd_attribute_get_uchar_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return UcharArray(value)
        elif property_type == _lib.NUSD_TYPE_TOKEN:
            value = c_char_p()
            result = _lib.nusd_attribute_get_token(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value.decode("utf-8")
        elif property_type == _lib.NUSD_TYPE_TOKENARRAY:
            value = _lib.nusd_token_array_iterator_t()
            result = _lib.nusd_attribute_get_token_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )

            result = []
            tok = c_char_p()
            while _lib.nusd_token_array_iterator_next(value, byref(tok)):
                result.append(tok.value.decode("utf-8"))

            return result
        elif property_type == _lib.NUSD_TYPE_ASSET:
            value = _lib.nusd_asset_path_t()
            result = _lib.nusd_attribute_get_asset(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            asset_value = _lib.nusd_asset_path_get_asset_path(value)
            path_result = asset_value.decode("utf-8") if asset_value else ""
            _lib.nusd_asset_path_destroy(value)
            return path_result
        elif property_type == _lib.NUSD_TYPE_ASSETARRAY:
            value = _lib.nusd_asset_path_array_iterator_t()
            result = _lib.nusd_attribute_get_asset_array(
                self._stage, property_path, time_code, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )

            result = []
            asset_path = c_char_p()
            while _lib.nusd_asset_path_array_iterator_next(value, byref(asset_path)):
                result.append(asset_path.value.decode("utf-8"))

            _lib.nusd_asset_path_array_iterator_destroy(value)
            return result
        else:
            raise GetPropertyError(
                f'unknown type "{property_type}" for property "{property_path}"'
            )

    def define_prim(self, prim_path: str, prim_type: str):
        result = result = _lib.nusd_stage_define_prim(self._stage, prim_path, prim_type)
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define prim <{prim_path}> of type "{prim_type}": {result}'
            )

    def prim_set_transform(
        self,
        xformable_path: str,
        local_to_parent_matrix: np.ndarray,
        time_code: float = 0.0,
    ):
        """Set the transform matrix for an Xformable prim, positioning it relative to its parent.

        Args:
            xformable_path: USD path to an existing Xformable prim
            local_to_parent_matrix: 4x4 transformation matrix as NumPy array (float64) that transforms
                            from local space to its parent space (row-major order)
            time_code: The time at which to set the transform (default: 0.0)

        Raises:
            SetPropertyError: If xformable_path is invalid or local_to_parent_matrix is wrong shape/type
        """
        if (
            not isinstance(local_to_parent_matrix, np.ndarray)
            or local_to_parent_matrix.shape != (4, 4)
            or local_to_parent_matrix.dtype != np.float64
        ):
            raise SetPropertyError(
                f"local_to_parent_matrix must be a 4x4 float64 NumPy array, got {type(local_to_parent_matrix)} with shape {getattr(local_to_parent_matrix, 'shape', 'N/A')} and dtype {getattr(local_to_parent_matrix, 'dtype', 'N/A')}"
            )

        flat_matrix = local_to_parent_matrix.flatten()
        result = _lib.nusd_prim_set_transform(
            self._stage,
            xformable_path.encode("ascii"),
            flat_matrix.ctypes.data_as(POINTER(c_double)),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set local transform for "{xformable_path}": {result}'
            )

    def prim_compute_local_to_world_transform(
        self, xformable_path: str, time_code: float = 0.0
    ) -> np.ndarray:
        """Compute the complete transformation matrix from a prim's local space to world space.

        Args:
            xformable_path: USD path to a transformable prim (must inherit from UsdGeomXformable)
            time_code: The time at which to evaluate the transformation (default: 0.0)

        Returns:
            4x4 transformation matrix as NumPy array (float64) in row-major order that transforms
            points from the prim's local coordinate space to world space

        Raises:
            GetPropertyError: If xformable_path is invalid or prim is not transformable
        """
        transform = (c_double * 16)()
        result = _lib.nusd_prim_compute_local_to_world_transform(
            self._stage, xformable_path.encode("ascii"), c_double(time_code), transform
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to compute local-to-world transform for "{xformable_path}": {result}'
            )

        return np.array(transform).reshape(4, 4)

    def set_property(
        self, property_path: str, property_type, value: Any, time_code: float = 0.0
    ):
        if property_type == FLOAT:
            if not isinstance(value, float):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of float and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_float(
                self._stage, property_path, c_float(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == FLOATARRAY:
            if not isinstance(value, np.ndarray) and not value.dtype == np.float32:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_float_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_float)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == DOUBLE:
            if not isinstance(value, float):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of float and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_double(
                self._stage, property_path, c_double(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type in [FLOAT2, TEXCOORD2F]:
            if isinstance(value, np.ndarray):
                if value.ndim != 1 or len(value) != 2 or value.dtype != np.float32:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not a 2-element float32 array {type(value)}, {value.ndim}, {len(value)} {value.dtype}"
                    )
            else:
                try:
                    iterator = iter(value)
                except TypeError:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not an iterable ({type(value)})"
                    )

                if len(value) != 2:
                    raise ValueError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value has length {len(value)} instead of 2"
                    )

            c_value = (c_float * 2)(value[0], value[1])
            result = _lib.nusd_attribute_set_float2(
                self._stage, property_path, c_value, time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type in [FLOAT2ARRAY, TEXCOORD2FARRAY]:
            if (
                not isinstance(value, np.ndarray)
                or not value.dtype == np.float32
                or value.ndim != 2
                or value.shape[1] != 2
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value, dtype=np.float32)
            result = _lib.nusd_attribute_set_float2_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_float)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type in [
            FLOAT3ARRAY,
            TEXCOORD3FARRAY,
            COLOR3FARRAY,
            POINT3FARRAY,
            VECTOR3FARRAY,
            NORMAL3FARRAY,
        ]:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.float32
                or value.ndim != 2
                or value.shape[1] != 3
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.float32)
            result = _lib.nusd_attribute_set_float3_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_float)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type in [FLOAT4ARRAY, COLOR4FARRAY]:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.float32
                or value.ndim != 2
                or value.shape[1] != 4
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.float32)
            result = _lib.nusd_attribute_set_float4_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_float)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type in [
            FLOAT3,
            TEXCOORD3F,
            COLOR3F,
            POINT3F,
            VECTOR3F,
            NORMAL3F,
        ]:
            if isinstance(value, np.ndarray):
                if value.ndim != 1 or len(value) != 3 or value.dtype != np.float32:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not a 3-element float32 array {type(value)}, {value.ndim}, {len(value)} {value.dtype}"
                    )
            else:
                try:
                    iterator = iter(value)
                except TypeError:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not an iterable ({type(value)})"
                    )

                if len(value) != 3:
                    raise ValueError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value has length {len(value)} instead of 3"
                    )

            c_value = (c_float * 3)(value[0], value[1], value[2])
            result = _lib.nusd_attribute_set_float3(
                self._stage, property_path, c_value, time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type in [FLOAT4, COLOR4F]:
            if isinstance(value, np.ndarray):
                if value.ndim != 1 or len(value) != 4 or value.dtype != np.float32:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not a 4-element float32 array {type(value)}, {value.ndim}, {len(value)} {value.dtype}"
                    )
            else:
                try:
                    iterator = iter(value)
                except TypeError:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not an iterable ({type(value)})"
                    )

                if len(value) != 4:
                    raise ValueError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value has length {len(value)} instead of 4"
                    )

            c_value = (c_float * 4)(value[0], value[1], value[2], value[3])
            result = _lib.nusd_attribute_set_float4(
                self._stage, property_path, c_value, time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT:
            if not isinstance(value, int):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of int and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_int(
                self._stage, property_path, c_int(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT2:
            if isinstance(value, np.ndarray):
                if value.ndim != 1 or len(value) != 2 or value.dtype != np.int32:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not a 2-element int32 array {type(value)}, {value.ndim}, {len(value)} {value.dtype}"
                    )
            else:
                try:
                    iterator = iter(value)
                except TypeError:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not an iterable ({type(value)})"
                    )

                if len(value) != 2:
                    raise ValueError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value has length {len(value)} instead of 2"
                    )

            c_value = (c_int * 2)(int(value[0]), int(value[1]))
            result = _lib.nusd_attribute_set_int2(
                self._stage, property_path, c_value, time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT3:
            if isinstance(value, np.ndarray):
                if value.ndim != 1 or len(value) != 3 or value.dtype != np.int32:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not a 3-element int32 array {type(value)}, {value.ndim}, {len(value)} {value.dtype}"
                    )
            else:
                try:
                    iterator = iter(value)
                except TypeError:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not an iterable ({type(value)})"
                    )

                if len(value) != 3:
                    raise ValueError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value has length {len(value)} instead of 3"
                    )

            c_value = (c_int * 3)(int(value[0]), int(value[1]), int(value[2]))
            result = _lib.nusd_attribute_set_int3(
                self._stage, property_path, c_value, time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT4:
            if isinstance(value, np.ndarray):
                if value.ndim != 1 or len(value) != 4 or value.dtype != np.int32:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not a 4-element int32 array {type(value)}, {value.ndim}, {len(value)} {value.dtype}"
                    )
            else:
                try:
                    iterator = iter(value)
                except TypeError:
                    raise TypeError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value is not an iterable ({type(value)})"
                    )

                if len(value) != 4:
                    raise ValueError(
                        f"incompatible types for property <{property_path}>: requested {property_type} but value has length {len(value)} instead of 4"
                    )

            c_value = (c_int * 4)(
                int(value[0]), int(value[1]), int(value[2]), int(value[3])
            )
            result = _lib.nusd_attribute_set_int4(
                self._stage, property_path, c_value, time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT64:
            if not isinstance(value, int):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of int and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_int64(
                self._stage, property_path, c_longlong(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INTARRAY:
            if not isinstance(value, np.ndarray) or value.dtype != np.int32:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_int_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_int)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT2ARRAY:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.int32
                or value.ndim != 2
                or value.shape[1] != 2
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.int32)
            result = _lib.nusd_attribute_set_int2_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_int)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT3ARRAY:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.int32
                or value.ndim != 2
                or value.shape[1] != 3
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.int32)
            result = _lib.nusd_attribute_set_int3_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_int)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT4ARRAY:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.int32
                or value.ndim != 2
                or value.shape[1] != 4
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.int32)
            result = _lib.nusd_attribute_set_int4_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_int)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == INT64ARRAY:
            if not isinstance(value, np.ndarray) or value.dtype != np.int64:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_int64_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_longlong)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == DOUBLEARRAY:
            if not isinstance(value, np.ndarray) or value.dtype != np.float64:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_double_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == DOUBLE2ARRAY:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.float64
                or value.ndim != 2
                or value.shape[1] != 2
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.float64)
            result = _lib.nusd_attribute_set_double2_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == DOUBLE3ARRAY:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.float64
                or value.ndim != 2
                or value.shape[1] != 3
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.float64)
            result = _lib.nusd_attribute_set_double3_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == DOUBLE4ARRAY:
            if (
                not isinstance(value, np.ndarray)
                or value.dtype != np.float64
                or value.ndim != 2
                or value.shape[1] != 4
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            value_flat = np.ascontiguousarray(value.flatten(), dtype=np.float64)
            result = _lib.nusd_attribute_set_double4_array(
                self._stage,
                property_path,
                value_flat.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == BOOL:
            if not isinstance(value, bool):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of bool and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_bool(
                self._stage, property_path, c_bool(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == BOOLARRAY:
            if not isinstance(value, np.ndarray) or value.dtype != np.bool_:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_bool_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_bool)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == MATRIX2D:
            if (
                not isinstance(value, np.ndarray)
                or value.shape != (2, 2)
                or value.dtype != np.float64
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}>: expected 2x2 float64 array, got {type(value)} with shape {getattr(value, 'shape', 'N/A')} and dtype {getattr(value, 'dtype', 'N/A')}"
                )
            flat_data = value.flatten()
            result = _lib.nusd_attribute_set_matrix2d(
                self._stage,
                property_path,
                flat_data.ctypes.data_as(POINTER(c_double)),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == MATRIX2DARRAY:
            if (
                not isinstance(value, np.ndarray)
                or len(value.shape) != 3
                or value.shape[1:] != (2, 2)
                or value.dtype != np.float64
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}>: expected Nx2x2 float64 array, got {type(value)} with shape {getattr(value, 'shape', 'N/A')} and dtype {getattr(value, 'dtype', 'N/A')}"
                )
            flat_data = value.flatten()
            result = _lib.nusd_attribute_set_matrix2d_array(
                self._stage,
                property_path,
                flat_data.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == MATRIX3D:
            if (
                not isinstance(value, np.ndarray)
                or value.shape != (3, 3)
                or value.dtype != np.float64
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}>: expected 3x3 float64 array, got {type(value)} with shape {getattr(value, 'shape', 'N/A')} and dtype {getattr(value, 'dtype', 'N/A')}"
                )
            flat_data = value.flatten()
            result = _lib.nusd_attribute_set_matrix3d(
                self._stage,
                property_path,
                flat_data.ctypes.data_as(POINTER(c_double)),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == MATRIX3DARRAY:
            if (
                not isinstance(value, np.ndarray)
                or len(value.shape) != 3
                or value.shape[1:] != (3, 3)
                or value.dtype != np.float64
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}>: expected Nx3x3 float64 array, got {type(value)} with shape {getattr(value, 'shape', 'N/A')} and dtype {getattr(value, 'dtype', 'N/A')}"
                )
            flat_data = value.flatten()
            result = _lib.nusd_attribute_set_matrix3d_array(
                self._stage,
                property_path,
                flat_data.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == MATRIX4D:
            if (
                not isinstance(value, np.ndarray)
                or value.shape != (4, 4)
                or value.dtype != np.float64
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}>: expected 4x4 float64 array, got {type(value)} with shape {getattr(value, 'shape', 'N/A')} and dtype {getattr(value, 'dtype', 'N/A')}"
                )
            flat_data = value.flatten()
            result = _lib.nusd_attribute_set_matrix4d(
                self._stage,
                property_path,
                flat_data.ctypes.data_as(POINTER(c_double)),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == MATRIX4DARRAY:
            if (
                not isinstance(value, np.ndarray)
                or len(value.shape) != 3
                or value.shape[1:] != (4, 4)
                or value.dtype != np.float64
            ):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}>: expected Nx4x4 float64 array, got {type(value)} with shape {getattr(value, 'shape', 'N/A')} and dtype {getattr(value, 'dtype', 'N/A')}"
                )
            flat_data = value.flatten()
            result = _lib.nusd_attribute_set_matrix4d_array(
                self._stage,
                property_path,
                flat_data.ctypes.data_as(POINTER(c_double)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == UINT:
            from ctypes import c_uint

            if not isinstance(value, int):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of int and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_uint(
                self._stage, property_path, c_uint(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == UINTARRAY:
            from ctypes import c_uint

            if not isinstance(value, np.ndarray) or value.dtype != np.uint32:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_uint_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_uint)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == UINT64:
            from ctypes import c_ulonglong

            if not isinstance(value, int):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of int and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_uint64(
                self._stage, property_path, c_ulonglong(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == UINT64ARRAY:
            from ctypes import c_ulonglong

            if not isinstance(value, np.ndarray) or value.dtype != np.uint64:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_uint64_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_ulonglong)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == UCHAR:
            from ctypes import c_ubyte

            if not isinstance(value, int):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of int and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_uchar(
                self._stage, property_path, c_ubyte(value), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == UCHARARRAY:
            from ctypes import c_ubyte

            if not isinstance(value, np.ndarray) or value.dtype != np.uint8:
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_uchar_array(
                self._stage,
                property_path,
                value.ctypes.data_as(POINTER(c_ubyte)),
                c_size_t(value.shape[0]),
                time_code,
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == TOKEN:
            if not isinstance(value, str):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_token(
                self._stage, property_path.encode("ascii"), value.encode("ascii"), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == TOKENARRAY:
            if not isinstance(value, (list, tuple)) or not all(isinstance(v, str) for v in value):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            # Convert string list to C array of char pointers
            c_strings = [v.encode("ascii") for v in value]
            c_array = (c_char_p * len(c_strings))(*c_strings)
            result = _lib.nusd_attribute_set_token_array(
                self._stage, property_path.encode("ascii"), ctypes.cast(c_array, POINTER(POINTER(c_char))), c_size_t(len(value)), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == ASSET:
            if not isinstance(value, str):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_asset(
                self._stage, property_path.encode("ascii"), value.encode("ascii"), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        elif property_type == ASSETARRAY:
            if not isinstance(value, (list, tuple)) or not all(isinstance(v, str) for v in value):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
                )
            # Convert string list to C array of char pointers
            c_strings = [v.encode("ascii") for v in value]
            c_array = (c_char_p * len(c_strings))(*c_strings)
            result = _lib.nusd_attribute_set_asset_array(
                self._stage, property_path.encode("ascii"), ctypes.cast(c_array, POINTER(POINTER(c_char))), c_size_t(len(value)), time_code
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        else:
            raise SetPropertyError(f"invalid type for property: {type(value)}")

    def prim_create_property(
        self,
        prim: str,
        property_name: str,
        property_type: str,
        value=None,
        time_code: float = 0.0,
    ):
        result = _lib.nusd_prim_create_property(
            self._stage, prim, property_name, property_type
        )
        if result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create property "{property_name} on prim <{prim}>: {result}'
            )

        if value is not None:
            self.set_property(
                f"{prim}.{property_name}", property_type, value, time_code
            )

    def camera_define(self, camera_path: str):
        """Define a new USD camera prim at the specified path.

        Args:
            camera_path: USD path where the camera should be created (e.g., "/World/Camera")

        Raises:
            DefinePrimError: If the camera cannot be defined at the specified path
        """
        result = _lib.nusd_camera_define(self._stage, camera_path.encode("ascii"))
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define camera at "{camera_path}": {result}'
            )

    def camera_set_fov_w(
        self, camera_path: str, fov_w_deg: float, time_code: float = 0.0
    ):
        """Set the horizontal field of view for a camera by setting its focal length.

        Args:
            camera_path: USD path to an existing camera prim
            fov_w_deg: Horizontal field of view in degrees
            time_code: The time at which to set the field of view (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid
        """
        result = _lib.nusd_camera_set_fov_w(
            self._stage,
            camera_path.encode("ascii"),
            c_float(fov_w_deg),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera FOV for "{camera_path}": {result}'
            )

    def camera_set_exposure(
        self,
        camera_path: str,
        iso: float,
        time: float,
        f_stop: float,
        compensation: float,
        responsivity: float,
        time_code: float = 0.0,
    ):
        """Set the exposure parameters for a camera, simulating real camera controls.

        Args:
            camera_path: USD path to an existing camera prim
            iso: ISO sensitivity value (e.g., 100, 400, 800, 1600)
            time: Exposure time in seconds (e.g., 1/60 = 0.0167 for 60fps)
            f_stop: F-stop value controlling depth of field (e.g., 1.4, 2.8, 5.6, 11)
            compensation: Exposure compensation in stops (positive brightens, negative darkens)
            responsivity: Camera sensor responsivity factor
            time_code: The time at which to set the exposure parameters (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid
        """
        result = _lib.nusd_camera_set_exposure(
            self._stage,
            camera_path.encode("ascii"),
            c_float(iso),
            c_float(time),
            c_float(f_stop),
            c_float(compensation),
            c_float(responsivity),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera exposure for "{camera_path}": {result}'
            )

    def camera_set_clipping_range(
        self, camera_path: str, near: float, far: float, time_code: float = 0.0
    ):
        """Set the near and far clipping distances for a camera's viewing frustum.

        Args:
            camera_path: USD path to an existing camera prim
            near: Near clipping distance in scene units (should be small positive value like 0.1)
            far: Far clipping distance in scene units (should be greater than near)
            time_code: The time at which to set the clipping range (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid
        """
        result = _lib.nusd_camera_set_clipping_range(
            self._stage,
            camera_path.encode("ascii"),
            c_float(near),
            c_float(far),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera clipping range for "{camera_path}": {result}'
            )

    def camera_set_aperture(
        self, camera_path: str, width: float, height: float, time_code: float = 0.0
    ):
        """Set the horizontal and vertical aperture dimensions for a camera.

        Args:
            camera_path: USD path to an existing camera prim
            width: Horizontal aperture in tenths of a scene unit (e.g., millimeters if scene is in centimeters)
            height: Vertical aperture in tenths of a scene unit (e.g., millimeters if scene is in centimeters)
            time_code: The time at which to set the aperture dimensions (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid

        Note:
            The aperture dimensions control the camera's field of view in conjunction with the focal length.
            Common film aperture sizes: 35mm full frame (36x24), Super 35 (24.89x18.66) in tenths of scene units.
            The aspect ratio is determined by width/height and affects the final rendered image proportions.
        """
        result = _lib.nusd_camera_set_aperture(
            self._stage,
            camera_path.encode("ascii"),
            c_float(width),
            c_float(height),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera aperture for "{camera_path}": {result}'
            )

    def material_define(self, material_path: str):
        """Define a new USD material prim at the specified path.

        Args:
            material_path: USD path where the material should be created (e.g., "/World/Materials/MyMaterial")

        Raises:
            DefinePrimError: If the material cannot be defined at the specified path
        """
        result = _lib.nusd_material_define(self._stage, material_path.encode("ascii"))
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(f'failed to define material at "{material_path}": {result}')

    def shader_define(self, shader_path: str, shader_id: str):
        """Define a new USD shader prim at the specified path with the given shader identifier.

        Args:
            shader_path: USD path where the shader should be created (e.g., "/World/Materials/MyMaterial/Shader")
            shader_id: Shader type identifier (e.g., "UsdPreviewSurface", "UsdUVTexture", "UsdPrimvarReader_float2")

        Raises:
            DefinePrimError: If the shader cannot be defined at the specified path

        Note:
            Common shader_id values include "UsdPreviewSurface" for materials, "UsdUVTexture" for textures.
        """
        result = _lib.nusd_shader_define(
            self._stage, shader_path.encode("ascii"), shader_id.encode("ascii")
        )
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(f'failed to define shader at "{shader_path}" with id "{shader_id}": {result}')

    def shader_create_input(self, shader_path: str, input_name: str, input_type: str, value=None, time_code=0.0):
        """Create an input parameter on a shader for receiving values or connections from other shaders.

        Args:
            shader_path: USD path to an existing shader prim
            input_name: Name of the input parameter to create (e.g., "diffuseColor", "roughness", "st")
            input_type: USD type for the input parameter (e.g., COLOR3F, FLOAT, FLOAT2)
            value: Optional value to set on the input parameter
            time_code: Time code for the value (default: 0.0)

        Raises:
            CreatePropertyError: If the input cannot be created
            SetPropertyError: If input_type is RELATIONSHIP (not supported for shader inputs)

        Note:
            The created input will be automatically placed in the "inputs:" namespace (e.g., "inputs:diffuseColor").
            Shader inputs can receive constant values or connections from other shader outputs.
            If value is provided, it will be automatically set on the input parameter.
        """
        result = _lib.nusd_shader_create_input(
            self._stage, 
            shader_path.encode("ascii"), 
            input_name.encode("ascii"), 
            input_type
        )
        if result == _lib.NUSD_RESULT_WRONG_TYPE:
            raise SetPropertyError(f'RELATIONSHIP type not supported for shader input "{input_name}"')
        elif result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(f'failed to create shader input "{input_name}" on "{shader_path}": {result}')

        if value is not None:
            input_path = f"{shader_path}.inputs:{input_name}"
            self.set_property(input_path, input_type, value, time_code)


    def shader_create_output(self, shader_path: str, output_name: str, output_type: str, value=None, time_code=0.0):
        """Create an output parameter on a shader for providing values to other shaders or materials.

        Args:
            shader_path: USD path to an existing shader prim
            output_name: Name of the output parameter to create (e.g., "surface", "rgb", "r")
            output_type: USD type for the output parameter (e.g., TOKEN, COLOR3F, FLOAT)
            value: Optional value to set on the output parameter
            time_code: Time code for the value (default: 0.0)

        Raises:
            CreatePropertyError: If the output cannot be created
            SetPropertyError: If output_type is RELATIONSHIP (not supported for shader outputs)

        Note:
            The created output will be automatically placed in the "outputs:" namespace (e.g., "outputs:rgb").
            Shader outputs provide computed values that can be connected to inputs of other shaders.
            If value is provided, it will be automatically set on the output parameter.
        """
        result = _lib.nusd_shader_create_output(
            self._stage, 
            shader_path.encode("ascii"), 
            output_name.encode("ascii"), 
            output_type
        )
        if result == _lib.NUSD_RESULT_WRONG_TYPE:
            raise SetPropertyError(f'RELATIONSHIP type not supported for shader output "{output_name}"')
        elif result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(f'failed to create shader output "{output_name}" on "{shader_path}": {result}')

        if value is not None:
            output_path = f"{shader_path}.outputs:{output_name}"
            self.set_property(output_path, output_type, value, time_code)

    def shader_connect(self, source_output_path: str, destination_input_path: str):
        """Connect a shader output to a shader input, creating a data flow connection in the shader network.

        Args:
            source_output_path: Full USD path to the source shader output (e.g., "/World/Materials/Mat/Texture.outputs:rgb")
            destination_input_path: Full USD path to the destination shader input (e.g., "/World/Materials/Mat/Surface.inputs:diffuseColor")

        Raises:
            GetPropertyError: If either the source output or destination input cannot be found
            SetPropertyError: If the connection cannot be established

        Note:
            The connection creates a data flow from the source shader's output to the destination shader's input.
            Connected inputs override any authored constant values on the destination input.
            Both the source and destination must exist before calling this function.
        """
        result = _lib.nusd_shader_connect(
            self._stage, 
            source_output_path.encode("ascii"), 
            destination_input_path.encode("ascii")
        )
        if result == _lib.NUSD_RESULT_INVALID_ATTRIBUTE_PATH:
            raise GetPropertyError(f'cannot find source output "{source_output_path}" or destination input "{destination_input_path}"')
        elif result == _lib.NUSD_RESULT_CONNECTION_FAILED:
            raise SetPropertyError(f'failed to connect "{source_output_path}" to "{destination_input_path}"')
        elif result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(f'failed to connect shaders: {result}')
