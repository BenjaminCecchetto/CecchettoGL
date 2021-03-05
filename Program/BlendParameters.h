/*
 * BlendParameters.h
 *
 *  Created on: Jan 14, 2014
 *      Author: root
 */

#ifndef CGL_BLENDPARAMETERS_H_
#define CGL_BLENDPARAMETERS_H_

#include <memory>

namespace cgl {

class BlendParameters;
typedef std::shared_ptr<BlendParameters> BlendParametersPtr;

class BlendParameters {
public:
    GLenum _srcRGB;
    GLenum _dstRGB;
    GLenum _srcAlpha;
    GLenum _dstAlpha;

    GLenum _modeRGB;
    GLenum _modeAlpha;

    bool _separate;

    /* src, dst: GL_ZERO,
                 GL_ONE,
                 GL_SRC_COLOR,
                 GL_ONE_MINUS_SRC_COLOR,
                 GL_DST_COLOR,
                 GL_ONE_MINUS_DST_COLOR,
                 GL_SRC_ALPHA,
                 GL_ONE_MINUS_SRC_ALPHA,
                 GL_DST_ALPHA,
                 GL_ONE_MINUS_DST_ALPHA.
                 GL_CONSTANT_COLOR,
                 GL_ONE_MINUS_CONSTANT_COLOR,
                 GL_CONSTANT_ALPHA, and
                 GL_ONE_MINUS_CONSTANT_ALPHA.
                 The initial value is GL_ZERO.

     mode :  GL_FUNC_ADD,
             GL_FUNC_SUBTRACT,
             GL_FUNC_REVERSE_SUBTRACT,
             GL_MIN,
             GL_MAX
     */
    BlendParameters(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
            GLenum dstAlpha, GLenum modeRGB, GLenum modeAlpha) :
            _srcRGB(srcRGB), _dstRGB(dstRGB), _srcAlpha(srcAlpha), _dstAlpha(
                    dstAlpha), _modeRGB(modeRGB), _modeAlpha(modeAlpha), _separate(
                    true) {
    }

    BlendParameters(GLenum src, GLenum dst, GLenum mode) :
            _srcRGB(src), _dstRGB(dst), _srcAlpha(src), _dstAlpha(dst), _modeRGB(
                    mode), _modeAlpha(mode), _separate(false) {
    }

    static BlendParametersPtr New(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
            GLenum dstAlpha, GLenum modeRGB, GLenum modeAlpha) {
        return std::make_shared<BlendParameters>(srcRGB, dstRGB, srcAlpha,
                dstAlpha, modeRGB, modeAlpha);
    }

    static BlendParametersPtr New(GLenum src, GLenum dst, GLenum mode) {
        return std::make_shared<BlendParameters>(src, dst, mode);
    }
};

}

#endif /* BLENDPARAMETERS_H_ */
