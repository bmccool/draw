#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>
#include <math.h>
#include "interval.h"

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

static struct Vec3 vec3_divide(struct Vec3 v, float t) {
    return vec3_new(v.x / t, v.y / t, v.z / t);
}

static struct Vec3 unit_vector(struct Vec3 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return vec3_divide(v, length);
}

static Vec3 vec3_random() {
    return vec3_new(random_float(), random_float(), random_float());
}

static Vec3 vec3_bounded_random(float min_bound, float max_bound) {
    float x = random_bounded_float((float)min_bound, max_bound);
    float y = random_bounded_float(min_bound, max_bound);
    float z = random_bounded_float(min_bound, max_bound);
    return vec3_new(x, y, z);
}

static Vec3 vec3_random_unit_vector() {
    while (1) {
        Vec3 p = vec3_bounded_random(-1, 1);
        float len_squared = vec3_dot(p, p);
        if (1e-160 < len_squared && len_squared <= 1){
            return vec3_divide(p, sqrtf(len_squared));
        }
    }
}

static Vec3 vec3_random_on_hemisphere(Vec3* normal) {
    Vec3 on_unit_sphere = vec3_random_unit_vector();
    if (vec3_dot(on_unit_sphere, *normal) > 0.0) {
        return on_unit_sphere;
    }
    else {
        return vec3_multiply(on_unit_sphere, -1.0);
    }
}

static bool vec3_near_zero(Vec3 v) {
    // Return true if the vector is close to zero in all dimensions.
    const float s = 1e-8;
    return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

static Vec3 vec3_reflect(Vec3 v, Vec3 n) {
    // Reflect vector v around normal n
    return vec3_subtract(v, vec3_multiply(n, 2 * vec3_dot(v, n)));
}

static Vec3 vec3_refract(Vec3 uv, Vec3 n, float relative_ref_idx) {
    float cos_theta = fminf(vec3_dot(vec3_multiply(uv, -1), n), 1.0);
    Vec3 r_out_perp = vec3_multiply(vec3_add(uv, vec3_multiply(n, cos_theta)), relative_ref_idx);
    Vec3 r_out_parallel = vec3_multiply(n, -sqrtf(fabsf(1.0 - vec3_dot(r_out_perp, r_out_perp))));
    return vec3_add(r_out_perp, r_out_parallel);
}

#endif // VEC3_H