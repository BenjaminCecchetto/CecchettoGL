/*
 * Shaders.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: cecchett
 */

#include "Shaders.h"
#include <iostream>
#include <string>
#include "../GLInfo.h"

namespace cgl {

Shader::Shader(GLenum type, std::string source) {
    id = glCreateShader(type);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    GLint length = source.length();
    const char* c_str = source.c_str();
    glShaderSource(id, 1, (const char **) (&c_str), &length);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    glCompileShader(id);
    GLInfo::CheckGLError(__FILE__,__LINE__);

    /* make sure the compilation was successful */
    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    if (result == GL_FALSE) {
        char *log;

        /* get the shader info log */
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        log = new char[length];
        glGetShaderInfoLog(id, length, &result, log);
        GLInfo::CheckGLError(__FILE__,__LINE__);

        /* print an error message and the info log */
        std::cerr << "Shader::Shader(): Unable to compile:" << std::endl
                <<  std::endl << log << std::endl;
        delete[] log;

        glDeleteShader(id);
        GLInfo::CheckGLError(__FILE__,__LINE__);
        id = 0;
        exit(0);
    } else {
        std::cout << "Compiled ";
    }

    switch (type) {
    case GL_VERTEX_SHADER:
        std::cout << "Vertex Shader";
        break;
    case GL_TESS_CONTROL_SHADER:
        std::cout << "Tess Control Shader";
        break;
    case GL_TESS_EVALUATION_SHADER:
        std::cout << "Tess Evaluation Shader";
        break;
    case GL_GEOMETRY_SHADER:
        std::cout << "Geometry Shader";
        break;
    case GL_FRAGMENT_SHADER:
        std::cout << "Fragment Shader";
        break;
    }
    std::cout << " id:" << id << std::endl;

}

Shader::~Shader() {
    glDeleteShader(id);
    GLInfo::CheckGLError(__FILE__,__LINE__);
    id = 0;
}

}

