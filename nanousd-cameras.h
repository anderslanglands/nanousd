#ifndef NANOUSD_CAMERAS_H
#define NANOUSD_CAMERAS_H

#include "nanousd-types.h"
#include "nanousd-arrays.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @defgroup CameraFunctions Camera Functions
/// 
/// @brief Functions related to managing cameras
///
/// @{

/// Defines a new USD camera prim at the specified path.
/// 
/// @param stage Valid stage handle.
/// @param camera_path USD path where the camera should be created (e.g., "/World/Camera").
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the camera cannot be defined at the specified path
/// 
/// @note stage must not be null.
/// @note camera_path must not be null and should be a valid USD prim path.
/// @note Creates a UsdGeomCamera prim with default camera properties.
/// @note The camera follows USD's "Y up" coordinate system regardless of the stage's orientation.
NANOUSD_API
nusd_result_t nusd_camera_define(nusd_stage_t stage, char const* camera_path);

/// Sets the horizontal field of view for a camera by setting its focal length (`float focalLength`).
/// 
/// @param stage Valid stage handle.
/// @param camera_path USD path to an existing camera prim.
/// @param fov_w_deg Horizontal field of view in degrees.
/// @param time_code The time at which to set the field of view. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set for animation.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no camera exists at the specified path
/// 
/// @note stage must not be null.
/// @note camera_path must not be null and should point to an existing camera prim.
/// @note fov_w_deg should be a positive value representing the horizontal field of view in degrees.
/// @note This function calculates the focal length based on the camera's horizontal aperture and the specified FOV.
/// @note The focal length is computed using: focal_length = aperture / (2 * tan(fov/2)).
NANOUSD_API
nusd_result_t nusd_camera_set_fov_w(nusd_stage_t stage, char const* camera_path, float fov_w_deg, double time_code);

/// Sets the exposure parameters for a camera, simulating real camera controls.
/// 
/// @param stage Valid stage handle.
/// @param camera_path USD path to an existing camera prim.
/// @param iso ISO sensitivity value (e.g., 100, 400, 800, 1600). This sets `float exposure:iso`.
/// @param time Exposure time in seconds (e.g., 1/60 = 0.0167 for 60fps). This sets `float exposure:time`.
/// @param f_stop F-stop value controlling depth of field (e.g., 1.4, 2.8, 5.6, 11). This sets `float exposure:fStop`.
/// @param compensation Exposure compensation in stops (positive brightens, negative darkens). This sets `float exposure`.
/// @param responsivity Camera sensor responsivity factor. This sets `float exposure:responsivity`.
/// @param time_code The time at which to set the exposure parameters. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set for animation.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no camera exists at the specified path
/// 
/// @note stage must not be null.
/// @note camera_path must not be null and should point to an existing camera prim.
/// @note These parameters mimic real camera exposure controls for physically-based rendering.
/// @note iso should be a positive value representing sensor sensitivity.
/// @note time should be a positive value representing exposure duration in seconds.
/// @note f_stop should be a positive value, with lower values creating shallower depth of field.
/// @note compensation adjusts overall exposure in photographic stops (1 stop = 2x brightness change).
NANOUSD_API
nusd_result_t nusd_camera_set_exposure(nusd_stage_t stage, char const* camera_path, float iso, float time, float f_stop, float compensation, float responsivity, double time_code);

/// Sets the near and far clipping distances for a camera's viewing frustum.
/// 
/// @param stage Valid stage handle.
/// @param camera_path USD path to an existing camera prim.
/// @param near Near clipping distance in scene units. Objects closer than this distance will be clipped. This sets the first element of `float2 clippingRange`.
/// @param far Far clipping distance in scene units. Objects farther than this distance will be clipped. This sets the second element of `float2 clippingRange`.
/// @param time_code The time at which to set the clipping range. Use NUSD_TIMECODE_DEFAULT 
///                  for the default time. Time samples can be set for animation.
/// 
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_INVALID_PRIM_PATH if no camera exists at the specified path
/// 
/// @note stage must not be null.
/// @note camera_path must not be null and should point to an existing camera prim.
/// @note near should be a small positive value (e.g., 0.1) to avoid Z-fighting issues.
/// @note far should be greater than near and represent the maximum visible distance.
/// @note Values are in scene units as defined by the stage's metersPerUnit setting.
/// @note Proper clipping range setup is crucial for depth buffer precision and rendering performance.
NANOUSD_API
nusd_result_t nusd_camera_set_clipping_range(nusd_stage_t stage, char const* camera_path, float near, float far, double time_code);

/// @}


#ifdef __cplusplus
}
#endif

#endif
