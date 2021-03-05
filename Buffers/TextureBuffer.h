/*
 * TextureBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_TEXTUREBUFFER_H_
#define CGL_TEXTUREBUFFER_H_

#include <memory>

namespace cgl {

class TextureBuffer;
typedef std::shared_ptr<TextureBuffer> TextureBufferPtr;

class TextureBuffer: public Buffer {
public:
    TextureBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_TEXTURE_BUFFER, bytes, usage) {
    }
    static TextureBufferPtr New(bool isMutable, uint32_t bytes, GLenum usage) {
        return std::make_shared<TextureBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* TEXTUREBUFFER_H_ */
