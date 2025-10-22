#ifndef COLOR_H
#define COLOR_H

#include <windows.h> // RGB macro
#include "vec3.h"
#include "interval.h"
#include <math.h>

typedef struct Color {
    struct Vec3 vec;
} Color;

static Interval intensity = {0.0f, 0.999f};

static inline float linear_to_gamma(float value) {
    return sqrtf(value);
}

static uint8_t color_red(struct Color *this) {
    return (uint8_t)(255.999 * linear_to_gamma(interval_clamp(&intensity, this->vec.x)));
}

static uint8_t color_green(struct Color *this) {
    return (uint8_t)(255.999 * linear_to_gamma(interval_clamp(&intensity, this->vec.y)));
}

static uint8_t color_blue(struct Color *this) {
    return (uint8_t)(255.999 * linear_to_gamma(interval_clamp(&intensity, this->vec.z)));
}

static struct Color color_new(float r, float g, float b) {
    struct Color c;
    c.vec = vec3_new(r, g, b);
    return c;
}

static COLORREF color_rgb(struct Color *this) {
    return RGB(color_red(this), color_green(this), color_blue(this));
}

static struct Color color_multiply(struct Color c, float t) {
    struct Vec3 result_vec = vec3_multiply(c.vec, t);
    struct Color result = {result_vec};
    return result;
}

static struct Color color_add(struct Color a, struct Color b) {
    struct Vec3 result_vec = vec3_add(a.vec, b.vec);
    struct Color result = {result_vec};
    return result;
}

static struct Color color_lerp(float blend, struct Color start, struct Color end) {
    // Lerp from start color to end color based on blend
    // Follow blendedValue = ((1 - blend) * startValue) + (blend * endValue)
    Color t1 = color_multiply(start, (1.0 - blend));
    Color t2 = color_multiply(end, blend);
    return color_add(t1, t2);
}

static struct Color color_elementwise_multiply(struct Color a, struct Color b) {
    struct Vec3 result_vec = vec3_new(a.vec.x * b.vec.x, a.vec.y * b.vec.y, a.vec.z * b.vec.z);
    struct Color result = {result_vec};
    return result;
}

#endif // COLOR_H