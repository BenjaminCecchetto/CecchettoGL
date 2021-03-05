/*
 * ComputePass.h
 *
 *  Created on: Mar 11, 2014
 *      Author: root
 */

#ifndef COMPUTEPASS_H_
#define COMPUTEPASS_H_

#include "Pass.h"

namespace cgl {
class ComputePass;
typedef std::shared_ptr<ComputePass> ComputePassPtr;

struct ComputeImage;
typedef std::shared_ptr<ComputeImage> ComputeImagePtr;

struct ComputeImage {
    TexturePtr _tex;
    bool _layered;
    int _layer;
    GLenum _access;

    ComputeImage(TexturePtr tex, bool layered, int layer, GLenum access) :
            _tex(tex), _layered(layered), _layer(layer), _access(access) {
    }

    static ComputeImagePtr New(TexturePtr tex, bool layered, int layer,
            GLenum access) {
        return std::make_shared<ComputeImage>(tex, layered, layer, access);
    }
};
class ComputePass: public Pass {
    ProgramPtr _program;

    uint32_t _numGroupsX, _numGroupsY, _numGroupsZ;

    std::vector<ComputeImagePtr> _images;
    std::vector<uint32_t> _imageBindings;

public:
    ComputePass(ProgramPtr program, uint32_t numGroupsX, uint32_t numGroupsY,
            uint32_t numGroupsZ) :
            _program(program), _numGroupsX(numGroupsX), _numGroupsY(numGroupsY), _numGroupsZ(
                    numGroupsZ) {
    }

    static ComputePassPtr New(ProgramPtr program, uint32_t numGroupsX,
            uint32_t numGroupsY, uint32_t numGroupsZ) {
        return std::make_shared<ComputePass>(program, numGroupsX, numGroupsY,
                numGroupsZ);
    }

    void Dispatch() {
        _program->Bind();

        Pass::Dispatch();

        for (uint32_t i = 0; i < _images.size(); i++) {
            _images[i]->_tex->BindImageTexture(_imageBindings[i],
                    _images[i]->_layered, _images[i]->_layer,
                    _images[i]->_access);
        }

        glDispatchCompute(_numGroupsX, _numGroupsY, _numGroupsZ);
        GLInfo::CheckGLError(__FILE__,__LINE__);

    }

        void AppendTexture(TexturePtr tex, bool layered, int layer, GLenum access, uint32_t bindingNumber) {
            ComputeImagePtr computeImage = ComputeImage::New(tex, layered, layer,
                    access);
            _images.push_back(computeImage);
            _imageBindings.push_back(bindingNumber);
        }

    };

}

#endif /* COMPUTEPASS_H_ */
