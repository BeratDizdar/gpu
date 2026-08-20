/*
- KESKIN bir kural kümesi olmayacak.
- Amaç ortak noktada buluşturmak. Bunun için farklı teknikler kullanılabilir.
- Sonuçta olay veri gönder, veri işle[, veri al] olduğu için kolaylık olmalı.
- Bu konuda implemente edene sorumluluk düşecek.
- Referans olarak kendi resmi implementasyonlarım olacak.
- 2 farklı Vulkan implementasyonu farklı teknikler kullanıp farklı performanslar
verebilecek.
- Biraz driver yaklaşımı gibi düşünülebilir.
*/

#pragma once
#include <stdint.h>
#include <stddef.h>
#define guaranteed(_count) /* impl'da garanti edilen */
#define optional /* opsiyonel argüman */
#define impl_diff

typedef struct { // devamını düşüneceğim bir ara
    impl_diff void*(*get_proc_address)(const char*);
    impl_diff void *native_window;
    guaranteed(256) uint16_t min_buffer_objects; // acaba bunlara max mı desem?
    guaranteed(256) uint16_t min_texture_objects;
    guaranteed(256) uint16_t min_pipeline_objects;
} device_request_t;

#ifdef __cplusplus

struct IGPUDevice {
    // henüz renderbuffer, framebuffer gibi şeyler eklemeyeceğim. 
    // Stencil, depth falan da zira basit tutmak istiyorum şimdilik.
    // eğer gerekli olduğunu hissedersem direkt ekleyeceğim.
    virtual const char *QueryProps() = 0;

    // basit yapılar işte
    virtual void Scissor(int x, int y, int w, int h) = 0;
    virtual void Viewport(int x, int y, int w, int h) = 0;
    virtual void Clear(uint8_t r, uint8_t g, uint8_t b) = 0;

    // format tipleri olarak unsigned int mi kullanmalıyım yoksa formata göre
    // değişiyor mu???
    // format:
    // [0, 3]   = {RGBA8, RGBA4, RGB5_A1, RGBA2}
    // (3, ???] = impl extension
    virtual void NewTexture(int id, int format, int w, int h, const void *data) = 0;
    // filter:
    // [0, 1]   = {NEAREST, LINEAR}
    // (1, ???] = impl extension
    virtual void BindTexture(int id, int slot, int filter) = 0;

    // data float* veriliyor varsayılıyor şuanlık
    // merak etmeyin çok hızlı değiştireceğim sonrasında bu durumu
    virtual void NewBuffer(int id, size_t size, const void *data) = 0;
    virtual void UpdateBuffer(int id, size_t offset, size_t size, const void *data) = 0;
    virtual void BindBuffer(int id, int slot) = 0;

    // ve burada da implemente edenler istediği shaderi arkada impl etsinler
    // diye böyle yaptım.
    // software port içinde aklımda bir VM yazıp üzerinde çalıştırmak var.
    // evet impl kısmına bıraktım. bunun sıkıntı bir sonucu var impl karar verecek
    // ne olduğuna, bu hem iyi hem kötü.
    // nihai çözümü bu apiye özgü bir SHADER IR olması. fakat henüz yapamam.
    // bu nedenle şuanlık böyle olması yeterli
    virtual void NewPipeline(int id, int shader_count, void **shader) = 0;
    virtual void CurrentPipeline(int id) = 0;

    // normalde bu execute içinde type'ın tipi topology_t olacaktı fakat int
    // demeyi daha uygun gördüm zira implemente edenler desteğine göre içeride
    // planlayıp dışarıya bunu söyleyebilir
    // count parametresi aslında vertex_id gibi olacak
    // type:
    // [0, 4]   = {POINT, LINE, LINE_STRIP, TRIANGLE, TRIANGLE_STRIP}
    // (4, ???] = impl extension
    virtual void Draw(int type, int count) = 0;
    virtual void Compute(int num_groups_x, int num_groups_y, int num_groups_z) = 0;
    virtual void MemoryBarrier() = 0;

    // opengl ise zaten hatayı kendi içinde verir.
    virtual void Present() = 0;
};

extern "C" IGPUDevice *GPU_GetDefaultDevice(optional const device_request_t *r);

#else

struct IGPUDevice;

typedef struct {
    const char *(*QueryProps)(struct IGPUDevice *self);
    void (*Scissor)(struct IGPUDevice *self, int x, int y, int w, int h);
    void (*Viewport)(struct IGPUDevice *self, int x, int y, int w, int h);
    void (*Clear)(struct IGPUDevice *self, uint8_t r, uint8_t g, uint8_t b);
    void (*NewTexture)(struct IGPUDevice *self, int id, int format, int w, int h, const void *data);
    void (*BindTexture)(struct IGPUDevice *self, int id, int slot, int filter);
    void (*NewBuffer)(struct IGPUDevice *self, int id, size_t size, const void *data);
    void (*UpdateBuffer)(struct IGPUDevice *self, int id, size_t offset, size_t size, const void *data);
    void (*BindBuffer)(struct IGPUDevice *self, int id, int slot);
    void (*NewPipeline)(struct IGPUDevice *self, int id, int shader_count, void **shader);
    void (*CurrentPipeline)(struct IGPUDevice *self, int id);
    void (*Draw)(struct IGPUDevice *self, int type, int count);
    void (*Compute)(struct IGPUDevice *self, int num_groups_x, int num_groups_y, int num_groups_z);
    void (*MemoryBarrier)(struct IGPUDevice *self);
    void (*Present)(struct IGPUDevice *self);
} IGPUDeviceVirtualTable;

typedef struct IGPUDevice {
    IGPUDeviceVirtualTable *vtbl;
    void *internal;
} IGPUDevice;

IGPUDevice *GPU_GetDefaultDevice(optional const device_request_t *r);

#endif