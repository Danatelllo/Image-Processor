#pragma once
#include "pattern_filters.h"
#include "Write_and_Read.h"
class Crop : public Filter {
public:
    Crop(size_t new_width, size_t new_height): new_width_(new_width), new_height_(new_height) {};
    Image Apply(const Image& picture) override;

private:
    size_t new_width_;
    size_t new_height_;
};