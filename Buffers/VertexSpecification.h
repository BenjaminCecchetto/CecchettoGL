/*
 * VertexSpecification.h
 *
 *  Created on: Nov 11, 2013
 *      Author: cecchett
 */

#ifndef CGL_VERTEXSPECIFICATION_H_
#define CGL_VERTEXSPECIFICATION_H_

#include <memory>
#include <GL/glew.h>
#include <vector>
#include "ElementArrayBuffer.h"
#include "Buffer.h"
#include "VertexBuffer.h"

namespace cgl {

class VertexSpecification;
typedef std::shared_ptr<VertexSpecification> VertexSpecificationPtr;

//list of vertex buffers
typedef std::vector<VertexBufferPtr> VertexBufferList;

//is a VAO that has multiple VBOs and one Element Array Buffer
class VertexSpecification {
    GLenum _id;
    uint32_t _vertices;

    VertexBufferList _vertexBuffers;
    ElementArrayBufferPtr _elementArrayBuffer;
public:
    VertexSpecification();
    ~VertexSpecification();
    
    static VertexSpecificationPtr New() {
        return std::make_shared<VertexSpecification>();
    }

    void SetElementArrayBuffer(ElementArrayBufferPtr eab);
    void Append(VertexBufferPtr buffer);

    void Set();

    uint32_t GetVertices() {
        return _vertices;
    }

    void Bind() {
        glBindVertexArray(_id);
        GLInfo::CheckGLError(__FILE__,__LINE__);}

        void Unbind() {
            glBindVertexArray(0);
            GLInfo::CheckGLError(__FILE__,__LINE__);
        }
    };

}

#endif /* VERTEXSPECIFICATION_H_ */
