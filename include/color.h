#ifndef COLOR_H
#define COLOR_H

#include <windows.h> // RGB macro
#include "vec3.h"

typedef struct Color {
    struct Vec3 vec;
} Color;

static uint8_t color_red(struct Color *this) {
    return (uint8_t)(255.999 * this->vec.x);
}

static uint8_t color_green(struct Color *this) {
    return (uint8_t)(255.999 * this->vec.y);
}

static uint8_t color_blue(struct Color *this) {
    return (uint8_t)(255.999 * this->vec.z);
}

static struct Color color_new(float r, float g, float b) {
    struct Color c;
    c.vec = vec3_new(r, g, b);
    return c;
}

static COLORREF color_rgb(struct Color *this) {
    return RGB(color_red(this), color_green(this), color_blue(this));
}

#endif // COLOR_H