#include <gtest/gtest.h>

#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>

#include <cmath>


TEST(nusd, camera_define) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-camera_define", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera at the specified path
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify the camera was created as a valid prim
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Camera"), true);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, camera_set_fov_w) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-camera_set_fov_w", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // First, read the default horizontal aperture to understand what the camera uses
    float horizontal_aperture;
    result = nusd_attribute_get_float(stage, "/World/Camera.horizontalAperture", NUSD_TIMECODE_DEFAULT, &horizontal_aperture);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    // Set horizontal field of view to 60 degrees
    float test_fov = 60.0f;
    result = nusd_camera_set_fov_w(stage, "/World/Camera", test_fov, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify by reading the focalLength attribute that was set
    // According to the documentation, this function sets the focalLength attribute
    float focal_length;
    result = nusd_attribute_get_float(stage, "/World/Camera.focalLength", NUSD_TIMECODE_DEFAULT, &focal_length);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // The focal length should be calculated from FOV and the actual horizontal aperture
    // focal_length = aperture / (2 * tan(fov/2))
    float expected_focal_length = horizontal_aperture / (2.0f * tanf((test_fov * M_PI / 180.0f) / 2.0f));
    EXPECT_NEAR(focal_length, expected_focal_length, 0.01f);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, camera_set_exposure) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-camera_set_exposure", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Set exposure parameters
    float iso = 400.0f;
    float time = 1.0f / 60.0f;  // 1/60 second
    float f_stop = 2.8f;
    float compensation = 0.5f;
    float responsivity = 1.0f;
    
    result = nusd_camera_set_exposure(stage, "/World/Camera", iso, time, f_stop, compensation, responsivity, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify each exposure attribute was set correctly according to the documentation
    
    // Check exposure:iso
    float read_iso;
    result = nusd_attribute_get_float(stage, "/World/Camera.exposure:iso", NUSD_TIMECODE_DEFAULT, &read_iso);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_iso, iso);
    
    // Check exposure:time  
    float read_time;
    result = nusd_attribute_get_float(stage, "/World/Camera.exposure:time", NUSD_TIMECODE_DEFAULT, &read_time);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_time, time);
    
    // Check exposure:fStop
    float read_f_stop;
    result = nusd_attribute_get_float(stage, "/World/Camera.exposure:fStop", NUSD_TIMECODE_DEFAULT, &read_f_stop);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_f_stop, f_stop);
    
    // Check exposure (compensation)
    float read_compensation;
    result = nusd_attribute_get_float(stage, "/World/Camera.exposure", NUSD_TIMECODE_DEFAULT, &read_compensation);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_compensation, compensation);
    
    // Check exposure:responsivity
    float read_responsivity;
    result = nusd_attribute_get_float(stage, "/World/Camera.exposure:responsivity", NUSD_TIMECODE_DEFAULT, &read_responsivity);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_responsivity, responsivity);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, camera_set_clipping_range) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-camera_set_clipping_range", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Set clipping range
    float near = 0.1f;
    float far = 1000.0f;
    
    result = nusd_camera_set_clipping_range(stage, "/World/Camera", near, far, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify by reading the clippingRange attribute (float2)
    // According to the documentation, this sets the float2 clippingRange attribute
    float clipping_range[2];
    result = nusd_attribute_get_float2(stage, "/World/Camera.clippingRange", NUSD_TIMECODE_DEFAULT, clipping_range);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // First element should be near, second element should be far
    EXPECT_FLOAT_EQ(clipping_range[0], near);
    EXPECT_FLOAT_EQ(clipping_range[1], far);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, camera_set_aperture) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-camera_set_aperture", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Set aperture dimensions (e.g., 35mm full frame: 36x24 in tenths of scene units)
    float width = 36.0f;   // horizontal aperture
    float height = 24.0f;  // vertical aperture
    
    result = nusd_camera_set_aperture(stage, "/World/Camera", width, height, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify by reading the horizontalAperture and verticalAperture attributes
    float read_width;
    result = nusd_attribute_get_float(stage, "/World/Camera.horizontalAperture", NUSD_TIMECODE_DEFAULT, &read_width);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_width, width);
    
    float read_height;
    result = nusd_attribute_get_float(stage, "/World/Camera.verticalAperture", NUSD_TIMECODE_DEFAULT, &read_height);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_FLOAT_EQ(read_height, height);
    
    nusd_stage_destroy(stage);
}
