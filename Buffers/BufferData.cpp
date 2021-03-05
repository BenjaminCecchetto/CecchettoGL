/*
 * BufferData.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: cecchett
 */

#include "BufferData.h"

namespace cgl {

template<>
std::string ByteBuffer::Name() {
    return "Byte";
}

template<>
std::string UnsignedByteBuffer::Name() {
    return "UnsignedByte";
}

template<>
std::string ShortBuffer::Name() {
    return "Short";
}

template<>
std::string UnsignedShortBuffer::Name() {
    return "UnsignedShort";
}

template<>
std::string IntBuffer::Name() {
    return "Int";
}

template<>
std::string UnsignedIntBuffer::Name() {
    return "UnsignedInt";
}

template<>
std::string FloatBuffer::Name() {
    return "Float";
}

template<>
std::string DoubleBuffer::Name() {
    return "Double";
}

template<>
GLenum ByteBuffer::Type() {
    return GL_BYTE;
}

template<>
GLenum UnsignedByteBuffer::Type() {
    return GL_UNSIGNED_BYTE;
}

template<>
GLenum ShortBuffer::Type() {
    return GL_SHORT;
}

template<>
GLenum UnsignedShortBuffer::Type() {
    return GL_UNSIGNED_SHORT;
}

template<>
GLenum IntBuffer::Type() {
    return GL_INT;
}

template<>
GLenum UnsignedIntBuffer::Type() {
    return GL_UNSIGNED_INT;
}

template<>
GLenum FloatBuffer::Type() {
    return GL_FLOAT;
}

template<>
GLenum DoubleBuffer::Type() {
    return GL_DOUBLE;
}

}

