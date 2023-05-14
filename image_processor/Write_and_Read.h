#pragma once
#include "Image.h"
const size_t BMP_BEGIN_SIZE = 2;
const size_t BMP_BEGIN_WIDTH = 18;
const size_t BMP_BEGIN_HEIGHT = 22;
const size_t BMP_BITS_PER_PIXEL = 24;
const size_t BMP_SIZE_HEADER = 54;
const size_t BMP_BEGIN_BEGIN_B = 0;
const size_t BMP_BEGIN_REVERSED = 6;
const size_t BMP_BEGIN_BITS_PER_PIXEL = 26;
const size_t BMP_BEGIN_CHAR_M = 1;
const size_t BMP_BEGIN_SIZE_OF_DIB_HEADER = 14;
const size_t MAX_VALUE_UINT8 = 255;
uint32_t Get32(const char* buf, size_t begin);
uint8_t Get8(const char* buf, size_t begin);
uint16_t Get16(const char* buf, size_t begin);
Image ReadFile(const std::string& path_input);
void WriteFile(Image& picture, const std::string& path_output);
void ReadPixelArr(Image& picture, std::ifstream& data);
size_t GetOst(size_t width);
void Executor(char* argv[], int argc);
const std::string program_reference = "Hello, user, here you can apply the following filters for your images in BMP format:\n"
    "1) Sharpening make your image clearer.  The input signal is -sharp.\n"
    "2) Crop takes two arguments width and height and cuts your picture. It uses left upper corner of your image. The input signal is -crop, width and height .\n"
    "3) Grayscale converts your image to grayscale. The input signal is -gs.\n"
    "4) Negative converts your image to negative.  The input signal is -negative.\n"
    "5) Edge Detection converts your image to grayscale and if the meaning pixel is less than threshold that it will be white else black. The input signal is -edg and threshold.\n"
    "6) Gaussian Blur blur your image with deep which depends on the blur parameter.  The input signal is -edg and sigma.\n"
    "7) Nikolay creates wavy lines on your image their size depends on the sigma parameter. \n"
    "First of all, you need type a name program, then input file your picture, output file for your new image and order filters with their parameters.";