#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>

extern struct Vec3 {
    float x;
    float y;
    float z;
};

extern const struct Vec3Class{
    struct Vec3 (*new)(float x, float y, float z);
    struct Vec3 (*add)(struct Vec3 a, struct Vec3 b);
    struct Vec3 (*subtract)(struct Vec3 a, struct Vec3 b);
    float (*dot)(struct Vec3 a, struct Vec3 b);
    struct Vec3 (*cross)(struct Vec3 a, struct Vec3 b);
    uint8_t (*red)(struct Vec3 v);
    uint8_t (*green)(struct Vec3 v);
    uint8_t (*blue)(struct Vec3 v);
} Vec3;

#endif // VEC3_H