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
                                     float const* color);

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
                                     float const* color);

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
                                     float const* color);

/// Defines a new USD dome light prim at the specified path with environment lighting parameters.
///
/// @param stage Valid stage handle.
/// @param light_path USD path where the dome light should be created (e.g., 
/// "/World/Lights/MyDomeLight").
/// @param texture_file Optional path to an HDRI texture file for environment lighting. 
/// Can be null for procedural dome lighting.
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
/// @note texture_file can be null for procedural dome lighting, or a valid file path 
/// to an HDRI environment map.
/// @note color must not be null and should contain exactly 3 float values for RGB.
/// @note Creates a UsdLuxDomeLight prim with the specified texture, intensity, and color.
/// @note intensity controls the brightness of the environment lighting (1.0 is normal intensity).
/// @note color components should typically be in the range [0.0, 1.0] for normalized RGB.
/// @note Dome lights provide infinite-distance environment lighting that illuminates the 
/// entire scene from all directions, commonly used for IBL (Image-Based Lighting).
/// @note When texture_file is provided, it should be an HDRI (.exr, .hdr) file for 
/// realistic environment lighting.
/// @note The dome light creates ambient lighting that affects all objects in the scene 
/// and provides realistic reflections and global illumination.
NANOUSD_API
nusd_result_t nusd_dome_light_define(nusd_stage_t stage,
                                     char const* light_path,
                                     char const* texture_file,
                                     float intensity,
                                     float const* color);
/// @}

#ifdef __cplusplus
}
#endif

#endif
