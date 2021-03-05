/*
 * Buffer.h
 *
 *  Created on: Oct 29, 2013
 *      Author: cecchett
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <memory>
#include <GL/glew.h>
#include <vector>
#include "BufferData.h"

namespace cgl {

class Buffer;
typedef std::shared_ptr<Buffer> BufferPtr;

class Buffer {
protected:

    GLuint _id;
    bool _mutable;
    GLenum _target;
    GLenum _usage;
    BufferDataPtr _data;

    uint32_t _bytes;

public:
    //make a null buffer
    Buffer(bool isMutable, GLenum target, uint32_t bytes, GLenum usage);
    static BufferPtr New(bool isMutable, GLenum target, uint32_t bytes,
            GLenum usage) {
        return std::make_shared<Buffer>(isMutable, target, bytes, usage);
    }

    //make a buffer from bufferdata array
    Buffer(bool isMutable, GLenum target, BufferDataPtr data, GLenum usage);
    static BufferPtr New(bool isMutable, GLenum target, BufferDataPtr data,
            GLenum usage) {
        return std::make_shared<Buffer>(isMutable, target, data, usage);
    }

    //make a buffer given a bytesize and pointer
    Buffer(bool isMutable, GLenum target, uint32_t bytes, GLvoid* data,
            GLenum usage);
    static BufferPtr New(bool isMutable, GLenum target, uint32_t bytes,
            GLvoid* data, GLenum usage) {
        return std::make_shared<Buffer>(isMutable, target, bytes, data, usage);
    }

    virtual ~Buffer();

    void Bind();
    void Unbind();
    GLuint GetID() {
        return _id;
    }

    GLenum GetTarget() {
        return _target;
    }

    //mutable storage parameters cpu->gpu
    void UploadAll();
    void UploadOffset(uint32_t offset, uint32_t size);
    void UploadOffset(uint32_t offset, BufferDataPtr buffer);

    BufferDataPtr GetBufferDataPtr();

    template<typename T>
    std::string GetGPUString(uint32_t size = 0, uint32_t components = 1, uint32_t specifiComponent = 0);
};

}

#endif /* BUFFER_H_ */
