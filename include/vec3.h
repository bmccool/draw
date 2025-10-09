#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>

// Instance Type
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;


static struct Vec3 vec3_new(float x, float y, float z) {
    struct Vec3 v = {x, y, z};
    return v;
}

static struct Vec3 vec3_add(struct Vec3 a, struct Vec3 b) {
    return vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

static struct Vec3 vec3_subtract(struct Vec3 a, struct Vec3 b) {
    return vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}

static float vec3_dot(struct Vec3 a, struct Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static struct Vec3 vec3_cross(struct Vec3 a, struct Vec3 b) {
    return vec3_new(
        a.y * b.z - a.z * b.y, // X
        a.z * b.x - a.x * b.z, // Y
        a.x * b.y - a.y * b.x  // Z
    );
}

static struct Vec3 vec3_multiply(struct Vec3 v, float t) {
    return vec3_new(v.x * t, v.y * t, v.z * t);
}

#endif // VEC3_H