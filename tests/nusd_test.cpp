#include <gtest/gtest.h>
#include <nanousd.h>

TEST(nusd, create_stage) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_stage", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
}

TEST(nusd, define_prim) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
}

TEST(nusd, define_prim_and_check_valid) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);
}

TEST(nusd, invalid_prim_path_fails_validity_check) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-create_prim", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/Worldx"), false);
}

TEST(nusd, create_properties) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
}


TEST(nusd, set_float_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World"), true);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_FLOAT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_float(stage, "/World.testattr", 1.0f);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    float value = 0.0f;
    result = nusd_attribute_get_float(stage, "/World.testattr", &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 1.0f);
}
