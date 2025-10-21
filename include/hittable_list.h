#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "interval.h"
#include "hittable.h"
#include "sphere.h" // Include the header for Sphere to use its hit function

#define HITTABLE_SPHERE 1

typedef struct Hittable_list {
    struct Hittable *objects; // Array of Hittable function pointers
    int size;                // Number of objects in the list
    int index;               // Current index for adding new objects
} Hittable_list;

static struct Hittable_list hittable_list_new(int size) {
    Hittable* objects;
    objects = (Hittable*)malloc(size * sizeof(Hittable));
    struct Hittable_list list = {objects, size};
    list.index = 0;
    return list;
}

static void hittable_list_add(struct Hittable_list *this_list, struct Hittable new_hittable, int index) {
    if (index < this_list->size) {
        this_list->objects[index] = new_hittable;
    }
    // TODO what happens if index >= size?
}

static void hittable_list_add_sphere(struct Hittable_list *this_list, float x, float y, float z, float radius) {
    if (this_list->index < this_list->size) {
        Sphere* s = (Sphere*)malloc(sizeof(Sphere));
        *s = sphere_new(point3_new(x, y, z), radius);
        struct Hittable h = {HITTABLE_SPHERE, s};
        this_list->objects[this_list->index] = h;
        this_list->index += 1;
    }
}

static bool list_hit(struct Hittable_list *this_list, struct Ray* r, Interval ray_t, struct Hit_record* rec) {
    struct Hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = ray_t.max;
    bool hit_result = false;

    for(int i = 0; i < this_list->size; i++) {
        hit_result = false;
        switch(this_list->objects[i].hittable_type) {
            case HITTABLE_SPHERE:
                Sphere* s = (Sphere*)this_list->objects[i].obj;
                Hittable* p_hittable = &this_list->objects[i];
                Ray* p_ray = r;
                hit_result = s->hit(p_hittable, p_ray, interval_new(ray_t.min, closest_so_far), &temp_rec);
                break;
            default:
                // Unknown hittable type
                return false;
        }
        if (hit_result) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif // HITTABLE_LIST_H