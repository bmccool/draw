#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include <draw.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test_color.h"
#include "test_vec3.h"
#include "test_draw.h"
#include "test_point.h"
#include "test_ray.h"


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_vec3),
        cmocka_unit_test(test_color),
        cmocka_unit_test(test_new_point),
        cmocka_unit_test(test_new_ray),
        cmocka_unit_test(test_ray_at),
        cmocka_unit_test(test_random_bounded_float),
        cmocka_unit_test(test_main),
        //cmocka_unit_test(draw_gradient),
    };
    int ret_val = cmocka_run_group_tests(tests, NULL, NULL);

}

