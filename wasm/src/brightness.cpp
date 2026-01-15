#include <vector>
#include <algorithm>
#include "greyscaleImage.hpp"

std::vector<RGBA> brightness(std::vector<RGBA> image, int amount) {
    std::vector<RGBA> brightenedImage(image.size());
    for (int i = 0; i < image.size(); i++) {
        brightenedImage[i].r = static_cast<uint8_t>(std::clamp(image[i].r + amount, 0, 255));
        brightenedImage[i].g = static_cast<uint8_t>(std::clamp(image[i].g + amount, 0, 255));
        brightenedImage[i].b = static_cast<uint8_t>(std::clamp(image[i].b + amount, 0, 255));
        brightenedImage[i].a = image[i].a;
    }
    return brightenedImage;
}
