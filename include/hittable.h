#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "ray.h"


typedef struct Hit_record {
    Point3 p;
    Vec3 normal;
    float t;
    bool front_face;
} Hit_record;

void set_face_normal(Hit_record *rec, Ray *r, Vec3 outward_normal) {
    // Sets the hit record normal vector.
    // Note: the parameter  `outward_normal` is assumed to have unit length.
    rec->front_face = vec3_dot(r->direction, outward_normal) < 0;
    rec->normal = rec->front_face ? outward_normal : vec3_multiply(outward_normal, -1);
}




#define HITTABLE_SPHERE 1



typedef struct Hittable {
    uint8_t hittable_type; // Type of hittable object
    void *obj;           // Pointer to the actual object (e.g., Sphere)
}Hittable;

// Hittable Type - a function pointer that takes a void* argument and returns a bool
// Convention: the void* argument should be a struct containing all necessary data for the hit test
// See Sphere.h for an example implementation
typedef bool (*Hit)(Hittable* this, Ray* r, float t_min, float t_max, Hit_record* rec);

#endif // HITTABLE_H