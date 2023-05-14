#pragma once
#include "pattern_filters.h"
class Blur : public Filter {
public:
    explicit Blur(double sigma) {
        sigma_ = sigma;
    }
    Image Apply(const Image& picture) override;
    static void MatrixBlurring(double sigma, bool width_blur, PixelMatrix& pixel_array,const PixelMatrix& picture_pixels, uint32_t width);

private:
    double sigma_;
};