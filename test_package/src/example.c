#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include <draw.h>



int main() {
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
