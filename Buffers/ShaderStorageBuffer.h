/*
 * ShaderStorageBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_SHADERSTORAGEBUFFER_H_
#define CGL_SHADERSTORAGEBUFFER_H_

#include <memory>
#include "Buffer.h"
#include "../GLInfo.h"

namespace cgl {

class ShaderStorageBuffer;
typedef std::shared_ptr<ShaderStorageBuffer> ShaderStorageBufferPtr;

class ShaderStorageBuffer: public Buffer {
public:
    ShaderStorageBuffer(bool isMutable, BufferDataPtr data, GLenum usage) :
            Buffer(isMutable, GL_SHADER_STORAGE_BUFFER, data, usage) {
    }

    static ShaderStorageBufferPtr New(bool isMutable, BufferDataPtr data,
            GLenum usage) {
        return std::make_shared<ShaderStorageBuffer>(isMutable, data, usage);
    }

    ShaderStorageBuffer(bool isMutable, GLuint bytes, GLvoid* data,
            GLenum usage) :
            Buffer(isMutable, GL_SHADER_STORAGE_BUFFER, bytes, data, usage) {
    }
    static ShaderStorageBufferPtr New(bool isMutable, GLuint bytes,
            GLvoid* data, GLenum usage) {
        return std::make_shared<ShaderStorageBuffer>(isMutable, bytes, data,
                usage);
    }
};

}

#endif /* SHADERSTORAGEBUFFER_H_ */
