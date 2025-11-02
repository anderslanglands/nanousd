#include <gtest/gtest.h>

#include <nanousd.h>
#include <nanousd-camera.h>
#include <nanousd-material.h>
#include <nanousd-mesh.h>
#include <nanousd-light.h>

#include <cmath>

TEST(nusd, create_stage) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_stage", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
}
