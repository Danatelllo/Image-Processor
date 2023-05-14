#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
using PixelMatrix = std::vector<std::vector<double>>;
struct Image {
public:
    Image() {};
    Image(uint32_t picture_size, uint32_t picture_width, uint32_t picture_height, const std::string& path);
    Image( uint32_t picture_size, uint32_t picture_width, uint32_t picture_height, char* buffer,
          PixelMatrix& picture_pixels);
    Image(uint32_t picture_size, uint32_t picture_width,uint32_t picture_height,
          const char* buffer, const PixelMatrix& picture_pixels);
    PixelMatrix pixels;
    uint32_t width;
    uint32_t height;
    uint32_t size;
    char buf[54];
};
Image UseMatrixFilter(const std::vector<std::vector<double>>& matrix,const Image& picture);
void BasicConvolution(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionLowerFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionUpperFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionRightFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionLeftFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionLowerLeftСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionLowerRightСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionUpperRightСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void ConvolutionUpperLeftСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array, const std::vector<std::vector<double>>& matrix, size_t width, size_t location);
void CopyBuf(char* new_picture, const char* picture);
size_t NewPictureSize(size_t bmp_size_header, size_t bits_per_pixel, size_t width, size_t height);
bool IsNotFramesAndCorners(size_t j, size_t height, size_t width);
bool IsLowerLeftCorner(size_t j, size_t height, size_t width);
bool IsLowerRightCorner(size_t j, size_t height, size_t width);
bool IsUpperRightCorner(size_t j, size_t height, size_t width);
bool IsUpperLeftCorner(size_t j, size_t height, size_t width);
bool IsLeftFrame(size_t j, size_t height, size_t width);
bool IsUpperFrame(size_t j, size_t height, size_t width);
bool IsLowerFrame(size_t j, size_t height, size_t width);
bool IsRightFrame(size_t j, size_t height, size_t width);
