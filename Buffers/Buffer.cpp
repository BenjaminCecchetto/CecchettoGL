/*
 * Buffer.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: cecchett
 */

#include "Buffer.h"
#include <GL/glew.h>
#include <exception>
#include <iostream>
#include "../GLInfo.h"

namespace cgl {

class ImmutableBufferAccessException: public std::exception {
    virtual const char* what() const throw () {
        return "Exception in class Buffer: Trying to access immutable buffer.";
    }
} immutableBufferAccessException;

Buffer::Buffer(bool isMutable, GLenum target, uint32_t bytes, GLenum usage) {
    _mutable = isMutable;
    _target = target;
    _bytes = bytes;
    _usage = usage;

    glGenBuffers(1, &_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glBindBuffer(_target, _id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    if (_mutable) {
        glBufferData(_target, bytes, NULL, _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
    else {
        glBufferStorage(_target, bytes, NULL, _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
}

Buffer::Buffer(bool isMutable, GLenum target, BufferDataPtr data,
        GLenum usage) {
    _mutable = isMutable;
    _target = target;
    _data = data;
    _bytes = _data->Bytes();
    _usage = usage;

    glGenBuffers(1, &_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    Bind();

    if (_mutable) {
        glBufferData(_target, _data->Bytes(), _data->Data(), _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
    else {
        glBufferStorage(_target, _data->Bytes(), _data->Data(), _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
    Unbind();
}

Buffer::Buffer(bool isMutable, GLenum target, uint32_t bytes, GLvoid* data,
        GLenum usage) {
    _mutable = isMutable;
    _target = target;
    _bytes = bytes;
    _usage = usage;

    GLInfo::CheckGLError(__FILE__,__LINE__);

    glGenBuffers(1, &_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glBindBuffer(_target, _id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    if (_mutable) {
        glBufferData(_target, bytes, data, _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
    else {
        glBufferStorage(_target, bytes, data, _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
}

Buffer::~Buffer() {
    Unbind();
    glDeleteBuffers(1, &_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Buffer::Bind() {
    glBindBuffer(_target, _id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Buffer::Unbind() {
    glBindBuffer(_target, 0);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}
void Buffer::UploadAll() {
    if (_mutable) {
        Bind();
        glBufferData(_target, _data->Bytes(), _data->Data(), _usage);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        Unbind();
    } else {
        throw immutableBufferAccessException;
    }
}

void Buffer::UploadOffset(uint32_t offset, uint32_t size) {
    if (_mutable) {
        Bind();
        glBufferSubData(_target, offset, size, _data->Data());
        GLInfo::CheckGLError(__FILE__,__LINE__);
        Unbind();
    } else {
        throw immutableBufferAccessException;
    }
}

void Buffer::UploadOffset(uint32_t offset, BufferDataPtr buffer) {
  if (_mutable) {
      Bind();
      glBufferSubData(_target, offset, buffer->Bytes(), buffer->Data());
      GLInfo::CheckGLError(__FILE__,__LINE__);
      Unbind();
  } else {
      throw immutableBufferAccessException;
  }
}

BufferDataPtr Buffer::GetBufferDataPtr() {
    if (_mutable)
        return _data;
    else {
        throw immutableBufferAccessException;
        return nullptr;
    }
}

template<typename T>
std::string Buffer::GetGPUString(uint32_t size, uint32_t components,
        uint32_t specifiComponent) {
    if (_mutable) {
        std::stringstream ss;
        Bind();

        uint32_t bufferSize;
        if (size == 0)
            bufferSize = _bytes / sizeof(T);
        else
            bufferSize = size;

        // glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

        T* buf = (T*) glMapBuffer(_target, GL_READ_ONLY);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        {
            std::cout << "Buffer " << _id << " of size " << bufferSize
                    << " mapped to " << buf;
            std::cout << std::endl;
            for (uint32_t i = 0; i < static_cast<uint32_t>(bufferSize*components); i +=
                    components) {

                if (components == 1) {
                    ss << i << ":\t";
                    ss << buf[i];
                    ss << std::endl;
                } else {
                    if (specifiComponent != 0) {
                        ss << i/components << ":\t";
                        ss << buf[i + specifiComponent - 1];
                        ss << std::endl;
                    } else {
                        ss << i / components << ":\t";
                        ss << "(";
                        for (uint32_t j = 0; j < components - 1; j++) {
                            ss << buf[i + j] << ",";
                        }
                        ss << buf[i + components - 1] << ")";
                        ss << std::endl;
                    }
                }

            }
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        return ss.str();

    } else {
		std::cerr << "Immutable Buffer Access Exception!" << std::endl;
        throw immutableBufferAccessException;
    }
}

template std::string Buffer::GetGPUString<GLfloat>(uint32_t, uint32_t,
        uint32_t);
template std::string Buffer::GetGPUString<GLdouble>(uint32_t, uint32_t,
        uint32_t);
template std::string Buffer::GetGPUString<GLuint>(uint32_t, uint32_t, uint32_t);

}
