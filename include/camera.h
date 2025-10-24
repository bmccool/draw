#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable_list.h"
#include "interval.h"
#include "ray.h"
#include "point.h"
#include "vec3.h"
#include "draw.h"
#include "material.h"

#define MAX_DEPTH 10
#define MIN_DISTANCE 0.001

typedef struct Camera {
    int image_height;      // Rendered image height
    Point3 center;         // Camera center
    Point3 pixel00_loc;    // Location of pixel (0,0)
    Vec3 pixel_delta_u;    // Delta vector to move right one pixel
    Vec3 pixel_delta_v;    // Delta vector to move down one pixel
    float aspect_ratio;    // Aspect ratio of the image
    int image_width;       // Rendered image width in pixel count
    int samples_per_pixel; // Number of samples per pixel for anti-aliasing
    float pixel_samples_scale; // Scale factor for averaging samples (1.0 / samples_per_pixel)
    float vfov;               // Vertical field of view angle in degrees
    Point3 look_from;        // Camera position
    Point3 look_at;          // Point camera is looking at
    Vec3 up;                 // Up vector
    Vec3 u, v, w;          // Camera coordinate frame basis vectors

} Camera;

Color ray_color(Ray* r, int depth, Hittable_list* world) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    //printf("Ray depth: %d\n", depth);
    if (depth <= 0) {
        return color_new(0, 0, 0);
    }

    struct Hit_record rec;
    if (list_hit(world, r, interval_new(MIN_DISTANCE, draw_infinity), &rec)) {
        Ray scattered;
        Color attenuation;
        if (material_scatter(rec.material_type, r, &rec, &attenuation, &scattered)) {
            return color_elementwise_multiply(ray_color(&scattered, depth - 1, world), attenuation);
        }
        return color_new(0, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r->direction);
    float a = 0.5 * (unit_direction.y + 1.0);
    // Lerp from (1, 1, 1) to (0.5, 0.7, 1.0) based on the Y direction
    return color_lerp(a, color_new(1.0, 1.0, 1.0), color_new(0.5, 0.7, 1.0));
}

static float degrees_to_radians(float degrees) {
    return degrees * (draw_pi / 180.0);
}



void camera_init(Camera *cam) {

    // Image
    int image_width = 1920;
    int image_height = 1080;
    int samples_per_pixel = 100;
    float aspect_ratio = (float)image_width / (float)image_height;

    // Determine Viewport dimensions
    float h = tanf(degrees_to_radians(cam->vfov) / 2);

    float focal_length = vec3_magnitude(vec3_from_point3s(cam->look_from, cam->look_at));

    float viewport_height = 2 * h * focal_length;
    float viewport_width = viewport_height * ((float)(image_width))/image_height;

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame
    Vec3 w = unit_vector(vec3_subtract(cam->look_from.vec, cam->look_at.vec));
    Vec3 u = unit_vector(vec3_cross(cam->up, w));
    Vec3 v = vec3_cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 viewport_u = vec3_multiply(u, viewport_width);
    Vec3 viewport_v = vec3_multiply(v, viewport_height);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vec3 pixel_delta_u = vec3_divide(viewport_u, (float)image_width);
    Vec3 pixel_delta_v = vec3_divide(viewport_v, (float)image_height);

    // Calculate the location of the upper left pixel.
    Point3 viewport_upper_left = point3_subtract(cam->look_from, point3_from_vec3(vec3_multiply(w, focal_length)));
    viewport_upper_left = point3_subtract(viewport_upper_left, point3_from_vec3(vec3_divide(viewport_u, 2)));
    viewport_upper_left = point3_subtract(viewport_upper_left, point3_from_vec3(vec3_divide(viewport_v, 2)));
    Point3 pixel00_loc = point3_add(viewport_upper_left, point3_from_vec3(vec3_multiply(vec3_add(pixel_delta_u, pixel_delta_v), 0.5)));
    float pixel_samples_scale = 1.0f / (float)samples_per_pixel;

    cam->image_height = image_height;
    cam->center = cam->look_from;
    cam->pixel00_loc = pixel00_loc;
    cam->pixel_delta_u = pixel_delta_u;
    cam->pixel_delta_v = pixel_delta_v;
    cam->aspect_ratio = aspect_ratio;
    cam->image_width = image_width;
    cam->samples_per_pixel = samples_per_pixel;
    cam->pixel_samples_scale = pixel_samples_scale;
    cam->w = w;
    cam->u = u;
    cam->v = v;
}

static struct Camera camera_setup() {
    Camera cam;
    cam.look_at = point3_new(0, 0, -1);
    cam.look_from = point3_new(0, 0, 0);
    cam.up = vec3_new(0, 1, 0);
    cam.vfov = 90.0;
    camera_init(&cam);
    return cam;
}


Vec3 sample_square() {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
    Vec3 vec = vec3_new(random_float() - 0.5, random_float() - 0.5, 0);
    return vec;
}

Ray get_ray(Camera* cam, int pixel_x, int pixel_y) {
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.
    Vec3 offset = sample_square();
    Point3 pixel_sample = cam->pixel00_loc;
    pixel_sample = point3_add(pixel_sample, point3_from_vec3(vec3_multiply(cam->pixel_delta_u, ((float)pixel_x + offset.x))));
    pixel_sample = point3_add(pixel_sample, point3_from_vec3(vec3_multiply(cam->pixel_delta_v, ((float)pixel_y + offset.y))));
    Vec3 ray_direction = vec3_from_point3s(pixel_sample, cam->center);
    Ray r = ray_new(cam->center, ray_direction);
    return r;
}

static Color* camera_render(Camera* cam, Hittable_list* world) {
    // Render
    printf("Rendering a %dx%d image\n255\n", cam->image_width, cam->image_height);

    // Create the image pixels in memory
    Color* img = create_image_stream(cam->image_width, cam->image_height);

    for (int j = 0; j < cam->image_height; j++) {
        printf("\rScanlines remaining: %d ", (cam->image_height - j));
        for (int i = 0; i < cam->image_width; i++) {
            Color color = color_new(0, 0, 0);
            for (int s = 0; s < cam->samples_per_pixel; s++) {
                Ray r = get_ray(cam, i, j);
                color = color_add(color, ray_color(&r, MAX_DEPTH, world));
            }
            //Point3 pixel_center = point3_add(cam->pixel00_loc, point3_from_vec3(vec3_add(vec3_multiply(cam->pixel_delta_u, (float)i), vec3_multiply(cam->pixel_delta_v, (float)j))));
            //Vec3 ray_direction = vec3_from_point3s(pixel_center, cam->center);
            //Ray r = ray_new(cam->center, ray_direction);

            //Color pixel_color = ray_color(&r, world);
            //img[j * cam->image_width + i] = pixel_color;
            img[j * cam->image_width + i] = color_multiply(color, cam->pixel_samples_scale);
        }
    }
    return img;
}

#endif // CAMERA_H