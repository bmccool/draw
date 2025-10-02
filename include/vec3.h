#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>

// Instance Type
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

// Class Object
extern const struct Vec3Class{
    struct Vec3 (*new)(float x, float y, float z);
    struct Vec3 (*add)(struct Vec3 a, struct Vec3 b);
    struct Vec3 (*subtract)(struct Vec3 a, struct Vec3 b);
    float (*dot)(struct Vec3 a, struct Vec3 b);
    struct Vec3 (*cross)(struct Vec3 a, struct Vec3 b);
    uint8_t (*red)(struct Vec3 *this);
    uint8_t (*green)(struct Vec3 *this);
    uint8_t (*blue)(struct Vec3 *this);
} Vec3Class;



static struct Vec3 new(float x, float y, float z) {
    struct Vec3 v = {x, y, z};
    return v;
}

static struct Vec3 add(struct Vec3 a, struct Vec3 b) {
    return new(a.x + b.x, a.y + b.y, a.z + b.z);
}

static struct Vec3 subtract(struct Vec3 a, struct Vec3 b) {
    return new(a.x - b.x, a.y - b.y, a.z - b.z);
}

static float dot(struct Vec3 a, struct Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static struct Vec3 cross(struct Vec3 a, struct Vec3 b) {
    return new(
        a.y * b.z - a.z * b.y, // X
        a.z * b.x - a.x * b.z, // Y
        a.x * b.y - a.y * b.x  // Z
    );
}

static struct Vec3 multiply(struct Vec3 v, float t) {
    return new(v.x * t, v.y * t, v.z * t);
}

static uint8_t red(struct Vec3 *this) {
    return (uint8_t)(255.999 * this->x);
}

static uint8_t green(struct Vec3 *this) {
    return (uint8_t)(255.999 * this->y);
}

static uint8_t blue(struct Vec3 *this) {
    return (uint8_t)(255.999 * this->z);
}



#endif // VEC3_H