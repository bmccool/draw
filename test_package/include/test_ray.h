#include "ray.h"

static void test_new_ray(void **state) {
    (void) state; /* unused */
    Ray ray = ray_new(point3_new(1.0, 2.0, 3.0),
                    vec3_new(4.0, 5.0, 6.0));
    Point3 o = ray.origin;
    Vec3 d = ray.direction;
    assert_float_equal(o.x(&o), 1.0, 0.1);
    assert_float_equal(o.y(&o), 2.0, 0.1);
    assert_float_equal(o.z(&o), 3.0, 0.1);
    assert_float_equal(d.x, 4.0, 0.1);
    assert_float_equal(d.y, 5.0, 0.1);
    assert_float_equal(d.z, 6.0, 0.1);
}

static void test_ray_at(void **state) {
    (void) state; /* unused */
    Ray ray = ray_new(point3_new(0.0, 0.0, 0.0),
                    vec3_new(1.0, 2.0, 3.0));
    Point3 p = ray.at(&ray, 2.0);
    assert_float_equal(p.x(&p), 2.0, 0.1);
    assert_float_equal(p.y(&p), 4.0, 0.1);
    assert_float_equal(p.z(&p), 6.0, 0.1);
}