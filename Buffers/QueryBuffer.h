/*
 * QueryBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_QUERYBUFFER_H_
#define CGL_QUERYBUFFER_H_

#include <memory>

namespace cgl {

class QueryBuffer;
typedef std::shared_ptr<QueryBuffer> QueryBufferPtr;

class QueryBuffer: public Buffer {
public:
    QueryBuffer(bool isMutable, uint32_t bytes, GLenum usage) :
            Buffer(isMutable, GL_QUERY_BUFFER, bytes, usage) {
    }
    static QueryBufferPtr New(bool isMutable, uint32_t bytes, GLenum usage) {
        return std::make_shared<QueryBuffer>(isMutable, bytes, usage);
    }
};

}

#endif /* QUERYBUFFER_H_ */
