/*
 * PixelUnpackBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_PIXELUNPACKBUFFER_H_
#define CGL_PIXELUNPACKBUFFER_H_

#include <memory>

namespace cgl {

class PixelUnpackBuffer;
typedef std::shared_ptr<PixelUnpackBuffer> PixelUnpackBufferPtr;

class PixelUnpackBuffer: public Buffer {
public:
    PixelUnpackBuffer(bool isMutable,  uint32_t bytes,
            GLenum usage) :
            Buffer(isMutable, GL_PIXEL_UNPACK_BUFFER, bytes, usage) {
    }
    static PixelUnpackBufferPtr New(bool isMutable,
            uint32_t bytes, GLenum usage) {
        return std::make_shared<PixelUnpackBuffer>(isMutable,  bytes,
                usage);
    }
};


}

#endif /* PIXELUNPACKBUFFER_H_ */
