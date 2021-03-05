#include "Program.h"

#include <GL/glew.h>
#include <iostream>
#include "../GLInfo.h"

#include <gtc/type_ptr.hpp>

namespace cgl {

Program::Program(ComputeShaderPtr cs) :
        _cs(cs) {
    _id = glCreateProgram();
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glAttachShader(_id, cs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    Link();
}

Program::Program(VertexShaderPtr vs, FragmentShaderPtr fs) :
        _vs(vs), _fs(fs) {
    _id = glCreateProgram();
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glAttachShader(_id, vs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, fs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    Link();
}
Program::Program(VertexShaderPtr vs, GeometryShaderPtr gs, FragmentShaderPtr fs) :
        _vs(vs), _gs(gs), _fs(fs) {
    _id = glCreateProgram();
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glAttachShader(_id, vs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, gs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, fs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    Link();
}

Program::Program(VertexShaderPtr vs, TessControlShaderPtr tcs,
        TessEvaluationShaderPtr tes, FragmentShaderPtr fs) :
        _vs(vs), _tcs(tcs), _tes(tes), _fs(fs) {
    _id = glCreateProgram();
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glAttachShader(_id, vs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, tcs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, tes->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, fs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    Link();
}
Program::Program(VertexShaderPtr vs, TessControlShaderPtr tcs,
        TessEvaluationShaderPtr tes, GeometryShaderPtr gs, FragmentShaderPtr fs) :
        _vs(vs), _tcs(tcs), _tes(tes), _gs(gs), _fs(fs) {
    _id = glCreateProgram();
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glAttachShader(_id, vs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, tcs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, tes->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, gs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glAttachShader(_id, fs->GetID());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    Link();
}

Program::Program(std::string computeShaderFile) :
        Program(ComputeShader::NewFromFile(computeShaderFile)) {
}
Program::Program(std::string vertexShaderFile, std::string fragmentShaderFile) :
        Program(VertexShader::NewFromFile(vertexShaderFile),
                FragmentShader::NewFromFile(fragmentShaderFile)) {
}
Program::Program(std::string vertexShaderFile, std::string geometryShaderFile,
        std::string fragmentShaderFile) :
        Program(VertexShader::NewFromFile(vertexShaderFile),
                GeometryShader::NewFromFile(geometryShaderFile),
                FragmentShader::NewFromFile(fragmentShaderFile)) {
}
Program::Program(std::string vertexShaderFile,
        std::string tessellationControlFile, std::string tessellationEvalFile,
        std::string fragmentShaderFile) :
        Program(VertexShader::NewFromFile(vertexShaderFile),
                TessControlShader::NewFromFile(tessellationControlFile),
                TessEvaluationShader::NewFromFile(tessellationEvalFile),
                FragmentShader::NewFromFile(fragmentShaderFile)) {
}

Program::Program(std::string vertexShaderFile,
        std::string tessellationControlFile, std::string tessellationEvalFile,
        std::string geometryShaderFile, std::string fragmentShaderFile) :
        Program(VertexShader::NewFromFile(vertexShaderFile),
                TessControlShader::NewFromFile(tessellationControlFile),
                TessEvaluationShader::NewFromFile(tessellationEvalFile),
                GeometryShader::NewFromFile(geometryShaderFile),
                FragmentShader::NewFromFile(fragmentShaderFile)) {
}

Program::~Program() {
    glDeleteProgram(_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    _id = 0;
}

void Program::Bind() {
    glUseProgram(_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}
void Program::Push() {
    glGetIntegerv(GL_CURRENT_PROGRAM, &_idPrev);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glUseProgram(_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Program::Pop() {
    glUseProgram(_idPrev);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Program::Link() {
    GLint result;

    glLinkProgram(_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    glGetProgramiv(_id, GL_LINK_STATUS, &result);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    if (result == GL_FALSE) {
        GLint length;
        char *log;

        /* get the program info log */
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        log = new char[length];
        glGetProgramInfoLog(_id, length, &result, log);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        /* print an error message and the info log */
        std::cerr << "Program::link(): Program linking failed: " << log
                << std::endl;
        delete[] log;

        /* delete the program */
        glDeleteProgram(_id);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        _id = 0;
    } else {
        std::cout << "Linked Program _id: " << _id << std::endl;
    }

    _idPrev = 0;
}

void Program::UniformMat4(std::string name, glm::mat4 matrix) {
    glUseProgram(_id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    GLint loc = glGetUniformLocation(_id, name.c_str());
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glUseProgram(0);
    GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Program::UniformUint(std::string name, uint32_t value) {
  glUseProgram(_id);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  GLint loc = glGetUniformLocation(_id, name.c_str());
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUniform1uiv(loc, 1, &value);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUseProgram(0);
  GLInfo::CheckGLError(__FILE__,__LINE__);
}


void Program::UniformFloat(std::string name, float value) {
  glUseProgram(_id);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  GLint loc = glGetUniformLocation(_id, name.c_str());
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUniform1fv(loc, 1, &value);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUseProgram(0);
  GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Program::UniformVec2f(std::string name, glm::vec2 vec) {
  glUseProgram(_id);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  GLint loc = glGetUniformLocation(_id, name.c_str());
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUniform2fv(loc, 1, glm::value_ptr(vec));
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUseProgram(0);
  GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Program::UniformVec3f(std::string name, glm::vec3 vec) {
  glUseProgram(_id);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  GLint loc = glGetUniformLocation(_id, name.c_str());
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUniform3fv(loc, 1, glm::value_ptr(vec));
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUseProgram(0);
  GLInfo::CheckGLError(__FILE__,__LINE__);
}

void Program::UniformVec4f(std::string name, glm::vec4 vec) {
  glUseProgram(_id);
  GLInfo::CheckGLError(__FILE__,__LINE__);

  GLint loc = glGetUniformLocation(_id, name.c_str());
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUniform4fv(loc, 1, glm::value_ptr(vec));
  GLInfo::CheckGLError(__FILE__,__LINE__);

  glUseProgram(0);
  GLInfo::CheckGLError(__FILE__,__LINE__);
}

}
