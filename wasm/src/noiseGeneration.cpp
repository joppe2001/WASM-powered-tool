#include <vector>
#include <cmath>
#include <random>
#include "greyscaleImage.hpp"

std::vector<RGBA> noiseGeneration(std::vector<RGBA> image, int amount) {
    std::vector<RGBA> outputImage(image.size());

    // STEP 1: You need a way to generate random numbers
    // Hint: look into <random> header, specifically a "distribution" and an "engine"

    // STEP 2: Loop through each pixel

        // STEP 3: Get a random value (positive or negative) based on "amount"

        // STEP 4: Add that random value to the pixel's RGB channels

        // STEP 5: Make sure values stay within 0-255

    return outputImage;
}
