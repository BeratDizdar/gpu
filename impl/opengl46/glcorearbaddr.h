#pragma once
#include <stdint.h>
#include <stddef.h>

#define GLCOREARBADDR_CLEAR \
    X(glClear, (uint32_t mask)) \
    X(glClearColor, (float r, float g, float b, float a))

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
    X(glMemoryBarrier, (uint32_t type))

#define GLCOREARBADDR_DUMMY \
    X(glGenVertexArrays, (int32_t n, uint32_t *array)) \
    X(glBindVertexArray, (uint32_t array))

#define GLCOREARBADDR \
    GLCOREARBADDR_CLEAR \
    GLCOREARBADDR_BUFFERS \
    GLCOREARBADDR_SHADERS \
    GLCOREARBADDR_COMMANDS \
    GLCOREARBADDR_DUMMY

#define X(name, args) void*(*name)args;
    GLCOREARBADDR
#undef X