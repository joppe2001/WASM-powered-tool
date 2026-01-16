#include <vector>
#include <algorithm>
#include "greyscaleImage.hpp"

std::vector<RGBA> boxBlurImage(std::vector<RGBA> image, int width, int height, int amount) {
    int radius = amount / 2;
    if (radius < 1) radius = 1;

    std::vector<RGBA> tempImage(image.size());
    std::vector<RGBA> outputImage(image.size());

    // Horizontal pass
    for (int y = 0; y < height; y++) {
        int sumR = 0, sumG = 0, sumB = 0, sumA = 0;
        int windowSize = 0;

        // Initialize window with first (radius + 1) pixels
        for (int i = 0; i <= radius && i < width; i++) {
            int idx = y * width + i;
            sumR += image[idx].r;
            sumG += image[idx].g;
            sumB += image[idx].b;
            sumA += image[idx].a;
            windowSize++;
        }

        for (int x = 0; x < width; x++) {
            // Store average
            tempImage[y * width + x].r = sumR / windowSize;
            tempImage[y * width + x].g = sumG / windowSize;
            tempImage[y * width + x].b = sumB / windowSize;
            tempImage[y * width + x].a = sumA / windowSize;

            // Remove pixel leaving on left (for next iteration)
            int leftLeaving = x - radius;
            if (leftLeaving >= 0) {
                int idx = y * width + leftLeaving;
                sumR -= image[idx].r;
                sumG -= image[idx].g;
                sumB -= image[idx].b;
                sumA -= image[idx].a;
                windowSize--;
            }

            // Add pixel entering on right (for next iteration)
            int rightEntering = x + radius + 1;
            if (rightEntering < width) {
                int idx = y * width + rightEntering;
                sumR += image[idx].r;
                sumG += image[idx].g;
                sumB += image[idx].b;
                sumA += image[idx].a;
                windowSize++;
            }
        }
    }

    // Vertical pass
    for (int x = 0; x < width; x++) {
        int sumR = 0, sumG = 0, sumB = 0, sumA = 0;
        int windowSize = 0;

        // Initialize window with first (radius + 1) pixels
        for (int i = 0; i <= radius && i < height; i++) {
            int idx = i * width + x;
            sumR += tempImage[idx].r;
            sumG += tempImage[idx].g;
            sumB += tempImage[idx].b;
            sumA += tempImage[idx].a;
            windowSize++;
        }

        for (int y = 0; y < height; y++) {
            // Store average
            outputImage[y * width + x].r = sumR / windowSize;
            outputImage[y * width + x].g = sumG / windowSize;
            outputImage[y * width + x].b = sumB / windowSize;
            outputImage[y * width + x].a = sumA / windowSize;

            // Remove pixel leaving on top (for next iteration)
            int topLeaving = y - radius;
            if (topLeaving >= 0) {
                int idx = topLeaving * width + x;
                sumR -= tempImage[idx].r;
                sumG -= tempImage[idx].g;
                sumB -= tempImage[idx].b;
                sumA -= tempImage[idx].a;
                windowSize--;
            }

            // Add pixel entering on bottom (for next iteration)
            int bottomEntering = y + radius + 1;
            if (bottomEntering < height) {
                int idx = bottomEntering * width + x;
                sumR += tempImage[idx].r;
                sumG += tempImage[idx].g;
                sumB += tempImage[idx].b;
                sumA += tempImage[idx].a;
                windowSize++;
            }
        }
    }

    return outputImage;
}
