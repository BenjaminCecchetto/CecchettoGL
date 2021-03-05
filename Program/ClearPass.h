/*
 * ClearPass.h
 *
 *  Created on: Mar 11, 2014
 *      Author: root
 */

#ifndef CLEARPASS_H_
#define CLEARPASS_H_

#include "Pass.h"

namespace cgl {
class ClearPass;
typedef std::shared_ptr<ClearPass> ClearPassPtr;

//clears a framebuffer
class ClearPass: public Pass {
    float _clearR, _clearG, _clearB, _clearA;
    GLenum _clearBuffer;

    DrawFramebufferPtr _frameBuffer;
public:
    ClearPass(DrawFramebufferPtr fbo, GLenum buffer, GLfloat r, GLfloat g,
            GLfloat b, GLfloat a) {
        _clearR = r;
        _clearG = g;
        _clearB = b;
        _clearA = a;
        _clearBuffer = buffer;
        _frameBuffer = fbo;
    }
    static ClearPassPtr New(DrawFramebufferPtr fbo, GLenum buffer, GLfloat r,
            GLfloat g, GLfloat b, GLfloat a) {
        return std::make_shared<ClearPass>(fbo, buffer, r, g, b, a);
    }

    void Dispatch() {
        if (_frameBuffer)
            _frameBuffer->Begin();

        glClearColor(_clearR, _clearG, _clearB, _clearA);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        glClear(_clearBuffer);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        if (_frameBuffer)
            _frameBuffer->End();
    }
};

}

#endif /* CLEARPASS_H_ */
