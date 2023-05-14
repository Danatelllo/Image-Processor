#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
class File {
public:
    std::string input_;

private:
    void process_input(std::string& input);
    void ReadFile();
    uint32_t get32(char* buf);
    uint16_t get16(char* buf);
    struct Filter {
        std::string name_filter;
        std::string parameter1;
        std::string parameter2;
    };
    struct InfoHeader {
        uint32_t header_lenght;  // Длина этого заголовка, 4 байта.
        uint32_t width;          // Ширина изображения, 4 байта.
        uint32_t height;         // Высота изображения, 4 байта.
        uint16_t planes;  // Уровень целевого устройства, чтобы это не значило, должен быть 1 байт, 2 байта.
        uint16_t distribution_bites;  // Должно быть 24, 2 байта.
        uint32_t is_comression;       // ожидается 0, 4 байта.;
        uint32_t size_image;          // Размер изображения в байтах, 4 байта.
        uint32_t pixel_per_meterX;  // Разрешение изображения по горизонтали, количество пикселей на метр, 4 байта.
        uint32_t pixel_per_meterY;  // Разрешение изображения по горизонтали, количество пикселей на метр, 4 байта.
        uint32_t clr_number;  // Количество цветов, использованных в изображении, 4 байта.
        uint32_t important_clr;  // Количество важных цветов, 4 байта.
    };
    struct FileHeader {
        uint16_t Type_file;       // Тип нашего изображения, 2 байта, должен быть BM
        uint32_t Size_file;       //Размер нашего изображения, 4 байта.
        uint16_t reserved_word1;  // Зарезервированное слово, должно быть 0, 2 байта
        uint16_t reserved_word2;  // Зарезервированное слово, должно быть 0, 2 байта
        uint32_t start_position;  // Длина от заголовка файла до фактической области данных изображения, 4 байта
    };
    struct Color {
        uint8_t red;
        uint8_t blue;
        uint8_t green;
    };
    std::string name_program_;
    std::string path_input_;
    std::string path_output_;
    std::vector<Filter> filters_;
};