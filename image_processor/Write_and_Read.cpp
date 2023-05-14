#include "Write_and_Read.h"
#include "Image.h"
#include "Edge_detection.h"
#include "Crop.h"
#include "Grayscale.h"
#include "Negative.h"
#include "Sharpening.h"
#include "exception"
#include "Blur.h"
#include "Nikolay.h"
uint8_t Get8(const char* buf, size_t begin) {
    return static_cast<uint8_t>(static_cast<uint8_t>(buf[begin]));
}
uint16_t Get16(const char* buf, size_t begin) {
    return static_cast<uint32_t>(static_cast<uint8_t>(buf[begin])) |
           static_cast<uint32_t>(static_cast<uint8_t>(buf[begin + 1])) << 8;
}
uint32_t Get32(const char* buf, size_t begin) {
    return static_cast<uint32_t>(static_cast<uint8_t>(buf[begin])) |
           static_cast<uint32_t>(static_cast<uint8_t>(buf[begin + 1])) << 8 |
           static_cast<uint32_t>(static_cast<uint8_t>(buf[begin + 2])) << 16 |
           static_cast<uint32_t>(static_cast<uint8_t>(buf[begin + 3])) << 24;
}
void Set32(uint32_t data, char* buf, size_t begin) {
    buf[begin] = static_cast<char>(data);
    buf[begin + 1] = static_cast<char>(data >> 8);
    buf[begin + 2] = static_cast<char>(data >> 16);
    buf[begin + 3] = static_cast<char>(data >> 24);
}
void WriteFile(Image& picture, const std::string& path_output) {
    std::ofstream answer(path_output);
    if (!answer.is_open()) {
        throw std::exception();
    }
    Set32(picture.size, picture.buf, BMP_BEGIN_SIZE);
    Set32(picture.width, picture.buf, BMP_BEGIN_WIDTH);
    Set32(picture.height, picture.buf, BMP_BEGIN_HEIGHT);
    char reader[3];
    answer.write(picture.buf, BMP_SIZE_HEADER);
    for (size_t j = 0; j < picture.height; ++j) {
        for (size_t i = 0; i < picture.width; ++i) {
            reader[0] = static_cast<char>(picture.pixels[picture.width * j + i][0] * MAX_VALUE_UINT8);
            reader[1] = static_cast<char>(picture.pixels[picture.width * j + i][1] * MAX_VALUE_UINT8);
            reader[2] = static_cast<char>(picture.pixels[picture.width * j + i][2] * MAX_VALUE_UINT8);
            answer.write(reader, 3);
        }
        reader[0] = 0;
        for (size_t k = 0; k < GetOst(picture.width); ++k) {
            answer.write(reader, 1);
        }
    }
}
Image ReadFile(const std::string& path_input) {
    std::ifstream data(path_input);
    char buffer[BMP_SIZE_HEADER];
    if (!data.is_open()) {
        throw std::exception();
    }
    data.read(buffer, BMP_SIZE_HEADER);
    if (Get8(buffer, BMP_BEGIN_BEGIN_B) != 'B' || Get8(buffer, BMP_BEGIN_CHAR_M) != 'M') {
        throw std::exception();
    }
    if (Get32(buffer, BMP_BEGIN_REVERSED) != 0) {
        throw std::exception();
    }
    if (Get32(buffer, BMP_BEGIN_SIZE_OF_DIB_HEADER) == BMP_SIZE_HEADER) {
        throw std::exception();
    }
    if (Get16(buffer, BMP_BEGIN_BITS_PER_PIXEL) == BMP_BITS_PER_PIXEL) {
        throw std::exception();
    }
    Image picture = Image(Get32(buffer, BMP_BEGIN_SIZE), Get32(buffer, BMP_BEGIN_WIDTH),
                          Get32(buffer, BMP_BEGIN_HEIGHT), path_input);
    ReadPixelArr(picture, data);
    return picture;
}
void ReadPixelArr(Image& picture, std::ifstream& data) {
    char reader[3];
    for (size_t j = 0; j < picture.height; ++j) {
        for (size_t i = 0; i < picture.width; ++i) {
            data.read(reader, 3);
            std::vector<double> pixel;
            pixel.push_back((static_cast<uint8_t>(reader[0]) / static_cast<double>(MAX_VALUE_UINT8)));
            pixel.push_back((static_cast<uint8_t>(reader[1]) / static_cast<double>(MAX_VALUE_UINT8)));
            pixel.push_back((static_cast<uint8_t>(reader[2]) / static_cast<double>(MAX_VALUE_UINT8)));
            picture.pixels.push_back(pixel);
        }
        reader[0] = 0;
        for (size_t k = 0; k < GetOst(picture.width); ++k) {
            data.read(reader, 1);
        }
    }

}
size_t GetOst(size_t width) {
    return (4 - (3 * width) % 4) % 4;
}
void Executor(char* argv[], int argc) {
    if (argc <= 2) {
        std::cout << program_reference << '\n';
        return;
    }
    try {
        Image photo = ReadFile(std::string(argv[1]));
        for (int j = 3; j < argc; ++j) {
            if (std::string(argv[j]) == "-crop") {
                try {
                    Crop filter(std::stoi(argv[j + 1]), std::stoi(argv[j + 2]));
                    photo = filter.Apply(photo);
                    j += 2;
                } catch (std::exception& e) {
                    std::cout << "parameters of crop are not integer numbers" << '\n';
                }
            } else if (std::string(argv[j]) == "-gs") {
                Grayscale filter;
                photo = filter.Apply(photo);
            } else if (std::string(argv[j]) == "-neg") {
                Negative filter;
                photo = filter.Apply(photo);
            } else if (std::string(argv[j]) == "-sharp") {
                Sharpening filter;
                photo = filter.Apply(photo);
            } else if (std::string(argv[j]) == "-edge") {
                try {
                    EdgeDetection filter(std::stod(argv[j + 1]));
                    photo = filter.Apply(photo);
                    ++j;
                } catch (std::exception &e) {
                    std::cout << "parameter of edge is not integer numbers" << '\n';
                }
            } else if (std::string(argv[j]) == "-blur") {
                try {
                    Blur filter(std::stod(argv[j + 1]));
                    photo = filter.Apply(photo);
                    ++j;
                } catch (std::exception& e) {
                    std::cout << "parameter of blur is not integer numbers" << '\n';
                }
            } else if (std::string(argv[j]) == "-Nikolay") {
                try {
                    Nikolay filter(std::stod(argv[j + 1]));
                    photo = filter.Apply(photo);
                    ++j;
                } catch (std::exception& e) {
                    std::cout << "parameter of Nikolay is not integer numbers" << '\n';
                }
            }
        }
        WriteFile(photo, argv[2]);
    } catch(std::exception& e) {
        std::cout << "It is not a BMP file or bad input path or output path" << '\n';
    }
}