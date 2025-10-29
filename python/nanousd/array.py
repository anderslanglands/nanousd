import numpy as np
from numpy.lib.mixins import NDArrayOperatorsMixin

from . import ffi as _lib

from ctypes import c_void_p


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
