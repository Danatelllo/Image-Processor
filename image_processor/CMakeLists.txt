cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_catch(image_processor
        image_processor.cpp
        Image.h
        pattern_filters.h
        Crop.h Crop.cpp Image.h Image.cpp Grayscale.h Grayscale.cpp Sharpening.h Sharpening.cpp Edge_detection.h Edge_detection.cpp Write_and_Read.h Write_and_Read.cpp Negative.cpp Negative.h Nikolay.cpp Nikolay.h  Blur.cpp Blur.h)
add_catch(test_image_processor test.cpp)