define __build
	$(1) -shared -o libgpu.dll $(2) -I.
	$(1) -o gpu.o -c $(2) -I.
	ar rcs libgpu.a gpu.o
	rm *.o
endef

first:
	@echo "make [install/mtl/gl]"

install:
	$(MAKE) -C depen

gl:
	$(call __build,gcc,opengl/gl_gpu.c)