#ifndef NANOUSD_PROPERTIES_H
#define NANOUSD_PROPERTIES_H

#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Gets the type of a property at the specified path.
/// 
/// @param stage Valid stage handle.
/// @param property_path USD path to the property.
/// @param property_type Output pointer that will contain the property's type on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PROPERTY_PATH if no property exists at the specified path
/// 
/// @note stage must not be null.
/// @note property_path must not be null.
/// @note property_type must not be null.
/// @note For relationships, property_type will be set to NUSD_TYPE_RELATIONSHIP.
NANOUSD_API
nusd_result_t nusd_property_get_type(nusd_stage_t stage, char const* property_path, nusd_type_t* property_type);

/// Gets the value of the given attribute as a token, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param token Output pointer that will contain the token value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of token type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note token must not be null.
/// @note The returned token pointer is valid until the stage is destroyed.
NANOUSD_API
nusd_result_t nusd_attribute_get_token(nusd_stage_t stage, char const* attribute_path, double time_code, char const** token);

/// Gets the value of the given attribute as a token array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param token_array Output pointer that will contain the token array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of token array type
/// 
/// @note The returned token array must be released with nusd_token_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note token_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_token_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_token_array_t* token_array);

// float
/// Gets the value of the given attribute as a float, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output pointer that will contain the float value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float(nusd_stage_t stage, char const* attribute_path, double time_code, float* value);

/// Gets the value of the given attribute as a float array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param float_array Output pointer that will contain the float array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float array type
/// 
/// @note The returned float array must be released with nusd_float_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float_array_t* float_array);

/// Gets the value of the given attribute as a 2-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 2) that will contain the float2 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 floats.
NANOUSD_API
nusd_result_t nusd_attribute_get_float2(nusd_stage_t stage, char const* attribute_path, double time_code, float* value);

/// Gets the value of the given attribute as a float2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param float2_array Output pointer that will contain the float2 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 array type
/// 
/// @note The returned float2 array must be released with nusd_float2_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float2_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float2_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float2_array_t* float2_array);

/// Gets the value of the given attribute as a 3-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 3) that will contain the float3 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 floats.
NANOUSD_API
nusd_result_t nusd_attribute_get_float3(nusd_stage_t stage, char const* attribute_path, double time_code, float* value);

/// Gets the value of the given attribute as a float3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param float3_array Output pointer that will contain the float3 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 array type
/// 
/// @note The returned float3 array must be released with nusd_float3_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float3_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float3_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float3_array_t* float3_array);

/// Gets the value of the given attribute as a 4-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 4) that will contain the float4 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 floats.
NANOUSD_API
nusd_result_t nusd_attribute_get_float4(nusd_stage_t stage, char const* attribute_path, double time_code, float* value);

/// Gets the value of the given attribute as a float4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param float4_array Output pointer that will contain the float4 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 array type
/// 
/// @note The returned float4 array must be released with nusd_float4_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note float4_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_float4_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_float4_array_t* float4_array);

/// Sets the value of the given attribute to a float, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Float value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_float(nusd_stage_t stage, char const* attribute_path, float value, double time_code);

/// Sets the value of the given attribute to a float array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float data to set.
/// @param num_elements Number of float elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 2-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 2 float values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 floats.
NANOUSD_API
nusd_result_t nusd_attribute_set_float2(nusd_stage_t stage, char const* attribute_path, float* value, double time_code);

/// Sets the value of the given attribute to a float2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float2 data to set (interleaved as x,y,x,y,...).
/// @param num_elements Number of float2 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float2 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 2 float values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float2_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 3-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 3 float values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 floats.
NANOUSD_API
nusd_result_t nusd_attribute_set_float3(nusd_stage_t stage, char const* attribute_path, float* value, double time_code);

/// Sets the value of the given attribute to a float3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float3 data to set (interleaved as x,y,z,x,y,z,...).
/// @param num_elements Number of float3 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float3 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 3 float values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float3_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 4-component float vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 float values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 floats.
NANOUSD_API
nusd_result_t nusd_attribute_set_float4(nusd_stage_t stage, char const* attribute_path, float* value, double time_code);

