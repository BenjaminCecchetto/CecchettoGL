#include "GLInfo.h"
#include <sstream>
#include <iostream>

namespace cgl {

GLInfo* GLInfo::s_instance = 0;


GLInfo& GLInfo::GetInstance() {
	if (!s_instance)
		s_instance = new GLInfo();
	return *s_instance;
}


//set the static variables
GLInfo::GLInfo() {
    glGetIntegerv(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
            &MaxComputeShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS,
            &MaxCombinedShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_BLOCKS, &MaxComputeUniformBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
            &MaxComputeTextureImageUnits);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS,
            &MaxComputeUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTERS, &MaxComputeAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
            &MaxComputeAtomicCounterBuffers);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,
            &MaxCombinedComputeUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
            &MaxComputeWorkGroupInvocations);CheckGLError(__FILE__, __LINE__);  //1

	for (uint32_t i = 0; i < 3; i++) {
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT,i, &MaxComputeWorkGroupCount[i]);CheckGLError(__FILE__, __LINE__);  //3    
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, i, &MaxComputeWorkGroupSize[i]);CheckGLError(__FILE__, __LINE__);  //3
	}

    glGetIntegerv(GL_MAX_DEBUG_GROUP_STACK_DEPTH, &MaxDebugGroupStackDepth);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &Max3DTextureSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &MaxArrayTextureLayers);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_CLIP_DISTANCES, &MaxClipDistances);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &MaxColorTextureSamples);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTERS, &MaxCombinedAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
            &MaxCombinedFragmentUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
            &MaxCombinedGeometryUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
            &MaxCombinedTextureImageUnits);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &MaxCombinedUniformBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
            &MaxCombinedVertexUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &MaxCubeMapTextureSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_DEPTH_TEXTURE_SAMPLES, &MaxDepthTextureSamples);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &MaxDrawBuffers);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, &MaxDualSourceDrawBuffers);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &MaxElementsIndices);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &MaxElementsVertices);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTERS, &MaxFragmentAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS,
            &MaxFragmentShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS,
            &MaxFragmentInputComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
            &MaxFragmentUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &MaxFragmentUniformVectors);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &MaxFragmentUniformBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &MaxFramebufferWidth);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &MaxFramebufferHeight);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAMEBUFFER_LAYERS, &MaxFramebufferLayers);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES, &MaxFramebufferSamples);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTERS, &MaxGeometryAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS,
            &MaxGeometryShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS,
            &MaxGeometryInputComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,
            &MaxGeometryOutputComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,
            &MaxGeometryTextureImageUnits);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &MaxGeometryUniformBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,
            &MaxGeometryUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_INTEGER_SAMPLES, &MaxIntegerSamples);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MIN_MAP_BUFFER_ALIGNMENT, &MinMapBufferAlignment);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_LABEL_LENGTH, &MaxLabelLength);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_PROGRAM_TEXEL_OFFSET, &MaxProgramTexelOffset);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MIN_PROGRAM_TEXEL_OFFSET, &MinProgramTexelOffset);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE, &MaxRectangleTextureSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &MaxRenderbufferSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_SAMPLE_MASK_WORDS, &MaxSampleMaskWords);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_SERVER_WAIT_TIMEOUT, &MaxServerWaitTimeout);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS,
            &MaxShaderStorageBufferBindings);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS,
            &MaxTessControlAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS,
            &MaxTessEvaluationAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS,
            &MaxTessControlShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS,
            &MaxTessEvaluationShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &MaxTextureBufferSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextureImageUnits);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TEXTURE_LOD_BIAS, &MaxTextureLODBias);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &MaxTextureSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &MaxUniformBufferBindings);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &MaxUniformBlockSize);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &MaxUniformLocations);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VARYING_COMPONENTS, &MaxVaryingComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VARYING_VECTORS, &MaxVaryingVectors);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VARYING_FLOATS, &MaxVaryingFloats);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTERS, &MaxVertexAtomicCounters);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttribs);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS,
            &MaxVertexShaderStorageBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
            &MaxVertexTextureImageUnits);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS,
            &MaxVertexUniformComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &MaxVertexUniformVectors);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &MaxVertexOutputComponents);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &MaxVertexUniformBlocks);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, MaxViewportDims);CheckGLError(__FILE__, __LINE__);  //2
    glGetIntegerv(GL_MAX_VIEWPORTS, &MaxViewports);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS,
            &NumCompressedTextureFormats);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_NUM_EXTENSIONS, &NumExtensions);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &NumProgramBinaryFormats);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &NumShaderBinaryFormats);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET,
            &MaxVertexAttribRelativeOffset);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &MaxVertexAttribBindings);CheckGLError(__FILE__, __LINE__);  //1
    glGetIntegerv(GL_MAX_ELEMENT_INDEX, &MaxElementIndex);CheckGLError(__FILE__, __LINE__);  //1

    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &MaxColorAttachments);CheckGLError(__FILE__, __LINE__); 
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_BUFFERS,
            &MaxTransformFeedbackBuffers);CheckGLError(__FILE__, __LINE__); 
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS,
            &MaxTransformFeedbackInterleavedComponents);CheckGLError(__FILE__, __LINE__); 
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS,
            &MaxTransformFeedbackSeparateAttribs);CheckGLError(__FILE__, __LINE__); 
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS,
            &MaxTransformFeedbackSeparateComponents);CheckGLError(__FILE__, __LINE__); 
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);CheckGLError(__FILE__, __LINE__); 
    glGetIntegerv(GL_MAX_IMAGE_UNITS, &MaxImageUnits);CheckGLError(__FILE__, __LINE__);  


}

