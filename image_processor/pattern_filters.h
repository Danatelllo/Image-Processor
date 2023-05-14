#pragma once
#include "Image.h"
class Filter {
    virtual Image Apply(const Image& picture)  = 0;

};