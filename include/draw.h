#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>
#include <vec3.h>

void draw();
void render();

struct Vec3* create_image_stream(int width, int height);
struct Vec3* create_gradient_demo_img(int width, int height);
void write_img_to_file(const char* filename, struct Vec3* img, int width, int height);
void write_img_to_screen(struct Vec3* img, int width, int height);

#endif // DRAW_H