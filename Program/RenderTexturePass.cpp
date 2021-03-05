/*
 * RenderTexturePass.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: root
 */

#include "RenderTexturePass.h"

namespace cgl {

const char* vert = "#version 430 core\n"
        "layout(location=0) in vec2 position;\n" //between [-1,-1]x[1,1]
        "out vec2 texCoord;\n"
        "void main() {\n"
        "    texCoord = position*0.5+0.5;\n"
        "    gl_Position = vec4(position, 0.0, 1.0);\n"
        "}\n";

const char* frag = "#version 430 core\n"
        "layout(binding=0) uniform sampler2D tex;"
        "in vec2 texCoord;\n"
        "layout(location=0) out vec4 fragColor;\n" //between [-1,-1]x[1,1]
        "void main() {\n"
        "    fragColor = texture(tex,texCoord);\n"
        "}\n";

RenderTexturePass::RenderTexturePass(Texture2DPtr tex, FragmentShaderPtr fragIn) :
        DrawPass(false) {

    VertexShaderPtr vertShader = VertexShader::New(vert);
    FragmentShaderPtr fragShader = nullptr;
    if (fragIn)
        fragShader = fragIn;
    else
        fragShader = FragmentShader::New(frag);

    _program = Program::New(vertShader, fragShader);
    _drawMode = DrawArrays::New(GL_TRIANGLE_FAN, 0, 4);

    //vertex buffer
    FloatBufferPtr vdata = FloatBuffer::New(8);
    {
        vdata->_data[0] = -1.0;
        vdata->_data[1] = -1.0;

        vdata->_data[2] = 1.0;
        vdata->_data[3] = -1.0;

        vdata->_data[4] = 1.0;
        vdata->_data[5] = 1.0;

        vdata->_data[6] = -1.0;
        vdata->_data[7] = 1.0;
    }
    VertexBufferPtr vbuff = VertexBuffer::New(true, vdata, GL_STATIC_DRAW,
            sizeof(float) * 2, 4);
		GLInfo::CheckGLError(__FILE__,__LINE__);
    vbuff->AddAttribute(2, false);

    _vertexSpec = VertexSpecification::New();
    _vertexSpec->Append(vbuff);
    _vertexSpec->Set();

    if (tex != nullptr) {
      AppendTexture(tex);
    }

}

RenderTexturePass::RenderTexturePass(Texture2DPtr tex, VertexShaderPtr vertIn, FragmentShaderPtr fragIn) :
        DrawPass(false) {

    _program = Program::New(vertIn, fragIn);
    _drawMode = DrawArrays::New(GL_TRIANGLE_FAN, 0, 4);

    //vertex buffer
    FloatBufferPtr vdata = FloatBuffer::New(8);
    {
        vdata->_data[0] = -1.0;
        vdata->_data[1] = -1.0;

        vdata->_data[2] = 1.0;
        vdata->_data[3] = -1.0;

        vdata->_data[4] = 1.0;
        vdata->_data[5] = 1.0;

        vdata->_data[6] = -1.0;
        vdata->_data[7] = 1.0;
    }
    VertexBufferPtr vbuff = VertexBuffer::New(true, vdata, GL_STATIC_DRAW,
            sizeof(float) * 2, 4);
		GLInfo::CheckGLError(__FILE__,__LINE__);
    vbuff->AddAttribute(2, false);

    _vertexSpec = VertexSpecification::New();
    _vertexSpec->Append(vbuff);
    _vertexSpec->Set();

    if (tex != nullptr) {
      AppendTexture(tex);
    }

}

}
