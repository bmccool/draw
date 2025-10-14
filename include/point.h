#ifndef POINT_H
#define POINT_H

#include <vec3.h>


typedef struct Point3 {
    struct Vec3 vec;
    float (*x)(struct Point3 *); // For direct access like p.x(&p)
    float (*y)(struct Point3 *);
    float (*z)(struct Point3 *);

} Point3;

static float point3_x(struct Point3 *this) {
    return this->vec.x;
}

static float point3_y(struct Point3 *this) {
    return this->vec.y;
}

static float point3_z(struct Point3 *this) {
    return this->vec.z;
}

static struct Point3 point3_new(float x, float y, float z) {
    struct Point3 p = {x, y, z};
    p.x = point3_x;
    p.y = point3_y;
    p.z = point3_z;
    return p;
}

static struct Point3 point3_from_vec3(struct Vec3 v) {
    return point3_new(v.x, v.y, v.z);
}

static struct Point3 point3_subtract(struct Point3 a, struct Point3 b) {
    struct Vec3 result_vec = vec3_subtract(a.vec, b.vec);
    return point3_from_vec3(result_vec);
}

static struct Point3 point3_add(struct Point3 a, struct Point3 b) {
    struct Vec3 result_vec = vec3_add(a.vec, b.vec);
    return point3_from_vec3(result_vec);
}

static struct Vec3 vec3_from_point3s(struct Point3 a, struct Point3 b) {
    Vec3 result = vec3_subtract(a.vec, b.vec);
    return result;
}

#endif // POINT_H