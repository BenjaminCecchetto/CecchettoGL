/*
 * DrawPass.h
 *
 *  Created on: Mar 11, 2014
 *      Author: root
 */

#ifndef DRAWPASS_H_
#define DRAWPASS_H_

#include "Pass.h"

namespace cgl {

class DrawPass;
typedef std::shared_ptr<DrawPass> DrawPassPtr;

class DrawPass: public Pass {
protected:
    //Minimum program -------------------------
    ProgramPtr _program;
    VertexSpecificationPtr _vertexSpec;
    bool _rasterDiscard;
    DrawModePtr _drawMode;
    GLenum _tfoMode;

    //OpenGL Draw State ----------------------------
    std::vector<GLenum> _glEnables;
    std::vector<GLenum> _glDisables;
    GLint _patchVertices;
    //blending
    std::vector<BlendParametersPtr> _blendParameters;

    //program inputs --------------------------
    std::vector<TexturePtr> _textures;
    TransformFeedbackObjectPtr _transformFeedbackIn;

    //outputs-----------------------------------
    DrawFramebufferPtr _framebuffer;
    TransformFeedbackObjectPtr _transformFeedbackOut;

    bool _visible;
public:

    DrawPass(bool rasterDiscard) :
            Pass(), _rasterDiscard(rasterDiscard), _tfoMode(0), _patchVertices(
                    0) {
        _program = nullptr;
        _vertexSpec = nullptr;
        _drawMode = nullptr;

        _visible = true;
    }

    virtual ~DrawPass() {
    }

    static DrawPassPtr New(bool rasterDiscard) {
        return std::make_shared<DrawPass>(rasterDiscard);
    }

    static DrawPassPtr New(ProgramPtr prog, VertexSpecificationPtr vertexSpec,
            DrawModePtr drawMode, bool rasterDiscard) {
        DrawPassPtr drawPass = std::make_shared<DrawPass>(rasterDiscard);
        drawPass->SetProgram(prog);
        drawPass->SetVertexSpecification(vertexSpec);
        drawPass->SetDrawMode(drawMode);
        return drawPass;
    }

    ProgramPtr GetProgram() {
      return _program;
    }
    void SetProgram(ProgramPtr prog) {
        _program = prog;
    }

    void SetVertexSpecification(VertexSpecificationPtr vertexSpec) {
        _vertexSpec = vertexSpec;
    }

    void SetDrawMode(DrawModePtr drawMode) {
        _drawMode = drawMode;
        if (_drawMode->GetMode() == GL_POINTS)
            _tfoMode = GL_POINTS;
        else if (_drawMode->GetMode() == GL_LINES
                || _drawMode->GetMode() == GL_LINE_LOOP
                || _drawMode->GetMode() == GL_LINE_STRIP
                || _drawMode->GetMode() == GL_LINES_ADJACENCY
                || _drawMode->GetMode() == GL_LINE_STRIP_ADJACENCY)
            _tfoMode = GL_LINES;
        else if (_drawMode->GetMode() == GL_TRIANGLES
                || _drawMode->GetMode() == GL_TRIANGLE_STRIP
                || _drawMode->GetMode() == GL_TRIANGLE_FAN
                || _drawMode->GetMode() == GL_TRIANGLES_ADJACENCY
                || _drawMode->GetMode() == GL_TRIANGLE_STRIP_ADJACENCY)
            _tfoMode = GL_TRIANGLES;
    }
    void SetTransformFeedbackOutput(TransformFeedbackObjectPtr tfo) {
        _transformFeedbackOut = tfo;
    }

    void ClearTextures() {
      _textures.clear();
    }
    void AppendTexture(TexturePtr tex) {
      _textures.push_back(tex);
    }

    void AppendBlendParameters(BlendParametersPtr blendParams) {
        _blendParameters.push_back(blendParams);
    }

    void Enable(GLenum enable) {
        _glEnables.push_back(enable);
    }

    void Disable(GLenum disable) {
        _glDisables.push_back(disable);
    }

    void SetTransformFeedbackInput(TransformFeedbackObjectPtr tfo) {
        _transformFeedbackIn = tfo;
    }

    void SetFramebufferOutput(DrawFramebufferPtr fbo) {
        _framebuffer = fbo;
    }

    void SetPatchVertices(int patchVertices) {
        if (patchVertices > 0
                && patchVertices <= GLInfo::GetInstance().MaxPatchVertices)
            _patchVertices = patchVertices;
    }

    bool GetVisible() {
      return _visible;
    }

    void SetVisible(bool visible) {
      _visible = visible;
    }

    void Dispatch() {
        if (!_visible) return;

        _program->Bind();

        Pass::Dispatch();

        for (GLenum e : _glEnables) {
            glEnable(e);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }
        if (_blendParameters.size() > 0) {

            GLInfo::CheckGLError(__FILE__,__LINE__);

            GLuint index = 0;
            for (BlendParametersPtr bp : _blendParameters) {
                glEnablei(GL_BLEND,index);
                if (bp->_separate) {
                    glBlendEquationSeparatei(index, bp->_modeRGB,
                            bp->_modeAlpha);
                    GLInfo::CheckGLError(__FILE__,__LINE__);
                    glBlendFuncSeparatei(index, bp->_srcRGB, bp->_dstRGB,
                            bp->_srcAlpha, bp->_dstAlpha);
                    GLInfo::CheckGLError(__FILE__,__LINE__);
                } else {
                    glBlendEquationi(index, bp->_modeAlpha);
                    GLInfo::CheckGLError(__FILE__,__LINE__);
                    glBlendFunci(index, bp->_srcAlpha, bp->_dstAlpha);
                    GLInfo::CheckGLError(__FILE__,__LINE__);
                }
                index++;
            }
        }

        for (GLenum d : _glDisables) {
            glDisable(d);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

        if (_program->HasTessellationShader()) {
            glPatchParameteri(GL_PATCH_VERTICES, _patchVertices);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

        for (uint32_t i = 0; i < _textures.size(); i++)
            _textures[i]->BindTextureLocation(i);

        if (_transformFeedbackOut) {
            _transformFeedbackOut->Begin(_rasterDiscard, _tfoMode);
        }

        if (_framebuffer) {

            _framebuffer->Begin();

            GLInfo::CheckGLError(__FILE__,__LINE__);
        }
        //Dispatch
        _vertexSpec->Bind();
        if (_transformFeedbackIn) {
            _transformFeedbackIn->Draw(_drawMode->GetMode());
        } else {
            _drawMode->Draw();
        }

        if (_framebuffer) {
            _framebuffer->End();

        }
        if (_transformFeedbackOut) {
            _transformFeedbackOut->End();

        }
    }
};
}

#endif /* DRAWPASS_H_ */
