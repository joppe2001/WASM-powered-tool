#ifndef GREYSCALE_IMAGE_HPP
#define GREYSCALE_IMAGE_HPP

#include <vector>
#include <cstdint>

struct RGBA { uint8_t r, g, b, a; };
std::vector<RGBA> greyscaleImage(std::vector<RGBA> image);

#endif
