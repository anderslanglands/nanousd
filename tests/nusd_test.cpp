#include <gtest/gtest.h>
#include <nanousd.h>
#include <nanousd-cameras.h>
#include <nanousd-materials.h>
#include <cmath>
#include <iostream>

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

    result = nusd_attribute_set_float(stage, "/World.testattr", 1.0f, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    float value = 0.0f;
    result = nusd_attribute_get_float(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 1.0f);
}

TEST(nusd, set_float2_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_FLOAT2ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    float test_data[] = {1, 2, 3, 4, 5, 6};  // 3 float2 values
    result = nusd_attribute_set_float2_array(stage, "/World.testattr", test_data, 3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_float2_array_t float2_array;
    result = nusd_attribute_get_float2_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &float2_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_float2_array_size(float2_array);
    EXPECT_EQ(size, 3);

    float* data = nusd_float2_array_data(float2_array);
    for (size_t i = 0; i < size * 2; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_float2_array_destroy(float2_array);
}


TEST(nusd, set_int_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_int(stage, "/World.testattr", 42, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value = 0;
    result = nusd_attribute_get_int(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
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
    result = nusd_attribute_set_int_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int_array_t int_array;
    result = nusd_attribute_get_int_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &int_array);
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
    result = nusd_attribute_set_int2(stage, "/World.testattr", test_value, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value[2] = {0, 0};
    result = nusd_attribute_get_int2(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
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
    result = nusd_attribute_set_int2_array(stage, "/World.testattr", test_data, 3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int2_array_t int2_array;
    result = nusd_attribute_get_int2_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &int2_array);
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
    result = nusd_attribute_set_int3(stage, "/World.testattr", test_value, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value[3] = {0, 0, 0};
    result = nusd_attribute_get_int3(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
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
    result = nusd_attribute_set_int3_array(stage, "/World.testattr", test_data, 3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int3_array_t int3_array;
    result = nusd_attribute_get_int3_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &int3_array);
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
    result = nusd_attribute_set_int4(stage, "/World.testattr", test_value, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int value[4] = {0, 0, 0, 0};
    result = nusd_attribute_get_int4(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
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
    result = nusd_attribute_set_int4_array(stage, "/World.testattr", test_data, 2, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int4_array_t int4_array;
    result = nusd_attribute_get_int4_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &int4_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_int4_array_size(int4_array);
    EXPECT_EQ(size, 2);

    int* data = nusd_int4_array_data(int4_array);
    for (size_t i = 0; i < size * 4; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_int4_array_destroy(int4_array);
}

TEST(nusd, set_int64_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT64);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_int64(stage, "/World.testattr", 9223372036854775807LL, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int64_t value = 0;
    result = nusd_attribute_get_int64(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST(nusd, set_int64_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_INT64ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    int64_t test_data[] = {1000000000000LL, 2000000000000LL, 3000000000000LL, 4000000000000LL, 5000000000000LL};
    result = nusd_attribute_set_int64_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_int64_array_t int64_array;
    result = nusd_attribute_get_int64_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &int64_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_int64_array_size(int64_array);
    EXPECT_EQ(size, 5);

    int64_t* data = nusd_int64_array_data(int64_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_int64_array_destroy(int64_array);
}

TEST(nusd, set_double_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_double(stage, "/World.testattr", 3.14159, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value = 0.0;
    result = nusd_attribute_get_double(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(value, 3.14159);
}

TEST(nusd, set_double_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLEARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    result = nusd_attribute_set_double_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_double_array_t double_array;
    result = nusd_attribute_get_double_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &double_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_double_array_size(double_array);
    EXPECT_EQ(size, 5);

    double* data = nusd_double_array_data(double_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_double_array_destroy(double_array);
}

TEST(nusd, set_double2_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE2);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_value[] = {1.1, 2.2};
    result = nusd_attribute_set_double2(stage, "/World.testattr", test_value, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value[2] = {0.0, 0.0};
    result = nusd_attribute_get_double2(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(value[0], 1.1);
    EXPECT_DOUBLE_EQ(value[1], 2.2);
}

TEST(nusd, set_double2_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE2ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};  // 3 double2 values
    result = nusd_attribute_set_double2_array(stage, "/World.testattr", test_data, 3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_double2_array_t double2_array;
    result = nusd_attribute_get_double2_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &double2_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_double2_array_size(double2_array);
    EXPECT_EQ(size, 3);

    double* data = nusd_double2_array_data(double2_array);
    for (size_t i = 0; i < size * 2; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_double2_array_destroy(double2_array);
}

TEST(nusd, set_double3_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE3);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_value[] = {1.1, 2.2, 3.3};
    result = nusd_attribute_set_double3(stage, "/World.testattr", test_value, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value[3] = {0.0, 0.0, 0.0};
    result = nusd_attribute_get_double3(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(value[0], 1.1);
    EXPECT_DOUBLE_EQ(value[1], 2.2);
    EXPECT_DOUBLE_EQ(value[2], 3.3);
}

TEST(nusd, set_double3_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE3ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};  // 3 double3 values
    result = nusd_attribute_set_double3_array(stage, "/World.testattr", test_data, 3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_double3_array_t double3_array;
    result = nusd_attribute_get_double3_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &double3_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_double3_array_size(double3_array);
    EXPECT_EQ(size, 3);

    double* data = nusd_double3_array_data(double3_array);
    for (size_t i = 0; i < size * 3; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_double3_array_destroy(double3_array);
}

TEST(nusd, set_double4_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE4);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_value[] = {1.1, 2.2, 3.3, 4.4};
    result = nusd_attribute_set_double4(stage, "/World.testattr", test_value, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value[4] = {0.0, 0.0, 0.0, 0.0};
    result = nusd_attribute_get_double4(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_DOUBLE_EQ(value[0], 1.1);
    EXPECT_DOUBLE_EQ(value[1], 2.2);
    EXPECT_DOUBLE_EQ(value[2], 3.3);
    EXPECT_DOUBLE_EQ(value[3], 4.4);
}

TEST(nusd, set_double4_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_DOUBLE4ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8};  // 2 double4 values
    result = nusd_attribute_set_double4_array(stage, "/World.testattr", test_data, 2, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_double4_array_t double4_array;
    result = nusd_attribute_get_double4_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &double4_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_double4_array_size(double4_array);
    EXPECT_EQ(size, 2);

    double* data = nusd_double4_array_data(double4_array);
    for (size_t i = 0; i < size * 4; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_double4_array_destroy(double4_array);
}

TEST(nusd, set_bool_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_BOOL);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_bool(stage, "/World.testattr", true, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    bool value = false;
    result = nusd_attribute_get_bool(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, true);
}

TEST(nusd, set_bool_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_BOOLARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    bool test_data[] = {true, false, true, false, true};
    result = nusd_attribute_set_bool_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_bool_array_t bool_array;
    result = nusd_attribute_get_bool_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &bool_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_bool_array_size(bool_array);
    EXPECT_EQ(size, 5);

    bool* data = nusd_bool_array_data(bool_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }

    nusd_bool_array_destroy(bool_array);
}

TEST(nusd, set_matrix2d_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_MATRIX2D);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_matrix[4] = {1.0, 2.0, 3.0, 4.0};
    result = nusd_attribute_set_matrix2d(stage, "/World.testattr", test_matrix, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value[4] = {0.0, 0.0, 0.0, 0.0};
    result = nusd_attribute_get_matrix2d(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    for (int i = 0; i < 4; i++) {
        EXPECT_DOUBLE_EQ(value[i], test_matrix[i]);
    }
}

TEST(nusd, set_matrix2d_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_MATRIX2DARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};  // 2 matrix2d values
    result = nusd_attribute_set_matrix2d_array(stage, "/World.testattr", test_data, 2, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_matrix2d_array_t matrix2d_array;
    result = nusd_attribute_get_matrix2d_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &matrix2d_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_matrix2d_array_size(matrix2d_array);
    EXPECT_EQ(size, 2);

    double* data = nusd_matrix2d_array_data(matrix2d_array);
    for (size_t i = 0; i < size * 4; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_matrix2d_array_destroy(matrix2d_array);
}

TEST(nusd, set_matrix3d_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_MATRIX3D);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_matrix[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    result = nusd_attribute_set_matrix3d(stage, "/World.testattr", test_matrix, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    result = nusd_attribute_get_matrix3d(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    for (int i = 0; i < 9; i++) {
        EXPECT_DOUBLE_EQ(value[i], test_matrix[i]);
    }
}

TEST(nusd, set_matrix3d_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_MATRIX3DARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[18] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0};  // 2 matrix3d values
    result = nusd_attribute_set_matrix3d_array(stage, "/World.testattr", test_data, 2, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_matrix3d_array_t matrix3d_array;
    result = nusd_attribute_get_matrix3d_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &matrix3d_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_matrix3d_array_size(matrix3d_array);
    EXPECT_EQ(size, 2);

    double* data = nusd_matrix3d_array_data(matrix3d_array);
    for (size_t i = 0; i < size * 9; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_matrix3d_array_destroy(matrix3d_array);
}

TEST(nusd, set_matrix4d_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_MATRIX4D);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_matrix[16] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
    result = nusd_attribute_set_matrix4d(stage, "/World.testattr", test_matrix, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double value[16] = {0.0};
    result = nusd_attribute_get_matrix4d(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    for (int i = 0; i < 16; i++) {
        EXPECT_DOUBLE_EQ(value[i], test_matrix[i]);
    }
}

TEST(nusd, set_matrix4d_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_MATRIX4DARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    double test_data[32];  // 2 matrix4d values
    for (int i = 0; i < 32; i++) {
        test_data[i] = i + 1.0;
    }
    result = nusd_attribute_set_matrix4d_array(stage, "/World.testattr", test_data, 2, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_matrix4d_array_t matrix4d_array;
    result = nusd_attribute_get_matrix4d_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &matrix4d_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_matrix4d_array_size(matrix4d_array);
    EXPECT_EQ(size, 2);

    double* data = nusd_matrix4d_array_data(matrix4d_array);
    for (size_t i = 0; i < size * 16; i++) {
        EXPECT_DOUBLE_EQ(data[i], test_data[i]);
    }

    nusd_matrix4d_array_destroy(matrix4d_array);
}

TEST(nusd, set_uint_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_UINT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    result = nusd_attribute_set_uint(stage, "/World.testattr", 42U, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    unsigned int value = 0;
    result = nusd_attribute_get_uint(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 42U);
}

TEST(nusd, set_uint_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_UINTARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    unsigned int test_data[] = {1U, 2U, 3U, 4U, 5U};
    result = nusd_attribute_set_uint_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    nusd_uint_array_t uint_array;
    result = nusd_attribute_get_uint_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &uint_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    size_t size = nusd_uint_array_size(uint_array);
    EXPECT_EQ(size, 5);
    
    unsigned int* data = nusd_uint_array_data(uint_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }
    
    nusd_uint_array_destroy(uint_array);
}

TEST(nusd, set_uint64_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_UINT64);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    result = nusd_attribute_set_uint64(stage, "/World.testattr", 18446744073709551615ULL, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    uint64_t value = 0;
    result = nusd_attribute_get_uint64(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST(nusd, set_uint64_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_UINT64ARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    uint64_t test_data[] = {1000000000000ULL, 2000000000000ULL, 3000000000000ULL, 4000000000000ULL, 5000000000000ULL};
    result = nusd_attribute_set_uint64_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    nusd_uint64_array_t uint64_array;
    result = nusd_attribute_get_uint64_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &uint64_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    size_t size = nusd_uint64_array_size(uint64_array);
    EXPECT_EQ(size, 5);
    
    uint64_t* data = nusd_uint64_array_data(uint64_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }
    
    nusd_uint64_array_destroy(uint64_array);
}

TEST(nusd, set_uchar_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_UCHAR);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    result = nusd_attribute_set_uchar(stage, "/World.testattr", 255, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    unsigned char value = 0;
    result = nusd_attribute_get_uchar(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &value);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(value, 255);
}

TEST(nusd, set_uchar_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);
    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_UCHARARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    unsigned char test_data[] = {100, 150, 200, 255, 50};
    result = nusd_attribute_set_uchar_array(stage, "/World.testattr", test_data, 5, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    nusd_uchar_array_t uchar_array;
    result = nusd_attribute_get_uchar_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &uchar_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    size_t size = nusd_uchar_array_size(uchar_array);
    EXPECT_EQ(size, 5);
    
    unsigned char* data = nusd_uchar_array_data(uchar_array);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(data[i], test_data[i]);
    }
    
    nusd_uchar_array_destroy(uchar_array);
}

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

TEST(nusd, prim_set_transform) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-prim_set_transform", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a camera
    result = nusd_camera_define(stage, "/World/Camera");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Set up a test transformation matrix (camera looking down negative Z with some translation)
    double local_to_parent_matrix[16] = {
        1.0, 0.0, 0.0, 0.0,  // X axis (right)
        0.0, 1.0, 0.0, 0.0,  // Y axis (up)
        0.0, 0.0, 1.0, 0.0,  // Z axis (forward)
        5.0, 3.0, 10.0, 1.0  // Translation (position)
    };
    
    // Set the camera transform
    result = nusd_prim_set_transform(stage, "/World/Camera", local_to_parent_matrix, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Use nusd_prim_compute_local_to_world_transform to verify the resulting world transform
    double world_transform[16];
    result = nusd_prim_compute_local_to_world_transform(stage, "/World/Camera", NUSD_TIMECODE_DEFAULT, world_transform);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Since camera is a direct child of World and World has identity transform,
    // the world transform should match our local_to_parent_matrix
    for (int i = 0; i < 16; i++) {
        EXPECT_DOUBLE_EQ(world_transform[i], local_to_parent_matrix[i]);
    }
    
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

TEST(nusd, material_define) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-material_define", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material at the specified path
    result = nusd_material_define(stage, "/World/Materials/MyMaterial");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify the material was created as a valid prim
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Materials/MyMaterial"), true);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_define) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_define", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a shader with UsdPreviewSurface identifier
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Verify the shader was created as a valid prim
    EXPECT_EQ(nusd_stage_path_is_valid_prim(stage, "/World/Materials/Mat/Surface"), true);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_create_input) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_create_input", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a shader first
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create a diffuseColor input of type COLOR3F
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "diffuseColor", NUSD_TYPE_COLOR3F);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create a roughness input of type FLOAT
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "roughness", NUSD_TYPE_FLOAT);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_create_output) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_create_output", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a shader first
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create a surface output of type TOKEN
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Surface", "surface", NUSD_TYPE_TOKEN);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a texture shader
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create an rgb output of type COLOR3F
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Texture", "rgb", NUSD_TYPE_COLOR3F);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, shader_connect) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test-shader_connect", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Define a material and two shaders
    result = nusd_material_define(stage, "/World/Materials/Mat");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Surface", "UsdPreviewSurface");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_define(stage, "/World/Materials/Mat/Texture", "UsdUVTexture");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Create inputs and outputs
    result = nusd_shader_create_input(stage, "/World/Materials/Mat/Surface", "diffuseColor", NUSD_TYPE_COLOR3F);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    result = nusd_shader_create_output(stage, "/World/Materials/Mat/Texture", "rgb", NUSD_TYPE_COLOR3F);
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    // Connect the texture output to the surface input
    result = nusd_shader_connect(stage, 
                                "/World/Materials/Mat/Texture.outputs:rgb", 
                                "/World/Materials/Mat/Surface.inputs:diffuseColor");
    EXPECT_EQ(result, NUSD_RESULT_OK);
    
    nusd_stage_destroy(stage);
}

TEST(nusd, set_asset_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_ASSET);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    result = nusd_attribute_set_asset(stage, "/World.testattr", "texture.jpg", NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_asset_path_t asset_path;
    result = nusd_attribute_get_asset(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &asset_path);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    char const* path_string = nusd_asset_path_get_asset_path(asset_path);
    EXPECT_STREQ(path_string, "texture.jpg");

    nusd_asset_path_destroy(asset_path);
    nusd_stage_destroy(stage);
}

TEST(nusd, set_asset_array_attribute) {
    nusd_stage_t stage;
    nusd_result_t result = nusd_stage_create_in_memory("test", &stage);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    EXPECT_EQ(nusd_stage_define_prim(stage, "/World", "Xform"), NUSD_RESULT_OK);

    result = nusd_prim_create_property(stage, "/World", "testattr", NUSD_TYPE_ASSETARRAY);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    char const* test_data[] = {"texture1.jpg", "texture2.png", "model.usd"};
    result = nusd_attribute_set_asset_array(stage, "/World.testattr", test_data, 3, NUSD_TIMECODE_DEFAULT);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    nusd_asset_path_array_iterator_t asset_array;
    result = nusd_attribute_get_asset_array(stage, "/World.testattr", NUSD_TIMECODE_DEFAULT, &asset_array);
    EXPECT_EQ(result, NUSD_RESULT_OK);

    size_t size = nusd_asset_path_array_iterator_size(asset_array);
    EXPECT_EQ(size, 3);

    // Test iteration through the array
    char const* asset_path;
    bool has_next;
    
    has_next = nusd_asset_path_array_iterator_next(asset_array, &asset_path);
    EXPECT_TRUE(has_next);
    EXPECT_STREQ(asset_path, "texture1.jpg");
    
    has_next = nusd_asset_path_array_iterator_next(asset_array, &asset_path);
    EXPECT_TRUE(has_next);
    EXPECT_STREQ(asset_path, "texture2.png");
    
    has_next = nusd_asset_path_array_iterator_next(asset_array, &asset_path);
    EXPECT_TRUE(has_next);
    EXPECT_STREQ(asset_path, "model.usd");
    
    has_next = nusd_asset_path_array_iterator_next(asset_array, &asset_path);
    EXPECT_FALSE(has_next);  // Should be end of array

    nusd_asset_path_array_iterator_destroy(asset_array);
    nusd_stage_destroy(stage);
}
