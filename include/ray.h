#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "point.h"

// Instance Type
typedef struct Ray {
    Point3 origin;
    Vec3 direction;
    Point3 (*at)(struct Ray *, float);
} Ray;

Point3 ray_at(Ray* r, float t) {
    Vec3 movement = vec3_multiply(r->direction, t);
    Vec3 result_vec = vec3_add(r->origin.vec, movement);
    return point3_new(result_vec.x, result_vec.y, result_vec.z);
}

static struct Ray ray_new(Point3 origin, Vec3 direction) {
    struct Ray r = {origin, direction};
    r.at = ray_at;
    return r;
}

#endif // RAY_H
