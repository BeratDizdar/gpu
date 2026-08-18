#pragma once

#include <stdint.h>

void gluLoadLibrary(void*(*gl_getprocaddres)(const char*));
void gluBindDummyVAO();
uint32_t gluCreateShaderProgramvFromFile(uint32_t type, const char *path);
int gluIsProgramLinked(uint32_t program);

#ifdef GLUTILS_IMPL

#include <stdio.h>
#include <stdlib.h>

void gluLoadLibrary(void*(*gl_getprocaddres)(const char*)) {
    #define X(name, args) name = gl_getprocaddres(#name);
        GLCOREARBADDR
    #undef X
}

void gluBindDummyVAO() {
    uint32_t dummy;
    glGenVertexArrays(1, &dummy);
    glBindVertexArray(dummy);
}

uint32_t gluCreateShaderProgramvFromFile(uint32_t type, const char *path) {
    char buf[8192] = {0};
    FILE *i;
    if (i = fopen(path, "rb")) {
        fread(buf, 1, 8191, i); fclose(i);
        const char *src = buf;
        return (uint32_t)glCreateShaderProgramv(type, 1, &src); 
    }
    return 0;
}

int gluIsProgramLinked(uint32_t program) {
    int32_t isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        int32_t maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = (char*)malloc(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
        return 0;
    }
    return 1;
}

#endif