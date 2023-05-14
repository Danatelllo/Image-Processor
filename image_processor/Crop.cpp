#include "Crop.h"
#include "Write_and_Read.h"
Image Crop::Apply(const Image& picture) {
    if (new_width_ > picture.width && new_height_ > picture.height) {
        return picture;
    }
    Image new_picture;
    new_picture.height = new_height_ < picture.height ? new_height_ : picture.height;
    new_picture.width = new_width_ < picture.width ? new_width_ : picture.width;
    new_picture.size = NewPictureSize(BMP_SIZE_HEADER, BMP_BITS_PER_PIXEL, picture.width, picture.height);
    PixelMatrix new_pixels;
    CopyBuf(new_picture.buf, picture.buf);
    for (size_t j = (picture.height - new_picture.height); j < picture.height; ++j) {
        for (size_t i = 0; i < new_picture.width; ++i) {
            new_picture.pixels.push_back(picture.pixels[j * picture.height + i]);
        }
    }
    return new_picture;
}
