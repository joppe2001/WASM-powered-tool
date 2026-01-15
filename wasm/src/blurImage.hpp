#ifndef BLUR_IMAGE_HPP
#define BLUR_IMAGE_HPP

#include <vector>
#include "greyscaleImage.hpp"

std::vector<RGBA> blurImage(std::vector<RGBA> image, int width, int height);

#endif
