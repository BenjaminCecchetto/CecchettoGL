/*
 * CopyReadBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_COPYREADBUFFER_H_
#define CGL_COPYREADBUFFER_H_

#include <memory>

namespace cgl {

class CopyReadBuffer;
typedef std::shared_ptr<CopyReadBuffer> CopyReadBufferPtr;

class CopyReadBuffer: public Buffer {
public:
    CopyReadBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_COPY_READ_BUFFER, bytes, usage) {
    }
    static CopyReadBufferPtr New(bool isMutable, uint32_t bytes,
            GLenum usage) {
        return std::make_shared<CopyReadBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* COPYREADBUFFER_H_ */
