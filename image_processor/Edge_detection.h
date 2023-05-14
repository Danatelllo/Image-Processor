#pragma once
#include "pattern_filters.h"
class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(const double& number) : threshold_(number) {};

    Image Apply(const Image& picture) override;

private:
    const double threshold_;
    std::vector<std::vector<double>> matrix_ = {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};
};