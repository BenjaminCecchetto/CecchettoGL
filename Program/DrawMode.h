/*
 * DrawMode.h
 *
 *  Created on: Mar 7, 2014
 *      Author: root
 */

#ifndef CGL_DRAWMODE_H_
#define CGL_DRAWMODE_H_

#include <memory>
#include "../GLInfo.h"

namespace cgl {

class DrawMode;
typedef std::shared_ptr<DrawMode> DrawModePtr;

class DrawArrays;
typedef std::shared_ptr<DrawArrays> DrawArraysPtr;

class DrawArraysInstanced;
typedef std::shared_ptr<DrawArraysInstanced> DrawArraysInstancedPtr;

class MultiDrawArrays;
typedef std::shared_ptr<MultiDrawArrays> MultiDrawArraysPtr;

class DrawMode {
protected:
    GLenum _mode;

public:
    DrawMode(GLenum mode) :
            _mode(mode) {
    }

    virtual ~DrawMode() {
    }
    virtual void Draw() = 0;

    GLenum GetMode() {
        return _mode;
    }
};

class DrawArrays: public DrawMode {
    GLint _first;
    GLsizei _count;
public:
    DrawArrays(GLenum mode, GLint first, GLsizei count) :
            DrawMode(mode), _first(first), _count(count) {
    }

    static DrawArraysPtr New(GLenum mode, GLint first, GLsizei count) {
        return std::make_shared<DrawArrays>(mode, first, count);
    }

    void Draw() {
        glDrawArrays(_mode, _first, _count);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
};

class DrawArraysInstanced: public DrawMode {
    GLint _first;
    GLsizei _count;
    GLsizei _instancecount;

public:
    DrawArraysInstanced(GLenum mode, GLint first, GLsizei count,
            GLsizei instancecount) :
            DrawMode(mode), _first(first), _count(count), _instancecount(
                    instancecount) {

    }

    static DrawArraysInstancedPtr New(GLenum mode, GLint first, GLsizei count,
            GLsizei instancecount) {
        return std::make_shared<DrawArraysInstanced>(mode, first, count,
                instancecount);
    }

    void Draw() {
        glDrawArraysInstanced(_mode, _first, _count, _instancecount);
        GLInfo::CheckGLError(__FILE__,__LINE__);
    }
};

class MultiDrawArrays : public DrawMode {
public:
  GLsizei m_primCount;
  std::vector<GLint> m_first;
  std::vector<GLsizei> m_count;

  MultiDrawArrays(GLenum mode, GLsizei primCount) :
                  DrawMode(mode), m_primCount(primCount) {
      m_first = std::vector<GLint>(primCount);
      m_count = std::vector<GLsizei>(primCount);
  }

  static MultiDrawArraysPtr New(GLenum mode,
                                GLsizei primCount) {
      return std::make_shared<MultiDrawArrays>(mode, primCount);
  }

  void Resize(GLsizei primCount) {
    m_primCount = primCount;
    m_first.resize(primCount);
    m_count.resize(primCount);
  }

  void Draw() {
     glMultiDrawArrays(_mode, &m_first[0], &m_count[0], m_primCount);
     GLInfo::CheckGLError(__FILE__,__LINE__);
  }
};

}


#endif /* DRAWMODE_H_ */
