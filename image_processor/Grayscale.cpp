#include "Grayscale.h"
Image Grayscale::Apply(const Image& picture) {
    Image new_picture = Image(picture.size, picture.width, picture.height, picture.buf,
                              picture.pixels);
    for (auto& pixel : new_picture.pixels) {
        pixel[0] = pixel[1] = pixel[2] =
            0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
    }
    return new_picture;
}