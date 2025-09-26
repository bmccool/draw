#include <stdio.h>
#include "draw.h"
#include <stdint.h>

uint8_t* create_image_stream(int width, int height);
uint8_t* create_gradient_demo_img(int width, int height);
void write_img_to_file(const char* filename, uint8_t* img, int width, int height);


uint8_t* create_image_stream(int width, int height) {
    size_t size = width * height * 3; // 3 bytes per pixel (R, G, B)
    uint8_t* img;
    img = (uint8_t*)malloc(size * sizeof(uint8_t));
    if (img == NULL) {
        fprintf(stderr, "Failed to allocate memory for image\n");
        return NULL;
    }
    return img;
}

uint8_t* create_gradient_demo_img(int width, int height) {
    uint8_t* img = create_image_stream(width, height);
    if (img == NULL) {
        return NULL; // Memory allocation failed
    }

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            float r = (float)i / (width - 1);
            float g = (float)j / (height - 1);
            float b = 0.25;

            uint8_t ir = (uint8_t)(255.999 * r);
            uint8_t ig = (uint8_t)(255.999 * g);
            uint8_t ib = (uint8_t)(255.999 * b);

            int index = (j * width + i) * 3;
            img[index] = ir;
            img[index + 1] = ig;
            img[index + 2] = ib;
        }
    }

    return img;
}

void write_img_to_file(const char* filename, uint8_t* img, int width, int height) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(img, sizeof(uint8_t), width * height * 3, file);
    fclose(file);
}


int main() {
    printf("Test Draw:\n");

    // Image
    int image_width = 256;
    int image_height = 256;

    // Render
    uint8_t* img = create_gradient_demo_img(image_width, image_height);
    if (img == NULL) {
        return 1; // Memory allocation failed
    }
    write_img_to_file("output.ppm", img, image_width, image_height);
    free(img);


    return 0;
}
