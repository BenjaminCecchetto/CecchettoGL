/*
 * PixelPackBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_PIXELPACKBUFFER_H_
#define CGL_PIXELPACKBUFFER_H_

#include <memory>

namespace cgl {

class PixelPackBuffer;
typedef std::shared_ptr<PixelPackBuffer> PixelPackBufferPtr;

class PixelPackBuffer: public Buffer {
public:
    PixelPackBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_PIXEL_PACK_BUFFER, bytes, usage) {
    }
    static PixelPackBufferPtr New(bool isMutable, uint32_t bytes,
            GLenum usage) {
        return std::make_shared<PixelPackBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* PIXELPACKBUFFER_H_ */
