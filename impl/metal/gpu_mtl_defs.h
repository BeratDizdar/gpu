#pragma once
#include <AppKit/AppKit.h>
#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>
#include <Quartz/Quartz.h>
#include <Cocoa/Cocoa.h>

typedef struct {
    CAMetalLayer* layer;
    id<MTLDevice> device;
    id<MTLCommandQueue> queue;
    id<MTLDrawable> surface;
} IDataMTL;