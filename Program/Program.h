/*
 * Program.h
 *
 *  Created on: Oct 28, 2013
 *      Author: cecchett
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <memory>
#include <GL/glew.h>
#include <glm.hpp>
#include "Shaders.h"


namespace cgl {

class Program;
typedef std::shared_ptr<Program> ProgramPtr;

class Program {
    GLuint _id;
    GLint _idPrev;

    VertexShaderPtr _vs;
    TessControlShaderPtr _tcs;
    TessEvaluationShaderPtr _tes;
    GeometryShaderPtr _gs;
    FragmentShaderPtr _fs;
    ComputeShaderPtr _cs;

public:
    //Given pointers
    Program(ComputeShaderPtr cs);
    Program(VertexShaderPtr vs, FragmentShaderPtr fs);
    Program(VertexShaderPtr vs, GeometryShaderPtr gs, FragmentShaderPtr fs);
    Program(VertexShaderPtr vs, TessControlShaderPtr tcs,
            TessEvaluationShaderPtr tes, FragmentShaderPtr fs);
    Program(VertexShaderPtr vs, TessControlShaderPtr tcs,
            TessEvaluationShaderPtr tes, GeometryShaderPtr gs,
            FragmentShaderPtr fs);

    static ProgramPtr New(ComputeShaderPtr cs) {
        return std::make_shared<Program>(cs);
    }

    static ProgramPtr New(VertexShaderPtr vs, FragmentShaderPtr fs) {
        return std::make_shared<Program>(vs, fs);
    }

    static ProgramPtr New(VertexShaderPtr vs, GeometryShaderPtr gs,
            FragmentShaderPtr fs) {
        return std::make_shared<Program>(vs, gs, fs);
    }

    static ProgramPtr New(VertexShaderPtr vs, TessControlShaderPtr tcs,
            TessEvaluationShaderPtr tes, FragmentShaderPtr fs) {
        return std::make_shared<Program>(vs, tcs, tes, fs);
    }

    static ProgramPtr New(VertexShaderPtr vs, TessControlShaderPtr tcs,
            TessEvaluationShaderPtr tes, GeometryShaderPtr gs,
            FragmentShaderPtr fs) {
        return std::make_shared<Program>(vs, tcs, tes, gs, fs);
    }

    //Given Strings
    Program(std::string computeShaderFile); //1
    Program(std::string vertexShaderFile, std::string fragmentShaderFile); //2
    Program(std::string vertexShaderFile, std::string geometryShaderFile,
            std::string fragmentShaderFile); //3
    Program(std::string vertexShaderFile, std::string tessellationControlFile,
            std::string tessellationEvalFile, std::string fragmentShaderFile); //4
    Program(std::string vertexShaderFile, std::string tessellationControlFile,
            std::string tessellationEvalFile, std::string geometryShaderFile,
            std::string fragmentShaderFile); //5

    static ProgramPtr New(std::string computeShaderFile) {
        return std::make_shared<Program>(computeShaderFile);
    }

    static ProgramPtr New(std::string vertexShaderFile,
            std::string fragmentShaderFile) {
        return std::make_shared<Program>(vertexShaderFile, fragmentShaderFile);
    }

    static ProgramPtr New(std::string vertexShaderFile,
            std::string geometryShaderFile, std::string fragmentShaderFile) {
        return std::make_shared<Program>(vertexShaderFile, geometryShaderFile,
                fragmentShaderFile);
    }

    static ProgramPtr New(std::string vertexShaderFile,
            std::string tessellationControlFile,
            std::string tessellationEvalFile, std::string fragmentShaderFile) {
        return std::make_shared<Program>(vertexShaderFile,
                tessellationControlFile, tessellationEvalFile,
                fragmentShaderFile);
    }

    static ProgramPtr New(std::string vertexShaderFile,
            std::string tessellationControlFile,
            std::string tessellationEvalFile, std::string geometryShaderFile,
            std::string fragmentShaderFile) {
        return std::make_shared<Program>(vertexShaderFile,
                tessellationControlFile, tessellationEvalFile,
                geometryShaderFile, fragmentShaderFile);
    }

    void Link();

    GLuint GetID() {
        return _id;
    }

    bool HasVertexShader() {
        return _vs != nullptr;
    }
    bool HasFragmentShader() {
        return _fs != nullptr;
    }
    bool HasTessellationShader() {
        return (_tcs != nullptr && _tes != nullptr);
    }
    bool HasTessControlShader() {
        return _tcs != nullptr;
    }
    bool HasTessEvaluationShader() {
        return _tes != nullptr;
    }
    bool HasGeometryShader() {
        return _gs != nullptr;
    }
    bool HasComputeShader() {
        return _cs != nullptr;
    }

    void Bind();
    void Push();
    void Pop();

    //SIMPLE UNIFORMS
    void UniformMat4(std::string name, glm::mat4 matrix);

    void UniformUint(std::string name, uint32_t value);

    void UniformFloat(std::string name, float value);
    void UniformVec2f(std::string name, glm::vec2 vec);
    void UniformVec3f(std::string name, glm::vec3 vec);
    void UniformVec4f(std::string name, glm::vec4 vec);

    ~Program();

private:

};

}
;

#endif /* PROGRAM_H_ */
