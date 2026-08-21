/* IGPUDevice ==================================================================
    Implementasyona dayalı bir api yaratmak istedim. Eğer benim yarattığım 
referans niteliğindeki yapısı sevmezseniz kendiniz yapmakta özgürsünüz.
Kesin bir kural kümesi olmayacak. Farklı teknikler kullanılabilir. Sonuçta
olay veri gönder, işle[, al] olduğu için kolaylık olmalı. Haliyle 2 farklı
Vulkan implementasyonu farklı teknikler kullanıp farklı performanslar verebilir.
    `New*` ile yarattığımız yapılar için `Delete*` gibi varyasyonların olmama 
sebebi heap kullanımına bu konularda karşı olmam. Bütün API boyunca kendi 
fikrimi dayattığım tek konu bu olacak.
    Herkese kolay gelsin.

* PLAN *
    * Henüz renderbuffer, framebuffer gibi şeyler eklemeyeceğim. 
    * Stencil, depth falan da zira basit tutmak istiyorum şimdilik.
    * Eğer gerekli olduğunu hissedersem direkt ekleyeceğim.
    * NewTexture için veri tipi istemeli.
    * QueryProps için sorgu sabitleri olmalı.

INFO ---------------------------------------------------------------------------

- QueryProps -> Donanım ile ilgili bilgiler

PIXEL-TEST ---------------------------------------------------------------------

- Scissor -> Piksel başına kesme testi

COORDINATE ---------------------------------------------------------------------

- Viewport -> Görüş alanı ayarı

TEXTURE ------------------------------------------------------------------------

- NewTexture:
    Belirli doku slotuna yeni doku ekle
    Yeni doku eklemek eskisinin temizlenmesi anlamına gelir
    Doku formatları için sabitler:
    - [0, 3]   = {RGBA8, RGBA4, RGB5_A1, RGBA2}
    - (3, ???] = impl extension
- BindTexture: 
    Belirli doku slotunu donanım için aktif birime koyar
    Filtre formatları için sabitler:
    - [0, 1]   = {NEAREST, LINEAR}
    - (1, ???] = impl extension

BUFFER -------------------------------------------------------------------------

- NewBuffer:
    Belirli veri slotuna yeni veri ekle
    Yeni veri eklemek eskisinin temizlenmesi anlamına gelir
- UpdateBuffer -> Belirli veri slotundaki veriyi güncelle
- BindBuffer -> Belirli veri slotunu donanım için aktif birime koyar

PIPELINE -----------------------------------------------------------------------
    Shader program işleme kısmını tek bir pipeline yapısında planladım. Hangi 
program tipini kullanacağınız implementasyona kalsa bile benim tercihim, verilen
`shader_count`a göre comp veya vert+frag şeklinde işlenmesi yönünde.
    Nihai çözüm için aklımda bir "ShaderIR" yaratmak var. Fakat şimdilik böyle 
bırakıyorum. :P

- NewPipeline:
    Belirli pipeline slotuna yenisini ekle
    Yeni pipeline eklemek eskisinin temizlenmesi anlamına gelir
- CurrentPipeline -> Seçili pipeline slotunu aktif et

COMMAND ------------------------------------------------------------------------

- Draw:
    Çizim komutunu gönder (vert+frag pipeline)
    Çizim topolojileri için sabitler:
    - [0, 4]   = {POINT, LINE, LINE_STRIP, TRIANGLE, TRIANGLE_STRIP}
    - (4, ???] = impl extension
- Compute -> İşleme komutunu gönder (comp pipeline)
- MemoryBarrier -> VRAM veri yarışını engeller

FRAMEBUFFER --------------------------------------------------------------------

- Clear -> Aktif yüzeyi temizle
- Present:
    İşlenen yüzeyi ekrana bas
    OpenGL için gerekli değil

==============================================================================*/

#pragma once
#include <stdint.h>
#include <stddef.h>
#define guaranteed(_count) /* impl'da garanti edilen */
#define optional /* opsiyonel argüman */
#define impl_diff

typedef struct { // devamını düşüneceğim bir ara
    impl_diff void*(*get_proc_address)(const char*);
    impl_diff void *native_window;
    guaranteed(256) uint16_t max_buffer_objects;
    guaranteed(256) uint16_t max_texture_objects;
    guaranteed(256) uint16_t max_pipeline_objects;
} device_request_t;

#ifdef __cplusplus

struct IGPUDevice {
    virtual const char *QueryProps() = 0;
    virtual void Scissor(int x, int y, int w, int h) = 0;
    virtual void Viewport(int x, int y, int w, int h) = 0;
    virtual void Clear(uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void NewTexture(int id, int format, int w, int h, const void *data) = 0;
    virtual void BindTexture(int id, int slot, int filter) = 0;
    virtual void NewBuffer(int id, size_t size, const void *data) = 0;
    virtual void UpdateBuffer(int id, size_t offset, size_t size, const void *data) = 0;
    virtual void BindBuffer(int id, int slot) = 0;
    virtual void NewPipeline(int id, int shader_count, void **shader) = 0;
    virtual void CurrentPipeline(int id) = 0;
    virtual void Draw(int type, int vertex_count, int first_vertex, int instance_count, int first_instance) = 0;
    virtual void Compute(int num_groups_x, int num_groups_y, int num_groups_z) = 0;
    virtual void MemoryBarrier() = 0;
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
    void (*Draw)(struct IGPUDevice *self, int type, int vertex_count, int first_vertex, int instance_count, int first_instance);
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