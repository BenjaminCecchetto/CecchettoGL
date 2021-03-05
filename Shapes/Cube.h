#ifndef CGL_CUBE_H_
#define CGL_CUBE_H_

#include <memory>
#include "../GLInfo.h"
#include "../Program/Program.h"
#include "../Program/DrawPass.h"

namespace cgl {

class Cube;
typedef std::shared_ptr<Cube> CubePtr;

class Cube {
    std::vector<glm::vec3> m_vertices;

    DrawPassPtr m_drawPass;
    ProgramPtr m_program;
public:
    Cube();

    static CubePtr New() {
      return std::make_shared<Cube>();
    }


    DrawPassPtr GetDrawPass() {
      return m_drawPass;
    }

    ProgramPtr GetProgram() {
      return m_program;
    }

};

}

#endif
