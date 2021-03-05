/*
 * BufferData.h
 *
 *  Created on: Nov 14, 2013
 *      Author: cecchett
 */

#ifndef CGL_BUFFERDATA_H_
#define CGL_BUFFERDATA_H_

#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <GL/glew.h>

namespace cgl {

//parent class buffer
class BufferData;
typedef std::shared_ptr<BufferData> BufferDataPtr;

//available buffers
template<typename T> class TypedBufferData;
typedef TypedBufferData<GLbyte> ByteBuffer;
typedef std::shared_ptr<ByteBuffer> ByteBufferPtr;

typedef TypedBufferData<GLubyte> UnsignedByteBuffer;
typedef std::shared_ptr<UnsignedByteBuffer> UnsignedByteBufferPtr;

typedef TypedBufferData<GLshort> ShortBuffer;
typedef std::shared_ptr<ShortBuffer> ShortBufferPtr;

typedef TypedBufferData<GLushort> UnsignedShortBuffer;
typedef std::shared_ptr<UnsignedShortBuffer> UnsignedShortBufferPtr;

typedef TypedBufferData<GLint> IntBuffer;
typedef std::shared_ptr<IntBuffer> IntBufferPtr;

typedef TypedBufferData<GLuint> UnsignedIntBuffer;
typedef std::shared_ptr<UnsignedIntBuffer> UnsignedIntBufferPtr;

typedef TypedBufferData<GLfloat> FloatBuffer;
typedef std::shared_ptr<FloatBuffer> FloatBufferPtr;

typedef TypedBufferData<GLdouble> DoubleBuffer;
typedef std::shared_ptr<DoubleBuffer> DoubleBufferPtr;

typedef TypedBufferData<void> NullBuffer;
typedef std::shared_ptr<NullBuffer> NullBufferPtr;

class BufferData {
protected:
    BufferData() {
    }
public:
    virtual ~BufferData() {
    }

    virtual void* Data() = 0;
    virtual uint32_t Size() = 0;
    virtual uint32_t Bytes() = 0;
    virtual std::string Name() = 0;
    virtual GLenum Type() = 0;

    virtual std::string ToString() = 0;
};



template<typename T>
class StructBufferData : public BufferData {
    T _struct;
public:
    void* Data() {
        return &_struct;
    }

    uint32_t Bytes() {
        return sizeof(_struct);
    }

    std::string Name() {
        return std::string("Struct");
    }

    GLenum Type() {
        return GL_SHADER_STORAGE_BUFFER;
    }

    std::string ToString() {
        return std::string("Struct");
    }
};


template<typename T>
class TypedBufferData: public BufferData {
    uint32_t _size;
public:
    TypedBufferData() :
            _size(0) {
    }
    TypedBufferData(uint32_t size) :
            _size(size), _data(size) {
    }

    static std::shared_ptr<TypedBufferData<T> > New(uint32_t size) {
        return std::make_shared<TypedBufferData<T> >(size);
    }

    void* Data() {
        return (void*) (&(_data[0]));
    }

    uint32_t Size() {
        return _size;
    }

    uint32_t Bytes() {
        return _size * sizeof(T);
    }

    std::string Name();

    std::string ToString() {
        std::stringstream ss;
        ss << Name() << " Buffer of size " << Size() << std::endl;

        for (uint32_t i = 0; i < Size(); i++) {
            ss << static_cast<T>(_data[i]);
            ss << std::endl;
        }

        return ss.str();
    }

    GLenum Type();

    std::vector<T> _data;
};

}

#endif /* BUFFERDATA_H_ */
