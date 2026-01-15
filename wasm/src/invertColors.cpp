#include <vector>
#include "greyscaleImage.hpp"

std::vector<RGBA> invertColors(std::vector<RGBA> image) {
    std::vector<RGBA> invertedColorImage(image.size());
    for (int i = 0; i < image.size(); i++) {
        invertedColorImage[i].r = 255 - image[i].r;
        invertedColorImage[i].g = 255 - image[i].g;
        invertedColorImage[i].b = 255 - image[i].b;
        invertedColorImage[i].a = image[i].a;
    }
    return invertedColorImage;
}
