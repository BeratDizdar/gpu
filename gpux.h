#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *heap_data;
    int width, height;
    size_t size_of_bytes;
} GPUX_Texture;

GPUX_Texture GPUX_LoadTextureToMemory(const char *path);
void *GPUX_LoadShaderToMemory(const char *path);

#ifdef GPUX_IMPL

#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "depen/stb_image.h"
#include <stdio.h>
#include <stdlib.h>

GPUX_Texture GPUX_LoadTextureToMemory(const char *path) {
    GPUX_Texture tex;
    int comp;

    tex.heap_data = stbi_load(path, &tex.width, &tex.height, &comp, 4);
    if (tex.heap_data != NULL) {
        tex.size_of_bytes = tex.width * tex.height * 4;
        printf("GPUX_TEXTURE: [%s] (%.2f MB) {%dx%d}\n", path, tex.size_of_bytes/(1024.0*1024.0), tex.width, tex.height);
        return tex;
    }

    printf("GPUX_LoadTextureToMemory(%s) ???\n", path);
    return (GPUX_Texture){0};
}

void *GPUX_LoadShaderToMemory(const char *path) {
    char b[8192] = {0};
    FILE *i = fopen(path, "rb");
    if (i == NULL) {
        printf("GPUX_LoadShaderToMemory(%s) ???\n", path);
        return NULL;
    }

    fseek(i, 0, SEEK_END);
    size_t len = ftell(i);
    rewind(i);
    char *ptr = malloc(len + 1);
    if (ptr != NULL) {
        fread(ptr, 1, len, i);
        ptr[len] = '\0';
    }
    fclose(i);

    if (ptr != NULL) {
        printf("GPUX_SHADER: [%s] (%zu byte)\n", path, len);
    }

    return (void*)ptr;
}

#endif