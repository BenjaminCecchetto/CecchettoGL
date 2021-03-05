/*
 * CopyWriteBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_COPYWRITEBUFFER_H_
#define CGL_COPYWRITEBUFFER_H_

#include <memory>

namespace cgl {

class CopyWriteBuffer;
typedef std::shared_ptr<CopyWriteBuffer> CopyWriteBufferPtr;

class CopyWriteBuffer: public Buffer {
public:
    CopyWriteBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_COPY_WRITE_BUFFER, bytes, usage) {
    }
    static CopyWriteBufferPtr New(bool isMutable, uint32_t bytes,
            GLenum usage) {
        return std::make_shared<CopyWriteBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* COPYWRITEBUFFER_H_ */
