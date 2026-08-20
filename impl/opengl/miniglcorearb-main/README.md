## Example
```glsl
// main.vert
#version 460 core

void main() {
    float x = float((gl_VertexID & 1) << 1) - 1.0;
    float y = float(gl_VertexID & 2) - 1.0;
    gl_Position = vec4(x, y, 0.0, 1.0);
}

// main.frag
#version 460 core

out vec4 fout;
void main() {
    fout = vec4(0.2, 0.8, 0.4, 1.0);
}
```
```c
// main.c
#include "swl/swl.h"
#define GLUTILS_IMPL
#include "miniglcorearb/miniglcorearb.h"

int main() {
    swl_CreateWindow("X", 400, 300);
    swl_GL_CreateContext(4, 6, 24, 8);
    gluLoadLibrary(swl_GL_GetProcAddress);
    gluBindDummyVAO();

    uint32_t vert = gluCreateShaderProgramvFromFile(GL_VERTEX_SHADER, "main.vert");
    gluIsProgramLinked(vert);
    uint32_t frag = gluCreateShaderProgramvFromFile(GL_FRAGMENT_SHADER, "main.frag");
    gluIsProgramLinked(frag);

    uint32_t p;
    glCreateProgramPipelines(1, &p);
    glUseProgramStages(p, GL_VERTEX_SHADER_BIT, vert);
    glUseProgramStages(p, GL_FRAGMENT_SHADER_BIT, frag);

    for (;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindProgramPipeline(p);
        glDrawArraysInstancedBaseInstance(GL_TRIANGLE_STRIP, 0, 4, 1, 0);

        swl_GL_SwapBuffers();
        swl_PollEvents();
        swl_PassScheduler();
    }

    glDeleteProgram(vert);
    glDeleteProgram(frag);
    glDeleteProgramPipelines(1, &p);
    swl_GL_DestroyContext();
    swl_CloseWindow();
    return 0;
}
```

## References
- [OpenGLSL Specification](https://registry.khronos.org/OpenGL/specs/gl/GLSLangSpec.4.60.pdf)
- [OpenGL Core Profile Specification](https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf)
- [OpenGL API Reference Pages](https://registry.khronos.org/OpenGL-Refpages/gl4/)
- [OpenGL API Reference Pages (Better)](https://docs.gl)
- [OpenGL API Reference Cards](https://www.khronos.org/files/opengl46-quick-reference-card.pdf)
- [OpenGL Core ARB Header](https://registry.khronos.org/OpenGL/api/GL/glcorearb.h)
- [OpenGL Extension](https://registry.khronos.org/OpenGL/index_gl.php#arbextspecs)

## TODO
- miniglcorearb.h -> texture
- glutils.h -> loadtexturefromfile
- glmath.h
- glvram.h