#include "../gpu.h"
#define GLUTILS_IMPL
#include "opengl46/miniglcorearb.h"

static struct {uint32_t bank[256];} Buffer;
static struct {uint32_t bank[256];} Texture;
static struct {
    uint32_t bank[256];
    uint32_t vert[256];
    uint32_t frag[256];
    uint32_t comp[256];
    uint32_t current;
} Pipeline;

static const char *impl__QueryProps();
static void impl__Scissor(int x, int y, int w, int h);
static void impl__Viewport(int x, int y, int w, int h);

static void impl__Clear(uint32_t r, uint32_t g, uint32_t b) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void impl__NewTexture(int id, int format, int w, int h, const void *data);
static void impl__BindTexture(int id, int slot, int filter);

static void impl__NewBuffer(int id, size_t size, const void *data) {
    if (Buffer.bank[id] != 0) {
        glDeleteBuffers(1, &Buffer.bank[id]);
    }
    glCreateBuffers(1, &Buffer.bank[id]);
    glNamedBufferStorage(Buffer.bank[id], size, data, GL_DYNAMIC_STORAGE_BIT);
}

static void impl__UpdateBuffer(int id, size_t offset, size_t size, const void *data) {
    glNamedBufferSubData(Buffer.bank[id], offset, size, data);
}

static void impl__BindBuffer(int id, int slot) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, Buffer.bank[id]);
}

static void impl__NewPipeline(int id, int shader_count, void **shader) {
    if (Pipeline.bank[id] != 0) {
        glDeleteProgramPipelines(1, &Pipeline.bank[id]);
        if (Pipeline.vert[id] != 0) { glDeleteProgram(Pipeline.vert[id]); Pipeline.vert[id] = 0; }
        if (Pipeline.frag[id] != 0) { glDeleteProgram(Pipeline.frag[id]); Pipeline.frag[id] = 0; }
        if (Pipeline.comp[id] != 0) { glDeleteProgram(Pipeline.comp[id]); Pipeline.comp[id] = 0; }
    }

    if (shader_count == 1) { // compute pipeline
        Pipeline.comp[id] = (uint32_t)glCreateShaderProgramv(GL_COMPUTE_SHADER, 1, (const char*const*)&shader[0]);
        gluIsProgramLinked(Pipeline.comp[id]);
        glCreateProgramPipelines(1, &Pipeline.bank[id]);
        glUseProgramStages(Pipeline.bank[id], GL_COMPUTE_SHADER_BIT, Pipeline.comp[id]);
    }
    else if (shader_count == 2) {
        Pipeline.vert[id] = (uint32_t)glCreateShaderProgramv(GL_VERTEX_SHADER, 1, (const char*const*)&shader[0]);
        gluIsProgramLinked(Pipeline.vert[id]);
        Pipeline.frag[id] = (uint32_t)glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, (const char*const*)&shader[1]);
        gluIsProgramLinked(Pipeline.frag[id]);
        glCreateProgramPipelines(1, &Pipeline.bank[id]);
        glUseProgramStages(Pipeline.bank[id], GL_VERTEX_SHADER_BIT, Pipeline.vert[id]);
        glUseProgramStages(Pipeline.bank[id], GL_FRAGMENT_SHADER_BIT, Pipeline.frag[id]);
    }
    else {
        return;
    }
}

static void impl__CurrentPipeline(int id) {
    glBindProgramPipeline(Pipeline.bank[id]);
    Pipeline.current = id;
}

static void impl__Draw(int type, int count) {
    if (Pipeline.vert[Pipeline.current] != 0 && Pipeline.frag[Pipeline.current] != 0) {
        uint32_t topology;
        if (type == 0) topology = GL_POINTS;
        else if (type == 1) topology = GL_LINES;
        else if (type == 2) topology = GL_TRIANGLES;
        else if (type == 3) topology = GL_TRIANGLE_STRIP;
        else return;
        glDrawArraysInstancedBaseInstance(topology, 0, count, 1, 0);
    }
    else {
        return;
    }
}

static void impl__Compute(int num_groups_x, int num_groups_y, int num_groups_z) {
    glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

static void impl__MemoryBarrier(void) {
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

static void impl__Present(void);

static IGPUDeviceVirtualTable table = {
    //.QueryProps = impl__QueryProps,
    //.Scissor = impl__Scissor,
    //.Viewport = impl__Viewport,
    .Clear = impl__Clear,
    //.NewTexture = impl__NewTexture,
    //.BindTexture = impl__BindTexture,
    .NewBuffer = impl__NewBuffer,
    .UpdateBuffer = impl__UpdateBuffer,
    .BindBuffer = impl__BindBuffer,
    .NewPipeline = impl__NewPipeline,
    .CurrentPipeline = impl__CurrentPipeline,
    .Draw = impl__Draw,
    .Compute = impl__Compute,
    .MemoryBarrier = impl__MemoryBarrier,
    //.Present = impl__Present,
};
static struct {
    IGPUDevice device[16];
    uint32_t top;
} DeviceArray;

#include <stdio.h>
IGPUDevice *GPU_GetDefaultDevice(optional const device_request_t *r) {
    gluLoadLibrary(r->get_proc_address);
    gluBindDummyVAO();
    if (DeviceArray.top <= 15) {
        IGPUDevice *device = &DeviceArray.device[DeviceArray.top++];
        device->vtbl = &table;
        return device;
    }
    return NULL;
}