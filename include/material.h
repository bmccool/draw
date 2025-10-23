#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "color.h"
#include "ray.h"


#define MATERIAL_LAMBERTIAN 1
#define MATERIAL_METAL 2
#define MATERIAL_DIELECTRIC 3
#define MATERIAL_UNKNOWN 255

typedef struct Material{
    uint8_t material_type;
    Color albedo;
    float fuzz;
    bool (*scatter)(struct Material*, Ray*, Hit_record*, Color*, Ray*);
    float refraction_idx;
} Material;

static bool material_scatter(Material* this_material, Ray* ray_in, Hit_record* rec, Color* attenuation, Ray* scattered) {
    switch(this_material->material_type) {
        case MATERIAL_UNKNOWN:
            return false;
        default:
            return this_material->scatter(this_material, ray_in, rec, attenuation, scattered);
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
    // Returns True if the ray is scattered (Reflected outward)
    Vec3 reflected = vec3_reflect(ray_in->direction, rec->normal);
    reflected = vec3_add(unit_vector(reflected), vec3_multiply(vec3_random_unit_vector(), this_material->fuzz));
    *scattered = ray_new(rec->p, reflected);
    *attenuation = this_material->albedo;
    return vec3_dot(scattered->direction, rec->normal) > 0;
}

static bool dielectric_scatter(Material* this_material, Ray* ray_in, Hit_record* rec, Color* attenuation, Ray* scattered) {
    float refraction_ratio = rec->front_face ? (1.0 / this_material->refraction_idx) : this_material->refraction_idx;
    Vec3 unit_direction = unit_vector(ray_in->direction);
    Vec3 refracted = vec3_refract(unit_direction, rec->normal, refraction_ratio);
    *scattered = ray_new(rec->p, refracted);
    *attenuation = color_new(1.0, 1.0, 1.0);
    return true;
}

static Material material_lambertian(Color albedo) {
    Material mat;
    mat.material_type = MATERIAL_LAMBERTIAN;
    mat.scatter = lambertian_scatter;
    mat.albedo = albedo;
    return mat;
}

static Material material_metal(Color albedo, float fuzz) {
    Material mat;
    mat.material_type = MATERIAL_METAL;
    mat.scatter = metal_scatter;
    mat.albedo = albedo;
    mat.fuzz = fuzz;
    return mat;
}

static Material material_dielectric(float ref_idx) {
    Material mat;
    mat.material_type = MATERIAL_DIELECTRIC;
    mat.scatter = dielectric_scatter;
    mat.refraction_idx = ref_idx;
    return mat;
}

#endif // MATERIAL_H