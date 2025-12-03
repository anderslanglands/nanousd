#include "nanousd.h"

#include <algorithm>
#include <stdio.h>

#include <pxr/usd/sdf/types.h>

void print_property(nusd_stage_t stage, char const* property_path, nusd_type_t property_type);

int main() {
    nusd_stage_t stage;
    nusd_stage_open("test01.usda", &stage);

    nusd_prim_iterator_t it;
    nusd_stage_traverse(stage, &it);

    char const* prim_path;
    while (nusd_prim_iterator_next(it, &prim_path)) {
        printf("%s\n", prim_path);

        char const* property_path;
        nusd_property_iterator_t it_prop;
        nusd_type_t property_type;
        nusd_prim_get_properties(stage, prim_path, &it_prop);

        while (nusd_property_iterator_next(it_prop, &property_path, &property_type)) {
            print_property(stage, property_path, property_type);
        }
        nusd_property_iterator_destroy(it_prop);
        
    }
    nusd_prim_iterator_destroy(it);

    nusd_stage_destroy(stage);

    return 0;
}



void print_property(nusd_stage_t stage, char const* property_path, nusd_type_t property_type) {
    char const* name = nusd_path_get_name(property_path);

    if (property_type == NUSD_TYPE_RELATIONSHIP) {
        nusd_relationship_targets_iterator_t targets;
        size_t num_targets = 0;
        nusd_relationship_get_targets(stage, property_path, &targets, &num_targets);

        if (num_targets == 0) {
            printf("    %s %s = <>\n", nusd_type_to_string(property_type), name);
        } else {
            char const* target_path;
            printf("    %s %s = ", nusd_type_to_string(property_type), name);
            if (num_targets > 1) {
                printf("[");
            }
            while (nusd_relationship_targets_iterator_next(targets, &target_path)) {
                printf("<%s> ", target_path);
            }
            if (num_targets > 1) {
                printf("]\n");
            } else {
                printf("\n");
            }
            nusd_relationship_targets_iterator_destroy(targets);
        }

    } else if (property_type == NUSD_TYPE_TOKEN) {
        char const* value;
        nusd_attribute_get_token(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        printf("    %s %s = \"%s\"\n", nusd_type_to_string(property_type), name, value);
    } else if (property_type == NUSD_TYPE_TOKENARRAY) {
        nusd_token_array_iterator_t value;
        int result = nusd_attribute_get_token_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_token_array_iterator_size(value);
        printf("    token[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            char const* tok;
            while (nusd_token_array_iterator_next(value, &tok)) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("\"%s\"", tok);
            }
        } else {
            char const* tok;
            int i = 0;
            while (nusd_token_array_iterator_next(value, &tok)) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }

                if (i++ < 4) {
                    printf("\"%s\"", tok);
                }
            }

            printf(", ... \"%s\"", tok);
        }
        printf("]\n");
        nusd_token_array_iterator_destroy(value);
    } else if (property_type == NUSD_TYPE_FLOAT) {
        float value;
        nusd_attribute_get_float(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        printf("    %s %s = %f\n", nusd_type_to_string(property_type), name, value);
    } else if (property_type == NUSD_TYPE_FLOATARRAY) {
        nusd_float_array_t value;
        int result = nusd_attribute_get_float_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_float_array_size(value);
        float* data = nusd_float_array_data(value);
        printf("    float[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%f", data[i]);
            }
        } else {
            for (size_t i = 0; i < 4; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%f", data[i]);
            }

            printf(", ... %f", data[(size-1)]);
        }
        printf("]\n");
        nusd_float_array_destroy(value);
    } else if (property_type == NUSD_TYPE_FLOAT2 || property_type == NUSD_TYPE_TEXCOORD2F) {
        float value[2];
        nusd_attribute_get_float2(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%f, %f)\n", nusd_type_to_string(property_type), name, value[0], value[1]);
    } else if (property_type == NUSD_TYPE_FLOAT2ARRAY || property_type == NUSD_TYPE_TEXCOORD2FARRAY) {
        nusd_float2_array_t value;
        int result = nusd_attribute_get_float2_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_float2_array_size(value);
        float* data = nusd_float2_array_data(value);
        printf("    float2[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f)", data[i*2], data[i*2+1]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f)", data[i*2], data[i*2+1]);
            }

            printf(", ... (%f, %f)", data[(size-1)*2], data[(size-1)*2+1]);
        }
        printf("]\n");
        nusd_float2_array_destroy(value);
    } else if (property_type == NUSD_TYPE_FLOAT3 || 
                property_type == NUSD_TYPE_TEXCOORD3F  ||
                property_type == NUSD_TYPE_VECTOR3F  ||
                property_type == NUSD_TYPE_POINT3F  ||
                property_type == NUSD_TYPE_NORMAL3F  ||
                property_type == NUSD_TYPE_COLOR3F
        ) {
        float value[3];
        nusd_attribute_get_float3(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%f, %f, %f)\n", nusd_type_to_string(property_type), name, value[0], value[1], value[2]);
    } else if (property_type == NUSD_TYPE_FLOAT3ARRAY || 
                property_type == NUSD_TYPE_TEXCOORD3FARRAY  ||
                property_type == NUSD_TYPE_VECTOR3FARRAY  ||
                property_type == NUSD_TYPE_POINT3FARRAY  ||
                property_type == NUSD_TYPE_NORMAL3FARRAY  ||
                property_type == NUSD_TYPE_COLOR3FARRAY
        ) {
        nusd_float3_array_t value;
        int result = nusd_attribute_get_float3_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_float3_array_size(value);
        float* data = nusd_float3_array_data(value);
        printf("    float3[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*3], data[i*3+1], data[i*3+2]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*3], data[i*3+1], data[i*3+2]);
            }

            printf(", ... (%f, %f, %f)", data[(size-1)*3], data[(size-1)*3+1], data[(size-1)*3+2]);
        }
        printf("]\n");
        nusd_float3_array_destroy(value);
    } else if (property_type == NUSD_TYPE_FLOAT4 || 
                property_type == NUSD_TYPE_COLOR4F
        ) {
        float value[4];
        nusd_attribute_get_float4(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%f, %f, %f)\n", nusd_type_to_string(property_type), name, value[0], value[1], value[2]);
    } else if (property_type == NUSD_TYPE_FLOAT4ARRAY || 
                property_type == NUSD_TYPE_COLOR4FARRAY
        ) {
        nusd_float4_array_t value;
        int result = nusd_attribute_get_float4_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_float4_array_size(value);
        float* data = nusd_float4_array_data(value);
        printf("    float4[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*4], data[i*4+1], data[i*4+2]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*4], data[i*4+1], data[i*4+2]);
            }

            printf(", ... (%f, %f, %f)", data[(size-1)*4], data[(size-1)*4+1], data[(size-1)*4+2]);
        }
        printf("]\n");
        nusd_float4_array_destroy(value);
    } else if (property_type == NUSD_TYPE_INT) {
        int value;
        nusd_attribute_get_int(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        printf("    %s %s = %d\n", nusd_type_to_string(property_type), name, value);
    } else if (property_type == NUSD_TYPE_INTARRAY) {
        nusd_int_array_t value;
        int result = nusd_attribute_get_int_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_int_array_size(value);
        int* data = nusd_int_array_data(value);
        printf("    int[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%d", data[i]);
            }
        } else {
            for (size_t i = 0; i < 4; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%d", data[i]);
            }

            printf(", ... %d", data[(size-1)]);
        }
        printf("]\n");
        nusd_int_array_destroy(value);
    } else if (property_type == NUSD_TYPE_INT2) {
        int value[2];
        nusd_attribute_get_int2(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%d, %d)\n", nusd_type_to_string(property_type), name, value[0], value[1]);
    } else if (property_type == NUSD_TYPE_INT2ARRAY) {
        nusd_int2_array_t value;
        int result = nusd_attribute_get_int2_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_int2_array_size(value);
        int* data = nusd_int2_array_data(value);
        printf("    int2[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%d, %d)", data[i*2], data[i*2+1]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%d, %d)", data[i*2], data[i*2+1]);
            }

            printf(", ... (%d, %d)", data[(size-1)*2], data[(size-1)*2+1]);
        }
        printf("]\n");
        nusd_int2_array_destroy(value);
    } else if (property_type == NUSD_TYPE_INT3) {
        int value[3];
        nusd_attribute_get_int3(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%d, %d, %d)\n", nusd_type_to_string(property_type), name, value[0], value[1], value[2]);
    } else if (property_type == NUSD_TYPE_INT3ARRAY) {
        nusd_int3_array_t value;
        int result = nusd_attribute_get_int3_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_int3_array_size(value);
        int* data = nusd_int3_array_data(value);
        printf("    int3[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%d, %d, %d)", data[i*3], data[i*3+1], data[i*3+2]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%d, %d, %d)", data[i*3], data[i*3+1], data[i*3+2]);
            }

            printf(", ... (%d, %d, %d)", data[(size-1)*3], data[(size-1)*3+1], data[(size-1)*3+2]);
        }
        printf("]\n");
        nusd_int3_array_destroy(value);
    } else if (property_type == NUSD_TYPE_INT4) {
        int value[4];
        nusd_attribute_get_int4(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%d, %d, %d)\n", nusd_type_to_string(property_type), name, value[0], value[1], value[2]);
    } else if (property_type == NUSD_TYPE_INT4ARRAY) {
        nusd_int4_array_t value;
        int result = nusd_attribute_get_int4_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_int4_array_size(value);
        int* data = nusd_int4_array_data(value);
        printf("    int4[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%d, %d, %d)", data[i*4], data[i*4+1], data[i*4+2]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%d, %d, %d)", data[i*4], data[i*4+1], data[i*4+2]);
            }

            printf(", ... (%d, %d, %d)", data[(size-1)*4], data[(size-1)*4+1], data[(size-1)*4+2]);
        }
        printf("]\n");
        nusd_int4_array_destroy(value);
    } else if (property_type == NUSD_TYPE_DOUBLE) {
        double value;
        nusd_attribute_get_double(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        printf("    %s %s = %f\n", nusd_type_to_string(property_type), name, value);
    } else if (property_type == NUSD_TYPE_DOUBLEARRAY) {
        nusd_double_array_t value;
        int result = nusd_attribute_get_double_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_double_array_size(value);
        double* data = nusd_double_array_data(value);
        printf("    double[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%f", data[i]);
            }
        } else {
            for (size_t i = 0; i < 4; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%f", data[i]);
            }

            printf(", ... %f", data[(size-1)]);
        }
        printf("]\n");
        nusd_double_array_destroy(value);
    } else if (property_type == NUSD_TYPE_DOUBLE2 || property_type == NUSD_TYPE_TEXCOORD2D) {
        double value[2];
        nusd_attribute_get_double2(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%f, %f)\n", nusd_type_to_string(property_type), name, value[0], value[1]);
    } else if (property_type == NUSD_TYPE_DOUBLE2ARRAY || property_type == NUSD_TYPE_TEXCOORD2DARRAY) {
        nusd_double2_array_t value;
        int result = nusd_attribute_get_double2_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_double2_array_size(value);
        double* data = nusd_double2_array_data(value);
        printf("    double2[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f)", data[i*2], data[i*2+1]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f)", data[i*2], data[i*2+1]);
            }

            printf(", ... (%f, %f)", data[(size-1)*2], data[(size-1)*2+1]);
        }
        printf("]\n");
        nusd_double2_array_destroy(value);
    } else if (property_type == NUSD_TYPE_DOUBLE3 || 
                property_type == NUSD_TYPE_TEXCOORD3D  ||
                property_type == NUSD_TYPE_VECTOR3D  ||
                property_type == NUSD_TYPE_POINT3D  ||
                property_type == NUSD_TYPE_NORMAL3D  ||
                property_type == NUSD_TYPE_COLOR3D
        ) {
        double value[3];
        nusd_attribute_get_double3(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%f, %f, %f)\n", nusd_type_to_string(property_type), name, value[0], value[1], value[2]);
    } else if (property_type == NUSD_TYPE_DOUBLE3ARRAY || 
                property_type == NUSD_TYPE_TEXCOORD3DARRAY  ||
                property_type == NUSD_TYPE_VECTOR3DARRAY  ||
                property_type == NUSD_TYPE_POINT3DARRAY  ||
                property_type == NUSD_TYPE_NORMAL3DARRAY  ||
                property_type == NUSD_TYPE_COLOR3DARRAY
        ) {
        nusd_double3_array_t value;
        int result = nusd_attribute_get_double3_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_double3_array_size(value);
        double* data = nusd_double3_array_data(value);
        printf("    double3[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*3], data[i*3+1], data[i*3+2]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*3], data[i*3+1], data[i*3+2]);
            }

            printf(", ... (%f, %f, %f)", data[(size-1)*3], data[(size-1)*3+1], data[(size-1)*3+2]);
        }
        printf("]\n");
        nusd_double3_array_destroy(value);
    } else if (property_type == NUSD_TYPE_DOUBLE4 || 
                property_type == NUSD_TYPE_COLOR4D
        ) {
        double value[4];
        nusd_attribute_get_double4(stage, property_path, NUSD_TIMECODE_DEFAULT, &value[0]);
        printf("    %s %s = (%f, %f, %f)\n", nusd_type_to_string(property_type), name, value[0], value[1], value[2]);
    } else if (property_type == NUSD_TYPE_DOUBLE4ARRAY || 
                property_type == NUSD_TYPE_COLOR4DARRAY
        ) {
        nusd_double4_array_t value;
        int result = nusd_attribute_get_double4_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_double4_array_size(value);
        double* data = nusd_double4_array_data(value);
        printf("    double4[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*4], data[i*4+1], data[i*4+2]);
            }
        } else {
            for (size_t i = 0; i < 2; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("(%f, %f, %f)", data[i*4], data[i*4+1], data[i*4+2]);
            }

            printf(", ... (%f, %f, %f)", data[(size-1)*4], data[(size-1)*4+1], data[(size-1)*4+2]);
        }
        printf("]\n");
        nusd_double4_array_destroy(value);
    } else if (property_type == NUSD_TYPE_BOOL) {
        bool value;
        nusd_attribute_get_bool(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        printf("    %s %s = %s\n", nusd_type_to_string(property_type), name, value ? "true" : "false");
    } else if (property_type == NUSD_TYPE_BOOLARRAY) {
        nusd_bool_array_t value;
        bool result = nusd_attribute_get_bool_array(stage, property_path, NUSD_TIMECODE_DEFAULT, &value);
        size_t size = nusd_bool_array_size(value);
        bool* data = nusd_bool_array_data(value);
        printf("    int[%d] %s = [", int(size), name);
        bool first = true;
        if (size <= 4) {
            for (size_t i = 0; i < size; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%s", data[i] ? "true" : "false");
            }
        } else {
            for (size_t i = 0; i < 4; ++i) {
                if (!first) {
                    printf(", ");
                } else {
                    first = false;
                }
                printf("%d", data[i]);
            }

            printf(", ... %s", data[(size-1)] ? "true" : "false");
        }
        printf("]\n");
        nusd_bool_array_destroy(value);
    } else {
        printf("    %s %s\n", nusd_type_to_string(property_type), name);
    }
}