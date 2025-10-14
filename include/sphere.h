#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>
#include <point.h>
#include <hittable.h>
#include <ray.h>


typedef struct Sphere {
    Point3 center;
    float radius;
    Hit hit;
} Sphere;


static bool sphere_hit(Hittable* this, Ray* r, float t_min, float t_max, Hit_record* rec) {
    // Return true if the ray hits the sphere between ray_t_min and ray_t_max
    // If hit, fill in the rec with the hit record details
    struct Sphere *s = (struct Sphere *)this->obj;

    Vec3 oc = vec3_from_point3s(s->center, r->origin);
    float a = vec3_dot(r->direction, r->direction);
    float h = vec3_dot(r->direction, oc);
    float c = vec3_dot(oc, oc) - (s->radius * s->radius);
    float discriminant = (h * h) - (a * c);
    if (discriminant < 0) {
        return false;
    }
    float sqrt_d = sqrtf(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (h - sqrt_d) / a;
    if (root <= t_min || t_max <= root){
        root = (h + sqrt_d) / a;
        if (root <= t_min || t_max <= root){
            return false;
        }
    }

    rec->t = root;
    rec->p = r->at(r, rec->t);
    rec->normal = vec3_divide(vec3_subtract(rec->p.vec, s->center.vec), s->radius);
    set_face_normal(rec, r, rec->normal);
    return true;
}

static struct Sphere sphere_new(Point3 center, float radius) {
    struct Sphere s = {center, radius};
    s.hit = sphere_hit;
    return s;
}

#endif // SPHERE_H