/*
 * DrawIndirectBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_DRAWINDIRECTBUFFER_H_
#define CGL_DRAWINDIRECTBUFFER_H_

#include <memory>

namespace cgl {

class DrawIndirectBuffer;
typedef std::shared_ptr<DrawIndirectBuffer> DrawIndirectBufferPtr;

class DrawIndirectBuffer: public Buffer {
public:
    DrawIndirectBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_DRAW_INDIRECT_BUFFER, bytes, usage) {
    }
    static DrawIndirectBufferPtr New(bool isMutable, uint32_t bytes,
            GLenum usage) {
        return std::make_shared<DrawIndirectBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* DRAWINDIRECTBUFFER_H_ */
