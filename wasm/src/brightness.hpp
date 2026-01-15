#ifndef BRIGHTNESS_IMAGE_HPP
#define BRIGHTNESS_IMAGE_HPP

#include <vector>
#include <algorithm>
#include "greyscaleImage.hpp"

std::vector<RGBA> brightness(std::vector<RGBA> image, int amount);

#endif
