#include <vector>
#include <cmath>
#include <algorithm>
#include "greyscaleImage.hpp"

std::vector<RGBA> blurImage(std::vector<RGBA> image, int width, int height, int amount) {
    int kernelSize = amount;
    if (kernelSize % 2 == 0) kernelSize++;
    if (kernelSize < 3) kernelSize = 3;
    int offset = kernelSize / 2;

    // Build 1D Gaussian kernel
    double sigma = kernelSize / 6.0;
    std::vector<double> kernel(kernelSize);
    double kernelSum = 0;

    for (int i = 0; i < kernelSize; i++) {
        int dist = i - offset;
        double gaussianValue = exp(-(dist * dist) / (2 * sigma * sigma));
        kernel[i] = gaussianValue;
        kernelSum += gaussianValue;
    }

    // Intermediate image for horizontal pass
    std::vector<RGBA> tempImage(image.size());

    // Pass 1: Horizontal blur
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double sumR = 0;
            double sumG = 0;
            double sumB = 0;
            double sumA = 0;

            for (int kx = -offset; kx <= offset; kx++) {
                int neighborX = std::max(0, std::min(x + kx, width - 1));
                int neighborIndex = y * width + neighborX;
                RGBA pixel = image[neighborIndex];
                double weight = kernel[kx + offset];

                sumR += pixel.r * weight;
                sumG += pixel.g * weight;
                sumB += pixel.b * weight;
                sumA += pixel.a * weight;
            }

            int outputIndex = y * width + x;
            tempImage[outputIndex].r = sumR / kernelSum;
            tempImage[outputIndex].g = sumG / kernelSum;
            tempImage[outputIndex].b = sumB / kernelSum;
            tempImage[outputIndex].a = sumA / kernelSum;
        }
    }

    // Final output image
    std::vector<RGBA> blurredImage(image.size());

    // Pass 2: Vertical blur
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double sumR = 0;
            double sumG = 0;
            double sumB = 0;
            double sumA = 0;

            for (int ky = -offset; ky <= offset; ky++) {
                int neighborY = std::max(0, std::min(y + ky, height - 1));
                int neighborIndex = neighborY * width + x;
                RGBA pixel = tempImage[neighborIndex];
                double weight = kernel[ky + offset];

                sumR += pixel.r * weight;
                sumG += pixel.g * weight;
                sumB += pixel.b * weight;
                sumA += pixel.a * weight;
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
