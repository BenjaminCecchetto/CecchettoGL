/*
 * Texture2D.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: cecchett
 */

#include "Texture2D.h"
#include <GL/glew.h>
#include <iostream>
#include <exception>
#include "Texture.h"
#include "Image.h"
#include "../GLInfo.h"

namespace cgl {

uint32_t DataFormatToNumChannels(GLenum dataFormat) {
    switch (dataFormat) {
    case GL_RED:
    case GL_DEPTH_COMPONENT:
        return 1;
    case GL_RG:
        return 2;
    case GL_RGB:
    case GL_RGB32F:
        return 3;
    case GL_RGBA:
        return 4;
    default:
        return 1;
    }

    return 0;
}

GLenum NumChannelsToDataFormat(uint32_t numChannels) {
    switch (numChannels) {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        return GL_RED;
    }

    return 0;
}

Texture2D::Texture2D(int level, int internalFormat, int width, int height,
        int dataFormat, int dataType, void* data, int minFilter, int magFilter,
        int wrapS, int wrapT) :
        Texture() {
    target = GL_TEXTURE_2D;
    _format = internalFormat;
    _width = width;
    _height = height;
    _channels = 1;
    _level = level;
    Bind();

    // allocate memory and/or send data
    if (data == NULL) {
        dataFormat = GL_RGBA;
        dataType = GL_UNSIGNED_BYTE;
    }

    if (internalFormat == GL_DEPTH_COMPONENT
            || internalFormat == GL_DEPTH_COMPONENT16
            || internalFormat == GL_DEPTH_COMPONENT24
            || internalFormat == GL_DEPTH_COMPONENT32
            || internalFormat == GL_DEPTH_COMPONENT32F)
        dataFormat = GL_DEPTH_COMPONENT;

    _channels = DataFormatToNumChannels(dataFormat);

    glTexImage2D(target, level, internalFormat, width, height, 0, dataFormat,
            dataType, data);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    //wrap
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    //filtering
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    if (minFilter == GL_NEAREST_MIPMAP_NEAREST
            || minFilter == GL_NEAREST_MIPMAP_LINEAR
            || minFilter == GL_LINEAR_MIPMAP_NEAREST
            || minFilter == GL_LINEAR_MIPMAP_LINEAR) {
        glGenerateMipmap(target);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }

    if (magFilter == GL_NEAREST_MIPMAP_NEAREST
            || magFilter == GL_NEAREST_MIPMAP_LINEAR
            || magFilter == GL_LINEAR_MIPMAP_NEAREST
            || magFilter == GL_LINEAR_MIPMAP_LINEAR) {
        std::cerr << "Texture2D: Magnification filter cannot be mipmap."
                << std::endl;
        ImproperTexParameter e("Texture2D",
                "Magnification filter cannot be mipmap.");
        throw e;
    }
}

Texture2D::Texture2D(int level, int internalFormat, int width, int height,
        int minFilter, int magFilter, int wrapS, int wrapT) :
        Texture2D(level, internalFormat, width, height, internalFormat,
        GL_UNSIGNED_BYTE, NULL, minFilter, magFilter, wrapS, wrapT) {

}

Texture2DPtr Texture2D::New(int level, int internalFormat,
        UnsignedByteImagePtr image, int minFilter, int magFilter, int wrapS,
        int wrapT) {
    GLenum dataFormat = NumChannelsToDataFormat(image->Channels());

    return std::make_shared<Texture2D>(level, internalFormat, image->Width(),
            image->Height(), dataFormat, GL_UNSIGNED_BYTE, image->Data(),
            minFilter, magFilter, wrapS, wrapT);

}

Texture2DPtr Texture2D::New(int level, int internalFormat, FloatImagePtr image,
        int minFilter, int magFilter, int wrapS, int wrapT) {
    GLenum dataFormat = NumChannelsToDataFormat(image->Channels());

    return std::make_shared<Texture2D>(level, internalFormat, image->Width(),
            image->Height(), dataFormat, GL_FLOAT, image->Data(), minFilter,
            magFilter, wrapS, wrapT);

}

UnsignedByteImagePtr Texture2D::GetImage() {
    UnsignedByteImagePtr im = UnsignedByteImage::New(_width, _height, _channels);
    GLenum dataFormat = NumChannelsToDataFormat(_channels);

    Bind();

    glGetTexImage(GL_TEXTURE_2D, _level, dataFormat, GL_UNSIGNED_BYTE, im->Data());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    return im;
}

FloatImagePtr Texture2D::GetImageF() {
    FloatImagePtr im = FloatImage::New(_width, _height, 3);
  //  GLenum dataFormat = NumChannelsToDataFormat(3);

    Bind();

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, im->Data());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    return im;
}

}
