/*
 * UniformBuffer.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: root
 */

#include "UniformBuffer.h"
#include "../GLInfo.h"
#include <iostream>

namespace cgl {

UniformBuffer::UniformBuffer(bool immutable, BufferDataPtr data, GLenum usage,
        ProgramPtr program, std::string bufferName, GLuint bindingPoint) :
        Buffer(immutable, GL_UNIFORM_BUFFER, data, usage), _bufferName(
                bufferName), _bindingPoint(bindingPoint) {

    _blockIndex = glGetUniformBlockIndex(program->GetID(), bufferName.c_str());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    if (_blockIndex == GL_INVALID_INDEX) {
        std::cerr << "UniformBuffer:: glGetUniformBlockIndex - \"" << bufferName
                << "\" does not correspond to an active block in program "
                << program->GetID() << std::endl;
    }

    glUniformBlockBinding(program->GetID(), _blockIndex, bindingPoint);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, _id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    }

}
