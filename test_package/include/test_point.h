#include "point.h"

static void test_new_point(void **state) {
    (void) state; /* unused */
    Point3 p = point3_new(1.0, 2.0, 3.0);
    assert_float_equal(p.x(&p), 1.0, 0.1);
    assert_float_equal(p.y(&p), 2.0, 0.1);
    assert_float_equal(p.z(&p), 3.0, 0.1);
}