/*
 * DispatchIndirectBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_DISPATCHINDIRECTBUFFER_H_
#define CGL_DISPATCHINDIRECTBUFFER_H_

#include <memory>

namespace cgl {

class DispatchIndirectBuffer;
typedef std::shared_ptr<DispatchIndirectBuffer> DispatchIndirectBufferPtr;

class DispatchIndirectBuffer: public Buffer {
public:
    DispatchIndirectBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_DISPATCH_INDIRECT_BUFFER, bytes, usage) {
    }
    static DispatchIndirectBufferPtr New(bool isMutable, uint32_t bytes,
            GLenum usage) {
        return std::make_shared<DispatchIndirectBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* DISPATCHINDIRECTBUFFER_H_ */
