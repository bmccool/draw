#include <stdio.h>
#include <stdint.h>

#define max_width 1920
#define max_height 1080

// Function to write content to a file
// Content is to be interpreted as a stream of bytes, in R,G,B order, size (width*height*3)
void write_to_file(const char* filename, const uint16_t* content, size_t width, size_t height) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    fwrite(content, sizeof(uint16_t), width * height * 3, file);
    fclose(file);
}

void draw(){
    printf("draw\n");
}

void render(){
    printf("render\n");
}

