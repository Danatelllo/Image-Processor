#include "Image.h"
#include "Write_and_Read.h"
Image::Image(uint32_t picture_size, uint32_t picture_width, uint32_t picture_height, const std::string& path) {
    size = picture_size;
    width = picture_width;
    height = picture_height;
    std::ifstream data(path);
    data.read(buf, BMP_SIZE_HEADER);
}

Image::Image(uint32_t picture_size, uint32_t picture_width, uint32_t picture_height, char* buffer,
             PixelMatrix& picture_pixels) {
    size = picture_size;
    width = picture_width;
    height = picture_height;
    pixels = picture_pixels;
    CopyBuf(buf, buffer);
}

Image::Image(const uint32_t picture_size, const uint32_t picture_width, const uint32_t picture_height,
             const char* buffer, const PixelMatrix& picture_pixels) {
    size = picture_size;
    width = picture_width;
    height = picture_height;
    pixels = picture_pixels;
    CopyBuf(buf, buffer);
}
void CopyBuf(char* buf, const char* buffer) {
    for (size_t j = 0; j < BMP_SIZE_HEADER; ++j) {
        buf[j] = buffer[j];
    }
}
void BasicConvolution(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                      const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location - width - 1][i] + matrix[0][1] * pixel_array[location - width][i] +
                matrix[0][2] * pixel_array[location - width + 1][i] + matrix[1][0] * pixel_array[location - 1][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location + 1][i] +
                matrix[2][0] * pixel_array[location + width - 1][i] + matrix[2][1] * pixel_array[location + width][i] +
                matrix[2][2] * pixel_array[location + width + 1][i],
            0.0, 1.0);
    }
}
void ConvolutionLowerLeftСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                                const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location][i] + matrix[0][1] * pixel_array[location][i] +
                matrix[0][2] * pixel_array[location + 1][i] + matrix[1][0] * pixel_array[location][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location + 1][i] +
                matrix[2][0] * pixel_array[location + width - 1][i] + matrix[2][1] * pixel_array[location + width][i] +
                matrix[2][2] * pixel_array[location + width + 1][i],
            0.0, 1.0);
    }
}
void ConvolutionLowerFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                           const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location][i] + matrix[0][1] * pixel_array[location][i] +
                matrix[0][2] * pixel_array[location + 1][i] + matrix[1][0] * pixel_array[location][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location + 1][i] +
                matrix[2][0] * pixel_array[location + width - 1][i] + matrix[2][1] * pixel_array[location + width][i] +
                matrix[2][2] * pixel_array[location + width + 1][i],
            0.0, 1.0);
    }
}
void ConvolutionLeftFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                          const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location][i] + matrix[0][1] * pixel_array[location - width][i] +
                matrix[0][2] * pixel_array[location - width + 1][i] + matrix[1][0] * pixel_array[location][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location + 1][i] +
                matrix[2][0] * pixel_array[location][i] + matrix[2][1] * pixel_array[location + width][i] +
                matrix[2][2] * pixel_array[location + width + 1][i],
            0.0, 1.0);
    }
}
void ConvolutionRightFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                           const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location - width][i] + matrix[0][1] * pixel_array[location - width][i] +
                matrix[0][2] * pixel_array[location - width - 1][i] + matrix[1][0] * pixel_array[location - 1][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location - 1][i] +
                matrix[2][0] * pixel_array[location + width - 1][i] + matrix[2][1] * pixel_array[location + width][i] +
                matrix[2][2] * pixel_array[location + width][i],
            0.0, 1.0);
    }
}
void ConvolutionLowerRightСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                                 const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(matrix[0][0] * pixel_array[location][i] + matrix[0][1] * pixel_array[location][i] +
                                  matrix[0][2] * pixel_array[location][i] + matrix[1][0] * pixel_array[location][i] +
                                  matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location][i] +
                                  matrix[2][0] * pixel_array[location + width][i] +
                                  matrix[2][1] * pixel_array[location + width][i] +
                                  matrix[2][2] * pixel_array[location + width][i],
                              0.0, 1.0);
    }
}
void ConvolutionUpperFrame(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                           const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location - width - 1][i] + matrix[0][1] * pixel_array[location - width][i] +
                matrix[0][2] * pixel_array[location - width][i] + matrix[1][0] * pixel_array[location - 1][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location][i] +
                matrix[2][0] * pixel_array[location - 1][i] + matrix[2][1] * pixel_array[location][i] +
                matrix[2][2] * pixel_array[location][i],
            0.0, 1.0);
    }
}
void ConvolutionUpperLeftСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                                const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location - width][i] + matrix[0][1] * pixel_array[location - width][i] +
                matrix[0][2] * pixel_array[location - width + 1][i] + matrix[1][0] * pixel_array[location][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location + 1][i] +
                matrix[2][0] * pixel_array[location][i] + matrix[2][1] * pixel_array[location][i] +
                matrix[2][2] * pixel_array[location][i],
            0.0, 1.0);
    }
}
void ConvolutionUpperRightСorner(std::vector<double>& pixel, const std::vector<std::vector<double>>& pixel_array,
                                 const std::vector<std::vector<double>>& matrix, size_t width, size_t location) {
    for (size_t i = 0; i < pixel.size(); ++i) {
        pixel[i] = std::clamp(
            matrix[0][0] * pixel_array[location - width - 1][i] + matrix[0][1] * pixel_array[location - width][i] +
                matrix[0][2] * pixel_array[location - width][i] + matrix[1][0] * pixel_array[location - 1][i] +
                matrix[1][1] * pixel_array[location][i] + matrix[1][2] * pixel_array[location][i] +
                matrix[2][0] * pixel_array[location - 1][i] + matrix[2][1] * pixel_array[location][i] +
                matrix[2][2] * pixel_array[location][i],
            0.0, 1.0);
    }
}
bool IsNotFramesAndCorners(size_t j, size_t height, size_t width) {
    return (j > width && j % width != 0 && (j + 1) % width != 0 && j < (width * (height - 1) - 1));
}
bool IsLowerLeftCorner(size_t j, size_t height, size_t width) {
    return j == 0;
}
bool IsLowerRightCorner(size_t j, size_t height, size_t width) {
    return j == width - 1;
}
bool IsUpperRightCorner(size_t j, size_t height, size_t width) {
    return j == width * height - 1;
}
bool IsUpperLeftCorner(size_t j, size_t height, size_t width) {
    return j == width * (height - 1);
}
bool IsLeftFrame(size_t j, size_t height, size_t width) {
    return j % width == 0;
}
bool IsUpperFrame(size_t j, size_t height, size_t width) {
    return j > (width - 1) * height - 1;
}
bool IsLowerFrame(size_t j, size_t height, size_t width) {
    return j < width;
}
bool IsRightFrame(size_t j, size_t height, size_t width) {
    return (j + 1) % width == 0;
}

