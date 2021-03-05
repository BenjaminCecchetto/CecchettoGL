#ifndef CGL_GLINFO_H
#define CGL_GLINFO_H

#include <string>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace cgl {



class GLInfo {
	static GLInfo* s_instance;

public:
    static GLInfo& GetInstance();

    std::string GetStaticInfo();
    std::string GetDynamicInfo();

    GLint MaxComputeShaderStorageBlocks, MaxCombinedShaderStorageBlocks,
            MaxComputeUniformBlocks, MaxComputeTextureImageUnits,
            MaxComputeUniformComponents, MaxComputeAtomicCounters,
            MaxComputeAtomicCounterBuffers, MaxCombinedComputeUniformComponents,
            MaxComputeWorkGroupInvocations;
    GLint MaxComputeWorkGroupCount[3];
    GLint MaxComputeWorkGroupSize[3];
    GLint MaxDebugGroupStackDepth, MajorVersion, Max3DTextureSize,
            MaxArrayTextureLayers, MaxClipDistances, MaxColorTextureSamples,
            MaxCombinedAtomicCounters, MaxCombinedFragmentUniformComponents,
            MaxCombinedGeometryUniformComponents, MaxCombinedTextureImageUnits,
            MaxCombinedUniformBlocks, MaxCombinedVertexUniformComponents,
            MaxCubeMapTextureSize, MaxDepthTextureSamples, MaxDrawBuffers,
            MaxDualSourceDrawBuffers, MaxElementsIndices, MaxElementsVertices,
            MaxFragmentAtomicCounters, MaxFragmentShaderStorageBlocks,
            MaxFragmentInputComponents, MaxFragmentUniformComponents,
            MaxFragmentUniformVectors, MaxFragmentUniformBlocks,
            MaxFramebufferWidth, MaxFramebufferHeight, MaxFramebufferLayers,
            MaxFramebufferSamples, MaxGeometryAtomicCounters,
            MaxGeometryShaderStorageBlocks, MaxGeometryInputComponents,
            MaxGeometryOutputComponents, MaxGeometryTextureImageUnits,
            MaxGeometryUniformBlocks, MaxGeometryUniformComponents,
            MaxIntegerSamples, MinMapBufferAlignment, MaxLabelLength,
            MaxProgramTexelOffset, MinProgramTexelOffset,
            MaxRectangleTextureSize, MaxRenderbufferSize, MaxSampleMaskWords;
    GLint MaxServerWaitTimeout;
    GLint MaxShaderStorageBufferBindings, MaxTessControlAtomicCounters,
            MaxTessEvaluationAtomicCounters, MaxTessControlShaderStorageBlocks,
            MaxTessEvaluationShaderStorageBlocks, MaxTextureBufferSize,
            MaxTextureImageUnits, MaxTextureLODBias, MaxTextureSize,
            MaxUniformBufferBindings, MaxUniformBlockSize, MaxUniformLocations,
            MaxVaryingComponents, MaxVaryingVectors, MaxVaryingFloats,
            MaxVertexAtomicCounters, MaxVertexAttribs,
            MaxVertexShaderStorageBlocks, MaxVertexTextureImageUnits,
            MaxVertexUniformComponents, MaxVertexUniformVectors,
            MaxVertexOutputComponents, MaxVertexUniformBlocks;
    GLint MaxViewportDims[2];
    GLint MaxViewports, MinorVersion, NumCompressedTextureFormats,
            NumExtensions, NumProgramBinaryFormats, NumShaderBinaryFormats,
            MaxVertexAttribRelativeOffset, MaxVertexAttribBindings,
            MaxElementIndex, MaxColorAttachments;
    GLint MaxTransformFeedbackBuffers,
            MaxTransformFeedbackInterleavedComponents,
            MaxTransformFeedbackSeparateAttribs,
            MaxTransformFeedbackSeparateComponents;
    GLint MaxPatchVertices, MaxImageUnits;

    static void CheckGLError(const char* file, int line);

    static uint32_t GetTypeSize(GLenum type);
private:
    GLInfo();
    GLInfo(GLInfo const&);
    void operator=(GLInfo const&);

};

}

#endif
