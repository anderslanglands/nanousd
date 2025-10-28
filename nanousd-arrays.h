#ifndef NANOUSD_ARRAYS_H
#define NANOUSD_ARRAYS_H

#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nusd_bool_array_s* nusd_bool_array_t;

typedef struct nusd_float_array_s* nusd_float_array_t;
typedef struct nusd_float2_array_s* nusd_float2_array_t;
typedef struct nusd_float3_array_s* nusd_float3_array_t;
typedef struct nusd_float4_array_s* nusd_float4_array_t;

typedef struct nusd_double_array_s* nusd_double_array_t;
typedef struct nusd_double2_array_s* nusd_double2_array_t;
typedef struct nusd_double3_array_s* nusd_double3_array_t;
typedef struct nusd_double4_array_s* nusd_double4_array_t;

typedef struct nusd_int_array_s* nusd_int_array_t;
typedef struct nusd_int2_array_s* nusd_int2_array_t;
typedef struct nusd_int3_array_s* nusd_int3_array_t;
typedef struct nusd_int4_array_s* nusd_int4_array_t;
typedef struct nusd_int64_array_s* nusd_int64_array_t;

typedef struct nusd_matrix2d_array_s* nusd_matrix2d_array_t;
typedef struct nusd_matrix3d_array_s* nusd_matrix3d_array_t;
typedef struct nusd_matrix4d_array_s* nusd_matrix4d_array_t;

typedef struct nusd_token_array_s* nusd_token_array_t;

typedef struct nusd_uint_array_s* nusd_uint_array_t;
typedef struct nusd_uint64_array_s* nusd_uint64_array_t;
typedef struct nusd_uchar_array_s* nusd_uchar_array_t;

/// Returns the number of elements in a bool array.
/// 
/// @param bool_array Valid bool array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note bool_array must not be null.
NANOUSD_API
size_t nusd_bool_array_size(nusd_bool_array_t bool_array);

/// Returns a pointer to the raw data of a bool array.
/// 
/// @param bool_array Valid bool array handle.
/// 
/// @return Pointer to the bool data
/// 
/// @note bool_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_bool_array_size() elements.
NANOUSD_API
bool* nusd_bool_array_data(nusd_bool_array_t bool_array);

/// Destroys a bool array and releases associated resources.
/// 
/// @param bool_array Valid bool array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_bool_array_destroy(nusd_bool_array_t bool_array);

/// Returns the number of elements in a float array.
/// 
/// @param float_array Valid float array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note float_array must not be null.
NANOUSD_API
size_t nusd_float_array_size(nusd_float_array_t float_array);

/// Returns a pointer to the raw data of a float array.
/// 
/// @param float_array Valid float array handle.
/// 
/// @return Pointer to the float data
/// 
/// @note float_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_float_array_size() elements.
NANOUSD_API
float* nusd_float_array_data(nusd_float_array_t float_array);

/// Destroys a float array and releases associated resources.
/// 
/// @param float_array Valid float array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float_array_destroy(nusd_float_array_t float_array);

/// Returns the number of float2 elements in a float2 array.
/// 
/// @param float2_array Valid float2 array handle.
/// 
/// @return Number of float2 elements in the array
/// 
/// @note float2_array must not be null.
NANOUSD_API
size_t nusd_float2_array_size(nusd_float2_array_t float2_array);

/// Returns a pointer to the raw data of a float2 array.
/// 
/// @param float2_array Valid float2 array handle.
/// 
/// @return Pointer to the float data (interleaved as x,y,x,y,...)
/// 
/// @note float2_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_float2_array_size() * 2 float values.
NANOUSD_API
float* nusd_float2_array_data(nusd_float2_array_t float2_array);

/// Destroys a float2 array and releases associated resources.
/// 
/// @param float2_array Valid float2 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float2_array_destroy(nusd_float2_array_t float2_array);

