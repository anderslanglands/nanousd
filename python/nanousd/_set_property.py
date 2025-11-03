from . import ffi as _lib
from .array import *
from .tokens import *

import ctypes
from ctypes import (
    c_bool,
    c_char,
    c_int,
    c_char_p,
    c_float,
    c_double,
    c_longlong,
    POINTER,
    c_size_t
)

from typing import Any

class SetPropertyError(RuntimeError):
    pass


def _set_property(
    stage, property_path: str, property_type, value: Any, time_code: float = TIMECODE_DEFAULT
):
    if property_type == FLOAT:
        if not isinstance(value, float) and not isinstance(value, int) and not isinstance(value, np.float32) and not isinstance(value, np.float64):
            raise SetPropertyError(
                f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
            )
        result = _lib.nusd_attribute_set_float(
            stage._stage, property_path, c_float(value), time_code
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
            stage._stage,
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
            stage._stage, property_path, c_double(value), time_code
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
            stage._stage, property_path, c_value, time_code
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage, property_path, c_value, time_code
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
            stage._stage, property_path, c_value, time_code
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
            stage._stage, property_path, c_int(value), time_code
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
            stage._stage, property_path, c_value, time_code
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
            stage._stage, property_path, c_value, time_code
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
            stage._stage, property_path, c_value, time_code
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
            stage._stage, property_path, c_longlong(value), time_code
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage, property_path, c_bool(value), time_code
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage,
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
            stage._stage, property_path, c_uint(value), time_code
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
            stage._stage,
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
            stage._stage, property_path, c_ulonglong(value), time_code
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
            stage._stage,
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
            stage._stage, property_path, c_ubyte(value), time_code
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
            stage._stage,
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
            stage._stage,
            property_path.encode("ascii"),
            value.encode("ascii"),
            time_code,
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set property "{property_path}: {result}'
            )
    elif property_type == TOKENARRAY:
        if not isinstance(value, (list, tuple)) or not all(
            isinstance(v, str) for v in value
        ):
            raise SetPropertyError(
                f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
            )
        # Convert string list to C array of char pointers
        c_strings = [v.encode("ascii") for v in value]
        c_array = (c_char_p * len(c_strings))(*c_strings)
        result = _lib.nusd_attribute_set_token_array(
            stage._stage,
            property_path.encode("ascii"),
            ctypes.cast(c_array, POINTER(POINTER(c_char))),
            c_size_t(len(value)),
            time_code,
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
            stage._stage,
            property_path.encode("ascii"),
            value.encode("ascii"),
            time_code,
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set property "{property_path}: {result}'
            )
    elif property_type == ASSETARRAY:
        if not isinstance(value, (list, tuple)) or not all(
            isinstance(v, str) for v in value
        ):
            raise SetPropertyError(
                f"incompatible types for property <{property_path}> with value type of {type(value)} and requested type of {property_type}"
            )
        # Convert string list to C array of char pointers
        c_strings = [v.encode("ascii") for v in value]
        c_array = (c_char_p * len(c_strings))(*c_strings)
        result = _lib.nusd_attribute_set_asset_array(
            stage._stage,
            property_path.encode("ascii"),
            ctypes.cast(c_array, POINTER(POINTER(c_char))),
            c_size_t(len(value)),
            time_code,
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set property "{property_path}: {result}'
            )
    else:
        raise SetPropertyError(f"invalid type for property: {type(value)}")
