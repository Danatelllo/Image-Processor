#pragma once
#include "pattern_filters.h"
class Grayscale : public Filter {
public:
    Image Apply(const Image& picture) override;
};