/// Returns the number of float3 elements in a float3 array.
/// 
/// @param float3_array Valid float3 array handle.
/// 
/// @return Number of float3 elements in the array
/// 
/// @note float3_array must not be null.
NANOUSD_API
size_t nusd_float3_array_size(nusd_float3_array_t float3_array);

/// Returns a pointer to the raw data of a float3 array.
/// 
/// @param float3_array Valid float3 array handle.
/// 
/// @return Pointer to the float data (interleaved as x,y,z,x,y,z,...)
/// 
/// @note float3_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_float3_array_size() * 3 float values.
NANOUSD_API
float* nusd_float3_array_data(nusd_float3_array_t float3_array);

/// Destroys a float3 array and releases associated resources.
/// 
/// @param float3_array Valid float3 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float3_array_destroy(nusd_float3_array_t float3_array);

/// Returns the number of float4 elements in a float4 array.
/// 
/// @param float4_array Valid float4 array handle.
/// 
/// @return Number of float4 elements in the array
/// 
/// @note float4_array must not be null.
NANOUSD_API
size_t nusd_float4_array_size(nusd_float4_array_t float4_array);

/// Returns a pointer to the raw data of a float4 array.
/// 
/// @param float4_array Valid float4 array handle.
/// 
/// @return Pointer to the float data (interleaved as x,y,z,w,x,y,z,w,...)
/// 
/// @note float4_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_float4_array_size() * 4 float values.
NANOUSD_API
float* nusd_float4_array_data(nusd_float4_array_t float4_array);

/// Destroys a float4 array and releases associated resources.
/// 
/// @param float4_array Valid float4 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_float4_array_destroy(nusd_float4_array_t float4_array);

/// Returns the number of elements in a double array.
/// 
/// @param double_array Valid double array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note double_array must not be null.
NANOUSD_API
size_t nusd_double_array_size(nusd_double_array_t double_array);

/// Returns a pointer to the raw data of a double array.
/// 
/// @param double_array Valid double array handle.
/// 
/// @return Pointer to the double data
/// 
/// @note double_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_double_array_size() elements.
NANOUSD_API
double* nusd_double_array_data(nusd_double_array_t double_array);

/// Destroys a double array and releases associated resources.
/// 
/// @param double_array Valid double array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double_array_destroy(nusd_double_array_t double_array);

/// Returns the number of double2 elements in a double2 array.
/// 
/// @param double2_array Valid double2 array handle.
/// 
/// @return Number of double2 elements in the array
/// 
/// @note double2_array must not be null.
NANOUSD_API
size_t nusd_double2_array_size(nusd_double2_array_t double2_array);

/// Returns a pointer to the raw data of a double2 array.
/// 
/// @param double2_array Valid double2 array handle.
/// 
/// @return Pointer to the double data (interleaved as x,y,x,y,...)
/// 
/// @note double2_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_double2_array_size() * 2 double values.
NANOUSD_API
double* nusd_double2_array_data(nusd_double2_array_t double2_array);

/// Destroys a double2 array and releases associated resources.
/// 
/// @param double2_array Valid double2 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double2_array_destroy(nusd_double2_array_t double2_array);

/// Returns the number of double3 elements in a double3 array.
/// 
/// @param double3_array Valid double3 array handle.
/// 
/// @return Number of double3 elements in the array
/// 
/// @note double3_array must not be null.
NANOUSD_API
size_t nusd_double3_array_size(nusd_double3_array_t double3_array);

/// Returns a pointer to the raw data of a double3 array.
/// 
/// @param double3_array Valid double3 array handle.
/// 
/// @return Pointer to the double data (interleaved as x,y,z,x,y,z,...)
/// 
/// @note double3_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_double3_array_size() * 3 double values.
NANOUSD_API
double* nusd_double3_array_data(nusd_double3_array_t double3_array);

/// Destroys a double3 array and releases associated resources.
/// 
/// @param double3_array Valid double3 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double3_array_destroy(nusd_double3_array_t double3_array);

