#include "Cube.h"

#include "../Program/DrawPass.h"

namespace cgl {

Cube::Cube() {
  using namespace glm;

  m_vertices.push_back(vec3(-1.0, -1.0, -1.0));
  m_vertices.push_back(vec3(-1.0, -1.0, 1.0));
  m_vertices.push_back(vec3(-1.0, 1.0, -1.0));
  m_vertices.push_back(vec3(-1.0, 1.0, 1.0));
  m_vertices.push_back(vec3(1.0, -1.0, -1.0));
  m_vertices.push_back(vec3(1.0, -1.0, 1.0));
  m_vertices.push_back(vec3(1.0, 1.0, -1.0));
  m_vertices.push_back(vec3(1.0, 1.0, 1.0));

  m_vertices.push_back(vec3(-1.0, -1.0, -1.0));
  m_vertices.push_back(vec3(1.0, -1.0, -1.0));
  m_vertices.push_back(vec3(-1.0, 1.0, -1.0));
  m_vertices.push_back(vec3(1.0, 1.0, -1.0));
  m_vertices.push_back(vec3(-1.0, -1.0, 1.0));
  m_vertices.push_back(vec3(1.0, -1.0, 1.0));
  m_vertices.push_back(vec3(-1.0, 1.0, 1.0));
  m_vertices.push_back(vec3(1.0, 1.0, 1.0));

  m_vertices.push_back(vec3(-1.0, -1.0, -1.0));
  m_vertices.push_back(vec3(-1.0, 1.0, -1.0));
  m_vertices.push_back(vec3(-1.0, -1.0, 1.0));
  m_vertices.push_back(vec3(-1.0, 1.0, 1.0));
  m_vertices.push_back(vec3(1.0, -1.0, -1.0));
  m_vertices.push_back(vec3(1.0, 1.0, -1.0));
  m_vertices.push_back(vec3(1.0, -1.0, 1.0));
  m_vertices.push_back(vec3(1.0, 1.0, 1.0));

  FloatBufferPtr fbp = FloatBuffer::New(3 * m_vertices.size());
  uint32_t index = 0;
  for (uint32_t i = 0; i < m_vertices.size(); i++) {
    fbp->_data[index++] = m_vertices[i].x;
    fbp->_data[index++] = m_vertices[i].y;
    fbp->_data[index++] = m_vertices[i].z;
  }

  m_program = Program::New("shaders/Cube-vert.glsl", "shaders/Cube-frag.glsl");

  VertexBufferPtr vbo = VertexBuffer::New(true, fbp, GL_DYNAMIC_DRAW,
                                          3 * sizeof(float), m_vertices.size());
  vbo->AddAttribute(3, false);
  VertexSpecificationPtr cubeSpec = VertexSpecification::New();
  cubeSpec->Append(vbo);
  cubeSpec->Set();

  DrawArraysPtr drawArrays = DrawArrays::New(GL_LINES, 0, m_vertices.size());

  m_drawPass = DrawPass::New(m_program, cubeSpec, drawArrays, false);
}

}  // namespace cgl
