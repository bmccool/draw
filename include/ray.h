#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "point.h"

// Instance Type
typedef struct Ray {
    Point3 origin;
    Vec3 direction;
} Ray;

Point3 ray_at(Ray* r, float t) {
    Vec3 movement = multiply(r->direction, t);
    return add(r->origin, movement);
}

#endif // RAY_H
