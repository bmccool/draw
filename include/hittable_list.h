#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "hittable.h"
#include "sphere.h" // Include the header for Sphere to use its hit function

#define HITTABLE_SPHERE 1

typedef struct Hittable_list {
    struct Hittable *objects; // Array of Hittable function pointers
    int size;                // Number of objects in the list
} Hittable_list;

static struct Hittable_list hittable_list_new(int size) {
    Hittable* objects;
    objects = (Hittable*)malloc(size * sizeof(Hittable));
    struct Hittable_list list = {objects, size};
    return list;
}

static bool list_hit(struct Hittable_list *this_list, struct Ray* r, float t_min, float t_max, struct Hit_record* rec) {
    struct Hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    bool hit_result = false;

    for(int i = 0; i < this_list->size; i++) {
        hit_result = false;
        switch(this_list->objects[i].hittable_type) {
            case HITTABLE_SPHERE:
                Sphere* s = (Sphere*)this_list->objects[i].obj;
                Hittable* p_hittable = &this_list->objects[i];
                Ray* p_ray = r;
                hit_result = s->hit(p_hittable, p_ray, t_min, closest_so_far, &temp_rec);
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