/// Returns the number of double4 elements in a double4 array.
/// 
/// @param double4_array Valid double4 array handle.
/// 
/// @return Number of double4 elements in the array
/// 
/// @note double4_array must not be null.
NANOUSD_API
size_t nusd_double4_array_size(nusd_double4_array_t double4_array);

/// Returns a pointer to the raw data of a double4 array.
/// 
/// @param double4_array Valid double4 array handle.
/// 
/// @return Pointer to the double data (interleaved as x,y,z,w,x,y,z,w,...)
/// 
/// @note double4_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_double4_array_size() * 4 double values.
NANOUSD_API
double* nusd_double4_array_data(nusd_double4_array_t double4_array);

/// Destroys a double4 array and releases associated resources.
/// 
/// @param double4_array Valid double4 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_double4_array_destroy(nusd_double4_array_t double4_array);

/// Returns the number of elements in an int array.
/// 
/// @param int_array Valid int array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note int_array must not be null.
NANOUSD_API
size_t nusd_int_array_size(nusd_int_array_t int_array);

/// Returns a pointer to the raw data of an int array.
/// 
/// @param int_array Valid int array handle.
/// 
/// @return Pointer to the int data
/// 
/// @note int_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_int_array_size() elements.
NANOUSD_API
int* nusd_int_array_data(nusd_int_array_t int_array);

/// Destroys an int array and releases associated resources.
/// 
/// @param int_array Valid int array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int_array_destroy(nusd_int_array_t int_array);

/// Returns the number of int2 elements in an int2 array.
/// 
/// @param int2_array Valid int2 array handle.
/// 
/// @return Number of int2 elements in the array
/// 
/// @note int2_array must not be null.
NANOUSD_API
size_t nusd_int2_array_size(nusd_int2_array_t int2_array);

/// Returns a pointer to the raw data of an int2 array.
/// 
/// @param int2_array Valid int2 array handle.
/// 
/// @return Pointer to the int data (interleaved as x,y,x,y,...)
/// 
/// @note int2_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_int2_array_size() * 2 int values.
NANOUSD_API
int* nusd_int2_array_data(nusd_int2_array_t int2_array);

/// Destroys an int2 array and releases associated resources.
/// 
/// @param int2_array Valid int2 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int2_array_destroy(nusd_int2_array_t int2_array);

/// Returns the number of int3 elements in an int3 array.
/// 
/// @param int3_array Valid int3 array handle.
/// 
/// @return Number of int3 elements in the array
/// 
/// @note int3_array must not be null.
NANOUSD_API
size_t nusd_int3_array_size(nusd_int3_array_t int3_array);

/// Returns a pointer to the raw data of an int3 array.
/// 
/// @param int3_array Valid int3 array handle.
/// 
/// @return Pointer to the int data (interleaved as x,y,z,x,y,z,...)
/// 
/// @note int3_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_int3_array_size() * 3 int values.
NANOUSD_API
int* nusd_int3_array_data(nusd_int3_array_t int3_array);

/// Destroys an int3 array and releases associated resources.
/// 
/// @param int3_array Valid int3 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int3_array_destroy(nusd_int3_array_t int3_array);

/// Returns the number of int4 elements in an int4 array.
/// 
/// @param int4_array Valid int4 array handle.
/// 
/// @return Number of int4 elements in the array
/// 
/// @note int4_array must not be null.
NANOUSD_API
size_t nusd_int4_array_size(nusd_int4_array_t int4_array);

/// Returns a pointer to the raw data of an int4 array.
/// 
/// @param int4_array Valid int4 array handle.
/// 
/// @return Pointer to the int data (interleaved as x,y,z,w,x,y,z,w,...)
/// 
/// @note int4_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data contains nusd_int4_array_size() * 4 int values.
NANOUSD_API
int* nusd_int4_array_data(nusd_int4_array_t int4_array);

