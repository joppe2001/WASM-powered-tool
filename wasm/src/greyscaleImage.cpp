#include <vector>
#include <cstdint>
#include "greyscaleImage.hpp"

std::vector<RGBA> greyscaleImage(std::vector<RGBA> image) {
    std::vector<RGBA> greyscaleImage(image.size());
    for (int i = 0; i < image.size(); i++) {
        uint8_t grey = 0.299 * image[i].r + 0.587 * image[i].g + 0.114 * image[i].b;
        greyscaleImage[i].r = grey;
        greyscaleImage[i].g = grey;
        greyscaleImage[i].b = grey;
        greyscaleImage[i].a = image[i].a;
    }
    return greyscaleImage;
}
