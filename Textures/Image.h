/*
 * Image.h
 *
 *  Created on: Nov 19, 2013
 *      Author: root
 */

#ifndef CGL_IMAGE_H_
#define CGL_IMAGE_H_

#include <SOIL.h>
#include <GL/glew.h>
#include <string>
#include <exception>
#include <sstream>
#include <vector>
#include <memory>
#include "../Buffers/BufferData.h"

namespace cgl {

class ImageReadError: public std::exception {
    uint32_t _i, _j, _c;
public:
    ImageReadError(uint32_t i, uint32_t j, uint32_t c) :
            _i(i), _j(j), _c(c) {
    }

    virtual const char* what() const throw () {
        std::stringstream ss;
        ss << "Exception in class Image: Cannot read element (row, col, chan):("
                << _i << "," << _j << "," << _c << ")" << std::endl;
        return ss.str().c_str();
    }
};

template<typename T>
class Image: public TypedBufferData<T> {

    uint32_t _width, _height, _channels;

public:
    Image(std::string filename);

    Image(uint32_t width, uint32_t height, uint32_t channels) :
            TypedBufferData<T>(width * height * channels), _width(width), _height(
                    height), _channels(channels) {
    }

    static std::shared_ptr<Image > New(std::string filename) {
        return std::make_shared<Image>(filename);
    }

    static std::shared_ptr<Image> New(uint32_t width, uint32_t height,
            uint32_t channels) {
        return std::make_shared<Image>(width, height, channels);
    }

    uint32_t Width() {
        return _width;
    }
    uint32_t Height() {
        return _height;
    }
    uint32_t Channels() {
        return _channels;
    }

    //row i, col j, channel c - opengl specification RGB RGB RGB
    //i*width +j specifies all for pixel (row i,col j) in opengl
    T& At(uint32_t i, uint32_t j, uint32_t c) {
        if (i < _height  && j < _width && c < _channels) {
            return TypedBufferData<T>::_data[(j + i * _width)*_channels
                    + c];
        } else {
            ImageReadError e(i, j, c);
            throw e;
        }
    }

    void Save(std::string filename);
};

//available Images
typedef Image<GLbyte> ByteImage;
typedef std::shared_ptr<ByteImage> ByteImagePtr;

typedef Image<GLubyte> UnsignedByteImage;
typedef std::shared_ptr<UnsignedByteImage> UnsignedByteImagePtr;

typedef Image<GLshort> ShortImage;
typedef std::shared_ptr<ShortImage> ShortImagePtr;

typedef Image<GLushort> UnsignedShortImage;
typedef std::shared_ptr<UnsignedShortImage> UnsignedShortImagePtr;

typedef Image<GLint> IntImage;
typedef std::shared_ptr<IntImage> IntImagePtr;

typedef Image<GLuint> UnsignedIntImage;
typedef std::shared_ptr<UnsignedIntImage> UnsignedIntImagePtr;

typedef Image<GLfloat> FloatImage;
typedef std::shared_ptr<FloatImage> FloatImagePtr;

typedef Image<GLdouble> DoubleImage;
typedef std::shared_ptr<DoubleImage> DoubleImagePtr;

}

#endif /* IMAGE_H_ */
