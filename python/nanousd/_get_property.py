from . import ffi as _lib
from .array import *

from ctypes import (
    c_bool,
    c_int,
    c_char_p,
    byref,
    c_float,
    c_double,
    c_longlong,
)

class GetPropertyError(RuntimeError):
    pass


def _get_property(stage, property_path: str, time_code: float = 0.0):
    property_type = _lib.nusd_type_t()
    result = _lib.nusd_property_get_type(
        stage._stage, property_path, byref(property_type)
    )

    if result != _lib.NUSD_RESULT_OK:
        raise GetPropertyError(
            f'failed to get property type for "{property_path}": {result}'
        )

    if property_type == _lib.NUSD_TYPE_FLOAT:
        value = c_float(0.0)
        result = _lib.nusd_attribute_get_float(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_FLOATARRAY:
        value = _lib.nusd_float_array_t()
        result = _lib.nusd_attribute_get_float_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return FloatArray(value)
    elif property_type in [_lib.NUSD_TYPE_FLOAT2, _lib.NUSD_TYPE_TEXCOORD2F]:
        value = (c_float * 2)()
        result = _lib.nusd_attribute_get_float2(
            stage._stage, property_path, time_code, value
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
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, value
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
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Float3Array(value)
    elif property_type in [_lib.NUSD_TYPE_FLOAT4, _lib.NUSD_TYPE_COLOR4F]:
        value = (c_float * 4)()
        result = _lib.nusd_attribute_get_float4(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value)
    elif property_type in [_lib.NUSD_TYPE_FLOAT4ARRAY, _lib.NUSD_TYPE_COLOR4FARRAY]:
        value = _lib.nusd_float4_array_t()
        result = _lib.nusd_attribute_get_float4_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Float4Array(value)
    elif property_type == _lib.NUSD_TYPE_DOUBLE:
        value = c_double(0.0)
        result = _lib.nusd_attribute_get_double(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_DOUBLEARRAY:
        value = _lib.nusd_double_array_t()
        result = _lib.nusd_attribute_get_double_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return DoubleArray(value)
    elif property_type in [_lib.NUSD_TYPE_DOUBLE2, _lib.NUSD_TYPE_TEXCOORD2D]:
        value = (c_double * 2)()
        result = _lib.nusd_attribute_get_double2(
            stage._stage, property_path, time_code, value
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
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, value
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
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Double3Array(value)
    elif property_type in [_lib.NUSD_TYPE_DOUBLE4, _lib.NUSD_TYPE_COLOR4D]:
        value = (c_double * 4)()
        result = _lib.nusd_attribute_get_double4(
            stage._stage, property_path, time_code, value
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
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Double4Array(value)
    elif property_type == _lib.NUSD_TYPE_INT:
        value = c_int(0)
        result = _lib.nusd_attribute_get_int(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_INTARRAY:
        value = _lib.nusd_int_array_t()
        result = _lib.nusd_attribute_get_int_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return IntArray(value)
    elif property_type == _lib.NUSD_TYPE_INT2:
        value = (c_int * 2)()
        result = _lib.nusd_attribute_get_int2(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value)
    elif property_type == _lib.NUSD_TYPE_INT2ARRAY:
        value = _lib.nusd_int2_array_t()
        result = _lib.nusd_attribute_get_int2_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Int2Array(value)
    elif property_type == _lib.NUSD_TYPE_INT3:
        value = (c_int * 3)()
        result = _lib.nusd_attribute_get_int3(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value)
    elif property_type == _lib.NUSD_TYPE_INT3ARRAY:
        value = _lib.nusd_int3_array_t()
        result = _lib.nusd_attribute_get_int3_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Int3Array(value)
    elif property_type == _lib.NUSD_TYPE_INT4:
        value = (c_int * 4)()
        result = _lib.nusd_attribute_get_int4(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value)
    elif property_type == _lib.NUSD_TYPE_INT4ARRAY:
        value = _lib.nusd_int4_array_t()
        result = _lib.nusd_attribute_get_int4_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Int4Array(value)
    elif property_type == _lib.NUSD_TYPE_INT64:
        value = c_longlong(0)
        result = _lib.nusd_attribute_get_int64(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_INT64ARRAY:
        value = _lib.nusd_int64_array_t()
        result = _lib.nusd_attribute_get_int64_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Int64Array(value)
    elif property_type == _lib.NUSD_TYPE_BOOL:
        value = c_bool(False)
        result = _lib.nusd_attribute_get_bool(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_BOOLARRAY:
        value = _lib.nusd_bool_array_t()
        result = _lib.nusd_attribute_get_bool_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return BoolArray(value)
    elif property_type == _lib.NUSD_TYPE_MATRIX2D:
        value = (c_double * 4)()
        result = _lib.nusd_attribute_get_matrix2d(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value).reshape(2, 2)
    elif property_type == _lib.NUSD_TYPE_MATRIX2DARRAY:
        value = _lib.nusd_matrix2d_array_t()
        result = _lib.nusd_attribute_get_matrix2d_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Matrix2dArray(value)
    elif property_type == _lib.NUSD_TYPE_MATRIX3D:
        value = (c_double * 9)()
        result = _lib.nusd_attribute_get_matrix3d(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value).reshape(3, 3)
    elif property_type == _lib.NUSD_TYPE_MATRIX3DARRAY:
        value = _lib.nusd_matrix3d_array_t()
        result = _lib.nusd_attribute_get_matrix3d_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return Matrix3dArray(value)
    elif property_type == _lib.NUSD_TYPE_MATRIX4D:
        value = (c_double * 16)()
        result = _lib.nusd_attribute_get_matrix4d(
            stage._stage, property_path, time_code, value
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return np.array(value).reshape(4, 4)
    elif property_type == _lib.NUSD_TYPE_MATRIX4DARRAY:
        value = _lib.nusd_matrix4d_array_t()
        result = _lib.nusd_attribute_get_matrix4d_array(
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_UINTARRAY:
        value = _lib.nusd_uint_array_t()
        result = _lib.nusd_attribute_get_uint_array(
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_UINT64ARRAY:
        value = _lib.nusd_uint64_array_t()
        result = _lib.nusd_attribute_get_uint64_array(
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value
    elif property_type == _lib.NUSD_TYPE_UCHARARRAY:
        value = _lib.nusd_uchar_array_t()
        result = _lib.nusd_attribute_get_uchar_array(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return UcharArray(value)
    elif property_type == _lib.NUSD_TYPE_TOKEN:
        value = c_char_p()
        result = _lib.nusd_attribute_get_token(
            stage._stage, property_path, time_code, byref(value)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get value for "{property_path}": {result}'
            )
        return value.value.decode("utf-8")
    elif property_type == _lib.NUSD_TYPE_TOKENARRAY:
        value = _lib.nusd_token_array_iterator_t()
        result = _lib.nusd_attribute_get_token_array(
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, byref(value)
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
            stage._stage, property_path, time_code, byref(value)
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
