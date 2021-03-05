/*
 * TransformFeedbackObject.h
 *
 *  Created on: Nov 27, 2013
 *      Author: root
 */

#ifndef CGL_TRANSFORMFEEDBACKOBJECT_H_
#define CGL_TRANSFORMFEEDBACKOBJECT_H_

#include <memory>
#include <vector>
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "../Program/Program.h"

namespace cgl {

class TransformFeedbackObject;
typedef std::shared_ptr<TransformFeedbackObject> TransformFeedbackObjectPtr;

class TransformFeedbackObject {
    GLuint _id;

    bool _rasterDiscard;
    std::vector<VertexBufferPtr> _vertexBuffers;

public:
    TransformFeedbackObject(ProgramPtr prog, const char* const varyings[]) {
        _rasterDiscard = true;
        glGenTransformFeedbacks(1, &_id);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        glTransformFeedbackVaryings(prog->GetID(), 4, varyings,
        GL_INTERLEAVED_ATTRIBS);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        prog->Link();
    }

    ~TransformFeedbackObject() {
        glDeleteTransformFeedbacks(1, &_id);
        GLInfo::CheckGLError(__FILE__,__LINE__);}

        static TransformFeedbackObjectPtr New(ProgramPtr prog,
                const char* const vars[]) {
            return std::make_shared<TransformFeedbackObject>(prog, vars);
        }

        void Append(VertexBufferPtr vbo) {
            _vertexBuffers.push_back(vbo);
        }

        GLuint GetID() {
            return _id;
        }
        void Set() {
            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _id);
            GLInfo::CheckGLError(__FILE__,__LINE__);

            for (uint32_t i = 0; i < _vertexBuffers.size(); i++) {
                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, i,
                        _vertexBuffers[i]->GetID());
                GLInfo::CheckGLError(__FILE__,__LINE__);
            }

            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

        void Bind() {
            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _id);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

        void Unbind() {
            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

        void Begin(bool rasterDiscard, GLenum primitiveMode) {
            _rasterDiscard = rasterDiscard;
            if (rasterDiscard) {
                glEnable(GL_RASTERIZER_DISCARD);
                GLInfo::CheckGLError(__FILE__,__LINE__);
            }
            Bind();
            glBeginTransformFeedback(primitiveMode);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }

        void End() {
            glEndTransformFeedback();
            GLInfo::CheckGLError(__FILE__,__LINE__);
            Unbind();
            if (_rasterDiscard) {
                glDisable(GL_RASTERIZER_DISCARD);
                GLInfo::CheckGLError(__FILE__,__LINE__);
            }
        }

        void Draw(GLenum drawMode) {
            glDrawTransformFeedback(drawMode, _id);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }
    };

}

#endif /* TRANSFORMFEEDBACKOBJECT_H_ */