Image UseMatrixFilter(const std::vector<std::vector<double>>& matrix, const Image& picture) {
    Image new_picture = Image(picture.size, picture.width, picture.height, picture.buf, picture.pixels);
    for (size_t j = 0; j < new_picture.pixels.size(); ++j) {
        if (IsLowerLeftCorner(j, picture.height, picture.width)) {
            ConvolutionLowerLeftСorner(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsLowerRightCorner(j, picture.height, picture.width)) {
            ConvolutionLowerRightСorner(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsUpperLeftCorner(j, picture.height, picture.width)) {
            ConvolutionUpperLeftСorner(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsUpperRightCorner(j, picture.height, picture.width)) {
            ConvolutionUpperRightСorner(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsNotFramesAndCorners(j, picture.height, picture.width)) {
            BasicConvolution(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsLowerFrame(j, picture.height, picture.width)) {
            ConvolutionLowerFrame(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsUpperFrame(j, picture.height, picture.width)) {
            ConvolutionUpperFrame(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsLeftFrame(j, picture.height, picture.width)) {
            ConvolutionLeftFrame(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        } else if (IsRightFrame(j, picture.height, picture.width)) {
            ConvolutionRightFrame(new_picture.pixels[j], picture.pixels, matrix, picture.width, j);
        }
    }

    return new_picture;
}
size_t NewPictureSize(const size_t bmp_size_header, const size_t bits_per_pixel, const size_t width,
                      const size_t height) {
    return bmp_size_header + ((bits_per_pixel * width + 31) / 32) * 4 * height;
}