#pragma once
#include <stdint.h>
typedef struct {uint32_t bank[256];} buffer_t;
typedef struct {uint32_t bank[256];} texture_t;
typedef struct {
    uint32_t bank[256];
    uint32_t vert[256];
    uint32_t frag[256];
    uint32_t comp[256];
    uint32_t current;
} pipeline_t;
typedef struct {
    uint32_t nearest;
    uint32_t linear;
} sampler_t;

typedef struct { /* INTERNAL DATA */
    buffer_t Buffer;
    texture_t Texture;
    pipeline_t Pipeline;
    sampler_t Sampler;
} IData;