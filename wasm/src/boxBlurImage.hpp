#ifndef BOX_BLUR_IMAGE_HPP
#define BOX_BLUR_IMAGE_HPP

#include <vector>
#include "greyscaleImage.hpp"

std::vector<RGBA> boxBlurImage(std::vector<RGBA> image, int width, int height, int amount);

#endif
