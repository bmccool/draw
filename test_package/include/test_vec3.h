#include <vec3.h>
#include <cmocka.h>

/* A test case that does nothing and succeeds. */
static void test_vec3(void **state) {
    (void) state; /* unused */
    // Vec3 v = (Vec3){1.0, 2.0, 3.0};  // Works
    Vec3 v = new(1.0, 2.0, 3.0); // Fails
    assert_true(v.x == 1.0);
    assert_true(v.y == 2.0);
    assert_true(v.z == 3.0);
}