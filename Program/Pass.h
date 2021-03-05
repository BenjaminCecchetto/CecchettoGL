/*
 * Pass.h
 *
 *  Created on: Dec 10, 2013
 *      Author: root
 */

#ifndef CGL_PASS_H_
#define CGL_PASS_H_

#include <memory>
#include <vector>
#include "Program.h"
#include "BlendParameters.h"
#include "../Buffers/VertexSpecification.h"
#include "../Buffers/TransformFeedbackObject.h"
#include "../Textures/Texture.h"
#include "../Textures/Framebuffer.h"
#include "DrawMode.h"

namespace cgl {

class UpdateCallbackClass;
typedef std::shared_ptr<UpdateCallbackClass> UpdateCallbackClassPtr;

class UpdateCallbackClass {
public:
    virtual ~UpdateCallbackClass() {
    }
    virtual void Update(double dt) = 0;
};

class Pass;
typedef std::shared_ptr<Pass> PassPtr;

class Pass {
protected:
    UpdateCallbackClassPtr _callbackClass;

    std::vector<BufferPtr> _buffers;
    std::vector<uint32_t> _bufferBindingPoints;
public:
    virtual void Dispatch() {
        BindBuffers();
    }

    void Update(double dt) {
        if (_callbackClass)
            _callbackClass->Update(dt);
    }

    void SetUpdateCallback(UpdateCallbackClassPtr callbackClass) {
        _callbackClass = callbackClass;
    }

    void AppendBuffer(BufferPtr buf, uint32_t bindingPoint) {
        _buffers.push_back(buf);
        _bufferBindingPoints.push_back(bindingPoint);
    }

    void BindBuffers() {
        for (uint32_t i = 0; i < _buffers.size(); i++) {
            _buffers[i]->Bind();
            glBindBufferBase(_buffers[i]->GetTarget(), _bufferBindingPoints[i],
                    _buffers[i]->GetID());
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

    }

    virtual ~Pass() {
    }
};

}

#endif /* PASS_H_ */
