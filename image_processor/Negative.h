#pragma once
#include "pattern_filters.h"
class Negative : public Filter {
public:
    Image Apply(const Image& picture) override ;
};
