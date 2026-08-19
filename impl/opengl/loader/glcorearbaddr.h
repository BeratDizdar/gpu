#pragma once
#include <stdint.h>
#include <stddef.h>

#define GLCOREARBADDR_CLEAR \
    X(glClear, (uint32_t mask)) \
    X(glClearColor, (float r, float g, float b, float a))

#define GLCOREARBADDR_TEXTURES \
    X(glCreateSamplers, (int32_t n, uint32_t *samplers)) \
    X(glBindSampler, (uint32_t unit, uint32_t sampler)) \
    X(glDeleteSamplers, (int32_t n, const uint32_t *samplers)) \
    X(glSamplerParameteri, (int32_t sampler, uint32_t pname, int32_t param)) \
    X(glCreateTextures, (uint32_t target, int32_t n, uint32_t *textures)) \
    X(glBindTextureUnit, (uint32_t unit, uint32_t texture)) \
    X(glDeleteTextures, (int32_t n, const uint32_t *textures)) \
    X(glTextureStorage2D, (uint32_t texture, int32_t levels, uint32_t internalformat, int32_t width, int32_t height)) \
    X(glTextureSubImage2D, (uint32_t texture, int32_t level, int32_t xoffset, int32_t yoffset, int32_t width, int32_t height, uint32_t format, uint32_t type, const void *pixels))

#define GLCOREARBADDR_BUFFERS \
    X(glCreateBuffers, (int32_t n, uint32_t* buffers)) \
    X(glBindBufferBase, (uint32_t target, uint32_t index, uint32_t buffer)) \
    X(glNamedBufferStorage, (uint32_t buffer, size_t size, const void* data, uint32_t flags)) \
    X(glNamedBufferSubData, (uint32_t buffer, size_t offset, size_t size, const void* data)) \
    X(glMapNamedBufferRange, (uint32_t buffer, intptr_t offset, size_t size, uint32_t access)) \
    X(glUnmapNamedBuffer, (uint32_t buffer)) \
    X(glDeleteBuffers, (int32_t n, const uint32_t* buffers))

#define GLCOREARBADDR_SHADERS \
    X(glCreateShaderProgramv, (uint32_t type, size_t count, const char** strings)) \
    X(glGetProgramiv, (uint32_t program, uint32_t pname, int32_t* params)) \
    X(glGetProgramInfoLog, (uint32_t program, int32_t maxLength, int32_t* length, char* infoLog)) \
    X(glUseProgramStages, (uint32_t pipeline, uint32_t stage, uint32_t program)) \
    X(glDeleteProgram, (uint32_t program)) \
    X(glCreateProgramPipelines, (int32_t n, uint32_t* pipelines)) \
    X(glBindProgramPipeline, (uint32_t pipeline)) \
    X(glDeleteProgramPipelines, (int32_t n, const uint32_t* pipelines))

#define GLCOREARBADDR_COMMANDS \
    X(glDrawArraysInstancedBaseInstance, (uint32_t mode, int32_t first, int32_t count, int32_t primcount, int32_t baseinstance)) \
    X(glDispatchCompute, (uint32_t num_groups_x, uint32_t num_groups_y, uint32_t num_groups_z)) \
    X(glMemoryBarrier, (uint32_t type)) \
    X(glViewport, (int32_t x, int32_t y, int32_t w, int32_t h)) \
    X(glScissor, (int32_t x, int32_t y, int32_t w, int32_t h))

#define GLCOREARBADDR_DUMMY \
    X(glGenVertexArrays, (int32_t n, uint32_t *array)) \
    X(glBindVertexArray, (uint32_t array))

#define GLCOREARBADDR_STATE \
    X(glEnable, (uint32_t cap)) \
    X(glBlendFunc, (uint32_t src, uint32_t dst))

#define GLCOREARBADDR \
    GLCOREARBADDR_STATE \
    GLCOREARBADDR_CLEAR \
    GLCOREARBADDR_TEXTURES \
    GLCOREARBADDR_BUFFERS \
    GLCOREARBADDR_SHADERS \
    GLCOREARBADDR_COMMANDS \
    GLCOREARBADDR_DUMMY

#define X(name, args) void*(*name)args;
    GLCOREARBADDR
#undef X