/*
 * Texture3D.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: cecchett
 */

#include "Texture3D.h"
#include <GL/glew.h>
#include <iostream>
#include "../GLInfo.h"

namespace cgl {

Texture3D::Texture3D(int level, int internalFormat, int width, int height,
        int depth, int dataFormat, int dataType, void* data, int minFilter,
        int magFilter, int wrapS, int wrapT, int wrapR) :
        Texture() {
    target = GL_TEXTURE_3D;
    _format = internalFormat;
    _level = level;
    _width = width;
    _height = height;
    _channels = depth;
    Bind();

    // allocate memory and/or send data
    glTexImage3D(target, level, internalFormat, width, height, depth, 0,
            dataFormat, dataType, data);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    //wrap
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapR);
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
        std::cerr << "Texture3D: Magnification filter cannot be mipmap."
                << std::endl;
        ImproperTexParameter e("Texture3D",
                "Magnification filter cannot be mipmap.");
        throw e;
    }
}

}

