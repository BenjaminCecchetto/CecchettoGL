/*
 * Framebuffer.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: cecchett
 */

#include "Framebuffer.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "../GLInfo.h"

namespace cgl {

DrawFramebuffer::DrawFramebuffer(uint32_t numColorBuffers,
        GLenum internalFormat, GLsizei width, GLsizei height) :
        _width(width), _height(height) {
    idPrev = 0;
    this->target = GL_DRAW_FRAMEBUFFER;
    glGenFramebuffers(1, &id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    if (numColorBuffers > 0) {
        glBindFramebuffer(target, id);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        for (uint32_t i = 0; i < numColorBuffers; i++) {
            Texture2DPtr texi = Texture2D::New(0, internalFormat, width, height,
            GL_LINEAR, GL_LINEAR, GL_MIRRORED_REPEAT,
            GL_MIRRORED_REPEAT);

            colorTextures.push_back(texi);

            drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);

            glFramebufferTexture(target, GL_COLOR_ATTACHMENT0 + i,
                    texi->GetID(), 0);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }
        depthTexture = Texture2D::New(0, GL_DEPTH_COMPONENT16, width, height,
        GL_LINEAR, GL_LINEAR, GL_MIRRORED_REPEAT,
        GL_MIRRORED_REPEAT);
        glFramebufferTexture(target, GL_DEPTH_ATTACHMENT, depthTexture->GetID(),
                0);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        CheckFramebufferStatus();
        glBindFramebuffer(target, 0);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
}

DrawFramebuffer::~DrawFramebuffer() {
    glDeleteFramebuffers(1, &id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void DrawFramebuffer::Begin() {
    glBindFramebuffer(target, id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    this->target = target;
    glDrawBuffers(drawBuffers.size(), drawBuffers.data());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glGetIntegerv(GL_VIEWPORT, viewport);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glViewport(0, 0, _width, _height);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void DrawFramebuffer::End() {
    glBindFramebuffer(target, 0);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void DrawFramebuffer::CheckFramebufferStatus() {
    GLenum value = glCheckFramebufferStatus(target);

    if (value != GL_FRAMEBUFFER_COMPLETE) {
        switch (value) {
        case GL_FRAMEBUFFER_UNDEFINED:
            std::cerr << "Framebuffer: The framebuffer is undefined."
                    << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cerr << "Framebuffer: Incomplete attachment." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cerr << "Framebuffer: Default width and height not set."
                    << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            std::cerr
                    << "Framebuffer: Images do not have the same number of multisamples."
                    << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            std::cerr
                    << "Framebuffer: All attachments must be layered if one is."
                    << std::endl;
            break;

        }
    }
}

}