/// Sets the value of the given attribute to a float4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the float4 data to set (interleaved as x,y,z,w,x,y,z,w,...).
/// @param num_elements Number of float4 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of float4 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 4 float values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_float4_array(nusd_stage_t stage, char const* attribute_path, float* data, size_t num_elements, double time_code);

// double
/// Gets the value of the given attribute as a double, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output pointer that will contain the double value on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a double array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param double_array Output pointer that will contain the double array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double array type
/// 
/// @note The returned double array must be released with nusd_double_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double_array_t* double_array);

/// Gets the value of the given attribute as a 2-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 2) that will contain the double2 values on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_double2(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a double2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param double2_array Output pointer that will contain the double2 array handle on success.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 array type
/// 
/// @note The returned double2 array must be released with nusd_double2_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double2_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double2_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double2_array_t* double2_array);

/// Gets the value of the given attribute as a 3-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 3) that will contain the double3 values on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_double3(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a double3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param double3_array Output pointer that will contain the double3 array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 array type
/// 
/// @note The returned double3 array must be released with nusd_double3_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double3_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double3_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double3_array_t* double3_array);

/// Gets the value of the given attribute as a 4-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 4) that will contain the double4 values on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_double4(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a double4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param double4_array Output pointer that will contain the double4 array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 array type
/// 
/// @note The returned double4 array must be released with nusd_double4_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note double4_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_double4_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_double4_array_t* double4_array);

// double setters
/// Sets the value of the given attribute to a double, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Double value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_double(nusd_stage_t stage, char const* attribute_path, double value, double time_code);

/// Sets the value of the given attribute to a double array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double data to set.
/// @param num_elements Number of double elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 2-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 2 double values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_double2(nusd_stage_t stage, char const* attribute_path, double* value, double time_code);

/// Sets the value of the given attribute to a double2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double2 data to set (interleaved as x,y,x,y,...).
/// @param num_elements Number of double2 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double2 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 2 double values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double2_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 3-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 3 double values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_double3(nusd_stage_t stage, char const* attribute_path, double* value, double time_code);

/// Sets the value of the given attribute to a double3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double3 data to set (interleaved as x,y,z,x,y,z,...).
/// @param num_elements Number of double3 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double3 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 3 double values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double3_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 4-component double vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 double values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_double4(nusd_stage_t stage, char const* attribute_path, double* value, double time_code);

/// Sets the value of the given attribute to a double4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the double4 data to set (interleaved as x,y,z,w,x,y,z,w,...).
/// @param num_elements Number of double4 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of double4 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 4 double values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_double4_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

// int
/// Gets the value of the given attribute as an int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output pointer that will contain the int value on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int(nusd_stage_t stage, char const* attribute_path, double time_code, int* value);

/// Gets the value of the given attribute as an int array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param int_array Output pointer that will contain the int array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int array type
/// 
/// @note The returned int array must be released with nusd_int_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int_array_t* int_array);

/// Gets the value of the given attribute as a 2-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 2) that will contain the int2 values on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 ints.
NANOUSD_API
nusd_result_t nusd_attribute_get_int2(nusd_stage_t stage, char const* attribute_path, double time_code, int* value);

/// Gets the value of the given attribute as an int2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param int2_array Output pointer that will contain the int2 array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 array type
/// 
/// @note The returned int2 array must be released with nusd_int2_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int2_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int2_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int2_array_t* int2_array);

/// Gets the value of the given attribute as a 3-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 3) that will contain the int3 values on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 ints.
NANOUSD_API
nusd_result_t nusd_attribute_get_int3(nusd_stage_t stage, char const* attribute_path, double time_code, int* value);

/// Gets the value of the given attribute as an int3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param int3_array Output pointer that will contain the int3 array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 array type
/// 
/// @note The returned int3 array must be released with nusd_int3_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int3_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int3_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int3_array_t* int3_array);

