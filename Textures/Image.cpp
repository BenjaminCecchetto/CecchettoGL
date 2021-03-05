/*
 * ImageLoader.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: root
 */
#include "Image.h"
#include <SOIL.h>
#include <GL/glew.h>
#include <string>
#include <exception>
#include <sstream>

#include <istream>
#include <fstream>
#include <iostream>

namespace cgl {

class ImageLoadError: public std::exception {
    std::string _filename;
public:
    ImageLoadError(std::string filename) :
            _filename(filename) {
    }

    virtual const char* what() const throw () {
        std::stringstream ss;
        ss << "Exception in class Image: Cannot load image file " << _filename
                << std::endl;
        return ss.str().c_str();
    }
};

//file loader for normal images
template<> Image<uint8_t>::Image(std::string filename) {
    int width, height, channels;
    uint8_t* data = SOIL_load_image(filename.c_str(), &width, &height,
            &channels, SOIL_LOAD_AUTO);

    if (data != 0) {
        _width = width;
        _height = height;
        _channels = channels;

        _data = std::vector<uint8_t>(data, data + width * height * channels);
    } else {
        ImageLoadError e(filename);
        throw e;
    }
}

template<>
void Image<uint8_t>::Save(std::string filename) {
    SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, _width, _height,
            _channels, (const uint8_t*) Data());
}

template<>
void Image<float>::Save(std::string filename) {
    std::ofstream myfile;
    myfile.open (filename, std::ios::out | std::ios::binary);

    myfile.write((char*)&_width , sizeof(uint32_t));
    myfile.write((char*)&_height, sizeof(uint32_t));
    myfile.write((char*)&_channels, sizeof(uint32_t));

    for (uint32_t i = 0; i < _width*_height*_channels; i++)
        myfile.write((char*)&_data[i], sizeof(float));

    myfile.close();

}

}
