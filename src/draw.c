#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
//#include "vec3.h"
#include "draw.h"

#define max_width 1920
#define max_height 1080

static struct Vec3 new(float x, float y, float z) {
    struct Vec3 v = {x, y, z};
    return v;
}

static struct Vec3 add(struct Vec3 a, struct Vec3 b) {
    return new(a.x + b.x, a.y + b.y, a.z + b.z);
}

static struct Vec3 subtract(struct Vec3 a, struct Vec3 b) {
    return new(a.x - b.x, a.y - b.y, a.z - b.z);
}

static float dot(struct Vec3 a, struct Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static struct Vec3 cross(struct Vec3 a, struct Vec3 b) {
    return new(
        a.y * b.z - a.z * b.y, // X
        a.z * b.x - a.x * b.z, // Y
        a.x * b.y - a.y * b.x  // Z
    );
}

static uint8_t red(struct Vec3 v) {
    return (uint8_t)(255.999 * v.x);
}

static uint8_t green(struct Vec3 v) {
    return (uint8_t)(255.999 * v.y);
}

static uint8_t blue(struct Vec3 v) {
    return (uint8_t)(255.999 * v.z);
}

Color* create_image_stream(int width, int height) {
    size_t size = width * height; // 1 "Color" struct per pixel (R, G, B)
    Color* img;
    img = (Color*)malloc(size * sizeof(Color));
    if (img == NULL) {
        fprintf(stderr, "Failed to allocate memory for image\n");
        return NULL;
    }
    return img;
}

Color* create_gradient_demo_img(int width, int height) {
    Color* img = (Color*)malloc(width * height * sizeof(Color));
    if (img == NULL) {
        printf("Failed to allocate memory for image\n");
        return NULL; // Memory allocation failed
    }

    for (int j = 0; j < height; j++) {
        printf("\rScanlines remaining: %d                 ", height - j);
        for (int i = 0; i < width; i++) {
            Color color = { (float)i / (width - 1), (float)j / (height - 1), 0.25f };
            img[j * width + i] = color;
        }
    }
    printf("\nDone.\n");

    return img;
}

void write_img_to_file(const char* filename, Color* img, int width, int height) {
    printf("Writing image to file: %s\n", filename);
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Failed to open file\n");
        perror("Failed to open file");
        return;
    }
    printf("Writing PPM...\n");
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = img[j * width + i];
            fputc(red(pixel), file);
            fputc(green(pixel), file);
            fputc(blue(pixel), file);
        }
    }
    fclose(file);
}

void write_img_to_screen(Color* img, int width, int height) {
    HDC hdesktop = GetDC(0);
    HDC memory_device_context = CreateCompatibleDC(hdesktop);
    HBITMAP hbitmap = CreateCompatibleBitmap(hdesktop, width, height);
    SelectObject(memory_device_context, hbitmap);

    // Draw to memory device context
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = img[j * width + i];
            SetPixel(memory_device_context, i, j, RGB(red(pixel), green(pixel), blue(pixel)));
        }
    }

    // BitBlt to screen
    for (int i = 0; i < 1000000; i++) { // Simple delay loop
        BitBlt(hdesktop, 0, 0, width, height, memory_device_context, 0, 0, SRCCOPY);
    }

    // Cleanup
    DeleteObject(hbitmap);
    DeleteDC(memory_device_context);
    ReleaseDC(0, hdesktop);
}


void draw(){
    printf("draw\n");
}

void render(){
    printf("render\n");
}