/// Gets the value of the given attribute as a 4-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output array (size 4) that will contain the int4 values on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 ints.
NANOUSD_API
nusd_result_t nusd_attribute_get_int4(nusd_stage_t stage, char const* attribute_path, double time_code, int* value);

/// Gets the value of the given attribute as an int4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param int4_array Output pointer that will contain the int4 array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 array type
/// 
/// @note The returned int4 array must be released with nusd_int4_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int4_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int4_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int4_array_t* int4_array);

// int64
/// Gets the value of the given attribute as an int64, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output pointer that will contain the int64 value on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int64(nusd_stage_t stage, char const* attribute_path, double time_code, int64_t* value);

/// Gets the value of the given attribute as an int64 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param int64_array Output pointer that will contain the int64 array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 array type
/// 
/// @note The returned int64 array must be released with nusd_int64_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note int64_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_int64_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_int64_array_t* int64_array);

// int setters
/// Sets the value of the given attribute to an int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Int value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_int(nusd_stage_t stage, char const* attribute_path, int value, double time_code);

/// Sets the value of the given attribute to an int array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int data to set.
/// @param num_elements Number of int elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 2-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 2 int values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 2 ints.
NANOUSD_API
nusd_result_t nusd_attribute_set_int2(nusd_stage_t stage, char const* attribute_path, int* value, double time_code);

/// Sets the value of the given attribute to an int2 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int2 data to set (interleaved as x,y,x,y,...).
/// @param num_elements Number of int2 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int2 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 2 int values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int2_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 3-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 3 int values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 3 ints.
NANOUSD_API
nusd_result_t nusd_attribute_set_int3(nusd_stage_t stage, char const* attribute_path, int* value, double time_code);

/// Sets the value of the given attribute to an int3 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int3 data to set (interleaved as x,y,z,x,y,z,...).
/// @param num_elements Number of int3 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int3 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 3 int values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int3_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements, double time_code);

/// Sets the value of the given attribute to a 4-component int vector, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 int values to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to an array of at least 4 ints.
NANOUSD_API
nusd_result_t nusd_attribute_set_int4(nusd_stage_t stage, char const* attribute_path, int* value, double time_code);

/// Sets the value of the given attribute to an int4 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int4 data to set (interleaved as x,y,z,w,x,y,z,w,...).
/// @param num_elements Number of int4 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int4 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must contain num_elements * 4 int values.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int4_array(nusd_stage_t stage, char const* attribute_path, int* data, size_t num_elements, double time_code);

// int64 setters
/// Sets the value of the given attribute to an int64, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Int64 value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_int64(nusd_stage_t stage, char const* attribute_path, int64_t value, double time_code);

/// Sets the value of the given attribute to an int64 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the int64 data to set.
/// @param num_elements Number of int64 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of int64 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_int64_array(nusd_stage_t stage, char const* attribute_path, int64_t* data, size_t num_elements, double time_code);

// bool
/// Gets the value of the given attribute as a bool, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Output pointer that will contain the bool value on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of bool type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_bool(nusd_stage_t stage, char const* attribute_path, double time_code, bool* value);

/// Gets the value of the given attribute as a bool array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param bool_array Output pointer that will contain the bool array handle on success.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of bool array type
/// 
/// @note The returned bool array must be released with nusd_bool_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note bool_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_bool_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_bool_array_t* bool_array);

// matrix2d getters
/// Gets the value of the given attribute as a 2x2 matrix of doubles, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Pointer to array of 4 doubles to store the matrix values in row-major order.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix2d type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to at least 4 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_matrix2d(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a matrix2d array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param matrix2d_array Pointer to store the matrix2d array handle.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix2d array type
/// 
/// @note The returned matrix2d array must be released with nusd_matrix2d_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note matrix2d_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_matrix2d_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_matrix2d_array_t* matrix2d_array);

