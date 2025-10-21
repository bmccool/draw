#include <vec3.h>
#include <cmocka.h>

/* A test case that does nothing and succeeds. */
static void test_vec3(void **state) {
    (void) state; /* unused */
    // Vec3 v = (Vec3){1.0, 2.0, 3.0};  // Works
    Vec3 v = vec3_new(1.0, 2.0, 3.0); // Fails
    assert_float_equal(v.x, 1.0, 0.1);
    assert_float_equal(v.y, 2.0, 0.1);
    assert_float_equal(v.z, 3.0, 0.1);

    for (int i = 0; i < 1; i++) {
        float l = -1.0;
        float h = 1.0;
        Vec3 r = vec3_bounded_random(l, h);
        assert_true(r.x >= l && r.x < h);
        assert_true(r.y >= l && r.y < h);
        assert_true(r.z >= l && r.z < h);
    }

}