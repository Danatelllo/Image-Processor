
#include "Negative.h"

Image Negative::Apply(const Image &picture) {
    Image new_picture = Image(picture.size, picture.width, picture.height, picture.buf,
                              picture.pixels);
    for (auto & pixel : new_picture.pixels) {
        pixel[0] = 1 - pixel[0];
        pixel[1] = 1 - pixel[1];
        pixel[2] = 1 - pixel[2];
    }

    return new_picture;
}

