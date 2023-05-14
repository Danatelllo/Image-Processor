#include "Edge_detection.h"
#include "Grayscale.h"

Image EdgeDetection::Apply(const Image& picture) {
    Grayscale filter;
    Image new_picture = filter.Apply(picture);
    new_picture = UseMatrixFilter(matrix_, new_picture);
    for (auto& pixel : new_picture.pixels) {
        if (pixel[0] > threshold_) {
            pixel[0] = pixel[1] = pixel[2] = 1;
        } else {
            pixel[0] = pixel[1] = pixel[2] = 0;
        }
    }
    return new_picture;
}
