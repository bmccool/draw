#include <color.h>

/* A test case that does nothing and succeeds. */
static void test_color(void **state) {
    (void) state; /* unused */
    Color c = color_new(0.1, 0.2, 0.3);
    //Color c = (Color){0.1, 0.2, 0.3};
    printf("Color: (%f, %f, %f)\n", c.vec.x, c.vec.y, c.vec.z);
    assert_float_equal(c.vec.x, 0.1, 0.1);
    assert_float_equal(c.vec.y, 0.2, 0.1);
    assert_float_equal(c.vec.z, 0.3, 0.1);
}