std::string GLInfo::GetStaticInfo() {
    std::stringstream ss;

    ss << "OpenGL " << MajorVersion << "." << MinorVersion;
    ss << std::endl << "MaxComputeShaderStorageBlocks "
            << MaxComputeShaderStorageBlocks;
    ss << std::endl << "MaxCombinedShaderStorageBlocks "
            << MaxCombinedShaderStorageBlocks;
    ss << std::endl << "MaxComputeUniformBlocks " << MaxComputeUniformBlocks;
    ss << std::endl << "MaxComputeTextureImageUnits "
            << MaxComputeTextureImageUnits;
    ss << std::endl << "MaxComputeUniformComponents "
            << MaxComputeUniformComponents;
    ss << std::endl << "MaxComputeAtomicCounters "
            << MaxComputeUniformComponents;
    ss << std::endl << "MaxComputeAtomicCounterBuffers "
            << MaxComputeAtomicCounterBuffers;
    ss << std::endl << "MaxCombinedComputeUniformComponents "
            << MaxCombinedComputeUniformComponents;
    ss << std::endl << "MaxComputeWorkGroupInvocations "
            << MaxComputeWorkGroupInvocations;
    ss << std::endl << "MaxComputeWorkGroupCount[3] "
            << MaxComputeWorkGroupCount[0] << " " << MaxComputeWorkGroupCount[1]
            << " " << MaxComputeWorkGroupCount[2];
    ss << std::endl << "MaxComputeWorkGroupSize[3] "
            << MaxComputeWorkGroupSize[0] << " " << MaxComputeWorkGroupSize[1]
            << " " << MaxComputeWorkGroupSize[2];
    ss << std::endl << "MaxDebugGroupStackDepth " << MaxDebugGroupStackDepth;

    ss << std::endl << "Max3DTextureSize " << Max3DTextureSize;
    ss << std::endl << "MaxArrayTextureLayers " << MaxArrayTextureLayers;
    ss << std::endl << "MaxClipDistances " << MaxClipDistances;
    ss << std::endl << "MaxColorTextureSamples " << MaxColorTextureSamples;
    ss << std::endl << "MaxCombinedAtomicCounters "
            << MaxCombinedAtomicCounters;
    ss << std::endl << "MaxCombinedFragmentUniformComponents "
            << MaxCombinedFragmentUniformComponents;
    ss << std::endl << "MaxCombinedGeometryUniformComponents "
            << MaxCombinedGeometryUniformComponents;
    ss << std::endl << "MaxCombinedTextureImageUnits "
            << MaxCombinedTextureImageUnits;
    ss << std::endl << "MaxCombinedUniformBlocks " << MaxCombinedUniformBlocks;
    ss << std::endl << "MaxCombinedVertexUniformComponents "
            << MaxCombinedVertexUniformComponents;
    ss << std::endl << "MaxCubeMapTextureSize " << MaxCubeMapTextureSize;
    ss << std::endl << "MaxDepthTextureSamples " << MaxDepthTextureSamples;
    ss << std::endl << "MaxDrawBuffers " << MaxDrawBuffers;
    ss << std::endl << "MaxDualSourceDrawBuffers " << MaxDualSourceDrawBuffers;
    ss << std::endl << "MaxElementsIndices " << MaxElementsIndices;
    ss << std::endl << "MaxElementsVertices " << MaxElementsVertices;
    ss << std::endl << "MaxFragmentAtomicCounters "
            << MaxFragmentAtomicCounters;
    ss << std::endl << "MaxFragmentShaderStorageBlocks "
            << MaxFragmentShaderStorageBlocks;
    ss << std::endl << "MaxFragmentInputComponents "
            << MaxFragmentInputComponents;
    ss << std::endl << "MaxFragmentUniformComponents "
            << MaxFragmentUniformComponents;
    ss << std::endl << "MaxFragmentUniformVectors "
            << MaxFragmentUniformVectors;
    ss << std::endl << "MaxFragmentUniformBlocks " << MaxFragmentUniformBlocks;
    ss << std::endl << "MaxFramebufferWidth " << MaxFramebufferWidth;
    ss << std::endl << "MaxFramebufferHeight " << MaxFramebufferHeight;
    ss << std::endl << "MaxFramebufferLayers " << MaxFramebufferLayers;
    ss << std::endl << "MaxFramebufferSamples " << MaxFramebufferSamples;
    ss << std::endl << "MaxGeometryAtomicCounters "
            << MaxGeometryAtomicCounters;
    ss << std::endl << "MaxGeometryShaderStorageBlocks "
            << MaxGeometryShaderStorageBlocks;
    ss << std::endl << "MaxGeometryInputComponents "
            << MaxGeometryInputComponents;
    ss << std::endl << "MaxGeometryOutputComponents "
            << MaxGeometryOutputComponents;
    ss << std::endl << "MaxGeometryTextureImageUnits "
            << MaxGeometryTextureImageUnits;
    ss << std::endl << "MaxGeometryUniformBlocks " << MaxGeometryUniformBlocks;
    ss << std::endl << "MaxGeometryUniformComponents "
            << MaxGeometryUniformComponents;
    ss << std::endl << "MaxIntegerSamples " << MaxIntegerSamples;
    ss << std::endl << "MinMapBufferAlignment " << MinMapBufferAlignment;
    ss << std::endl << "MaxLabelLength " << MaxLabelLength;
    ss << std::endl << "MaxProgramTexelOffset " << MaxProgramTexelOffset;
    ss << std::endl << "MinProgramTexelOffset " << MinProgramTexelOffset;
    ss << std::endl << "MaxRectangleTextureSize " << MaxRectangleTextureSize;
    ss << std::endl << "MaxRenderbufferSize " << MaxRenderbufferSize;
    ss << std::endl << "MaxSampleMaskWords " << MaxSampleMaskWords;
    ss << std::endl << "MaxServerWaitTimeout " << MaxServerWaitTimeout;
    ss << std::endl << "MaxShaderStorageBufferBindings "
            << MaxShaderStorageBufferBindings;
    ss << std::endl << "MaxTessControlAtomicCounters "
            << MaxTessControlAtomicCounters;
    ss << std::endl << "MaxTessEvaluationAtomicCounters "
            << MaxTessEvaluationAtomicCounters;
    ss << std::endl << "MaxTessControlShaderStorageBlocks "
            << MaxTessControlShaderStorageBlocks;
    ss << std::endl << "MaxTessEvaluationShaderStorageBlocks "
            << MaxTessEvaluationShaderStorageBlocks;
    ss << std::endl << "MaxTextureBufferSize " << MaxTextureBufferSize;
    ss << std::endl << "MaxTextureImageUnits " << MaxTextureImageUnits;
    ss << std::endl << "MaxTextureLODBias " << MaxTextureLODBias;
    ss << std::endl << "MaxTextureSize " << MaxTextureSize;
    ss << std::endl << "MaxUniformBufferBindings " << MaxUniformBufferBindings;
    ss << std::endl << "MaxUniformBlockSize " << MaxUniformBlockSize;
    ss << std::endl << "MaxUniformLocations " << MaxUniformLocations;
    ss << std::endl << "MaxVaryingComponents " << MaxVaryingComponents;
    ss << std::endl << "MaxVaryingVectors " << MaxVaryingVectors;
    ss << std::endl << "MaxVaryingFloats " << MaxVaryingFloats;
    ss << std::endl << "MaxVertexAtomicCounters " << MaxVertexAtomicCounters;
    ss << std::endl << "MaxVertexAttribs " << MaxVertexAttribs;
    ss << std::endl << "MaxVertexShaderStorageBlocks "
            << MaxVertexShaderStorageBlocks;
    ss << std::endl << "MaxVertexTextureImageUnits "
            << MaxVertexTextureImageUnits;
    ss << std::endl << "MaxVertexUniformComponents "
            << MaxVertexUniformComponents;
    ss << std::endl << "MaxVertexUniformVectors " << MaxVertexUniformVectors;
    ss << std::endl << "MaxVertexOutputComponents "
            << MaxVertexOutputComponents;
    ss << std::endl << "MaxVertexUniformBlocks " << MaxVertexUniformBlocks;
    ss << std::endl << "MaxViewportDims[2] " << MaxViewportDims[0] << " "
            << MaxViewportDims[1];
    ss << std::endl << "MaxViewports " << MaxViewports;
    ss << std::endl << "NumCompressedTextureFormats "
            << NumCompressedTextureFormats;
    ss << std::endl << "NumExtensions " << NumExtensions;
    ss << std::endl << "NumProgramBinaryFormats " << NumProgramBinaryFormats;
    ss << std::endl << "NumShaderBinaryFormats " << NumShaderBinaryFormats;
    ss << std::endl << "MaxVertexAttribRelativeOffset "
            << MaxVertexAttribRelativeOffset;
    ss << std::endl << "MaxVertexAttribBindings " << MaxVertexAttribBindings;
    ss << std::endl << "MaxElementIndex " << MaxElementIndex;
    ss << std::endl << "MaxColorAttachments " << MaxColorAttachments;

    ss << std::endl << "MaxTransformFeedbackBuffers "
            << MaxTransformFeedbackBuffers;
    ss << std::endl << "MaxTransformFeedbackInterleavedComponents "
            << MaxTransformFeedbackInterleavedComponents;
    ss << std::endl << "MaxTransformFeedbackSeparateAttribs "
            << MaxTransformFeedbackSeparateAttribs;
    ss << std::endl << "MaxTransformFeedbackSeparateComponents "
            << MaxTransformFeedbackSeparateComponents;
    ss << std::endl << "MaxPatchVertices " << MaxPatchVertices;
    ss << std::endl << "MaxImageUnits " << MaxImageUnits;
    return ss.str();

}

