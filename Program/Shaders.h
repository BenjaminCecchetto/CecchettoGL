/*
 * Shaders.h
 *
 *  Created on: Oct 29, 2013
 *      Author: cecchett
 */

#ifndef SHADERS_H_
#define SHADERS_H_

#include <GL/glew.h>
#include <string>
#include <memory>
#include "../Utility/FileLoader.h"

namespace cgl {

class VertexShader;
class TessControlShader;
class TessEvaluationShader;
class GeometryShader;
class FragmentShader;
class ComputeShader;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<TessControlShader> TessControlShaderPtr;
typedef std::shared_ptr<TessEvaluationShader> TessEvaluationShaderPtr;
typedef std::shared_ptr<GeometryShader> GeometryShaderPtr;
typedef std::shared_ptr<FragmentShader> FragmentShaderPtr;
typedef std::shared_ptr<ComputeShader> ComputeShaderPtr;

class Shader {
    GLuint id;
public:
    Shader(GLenum type, std::string source);

    virtual ~Shader();

    GLuint GetID() {
        return id;
    }
};

class VertexShader: public Shader {
public:
    VertexShader(std::string source) :
            Shader(GL_VERTEX_SHADER, source) {
    }

    static VertexShaderPtr New(std::string source) {
        return std::make_shared<VertexShader>(source);
    }
    static VertexShaderPtr NewFromFile(std::string filename) {
        std::string source;
        source = FileLoader::FilenameToString(filename);
        return std::make_shared<VertexShader>(source);
    }
};

class TessControlShader: public Shader {
public:
    TessControlShader(std::string source) :
            Shader(GL_TESS_CONTROL_SHADER, source) {
    }

    static TessControlShaderPtr New(std::string source) {
        return std::make_shared<TessControlShader>(source);
    }
    static TessControlShaderPtr NewFromFile(std::string filename) {
        std::string source;
        source = FileLoader::FilenameToString(filename);
        return std::make_shared<TessControlShader>(source);
    }
};

class TessEvaluationShader: public Shader {
public:
    TessEvaluationShader(std::string source) :
            Shader(GL_TESS_EVALUATION_SHADER, source) {
    }

    static TessEvaluationShaderPtr New(std::string source) {
        return std::make_shared<TessEvaluationShader>(source);
    }
    static TessEvaluationShaderPtr NewFromFile(std::string filename) {
        std::string source;
        source = FileLoader::FilenameToString(filename);
        return std::make_shared<TessEvaluationShader>(source);
    }
};

class GeometryShader: public Shader {
public:
    GeometryShader(std::string source) :
            Shader(GL_GEOMETRY_SHADER, source) {
    }

    static GeometryShaderPtr New(std::string source) {
        return std::make_shared<GeometryShader>(source);
    }
    static GeometryShaderPtr NewFromFile(std::string filename) {
        std::string source;
        source = FileLoader::FilenameToString(filename);
        return std::make_shared<GeometryShader>(source);
    }
};

class FragmentShader: public Shader {
public:
    FragmentShader(std::string source) :
            Shader(GL_FRAGMENT_SHADER, source) {
    }

    static FragmentShaderPtr New(std::string source) {
        return std::make_shared<FragmentShader>(source);
    }
    static FragmentShaderPtr NewFromFile(std::string filename) {
        std::string source;
        source = FileLoader::FilenameToString(filename);
        return std::make_shared<FragmentShader>(source);
    }
};

class ComputeShader: public Shader {
public:
    ComputeShader(std::string source) :
            Shader(GL_COMPUTE_SHADER, source) {
    }

    static ComputeShaderPtr New(std::string source) {
        return std::make_shared<ComputeShader>(source);
    }
    static ComputeShaderPtr NewFromFile(std::string filename) {
        std::string source;
        source = FileLoader::FilenameToString(filename);
        return std::make_shared<ComputeShader>(source);
    }
};

}

#endif /* SHADERS_H_ */
