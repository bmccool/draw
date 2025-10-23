#include <stdio.h>
#include <stdbool.h>

#include <draw.h>
#include <ray.h>
#include <sphere.h>
#include <hittable_list.h>
#include <hittable.h>
#include <interval.h>
#include "camera.h"

int draw_gradient() {
    printf("Test Draw:\n");

    // Image
    int image_width = 1920;
    int image_height = 1080;

    // Render
    printf("Rendering a %dx%d image\n", image_width, image_height);
    Color* img = create_gradient_demo_img(image_width, image_height);
    if (img == NULL) {
        printf("Failed to create image\n");
        return 1;
    }
    else {
        printf("Image created successfully\n");

        // Write image to file
        printf("Writing image to 'output.ppm'\n");
        write_img_to_file("output.ppm", img, image_width, image_height);

        // Draw image to screen
        printf("Draw image to screen...\n");
        write_img_to_screen(img, image_width, image_height);

        // Free img
        free(img);
    }
    return 0;
}

float hit_sphere(struct Point3 center, float radius, struct Ray r) {
    // Return the t value where the ray hits the sphere, or -1.0 if no hit
    Vec3 oc = vec3_from_point3s(center, r.origin);
    float a = vec3_dot(r.direction, r.direction); // This could be replaced with r.direction.length.squared()
    // use b = -2h to make quadratic formula simpler
    float h = vec3_dot(r.direction, oc);
    float c = vec3_dot(oc, oc) - (radius * radius);
    //float discriminant = (b * b) - (4 * a * c);
    float discriminant = (h * h) - (a * c);

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (h - sqrtf(discriminant)) / a;
    }
}



int test_main(void **state) {
    /* Sending Rays Into the Scene */
    (void) state; /* unused */

    Camera cam = camera_init();

    // Create World
    Hittable_list world = hittable_list_new(5);
    Material lambertian_red = material_lambertian(color_new(0.7, 0.3, 0.3));
    Material lambertian_green = material_lambertian(color_new(0.3, 0.7, 0.3));
    Material dielectric_glass = material_dielectric(1.50); // World of water (1.33) RI of glass (1.00)
    Material dielectric_bubble = material_dielectric(1.00 / 1.50); // Glass bubble in air
    Material metallic_gold = material_metal(color_new(0.8, 0.6, 0.2), 0.0);  // Fuzz factor 0.0 (mirror)
    hittable_list_add_sphere(&world,  0,       0,   -1,   0.5, &lambertian_red);
    hittable_list_add_sphere(&world,  0,    -100.5, -1, 100,   &lambertian_green);
    hittable_list_add_sphere(&world, -1,       0,   -1,   0.5, &dielectric_glass);
    hittable_list_add_sphere(&world,  1,       0,   -1,   0.5, &metallic_gold);
    hittable_list_add_sphere(&world, -1,       0,   -1,   0.4, &dielectric_bubble); // Hollow glass bubble

    // Render
    Color* img = camera_render(&cam, &world);

    printf("\rDone.                 \n");
    write_img_to_file("output.ppm", img, cam.image_width, cam.image_height);
    write_img_to_screen(img, cam.image_width, cam.image_height);
    free(img);

    return 0;
}

int test_random_bounded_float(void **state) {
    (void) state; /* unused */

    for (int i = 0; i < 10; i++) {
        float r = random_bounded_float(-1, 1);
        if (r < -1.0f || r >= 1.0f) {
            printf("Test failed: random_bounded_float returned %f which is out of bounds\n", r);
            return 1;
        }
        else {
            printf("Random bounded float %d: %f\n", i, r);
        }
    }
    return 0;
}
