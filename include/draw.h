#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>
#include <vec3.h>

void draw();
void render();

Color* create_image_stream(int width, int height);
Color* create_gradient_demo_img(int width, int height);
void write_img_to_file(const char* filename, Color* img, int width, int height);
void write_img_to_screen(Color* img, int width, int height);

#endif // DRAW_H