// matrix3d getters
/// Gets the value of the given attribute as a 3x3 matrix of doubles, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Pointer to array of 9 doubles to store the matrix values in row-major order.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix3d type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to at least 9 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_matrix3d(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a matrix3d array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param matrix3d_array Pointer to store the matrix3d array handle.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix3d array type
/// 
/// @note The returned matrix3d array must be released with nusd_matrix3d_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note matrix3d_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_matrix3d_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_matrix3d_array_t* matrix3d_array);

// matrix4d getters
/// Gets the value of the given attribute as a 4x4 matrix of doubles, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Pointer to array of 16 doubles to store the matrix values in row-major order.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix4d type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to at least 16 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_get_matrix4d(nusd_stage_t stage, char const* attribute_path, double time_code, double* value);

/// Gets the value of the given attribute as a matrix4d array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param matrix4d_array Pointer to store the matrix4d array handle.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix4d array type
/// 
/// @note The returned matrix4d array must be released with nusd_matrix4d_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note matrix4d_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_matrix4d_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_matrix4d_array_t* matrix4d_array);

// bool setters
/// Sets the value of the given attribute to a bool, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Bool value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of bool type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_bool(nusd_stage_t stage, char const* attribute_path, bool value, double time_code);

/// Sets the value of the given attribute to a bool array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the bool data to set.
/// @param num_elements Number of bool elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of bool array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_bool_array(nusd_stage_t stage, char const* attribute_path, bool* data, size_t num_elements, double time_code);

// matrix2d setters
/// Sets the value of the given attribute to a 2x2 matrix of doubles, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 4 doubles containing matrix values in row-major order.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix2d type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to at least 4 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_matrix2d(nusd_stage_t stage, char const* attribute_path, double* value, double time_code);

/// Sets the value of the given attribute to a matrix2d array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the matrix2d data to set. Each matrix2d should be 4 consecutive doubles in row-major order.
/// @param num_elements Number of matrix2d elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix2d array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must point to at least num_elements * 4 doubles.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_matrix2d_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

// matrix3d setters
/// Sets the value of the given attribute to a 3x3 matrix of doubles, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 9 doubles containing matrix values in row-major order.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix3d type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to at least 9 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_matrix3d(nusd_stage_t stage, char const* attribute_path, double* value, double time_code);

/// Sets the value of the given attribute to a matrix3d array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the matrix3d data to set. Each matrix3d should be 9 consecutive doubles in row-major order.
/// @param num_elements Number of matrix3d elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix3d array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must point to at least num_elements * 9 doubles.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_matrix3d_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

// matrix4d setters
/// Sets the value of the given attribute to a 4x4 matrix of doubles, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Pointer to array of 16 doubles containing matrix values in row-major order.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix4d type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null and must point to at least 16 doubles.
NANOUSD_API
nusd_result_t nusd_attribute_set_matrix4d(nusd_stage_t stage, char const* attribute_path, double* value, double time_code);

/// Sets the value of the given attribute to a matrix4d array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the matrix4d data to set. Each matrix4d should be 16 consecutive doubles in row-major order.
/// @param num_elements Number of matrix4d elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of matrix4d array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null and must point to at least num_elements * 16 doubles.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_matrix4d_array(nusd_stage_t stage, char const* attribute_path, double* data, size_t num_elements, double time_code);

// uint getters
/// Gets the value of the given attribute as an unsigned int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Pointer to store the unsigned int value.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_uint(nusd_stage_t stage, char const* attribute_path, double time_code, unsigned int* value);

/// Gets the value of the given attribute as a uint array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param uint_array Pointer to store the uint array handle.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint array type
/// 
/// @note The returned uint array must be released with nusd_uint_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note uint_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_uint_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_uint_array_t* uint_array);

// uint64 getters
/// Gets the value of the given attribute as an unsigned 64-bit int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Pointer to store the uint64 value.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint64 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_uint64(nusd_stage_t stage, char const* attribute_path, double time_code, uint64_t* value);

