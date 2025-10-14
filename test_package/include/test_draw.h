#include <stdio.h>
#include <stdbool.h>

#include <draw.h>
#include <ray.h>
#include <sphere.h>
#include <hittable_list.h>
#include <hittable.h>

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

Color ray_color(struct Ray r) {
    //float t = hit_sphere(point3_new(0,0,-1), 0.5, r);

    Sphere s = sphere_new(point3_new(0,0,-1), 0.5);
    Hittable h = {HITTABLE_SPHERE, &s};
    Hittable_list world = hittable_list_new(1);
    world.objects[0] = h;
    
    struct Hit_record rec;
    if (list_hit(&world, &r, 0.001, 1000, &rec)) {
        Vec3 normal = unit_vector(rec.normal);
        return color_multiply(color_new(normal.x + 1, normal.y + 1, normal.z + 1), 0.5);
    }

    //float t = s.hit(&h, &r, 0.001, 1000, &rec);
    //if (t > 0.0) {
    //    Vec3 normal = unit_vector(vec3_subtract(r.at(&r, t).vec, point3_new(0,0,-1).vec));
    //    return color_multiply(color_new(normal.x + 1, normal.y + 1, normal.z + 1), 0.5);
    //}


    Vec3 unit_direction = unit_vector(r.direction);
    float a = 0.5 * (unit_direction.y + 1.0);
    // Lerp from (1, 1, 1) to (0.5, 0.7, 1.0) based on the Y direction
    return color_lerp(a, color_new(1.0, 1.0, 1.0), color_new(0.5, 0.7, 1.0));
}

int test_4_2(void **state) {
    /* Sending Rays Into the Scene */
    (void) state; /* unused */

    // Image
    int image_width = 1920;
    int image_height = 1080;
    float aspect_ratio = (float)image_width / (float)image_height;

    // Camera
    float focal_length = 1.0;
    float viewport_height = 2;
    float viewport_width = viewport_height * ((float)(image_width))/image_height;
    Point3 camera_center = point3_new(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 viewport_u = vec3_new(viewport_width, 0, 0);
    Vec3 viewport_v = vec3_new(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vec3 pixel_delta_u = vec3_divide(viewport_u, (float)image_width);
    Vec3 pixel_delta_v = vec3_divide(viewport_v, (float)image_height);

    // Calculate the location of the upper left pixel.
    Point3 viewport_upper_left = point3_subtract(camera_center, point3_new(0, 0, focal_length));
    viewport_upper_left = point3_subtract(viewport_upper_left, point3_from_vec3(vec3_divide(viewport_u, 2)));
    viewport_upper_left = point3_subtract(viewport_upper_left, point3_from_vec3(vec3_divide(viewport_v, 2)));
    Point3 pixel00_loc = point3_add(viewport_upper_left, point3_from_vec3(vec3_multiply(vec3_add(pixel_delta_u, pixel_delta_v), 0.5)));

    // Render
    printf("Rendering a %dx%d image\n255\n", image_width, image_height);

    // Create the image pixels in memory
    Color* img = create_image_stream(image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        printf("\rScanlines remaining: %d ", (image_height - j));
        for (int i = 0; i < image_width; i++) {
            Point3 pixel_center = point3_add(pixel00_loc, point3_from_vec3(vec3_add(vec3_multiply(pixel_delta_u, (float)i), vec3_multiply(pixel_delta_v, (float)j))));
            Vec3 ray_direction = vec3_from_point3s(pixel_center, camera_center);
            Ray r = ray_new(camera_center, ray_direction);

            Color pixel_color = ray_color(r);
            img[j * image_width + i] = pixel_color;
        }
    }

    printf("\rDone.                 \n");
    write_img_to_file("output.ppm", img, image_width, image_height);
    write_img_to_screen(img, image_width, image_height);
    free(img);

    return 0;
}
