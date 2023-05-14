#pragma once
#include "pattern_filters.h"
class Sharpening : public Filter {
public:
    Image Apply(const Image &picture) override;

private:
    std::vector<std::vector<double>> matrix_ = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};
};