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

TEST(nusd, set_int_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_int(stage, "/World.testattr", 42);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value = 0;
    result = nusd_attribute_get_int(stage, "/World.testattr", &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 42);
}

TEST(nusd, set_int_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INTARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_data[] = {1, 2, 3, 4, 5};
    result = nusd_attribute_set_int_array(stage, "/World.testattr", test_data, 5);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int_array_t int_array;
    result = nusd_attribute_get_int_array(stage, "/World.testattr", &int_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_int_array_size(int_array);
    EXPECT_EQ(size, 5);

    int* data = nusd_int_array_data(int_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_int_array_destroy(int_array);
}

TEST(nusd, set_int2_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT2);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_value[] = {10, 20};
    result = nusd_attribute_set_int2(stage, "/World.testattr", test_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value[2] = {0, 0};
    result = nusd_attribute_get_int2(stage, "/World.testattr", value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value[0], 10);
    EXPECT_EQ(value[1], 20);
}

TEST(nusd, set_int2_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT2ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_data[] = {1, 2, 3, 4, 5, 6};  // 3 int2 values
    result = nusd_attribute_set_int2_array(stage, "/World.testattr", test_data, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int2_array_t int2_array;
    result = nusd_attribute_get_int2_array(stage, "/World.testattr", &int2_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_int2_array_size(int2_array);
    EXPECT_EQ(size, 3);

    int* data = nusd_int2_array_data(int2_array);
    for (size_t i = 0; i < size * 2; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_int2_array_destroy(int2_array);
}

TEST(nusd, set_int3_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_value[] = {100, 200, 300};
    result = nusd_attribute_set_int3(stage, "/World.testattr", test_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value[3] = {0, 0, 0};
    result = nusd_attribute_get_int3(stage, "/World.testattr", value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value[0], 100);
    EXPECT_EQ(value[1], 200);
    EXPECT_EQ(value[2], 300);
}

TEST(nusd, set_int3_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT3ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // 3 int3 values
    result = nusd_attribute_set_int3_array(stage, "/World.testattr", test_data, 3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int3_array_t int3_array;
    result = nusd_attribute_get_int3_array(stage, "/World.testattr", &int3_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_int3_array_size(int3_array);
    EXPECT_EQ(size, 3);

    int* data = nusd_int3_array_data(int3_array);
    for (size_t i = 0; i < size * 3; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_int3_array_destroy(int3_array);
}

TEST(nusd, set_int4_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT4);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_value[] = {1000, 2000, 3000, 4000};
    result = nusd_attribute_set_int4(stage, "/World.testattr", test_value);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value[4] = {0, 0, 0, 0};
    result = nusd_attribute_get_int4(stage, "/World.testattr", value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value[0], 1000);
    EXPECT_EQ(value[1], 2000);
    EXPECT_EQ(value[2], 3000);
    EXPECT_EQ(value[3], 4000);
}

TEST(nusd, set_int4_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT4ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int test_data[] = {1, 2, 3, 4, 5, 6, 7, 8};  // 2 int4 values
    result = nusd_attribute_set_int4_array(stage, "/World.testattr", test_data, 2);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int4_array_t int4_array;
    result = nusd_attribute_get_int4_array(stage, "/World.testattr", &int4_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_int4_array_size(int4_array);
    EXPECT_EQ(size, 2);

    int* data = nusd_int4_array_data(int4_array);
    for (size_t i = 0; i < size * 4; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_int4_array_destroy(int4_array);
}
