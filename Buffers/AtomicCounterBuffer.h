/*
 * AtomicCounterBuffer.h
 *
 *  Created on: Nov 1, 2013
 *      Author: cecchett
 */

#ifndef CGL_ATOMICCOUNTERBUFFER_H_
#define CGL_ATOMICCOUNTERBUFFER_H_

#include <memory>
#include "Buffer.h"
#include "../GLInfo.h"

namespace cgl {

class AtomicCounterBuffer;
typedef std::shared_ptr<AtomicCounterBuffer> AtomicCounterBufferPtr;

class AtomicCounterBuffer: public Buffer {
    uint32_t _numCounters;

public:
    AtomicCounterBuffer(uint32_t numCounters) :
            Buffer(true, GL_ATOMIC_COUNTER_BUFFER, 
					numCounters * sizeof(GLuint),
            		GL_DYNAMIC_DRAW), 
					_numCounters(numCounters) {

        Bind();

        Reset(0);
    }

    static AtomicCounterBufferPtr New(uint32_t numCounters) {
        return std::make_shared<AtomicCounterBuffer>(numCounters);
    }

    void Reset(GLuint value) {
        Bind();
	
  		GLuint* ptr = (GLuint*) glMapBufferRange(	GL_ATOMIC_COUNTER_BUFFER, 
													0,
													sizeof(GLuint)*_numCounters,
													GL_MAP_WRITE_BIT |
													GL_MAP_INVALIDATE_BUFFER_BIT |
													GL_MAP_UNSYNCHRONIZED_BIT);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        for (uint32_t i = 0; i < _numCounters; i++) {
            ptr[i] = value;
        }

        glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);
        GLInfo::CheckGLError(__FILE__,__LINE__);
   

        Unbind();
    }
};

}

#endif /* ATOMICCOUNTERBUFFER_H_ */