void GLInfo::CheckGLError(const char* file, int line) {
    GLenum err = glGetError();
    switch (err) {
    case GL_NO_ERROR:
        return;
        break;
    case GL_INVALID_ENUM:
        std::cerr << "Invalid Enum";
        break;
    case GL_INVALID_VALUE:
        std::cerr << "Invalid Value";
        break;
    case GL_INVALID_OPERATION:
        std::cerr << "Invalid Operation";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cerr << "Invalid Framebuffer Operation";
        break;
    case GL_OUT_OF_MEMORY:
        std::cerr << "Out of Memory";
        break;
    case GL_STACK_UNDERFLOW:
        std::cerr << "Stack Underflow";
        break;
    case GL_STACK_OVERFLOW:
        std::cerr << "Stack Overflow";
        break;
    }
    std::cerr << " OpenGL Error in file:" << file << ":" << line << std::endl;
}

uint32_t GLInfo::GetTypeSize(GLenum type) {
    switch (type) {
    case GL_BYTE:
        return sizeof(GLbyte);
    case GL_UNSIGNED_BYTE:
        return sizeof(GLubyte);
    case GL_SHORT:
        return sizeof(GLshort);
    case GL_UNSIGNED_SHORT:
        return sizeof(GLushort);
    case GL_INT:
        return sizeof(GLint);
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    case GL_FLOAT:
        return sizeof(GLfloat);
    case GL_DOUBLE:
        return sizeof(GLdouble);
    }
    return 0;
}

}
