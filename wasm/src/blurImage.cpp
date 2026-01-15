#include <vector>
#include <cmath>
#include <algorithm>
#include "greyscaleImage.hpp"

std::vector<RGBA> blurImage(std::vector<RGBA> image, int width, int height) {
    int kernelSize = std::min(width, height) / 50;
    if (kernelSize % 2 == 0) kernelSize++;
    if (kernelSize < 3) kernelSize = 3;
    int offset = kernelSize / 2;
    double kernelSum = 0;
    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));

    double sigma = kernelSize / 6.0;

    for (int i = 0; i < kernelSize; i++) {
        for (int j = 0; j < kernelSize; j++) {
            int distX = i - offset;
            int distY = j - offset;

            double euclideanDistanceSqrd = (distX * distX) + (distY * distY);
            double gaussianValue = exp(-euclideanDistanceSqrd / (2 * sigma * sigma));
            kernel[i][j] = gaussianValue;

            kernelSum += kernel[i][j];
        }
    }

    std::vector<RGBA> blurredImage(image.size());

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double sumR = 0;
            double sumG = 0;
            double sumB = 0;
            double sumA = 0;

            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    int neighborX = std::max(0, std::min(x + kx, width - 1));
                    int neighborY = std::max(0, std::min(y + ky, height - 1));

                    int neighborIndex = neighborY * width + neighborX;
                    RGBA pixel = image[neighborIndex];

                    double weight = kernel[ky + offset][kx + offset];

                    sumR += pixel.r * weight;
                    sumG += pixel.g * weight;
                    sumB += pixel.b * weight;
                    sumA += pixel.a * weight;

                }
            }

            int outputIndex = y * width + x;
            blurredImage[outputIndex].r = sumR / kernelSum;
            blurredImage[outputIndex].g = sumG / kernelSum;
            blurredImage[outputIndex].b = sumB / kernelSum;
            blurredImage[outputIndex].a = sumA / kernelSum;
        }
    }

    return blurredImage;
}
