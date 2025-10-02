#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "vec3.h"
#include "draw.h"
#include "color.h"

#define max_width 1920
#define max_height 1080


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
            fputc(red(&pixel), file);
            fputc(green(&pixel), file);
            fputc(blue(&pixel), file);
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
            SetPixel(memory_device_context, i, j, RGB(red(&pixel), green(&pixel), blue(&pixel)));
        }
    }

    // BitBlt to screen
    for (int i = 0; i < 25000; i++) { // Simple delay loop
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

