/*
 * VertexSpecification.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: cecchett
 */

#include "VertexSpecification.h"
#include "VertexBuffer.h"

#include <GL/glew.h>
#include <iostream>

namespace cgl {

VertexSpecification::VertexSpecification() {
    _vertices = 0;
    glGenVertexArrays(1, &_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

VertexSpecification::~VertexSpecification() {
    glBindVertexArray(0);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glDeleteVertexArrays(	1, &_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void VertexSpecification::SetElementArrayBuffer(ElementArrayBufferPtr eab) {
    _elementArrayBuffer = eab;
}

void VertexSpecification::Append(VertexBufferPtr data) {
    if (_vertices == 0)
        _vertices = data->GetVertices();
    else if (_vertices != data->GetVertices())
        std::cerr << "Error, mismatched vertices in buffer appended"
                << std::endl;
    _vertexBuffers.push_back(data);
}

void VertexSpecification::Set() {
    glBindVertexArray(_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    if (_elementArrayBuffer) {
        _elementArrayBuffer->Bind();
    }

    uint32_t vertBindingIndex = 0;
    for (uint32_t i = 0; i < _vertexBuffers.size(); i++) {
        glBindVertexBuffer(i, _vertexBuffers[i]->GetID(), 0,
                _vertexBuffers[i]->GetStride());
        GLInfo::CheckGLError(__FILE__,__LINE__);

        const VertexAttribVector& va = _vertexBuffers[i]->GetAttributeVector();
        GLenum vbtype = _vertexBuffers[i]->GetType();

        uint32_t offset = 0;
        for (uint32_t j = 0; j < va.size(); j++) {
            glVertexAttribFormat(vertBindingIndex, va[j].numComponents, vbtype,
                    va[j].normalized, offset);
            GLInfo::CheckGLError(__FILE__,__LINE__);

            glVertexAttribBinding(vertBindingIndex, i);
            GLInfo::CheckGLError(__FILE__,__LINE__);

            glEnableVertexAttribArray(vertBindingIndex);
            GLInfo::CheckGLError(__FILE__,__LINE__);

            offset += va[j].byteSize;
            vertBindingIndex++;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glBindVertexArray(0);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    }

}
