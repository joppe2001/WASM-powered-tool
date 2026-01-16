#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "greyscaleImage.hpp"

using namespace std;

vector<RGBA> noiseGeneration(vector<RGBA> image, int amount) {
    vector<RGBA> outputImage(image.size());

    random_device randomNumber;
    for ( int i = 0; i < image.size(); i++) {
        int noise = randomNumber() % (2 * amount + 1) - amount;

        outputImage[i].r = std::clamp(image[i].r + noise, 0, 255);
        outputImage[i].g = std::clamp(image[i].g + noise, 0, 255);
        outputImage[i].b = std::clamp(image[i].b + noise, 0, 255);
        outputImage[i].a = image[i].a;
    }

    return outputImage;
}
