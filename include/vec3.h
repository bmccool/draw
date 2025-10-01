#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>

// Instance Type
struct Vec3 {
    float x;
    float y;
    float z;
    uint8_t (*red)(struct Vec3 *this);
    uint8_t (*green)(struct Vec3 *this);
    uint8_t (*blue)(struct Vec3 *this);
};

// Class Object
extern const struct Vec3Class{
    struct Vec3 (*new)(float x, float y, float z);
    struct Vec3 (*add)(struct Vec3 a, struct Vec3 b);
    struct Vec3 (*subtract)(struct Vec3 a, struct Vec3 b);
    float (*dot)(struct Vec3 a, struct Vec3 b);
    struct Vec3 (*cross)(struct Vec3 a, struct Vec3 b);
} Vec3;

typedef struct Vec3 Color;
extern const struct Vec3Class ColorClass;

#endif // VEC3_H