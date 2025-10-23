#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "color.h"
#include "ray.h"


#define MATERIAL_LAMBERTIAN 1
#define MATERIAL_METAL 2

typedef struct Material{
    uint8_t material_type;
    Color albedo;
    bool (*scatter)(struct Material*, Ray*, Hit_record*, Color*, Ray*);
} Material;

static bool material_scatter(Material* this_material, Ray* ray_in, Hit_record* rec, Color* attenuation, Ray* scattered) {
    switch(this_material->material_type) {
        case MATERIAL_LAMBERTIAN:
            return this_material->scatter(this_material, ray_in, rec, attenuation, scattered);
        case MATERIAL_METAL:
            return this_material->scatter(this_material, ray_in, rec, attenuation, scattered);
        default:
            return false;
    }
}

static bool lambertian_scatter(Material* this_material, Ray* ray_in, Hit_record* rec, Color* attenuation, Ray* scattered) {
    Vec3 scatter_direction = vec3_add(rec->normal, vec3_random_unit_vector());
    // Catch degenerate scatter direction
    if (vec3_near_zero(scatter_direction)) {
        scatter_direction = rec->normal;
    }
    *scattered = ray_new(rec->p, scatter_direction);
    *attenuation = this_material->albedo;
    return true;
}

static bool metal_scatter(Material* this_material, Ray* ray_in, Hit_record* rec, Color* attenuation, Ray* scattered) {
    Vec3 reflected = vec3_reflect(ray_in->direction, rec->normal);
    *scattered = ray_new(rec->p, reflected);
    *attenuation = this_material->albedo;
    return true;
}

static Material material_lambertian(Color albedo) {
    Material mat;
    mat.material_type = MATERIAL_LAMBERTIAN;
    mat.scatter = lambertian_scatter;
    mat.albedo = albedo;
    return mat;
}

static Material material_metal(Color albedo) {
    Material mat;
    mat.material_type = MATERIAL_METAL;
    mat.scatter = metal_scatter;
    mat.albedo = albedo;
    return mat;
}

#endif // MATERIAL_H