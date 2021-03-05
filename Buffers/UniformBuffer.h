/*
 * UniformBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_UNIFORMBUFFER_H_
#define CGL_UNIFORMBUFFER_H_

#include <memory>
#include <string>
#include "../Program/Program.h"
#include "Buffer.h"

namespace cgl {

class UniformBuffer;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;

class UniformBuffer: public Buffer {
    std::string _bufferName;
    GLuint _blockIndex;
    GLuint _bindingPoint;
public:
    UniformBuffer(bool isMutable, BufferDataPtr data, GLenum usage,
            ProgramPtr program, std::string bufferName, GLuint bindingPoint);

    static UniformBufferPtr New(bool isMutable, BufferDataPtr data,
            GLenum usage, ProgramPtr program, std::string bufferName,
            GLuint bindingPoint) {
        return std::make_shared<UniformBuffer>(isMutable, data, usage, program,
                bufferName, bindingPoint);
    }
};

}

#endif /* UNIFORMBUFFER_H_ */