/// Destroys an int4 array and releases associated resources.
/// 
/// @param int4_array Valid int4 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int4_array_destroy(nusd_int4_array_t int4_array);

/// Returns the number of elements in an int64 array.
/// 
/// @param int64_array Valid int64 array handle.
/// 
/// @return Number of elements in the array
/// 
/// @note int64_array must not be null.
NANOUSD_API
size_t nusd_int64_array_size(nusd_int64_array_t int64_array);

/// Returns a pointer to the raw data of an int64 array.
/// 
/// @param int64_array Valid int64 array handle.
/// 
/// @return Pointer to the int64 data
/// 
/// @note int64_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note The data can be safely accessed up to nusd_int64_array_size() elements.
NANOUSD_API
int64_t* nusd_int64_array_data(nusd_int64_array_t int64_array);

/// Destroys an int64 array and releases associated resources.
/// 
/// @param int64_array Valid int64 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_int64_array_destroy(nusd_int64_array_t int64_array);

/// Returns the number of matrix2d elements in a matrix2d array.
/// 
/// @param matrix2d_array Valid matrix2d array handle.
/// 
/// @return Number of matrix2d elements in the array.
/// 
/// @note matrix2d_array must not be null.
NANOUSD_API
size_t nusd_matrix2d_array_size(nusd_matrix2d_array_t matrix2d_array);

/// Returns a pointer to the matrix2d data in a matrix2d array.
/// 
/// @param matrix2d_array Valid matrix2d array handle.
/// 
/// @return Pointer to the matrix2d data. Each matrix2d is stored as 4 consecutive doubles in row-major order.
/// 
/// @note matrix2d_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note Total data size is nusd_matrix2d_array_size(matrix2d_array) * 4 * sizeof(double).
NANOUSD_API
double* nusd_matrix2d_array_data(nusd_matrix2d_array_t matrix2d_array);

/// Destroys a matrix2d array and releases associated resources.
/// 
/// @param matrix2d_array Valid matrix2d array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_matrix2d_array_destroy(nusd_matrix2d_array_t matrix2d_array);

/// Returns the number of matrix3d elements in a matrix3d array.
/// 
/// @param matrix3d_array Valid matrix3d array handle.
/// 
/// @return Number of matrix3d elements in the array.
/// 
/// @note matrix3d_array must not be null.
NANOUSD_API
size_t nusd_matrix3d_array_size(nusd_matrix3d_array_t matrix3d_array);

/// Returns a pointer to the matrix3d data in a matrix3d array.
/// 
/// @param matrix3d_array Valid matrix3d array handle.
/// 
/// @return Pointer to the matrix3d data. Each matrix3d is stored as 9 consecutive doubles in row-major order.
/// 
/// @note matrix3d_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note Total data size is nusd_matrix3d_array_size(matrix3d_array) * 9 * sizeof(double).
NANOUSD_API
double* nusd_matrix3d_array_data(nusd_matrix3d_array_t matrix3d_array);

/// Destroys a matrix3d array and releases associated resources.
/// 
/// @param matrix3d_array Valid matrix3d array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_matrix3d_array_destroy(nusd_matrix3d_array_t matrix3d_array);

/// Returns the number of matrix4d elements in a matrix4d array.
/// 
/// @param matrix4d_array Valid matrix4d array handle.
/// 
/// @return Number of matrix4d elements in the array.
/// 
/// @note matrix4d_array must not be null.
NANOUSD_API
size_t nusd_matrix4d_array_size(nusd_matrix4d_array_t matrix4d_array);

/// Returns a pointer to the matrix4d data in a matrix4d array.
/// 
/// @param matrix4d_array Valid matrix4d array handle.
/// 
/// @return Pointer to the matrix4d data. Each matrix4d is stored as 16 consecutive doubles in row-major order.
/// 
/// @note matrix4d_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
/// @note Total data size is nusd_matrix4d_array_size(matrix4d_array) * 16 * sizeof(double).
NANOUSD_API
double* nusd_matrix4d_array_data(nusd_matrix4d_array_t matrix4d_array);

