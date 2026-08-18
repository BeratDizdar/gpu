#include "../../gpu.h"
#define GLUTILS_IMPL
#include "loader/miniglcorearb.h"
#include "gpu_gl_defs.h"


//##############################################################################
//==============================================================================
// IMPLEMENTATIONS
//==============================================================================
//##############################################################################


static const char *impl__QueryProps(struct IGPUDevice *self);
static void impl__Scissor(struct IGPUDevice *self, int x, int y, int w, int h) {
    glScissor(x, y, w, h);
}

static void impl__Viewport(struct IGPUDevice *self, int x, int y, int w, int h) {
    glViewport(x, y, w, h);
}

static void impl__Clear(struct IGPUDevice *self, uint8_t r, uint8_t g, uint8_t b) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void impl__NewTexture(struct IGPUDevice *self, int id, int format, int w, int h, const void *data) {
    texture_t *t = &((IData*)self->internal)->Texture;
    if (t->bank[id] != 0) {
        glDeleteTextures(1, &t->bank[id]);
    }
    glCreateTextures(GL_TEXTURE_2D, 1, &t->bank[id]);
    glTextureStorage2D(t->bank[id], 0, format, w, h);
    glTextureSubImage2D(t->bank[id], 0, 0, 0, w, h, GL_RGBA, GL_FLOAT, data);
}

static void impl__BindTexture(struct IGPUDevice *self, int id, int slot, int filter) {
    texture_t *t = &((IData*)self->internal)->Texture;
    sampler_t *s = &((IData*)self->internal)->Sampler;
    if (t->bank[id] != 0) {
        if (filter == 0) glBindSampler(slot, s->nearest);
        else if (filter == 1) glBindSampler(slot, s->linear);
        else return;
        glBindTextureUnit(slot, t->bank[id]);
    }
    else {
        return;
    }
}

static void impl__NewBuffer(struct IGPUDevice *self, int id, size_t size, const void *data) {
    buffer_t *b = &((IData*)self->internal)->Buffer;
    if (b->bank[id] != 0) {
        glDeleteBuffers(1, &b->bank[id]);
    }
    glCreateBuffers(1, &b->bank[id]);
    glNamedBufferStorage(b->bank[id], size, data, GL_DYNAMIC_STORAGE_BIT);
}

static void impl__UpdateBuffer(struct IGPUDevice *self, int id, size_t offset, size_t size, const void *data) {
    glNamedBufferSubData(((IData*)self->internal)->Buffer.bank[id], offset, size, data);
}

static void impl__BindBuffer(struct IGPUDevice *self, int id, int slot) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, ((IData*)self->internal)->Buffer.bank[id]);
}

static void impl__NewPipeline(struct IGPUDevice *self, int id, int shader_count, void **shader) {
    pipeline_t *p = &((IData*)self->internal)->Pipeline;
    if (p->bank[id] != 0) {
        glDeleteProgramPipelines(1, &p->bank[id]);
        if (p->vert[id] != 0) { glDeleteProgram(p->vert[id]); p->vert[id] = 0; }
        if (p->frag[id] != 0) { glDeleteProgram(p->frag[id]); p->frag[id] = 0; }
        if (p->comp[id] != 0) { glDeleteProgram(p->comp[id]); p->comp[id] = 0; }
    }

    if (shader_count == 1) { // compute pipeline
        p->comp[id] = (uint32_t)glCreateShaderProgramv(GL_COMPUTE_SHADER, 1, (const char*const*)&shader[0]);
        gluIsProgramLinked(p->comp[id]);
        glCreateProgramPipelines(1, &p->bank[id]);
        glUseProgramStages(p->bank[id], GL_COMPUTE_SHADER_BIT, p->comp[id]);
    }
    else if (shader_count == 2) {
        p->vert[id] = (uint32_t)glCreateShaderProgramv(GL_VERTEX_SHADER, 1, (const char*const*)&shader[0]);
        gluIsProgramLinked(p->vert[id]);
        p->frag[id] = (uint32_t)glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, (const char*const*)&shader[1]);
        gluIsProgramLinked(p->frag[id]);
        glCreateProgramPipelines(1, &p->bank[id]);
        glUseProgramStages(p->bank[id], GL_VERTEX_SHADER_BIT, p->vert[id]);
        glUseProgramStages(p->bank[id], GL_FRAGMENT_SHADER_BIT, p->frag[id]);
    }
    else {
        return;
    }
}

static void impl__CurrentPipeline(struct IGPUDevice *self, int id) {
    glBindProgramPipeline(((IData*)self->internal)->Pipeline.bank[id]);
    ((IData*)self->internal)->Pipeline.current = id;
}

static void impl__Draw(struct IGPUDevice *self, int type, int count) {
    pipeline_t *p = &((IData*)self->internal)->Pipeline;
    if (p->vert[p->current] != 0 && p->frag[p->current] != 0) {
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

static void impl__Compute(struct IGPUDevice *self, int num_groups_x, int num_groups_y, int num_groups_z) {
    pipeline_t *p = &((IData*)self->internal)->Pipeline;
    if (p->comp[p->current] != 0) {
        glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    }
    else {
        return;
    }
}

static void impl__MemoryBarrier(struct IGPUDevice *self) {
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

static void impl__Present(struct IGPUDevice *self);


//##############################################################################
//==============================================================================
// MAIN
//==============================================================================
//##############################################################################


static IGPUDeviceVirtualTable table = {
    //.QueryProps = impl__QueryProps,
    .Scissor = impl__Scissor,
    .Viewport = impl__Viewport,
    .Clear = impl__Clear,
    .NewTexture = impl__NewTexture,
    .BindTexture = impl__BindTexture,
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
    IData idata[16];
    uint32_t top;
} DeviceArray;

IGPUDevice *GPU_GetDefaultDevice(optional const device_request_t *r) {
    gluLoadLibrary(r->get_proc_address);
    gluBindDummyVAO();
    if (DeviceArray.top <= 15) {
        IGPUDevice *device = &DeviceArray.device[DeviceArray.top];
        device->vtbl = &table;
        device->internal = &DeviceArray.idata[DeviceArray.top++];

        sampler_t *s = &((IData*)DeviceArray.device->internal)->Sampler;
        glCreateSamplers(1, &s->nearest);
        glCreateSamplers(1, &s->linear);
        glSamplerParameteri(s->nearest, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(s->nearest, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(s->linear, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(s->linear, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        return device;
    }
    return 0;
}