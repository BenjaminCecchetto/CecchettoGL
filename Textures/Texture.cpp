/*
 * Texture.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: cecchett
 */

#include "Texture.h"
#include "../GLInfo.h"
#include <sstream>

namespace cgl {

const char* ImproperTexParameter::what() const throw () {
    std::stringstream ss;
    ss << "Exception in class " << _class << ": " << _type << std::endl;

    return ss.str().c_str();
}

Texture::Texture() {
    glGenTextures(1, &id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    target = GL_NONE;

    _level = 0;
    _width = 0;
    _height = 0;
    _channels = 4;
    _format = GL_RGBA;
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Texture::BindTextureLocation(int loc) {
    if (loc < GLInfo::GetInstance().MaxTextureImageUnits) {
        glActiveTexture(GL_TEXTURE0 + loc);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        Bind();
    }
}

void Texture::BindImageTexture(int loc, bool layered, int layer, GLenum access) {
    if (loc < GLInfo::GetInstance().MaxImageUnits) {
        glBindImageTexture(loc, id, _level, (layered)?GL_TRUE:GL_FALSE, layer, access, _format);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
}

void Texture::Bind() {
    if (target != GL_NONE) {
        glBindTexture(target, id);
        GLInfo::CheckGLError(__FILE__,__LINE__);}
    }

}
