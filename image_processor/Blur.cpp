#include "Blur.h"
void Blur::MatrixBlurring(double sigma, bool width_blur, PixelMatrix& pixel_array,const PixelMatrix& picture_pixels, uint32_t width) {
    size_t radius = ceil(3 * sigma);
    double element_form1 = (2.0 * sigma * sigma);
    double element_form2 = sqrt(2 * M_PI * sigma * sigma);
    bool condition1;
    bool condition2;
    size_t from_where_we_add1;
    size_t from_where_we_add2;
    std::vector<double> coefficients;
    for (size_t k = 0; k < radius; ++k) {
        coefficients.push_back(exp(-(static_cast<double>(k * k) / element_form1)) / element_form2);
    }
    for (size_t j = 0; j < picture_pixels.size(); ++j) {
        pixel_array[j][0] = 0;
        pixel_array[j][1] = 0;
        pixel_array[j][2] = 0;
        for (size_t k = 0; k < radius; ++k) {
            if (width_blur) {
                condition1 = (j > k && (j - k) % width != 0 && j % width != 0);
                condition2 = ((j + k + 1) % width != 0 && j + k < picture_pixels.size() && j + 1 % width != 0);
                from_where_we_add1 = j - k;
                from_where_we_add2 = j + k;
            } else {
                condition1 = (j > k * width);
                condition2 = (j + k * width) < picture_pixels.size() - 1;
                from_where_we_add1 = j - k * width;
                from_where_we_add2 = j + k * width;
            }
            for (size_t i = 0; i < 3; ++i) {
                if (k == 0) {
                    pixel_array[j][i] = coefficients[k] * picture_pixels[j][i];
                } else {
                    if (condition1) {
                        pixel_array[j][i] += coefficients[k] * picture_pixels[from_where_we_add1][i];
                    } else {
                        pixel_array[j][i] += coefficients[k] * picture_pixels[j][i];
                    }
                    if (condition2) {
                        pixel_array[j][i] += coefficients[k] * picture_pixels[from_where_we_add2][i];
                    } else {
                        pixel_array[j][i] += coefficients[k] * picture_pixels[j][i];
                    }
                }
            }
        }
    }
}

Image Blur::Apply(const Image &picture) {
    Image new_picture = Image(picture.size, picture.width, picture.height, picture.buf,
                              picture.pixels);
    PixelMatrix pixel_array = picture.pixels;
    MatrixBlurring(sigma_, true, pixel_array, picture.pixels, picture.width);
    MatrixBlurring(sigma_, false, new_picture.pixels, pixel_array, picture.width);
    return new_picture;
}