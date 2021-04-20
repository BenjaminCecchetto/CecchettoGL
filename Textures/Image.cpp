/*
 * ImageLoader.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: root
 */
#include "Image.h"

#include <GL/glew.h>
#include <SDL_Image.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

namespace cgl {

class ImageLoadError : public std::exception {
  std::string _filename;

 public:
  ImageLoadError(std::string filename) : _filename(filename) {}

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Exception in class Image: Cannot load image file " << _filename
       << std::endl;
    return ss.str().c_str();
  }
};

// file loader for normal images
template <>
Image<uint8_t>::Image(std::string filename) {
  auto img = IMG_Load(filename.c_str());

  if (img == nullptr) {
    std::cout << "Cannot load image: " << filename << std::endl;
    return;
  }

  uint8_t* data = static_cast<uint8_t*>(img->pixels);

  if (data != 0) {
    _width = img->w;
    _height = img->h;
    _channels = img->format->BytesPerPixel;

    _data = std::vector<uint8_t>(data, data + _width * _height * _channels);
    SDL_FreeSurface(img);
  } else {
    ImageLoadError e(filename);
    throw e;
  }
}

template <>
void Image<uint8_t>::Save(std::string filename) {
  // TODO SAVE
}

template <>
void Image<float>::Save(std::string filename) {
  std::ofstream myfile;
  myfile.open(filename, std::ios::out | std::ios::binary);

  myfile.write((char*)&_width, sizeof(uint32_t));
  myfile.write((char*)&_height, sizeof(uint32_t));
  myfile.write((char*)&_channels, sizeof(uint32_t));

  for (uint32_t i = 0; i < _width * _height * _channels; i++)
    myfile.write((char*)&_data[i], sizeof(float));

  myfile.close();
}

}  // namespace cgl
