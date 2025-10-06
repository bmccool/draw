#include <color.h>

/* A test case that does nothing and succeeds. */
static void test_color(void **state) {
    (void) state; /* unused */
    assert_true(1 == 1); // This test is expected to fail
}