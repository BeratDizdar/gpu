# Example

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

    GPUX_Texture t = GPUX_LoadTextureToMemory("test.png");
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