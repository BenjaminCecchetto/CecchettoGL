/*
 * RenderTexturePass.h
 *
 *  Created on: Mar 11, 2014
 *      Author: root
 */

#ifndef RENDERTEXTUREPASS_H_
#define RENDERTEXTUREPASS_H_

#include "DrawPass.h"


namespace cgl {

class RenderTexturePass;
typedef std::shared_ptr<RenderTexturePass> RenderTexturePassPtr;

class RenderTexturePass: public DrawPass {
public:
    RenderTexturePass(Texture2DPtr tex, FragmentShaderPtr frag);

    static RenderTexturePassPtr New(Texture2DPtr tex, FragmentShaderPtr frag = nullptr) {
        return std::make_shared<RenderTexturePass>(tex,frag);
    }

    RenderTexturePass(Texture2DPtr tex, VertexShaderPtr vert, FragmentShaderPtr frag);

    static RenderTexturePassPtr New(Texture2DPtr tex, VertexShaderPtr vert, FragmentShaderPtr frag) {
        return std::make_shared<RenderTexturePass>(tex,vert,frag);
    }
};

}

#endif /* RENDERTEXTUREPASS_H_ */
