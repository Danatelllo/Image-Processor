#include "Sharpening.h"
#include "Image.h"

Image Sharpening::Apply(const Image& picture) {
    Image new_picture = UseMatrixFilter(matrix_, picture);
    return new_picture;
}

