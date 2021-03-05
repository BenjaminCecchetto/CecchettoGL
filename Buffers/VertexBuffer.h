/*
 * ArrayBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_VERTEXBUFFER_H_
#define CGL_VERTEXBUFFER_H_

#include <memory>
#include <vector>
#include "Buffer.h"
#include "../GLInfo.h"
#include <iostream>

namespace cgl {

class VertexBuffer;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;

struct VertexAttributes {
    uint32_t numComponents;
    GLenum normalized;
    uint32_t byteSize;
};

typedef std::vector<VertexAttributes> VertexAttribVector;

class VertexBuffer: public Buffer {
    GLenum _type;
    uint32_t _typeSize;

    uint32_t _stride;
    uint32_t _vertices;

    VertexAttribVector _attribs;

public:
    VertexBuffer(bool isMutable, GLenum usage, GLenum type, uint32_t stride,
            uint32_t vertices) :
            Buffer(isMutable, GL_ARRAY_BUFFER, stride * vertices, usage) {

        _type = type;
        _typeSize = GLInfo::GetInstance().GetTypeSize(_type);

        _stride = stride;
        _vertices = vertices;

    }

    static VertexBufferPtr New(bool isMutable, GLenum type, uint32_t stride,
            uint32_t vertices, GLenum usage) {
        return std::make_shared<VertexBuffer>(isMutable, type, stride, vertices,
                usage);
    }

    VertexBuffer(bool isMutable, BufferDataPtr data, GLenum usage,
            uint32_t stride, uint32_t vertices) :
            Buffer(isMutable, GL_ARRAY_BUFFER, data, usage) {

        if (data->Name() == "Struct") {
            std::cerr << "Error in " << __FILE__ << " on line " << __LINE__
                    << std::endl;
            exit(-1);
        }

        _type = data->Type();
        _typeSize = GLInfo::GetInstance().GetTypeSize(_type);

        _stride = stride;
        _vertices = vertices;
		GLInfo::CheckGLError(__FILE__,__LINE__);
    }
    static VertexBufferPtr New(bool isMutable, BufferDataPtr data, GLenum usage,
            uint32_t stride, uint32_t vertices) {

        VertexBufferPtr v= std::make_shared<VertexBuffer>(isMutable, data, usage, stride,
                vertices);

		GLInfo::CheckGLError(__FILE__,__LINE__);
		return v;
    }

    GLenum GetType() const {
        return _type;
    }

    void AddAttribute(uint32_t numComponents, bool normalized) {
        VertexAttributes va;
        va.numComponents = numComponents;
        va.normalized = (normalized) ? GL_TRUE : GL_FALSE;

        va.byteSize = _typeSize * numComponents;
        _attribs.push_back(va);
    }

    VertexAttribVector GetAttributeVector() const {
        return _attribs;
    }

    uint32_t GetStride() const {
        return _stride;
    }

    uint32_t GetVertices() const {
        return _vertices;
    }

};

}

#endif /* VERTEXBUFFER_H_ */