/// Destroys a matrix4d array and releases associated resources.
/// 
/// @param matrix4d_array Valid matrix4d array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_matrix4d_array_destroy(nusd_matrix4d_array_t matrix4d_array);

// token
/// Returns the number of tokens in a token array.
/// 
/// @param token_array Valid token array handle.
/// 
/// @return Number of tokens in the array
/// 
/// @note token_array must not be null.
NANOUSD_API
size_t nusd_token_array_size(nusd_token_array_t token_array);

/// Returns the token at the specified index in a token array.
/// 
/// @param token_array Valid token array handle.
/// @param index Index of the token to retrieve (must be < nusd_token_array_size()).
/// 
/// @return Pointer to the token string at the specified index
/// 
/// @note token_array must not be null.
/// @note index must be a valid index within the array bounds.
/// @note The returned pointer is valid until the array is destroyed.
NANOUSD_API
char const* nusd_token_array_index(nusd_token_array_t token_array, size_t index);

/// Destroys a token array and releases associated resources.
/// 
/// @param token_array Valid token array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_token_array_destroy(nusd_token_array_t token_array);

/// Returns the number of elements in a uchar array.
/// 
/// @param uchar_array Valid uchar array handle.
/// 
/// @return Number of elements in the array.
/// 
/// @note uchar_array must not be null.
NANOUSD_API
size_t nusd_uchar_array_size(nusd_uchar_array_t uchar_array);

/// Returns a pointer to the uchar data in a uchar array.
/// 
/// @param uchar_array Valid uchar array handle.
/// 
/// @return Pointer to the uchar data.
/// 
/// @note uchar_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
NANOUSD_API
unsigned char* nusd_uchar_array_data(nusd_uchar_array_t uchar_array);

/// Destroys a uchar array and releases associated resources.
/// 
/// @param uchar_array Valid uchar array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_uchar_array_destroy(nusd_uchar_array_t uchar_array);

/// Returns the number of elements in a uint array.
/// 
/// @param uint_array Valid uint array handle.
/// 
/// @return Number of elements in the array.
/// 
/// @note uint_array must not be null.
NANOUSD_API
size_t nusd_uint_array_size(nusd_uint_array_t uint_array);

/// Returns a pointer to the uint data in a uint array.
/// 
/// @param uint_array Valid uint array handle.
/// 
/// @return Pointer to the uint data.
/// 
/// @note uint_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
NANOUSD_API
unsigned int* nusd_uint_array_data(nusd_uint_array_t uint_array);

/// Destroys a uint array and releases associated resources.
/// 
/// @param uint_array Valid uint array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_uint_array_destroy(nusd_uint_array_t uint_array);

/// Returns the number of elements in a uint64 array.
/// 
/// @param uint64_array Valid uint64 array handle.
/// 
/// @return Number of elements in the array.
/// 
/// @note uint64_array must not be null.
NANOUSD_API
size_t nusd_uint64_array_size(nusd_uint64_array_t uint64_array);

/// Returns a pointer to the uint64 data in a uint64 array.
/// 
/// @param uint64_array Valid uint64 array handle.
/// 
/// @return Pointer to the uint64 data.
/// 
/// @note uint64_array must not be null.
/// @note The returned pointer is valid until the array is destroyed.
NANOUSD_API
uint64_t* nusd_uint64_array_data(nusd_uint64_array_t uint64_array);

/// Destroys a uint64 array and releases associated resources.
/// 
/// @param uint64_array Valid uint64 array handle to destroy. Can be null (no-op).
/// 
/// @note After calling this function, the array handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null array handle.
NANOUSD_API
void nusd_uint64_array_destroy(nusd_uint64_array_t uint64_array);


#ifdef __cplusplus
}
#endif

#endif

