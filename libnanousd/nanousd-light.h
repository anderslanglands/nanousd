#ifndef NANOUSD_LIGHT_H
#define NANOUSD_LIGHT_H

#include "nanousd-array.h"
#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup LightFunctions Light Functions
///
/// @brief Functions for creating and manipulating lights
///
/// @{

/// Defines a new USD rectangular light prim at the specified path with light parameters.
///
/// @param stage Valid stage handle.
/// @param light_path USD path where the rectangular light should be created (e.g., 
/// "/World/Lights/MyRectLight").
/// @param width Width of the rectangular light in scene units.
/// @param height Height of the rectangular light in scene units.
/// @param intensity Intensity of the light (brightness multiplier).
/// @param color Array of 3 float values representing the light color as RGB components 
/// (range 0.0 to 1.0).
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage, light_path, or color is null
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the light cannot be defined at the 
/// specified path
///
/// @note stage must not be null.
/// @note light_path must not be null and should be a valid USD prim path.
/// @note color must not be null and should contain exactly 3 float values for RGB.
/// @note Creates a UsdLuxRectLight prim with the specified dimensions, intensity, and color.
/// @note width and height define the physical size of the light emitter in scene units.
/// @note intensity controls the brightness of the light (1.0 is normal intensity).
/// @note color components should typically be in the range [0.0, 1.0] for normalized RGB.
/// @note The light emits from a rectangular area, providing soft shadows and realistic 
/// area lighting.
NANOUSD_API
nusd_result_t nusd_rect_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     float width,
                                     float height,
                                     float intensity,
                                     float* color);

/// Defines a new USD disk light prim at the specified path with light parameters.
///
/// @param stage Valid stage handle.
/// @param light_path USD path where the disk light should be created (e.g., 
/// "/World/Lights/MyDiskLight").
/// @param radius Radius of the disk light in scene units.
/// @param intensity Intensity of the light (brightness multiplier).
/// @param color Array of 3 float values representing the light color as RGB components 
/// (range 0.0 to 1.0).
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage, light_path, or color is null
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the light cannot be defined at the 
/// specified path
///
/// @note stage must not be null.
/// @note light_path must not be null and should be a valid USD prim path.
/// @note color must not be null and should contain exactly 3 float values for RGB.
/// @note Creates a UsdLuxDiskLight prim with the specified radius, intensity, and color.
/// @note radius defines the size of the circular light emitter in scene units.
/// @note intensity controls the brightness of the light (1.0 is normal intensity).
/// @note color components should typically be in the range [0.0, 1.0] for normalized RGB.
/// @note The light emits from a circular disk area, providing soft shadows and realistic 
/// area lighting with circular falloff.
NANOUSD_API
nusd_result_t nusd_disk_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     float radius,
                                     float intensity,
                                     float* color);

/// Defines a new USD sphere light prim at the specified path with light parameters.
///
/// @param stage Valid stage handle.
/// @param light_path USD path where the sphere light should be created (e.g., 
/// "/World/Lights/MySphereLight").
/// @param radius Radius of the sphere light in scene units.
/// @param intensity Intensity of the light (brightness multiplier).
/// @param color Array of 3 float values representing the light color as RGB components 
/// (range 0.0 to 1.0).
///
/// @return NUSD_RESULT_OK on success
/// @return NUSD_RESULT_NULL_PARAMETER if stage, light_path, or color is null
/// @return NUSD_RESULT_DEFINE_PRIM_FAILED if the light cannot be defined at the 
/// specified path
///
/// @note stage must not be null.
/// @note light_path must not be null and should be a valid USD prim path.
/// @note color must not be null and should contain exactly 3 float values for RGB.
/// @note Creates a UsdLuxSphereLight prim with the specified radius, intensity, and color.
/// @note radius defines the size of the spherical light emitter in scene units.
/// @note intensity controls the brightness of the light (1.0 is normal intensity).
/// @note color components should typically be in the range [0.0, 1.0] for normalized RGB.
/// @note The light emits from a spherical volume, providing omnidirectional soft shadows 
/// and realistic volumetric area lighting.
NANOUSD_API
nusd_result_t nusd_sphere_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     float radius,
                                     float intensity,
                                     float* color);

/// @}

#ifdef __cplusplus
}
#endif

#endif
