#include "Nikolay.h"
Image Nikolay::Apply(const Image& picture) {
    Image new_picture = Image(picture.size, picture.width, picture.height,picture.buf,  picture.pixels);
    for (size_t j = 0; j < picture.height; ++j) {
        for (size_t i = 0; i < picture.width; ++i) {
            for (size_t k = 0; k < 3; ++k) {
                auto new_location = static_cast<size_t>(i + sigma_*sin((j * (2 * M_PI) / 20)));
                if ((j*picture.width + new_location) < picture.pixels.size()) {
                    new_picture.pixels[(j*picture.width + i)][k] = picture.pixels[(j*picture.width + new_location)][k];
                }
            }
        }
    }
    return new_picture;
}
