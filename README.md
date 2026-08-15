# Example

```c
#include "gpu/gpu.h"
#include "swl/swl.h"
#include <stdio.h>

int main() {
    swl_CreateWindow("X", 800, 600);
    swl_GL_CreateContext(4, 6, 24, 8);
    IGPUDevice *device = GPU_GetDefaultDevice(&(device_request_t){
        .get_proc_address = swl_GL_GetProcAddress
    });

    char buf[2][8192] = {0};
    FILE *i;
    i = fopen("main.vert", "rb");
    fread(buf[0], 1, 8191, i); fclose(i);
    i = fopen("main.frag", "rb");
    fread(buf[1], 1, 8191, i); fclose(i);
    
    void *src[2];
    src[0] = buf[0];
    src[1] = buf[1];

    device->vtbl->NewPipeline(0, 2, src);

    for(;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();
        
        device->vtbl->Clear(53, 75, 75);
        device->vtbl->CurrentPipeline(0);

        device->vtbl->Draw(3, 4);

        swl_GL_SwapBuffers();
        swl_PollEvents();
        swl_PassScheduler();
    }

    swl_GL_DestroyContext();
    swl_CloseWindow();
    return 0;
}
```