/// Gets the value of the given attribute as a uint64 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param uint64_array Pointer to store the uint64 array handle.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint64 array type
/// 
/// @note The returned uint64 array must be released with nusd_uint64_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note uint64_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_uint64_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_uint64_array_t* uint64_array);

// uchar getters
/// Gets the value of the given attribute as an unsigned char, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param value Pointer to store the uchar value.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uchar type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note value must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_uchar(nusd_stage_t stage, char const* attribute_path, double time_code, unsigned char* value);

/// Gets the value of the given attribute as a uchar array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param time_code The time at which to sample the attribute. If no value is authored at this time,
///                  returns an interpolated value based on neighboring time samples. Use NUSD_TIMECODE_DEFAULT
///                  for the default time.
/// @param uchar_array Pointer to store the uchar array handle.

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uchar array type
/// 
/// @note The returned uchar array must be released with nusd_uchar_array_destroy() when no longer needed.
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note uchar_array must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_get_uchar_array(nusd_stage_t stage, char const* attribute_path, double time_code, nusd_uchar_array_t* uchar_array);

// uint setters
/// Sets the value of the given attribute to an unsigned int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Unsigned int value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_uint(nusd_stage_t stage, char const* attribute_path, unsigned int value, double time_code);

/// Sets the value of the given attribute to a uint array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the uint data to set.
/// @param num_elements Number of uint elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_uint_array(nusd_stage_t stage, char const* attribute_path, unsigned int* data, size_t num_elements, double time_code);

// uint64 setters
/// Sets the value of the given attribute to an unsigned 64-bit int, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Uint64 value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint64 type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_uint64(nusd_stage_t stage, char const* attribute_path, uint64_t value, double time_code);

/// Sets the value of the given attribute to a uint64 array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the uint64 data to set.
/// @param num_elements Number of uint64 elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uint64 array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_uint64_array(nusd_stage_t stage, char const* attribute_path, uint64_t* data, size_t num_elements, double time_code);

// uchar setters
/// Sets the value of the given attribute to an unsigned char, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param value Unsigned char value to set.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uchar type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
NANOUSD_API
nusd_result_t nusd_attribute_set_uchar(nusd_stage_t stage, char const* attribute_path, unsigned char value, double time_code);

/// Sets the value of the given attribute to a uchar array, if the attribute is of that type.
/// 
/// @param stage Valid stage handle.
/// @param attribute_path USD path to the attribute.
/// @param data Pointer to the uchar data to set.
/// @param num_elements Number of uchar elements in the data array.
/// @param time_code The time at which to set the attribute value. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set even on uniform attributes.
/// 

/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_ATTRIBUTE_PATH if no attribute exists at the specified path
/// @return NUSD_RESULT_WRONG_TYPE if the attribute is not of uchar array type
/// 
/// @note stage must not be null.
/// @note attribute_path must not be null.
/// @note data must not be null.
/// @note num_elements must be greater than 0.
NANOUSD_API
nusd_result_t nusd_attribute_set_uchar_array(nusd_stage_t stage, char const* attribute_path, unsigned char* data, size_t num_elements, double time_code);

/// Gets an iterator for the target paths of a relationship.
/// 
/// @param stage Valid stage handle.
/// @param relationship_path USD path to the relationship.
/// @param targets Output pointer that will contain the targets iterator handle on success.
/// @param num_targets Optional output pointer that will contain the number of targets (can be null).
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_RELATIONSHIP_PATH if no relationship exists at the specified path
/// 
/// @note The returned iterator must be released with nusd_relationship_targets_iterator_destroy() when no longer needed.
/// @note stage must not be null.
/// @note relationship_path must not be null.
/// @note targets must not be null.
NANOUSD_API
nusd_result_t nusd_relationship_get_targets(nusd_stage_t stage, char const* relationship_path, nusd_relationship_targets_iterator_t* targets, size_t* num_targets);



#ifdef __cplusplus
}
#endif

#endif
