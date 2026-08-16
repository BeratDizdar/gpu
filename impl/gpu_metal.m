#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import <Quartz/Quartz.h>
#import <Cocoa/Cocoa.h>
#import "../gpu.h"

static id<MTLDevice> device;
static id<MTLCommandQueue> queue;
static id<CAMetalDrawable> drawable;
static id<MTLCommandBuffer> cb;
static id<MTLRenderCommandEncoder> encoder;
static CAMetalLayer* layer;
static id<MTLBuffer> Buffer[256];

static MTLRenderPassDescriptor *pass;
static bool encoder_open = NO;

void mtl__Scissor(int x, int y, int w, int h) {
    MTLScissorRect rect = { (NSUInteger)x, (NSUInteger)y, (NSUInteger)w, (NSUInteger)h };
    [encoder setScissorRect:rect];
}

void mtl__Clear(uint8_t r, uint8_t g, uint8_t b) {
    drawable = [layer nextDrawable];
    cb = [queue commandBuffer];

    pass = [MTLRenderPassDescriptor renderPassDescriptor];
    pass.colorAttachments[0].texture = drawable.texture;
    pass.colorAttachments[0].loadAction = MTLLoadActionClear;
    pass.colorAttachments[0].clearColor = (MTLClearColor){r/255.0, g/255.0, b/255.0, 1.0};
    pass.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    encoder = [cb renderCommandEncoderWithDescriptor:pass];
    encoder_open = YES;
}

void mtl__NewBuffer(int id, size_t size, const void *data) {
    Buffer[id] = data
        ? [device newBufferWithBytes:data length:size options:MTLResourceStorageModeShared]
        : [device newBufferWithLength:size options:MTLResourceStorageModeShared];
}

void mtl__BindBuffer(int id, int slot) {
    [encoder setVertexBuffer:Buffer[id] offset:0 atIndex:slot];
}

void mtl__Present(void) {
    [encoder endEncoding];
    [cb presentDrawable:drawable];
    [cb commit];
    encoder_open = NO;
}

static IGPUDeviceVirtualTable table = {
    .Scissor = mtl__Scissor,
    .Clear = mtl__Clear,
    .NewBuffer = mtl__NewBuffer,
    .BindBuffer = mtl__BindBuffer,
    .Present = mtl__Present
};

static struct {
    IGPUDevice device[16];
    uint32_t top;
} DeviceArray;

IGPUDevice *GPU_GetDefaultDevice(optional const device_request_t *r) {
    device = MTLCreateSystemDefaultDevice();
    queue = [device newCommandQueue];
    NSWindow *window = (__bridge NSWindow *)r->native_window;
    NSView *view = window.contentView;
    view.wantsLayer = YES;

    layer = [CAMetalLayer layer];
    layer.device = device;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.framebufferOnly = YES;
    layer.frame = view.bounds;

    view.layer = layer;

    if (DeviceArray.top <= 15) {
        IGPUDevice *dev = &DeviceArray.device[DeviceArray.top++];
        dev->vtbl = &table;
        return dev;
    }
    return NULL;
}