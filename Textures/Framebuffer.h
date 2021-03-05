/*
 * Framebuffer.h
 *
 *  Created on: Oct 29, 2013
 *      Author: cecchett
 */

#ifndef CGL_FRAMEBUFFER_H_
#define CGL_FRAMEBUFFER_H_

#include <memory>
#include <GL/glew.h>
#include <vector>
#include "Texture2D.h"

namespace cgl {

class DrawFramebuffer;
typedef std::shared_ptr<DrawFramebuffer> DrawFramebufferPtr;

class DrawFramebuffer {

    GLuint id;
    GLenum target;
    GLint idPrev;

    std::vector<Texture2DPtr> colorTextures;
    std::vector<GLenum> drawBuffers;

    Texture2DPtr depthTexture;

    uint32_t _width;
    uint32_t _height;
    GLint viewport[4];
public:
    // target must be
    //      GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER, GLFRAMEBUFFER
    DrawFramebuffer(uint32_t numColorBuffers, GLenum internalFormat,
            GLsizei width, GLsizei height);

    static DrawFramebufferPtr New(int32_t numColorBuffers,
            GLenum internalFormat, GLsizei width, GLsizei height) {
        return std::make_shared<DrawFramebuffer>(numColorBuffers,
                internalFormat, width, height);
    }

    Texture2DPtr GetColorBuffer(uint32_t index) {
        if (index < colorTextures.size())
            return colorTextures[index];
        else
            return nullptr;
    }

    Texture2DPtr GetDepthBuffer(){
        return depthTexture;
    }

    uint32_t GetWidth() { return _width; }
    uint32_t GetHeight() { return _height; }

    void Begin();
    void End();

    void CheckFramebufferStatus();

    virtual ~DrawFramebuffer();
};

}

#endif /* FRAMEBUFFER_H_ */
