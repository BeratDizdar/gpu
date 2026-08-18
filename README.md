# Example

```glsl
//main.vert
#version 460 core

out vec3 c;
void main() {

    vec2 pos[] = {
        vec2(0, 0.5),
        vec2(-0.5, -0.5),
        vec2(0.5, -0.5),
    };

    vec3 colors[] = {
        vec3(1.0, 0.0, 0.0),
        vec3(0.0, 1.0, 0.0),
        vec3(0.0, 0.0, 1.0),
    };

    gl_Position = vec4(pos[gl_VertexID], 0, 1);
    c = colors[gl_VertexID];
}

//main.frag
#version 460 core

in vec3 c;
out vec4 o;
void main() {
    o = vec4(c, 1.0);
}
```
```c
#define GPUX_IMPL
#include "gpu/gpux.h"
#include "gpu/gpu.h"
#include "swl/swl.h"

int main() {
    swl_CreateWindow("X", 800, 600);
    swl_GL_CreateContext(4, 6, 24, 8);
    IGPUDevice *device = GPU_GetDefaultDevice(&(device_request_t){
        .get_proc_address = swl_GL_GetProcAddress,
    });

    void *vert = GPUX_LoadShaderToMemory("main.vert");
    void *frag = GPUX_LoadShaderToMemory("main.frag");
    device->vtbl->NewPipeline(device, 0, 2, (void*[]){vert, frag});

    for(;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();

        device->vtbl->Clear(device, 53, 75, 75);
        device->vtbl->CurrentPipeline(device, 0);
        device->vtbl->Draw(device, 3, 4);

        swl_GL_SwapBuffers();
        swl_PollEvents();
        swl_PassScheduler();
    }

    swl_GL_DestroyContext();
    swl_CloseWindow();
    return 0;
}
```