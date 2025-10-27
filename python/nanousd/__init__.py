from typing import Any
from . import ffi as _lib
import numpy as np
from numpy.lib.mixins import NDArrayOperatorsMixin

import ctypes
from ctypes import c_void_p, c_bool, c_int, c_char_p, POINTER, byref, c_float, c_double, c_longlong

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


_lib.nusd_prim_iterator_next.argtypes = [_lib.nusd_prim_iterator_t, POINTER(c_char_p)]


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

    def get_property(self, property_path: str):
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
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_FLOATARRAY:
            value = _lib.nusd_float_array_t()
            result = _lib.nusd_attribute_get_float_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return FloatArray(value)
        elif property_type in [_lib.NUSD_TYPE_FLOAT2, _lib.NUSD_TYPE_TEXCOORD2F]:
            value = (c_float * 2)()
            result = _lib.nusd_attribute_get_float2(self._stage, property_path, value)
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
                self._stage, property_path, byref(value)
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
            result = _lib.nusd_attribute_get_float3(self._stage, property_path, value)
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
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Float3Array(value)
        elif property_type in [_lib.NUSD_TYPE_FLOAT4, _lib.NUSD_TYPE_COLOR4F]:
            value = (c_float * 4)()
            result = _lib.nusd_attribute_get_float4(self._stage, property_path, value)
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type in [_lib.NUSD_TYPE_FLOAT4ARRAY, _lib.NUSD_TYPE_COLOR4FARRAY]:
            value = _lib.nusd_float4_array_t()
            result = _lib.nusd_attribute_get_float4_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Float4Array(value)
        elif property_type == _lib.NUSD_TYPE_DOUBLE:
            value = c_double(0.0)
            result = _lib.nusd_attribute_get_double(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_DOUBLEARRAY:
            value = _lib.nusd_double_array_t()
            result = _lib.nusd_attribute_get_double_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return DoubleArray(value)
        elif property_type in [_lib.NUSD_TYPE_DOUBLE2, _lib.NUSD_TYPE_TEXCOORD2D]:
            value = (c_double * 2)()
            result = _lib.nusd_attribute_get_double2(self._stage, property_path, value)
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
                self._stage, property_path, byref(value)
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
            result = _lib.nusd_attribute_get_double3(self._stage, property_path, value)
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
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Double3Array(value)
        elif property_type in [_lib.NUSD_TYPE_DOUBLE4, _lib.NUSD_TYPE_COLOR4D]:
            value = (c_double * 4)()
            result = _lib.nusd_attribute_get_double4(self._stage, property_path, value)
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
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Double4Array(value)
        elif property_type == _lib.NUSD_TYPE_INT:
            value = c_int(0)
            result = _lib.nusd_attribute_get_int(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_INTARRAY:
            value = _lib.nusd_int_array_t()
            result = _lib.nusd_attribute_get_int_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return IntArray(value)
        elif property_type == _lib.NUSD_TYPE_INT2:
            value = (c_int * 2)()
            result = _lib.nusd_attribute_get_int2(self._stage, property_path, value)
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type == _lib.NUSD_TYPE_INT2ARRAY:
            value = _lib.nusd_int2_array_t()
            result = _lib.nusd_attribute_get_int2_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int2Array(value)
        elif property_type == _lib.NUSD_TYPE_INT3:
            value = (c_int * 3)()
            result = _lib.nusd_attribute_get_int3(self._stage, property_path, value)
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type == _lib.NUSD_TYPE_INT3ARRAY:
            value = _lib.nusd_int3_array_t()
            result = _lib.nusd_attribute_get_int3_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int3Array(value)
        elif property_type == _lib.NUSD_TYPE_INT4:
            value = (c_int * 4)()
            result = _lib.nusd_attribute_get_int4(self._stage, property_path, value)
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return np.array(value)
        elif property_type == _lib.NUSD_TYPE_INT4ARRAY:
            value = _lib.nusd_int4_array_t()
            result = _lib.nusd_attribute_get_int4_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int4Array(value)
        elif property_type == _lib.NUSD_TYPE_INT64:
            value = c_longlong(0)
            result = _lib.nusd_attribute_get_int64(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return value.value
        elif property_type == _lib.NUSD_TYPE_INT64ARRAY:
            value = _lib.nusd_int64_array_t()
            result = _lib.nusd_attribute_get_int64_array(
                self._stage, property_path, byref(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise GetPropertyError(
                    f'failed to get value for "{property_path}": {result}'
                )
            return Int64Array(value)

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

    def set_property(self, property_path: str, property_type, value: Any):
        if property_type == FLOAT:
            if not isinstance(value, float):
                raise SetPropertyError(
                    f"incompatible types for property <{property_path}> with value type of float and requested type of {property_type}"
                )
            result = _lib.nusd_attribute_set_float(
                self._stage, property_path, c_float(value)
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
                self._stage, property_path, c_double(value)
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
            result = _lib.nusd_attribute_set_float2(self._stage, property_path, c_value)
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
            result = _lib.nusd_attribute_set_float3(self._stage, property_path, c_value)
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

            c_value = (c_float * 4)(value[0], value[1], value[2])
            result = _lib.nusd_attribute_set_float4(self._stage, property_path, c_value)
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
                self._stage, property_path, c_int(value)
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
            result = _lib.nusd_attribute_set_int2(self._stage, property_path, c_value)
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
            result = _lib.nusd_attribute_set_int3(self._stage, property_path, c_value)
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

            c_value = (c_int * 4)(int(value[0]), int(value[1]), int(value[2]), int(value[3]))
            result = _lib.nusd_attribute_set_int4(self._stage, property_path, c_value)
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
                self._stage, property_path, c_longlong(value)
            )
            if result != _lib.NUSD_RESULT_OK:
                raise SetPropertyError(
                    f'failed to set property "{property_path}: {result}'
                )
        else:
            raise SetPropertyError(f"invalid type for property: {type(value)}")

    def prim_create_property(
        self, prim: str, property_name: str, property_type: str, value=None
    ):
        result = _lib.nusd_prim_create_property(
            self._stage, prim, property_name, property_type
        )
        if result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create property "{property_name} on prim <{prim}>: {result}'
            )

        if value is not None:
            self.set_property(f"{prim}.{property_name}", property_type, value)
