/*
 * ElementArrayBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_ELEMENTARRAYBUFFER_H_
#define CGL_ELEMENTARRAYBUFFER_H_

#include <memory>
#include "Buffer.h"

namespace cgl {

class ElementArrayBuffer;
typedef std::shared_ptr<ElementArrayBuffer> ElementArrayBufferPtr;

class ElementArrayBuffer: public Buffer {
public:
    ElementArrayBuffer(bool immutable, BufferDataPtr data, GLenum usage) :
            Buffer(immutable, GL_ELEMENT_ARRAY_BUFFER, data, usage) {
    }
    static ElementArrayBufferPtr New(bool immutable, BufferDataPtr data,
            GLenum usage) {
        return std::make_shared<ElementArrayBuffer>(immutable, data, usage);
    }
};

}

#endif /* ELEMENTARRAYBUFFER_H_ */
