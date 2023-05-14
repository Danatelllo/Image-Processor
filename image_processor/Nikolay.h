#pragma once
#include "pattern_filters.h"
class Nikolay : public Filter {
public:
    Image Apply(const Image& picture) override;
    Nikolay(double sigma) {
        sigma_ = sigma;
    }

private:
    double sigma_;
};