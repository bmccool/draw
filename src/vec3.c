#include "vec3.h"
#include <stdint.h>

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

static uint8_t red(struct Vec3 *this) {
    printf("In red()\n");
    return (uint8_t)(255.999 * this->x);
}

static uint8_t green(struct Vec3 *this) {
    printf("In green()\n");
    return (uint8_t)(255.999 * this->y);
}

static uint8_t blue(struct Vec3 *this) {
    printf("In blue()\n");
    return (uint8_t)(255.999 * this->z);
}