#pragma once

/* FALAN FILAN ISTE */
#define GL_FALSE                          0
#define GL_TRUE                           1

/* glClear */
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

/* glBindBufferBase */
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_SHADER_STORAGE_BUFFER          0x90D2

/* glNamedBufferStorage & glNamedBufferSubData & glUnmapNamedBuffer */
#define GL_ARRAY_BUFFER                   0x8892
//#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_COPY_READ_BUFFER               0x8F36
#define GL_COPY_WRITE_BUFFER              0x8F37
#define GL_DISPATCH_INDIRECT_BUFFER       0x90EE
#define GL_DRAW_INDIRECT_BUFFER           0x8F3F
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_QUERY_BUFFER                   0x9192
//#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_TEXTURE_BUFFER                 0x8C2A
//#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
//#define GL_UNIFORM_BUFFER                 0x8A11

/* glNamedBufferStorage */
#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_CLIENT_STORAGE_BIT             0x0200

/* glMemoryBarrier */
#define GL_SHADER_STORAGE_BARRIER_BIT     0x00002000

/* glMapBufferRange */
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020

/* glCreateShaderProgramv */
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_VERTEX_SHADER                  0x8B31
#define GL_TESS_CONTROL_SHADER            0x8E88
#define GL_TESS_EVALUATION_SHADER         0x8E87
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_GEOMETRY_SHADER                0x8DD9

/* glGetProgramiv */
#define GL_DELETE_STATUS                  0x8B80
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS  0x92D9
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_COMPUTE_WORK_GROUP_SIZE        0x8267
#define GL_PROGRAM_BINARY_LENGTH          0x8741
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_GEOMETRY_VERTICES_OUT          0x8916
#define GL_GEOMETRY_INPUT_TYPE            0x8917
#define GL_GEOMETRY_OUTPUT_TYPE           0x8918

/* glUseProgramStages */
#define GL_VERTEX_SHADER_BIT              0x00000001
#define GL_TESS_CONTROL_SHADER_BIT        0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#define GL_GEOMETRY_SHADER_BIT            0x00000004
#define GL_FRAGMENT_SHADER_BIT            0x00000002
#define GL_COMPUTE_SHADER_BIT             0x00000020

/* glDrawArraysInstancedBaseInstance */
#define GL_POINTS                         0x0000
#define GL_LINE_STRIP                     0x0003
#define GL_LINE_LOOP                      0x0002
#define GL_LINES                          0x0001
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_TRIANGLES                      0x0004
#define GL_LINES_ADJACENCY                0x000A
#define GL_LINE_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#define GL_PATCHES                        0x000E

/* glCreateTextures */
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_3D                     0x806F
#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_TEXTURE_2D_ARRAY               0x8C1A

/* glTextureStorage2D */
#define GL_RGBA2                          0x8055 //RGB
#define GL_RGBA4                          0x8056 //RGB
#define GL_RGB5_A1                        0x8057 //RGBA
#define GL_RGBA8                          0x8058 //RGBA

/* glTextureSubImage2D */
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908

/* gl types */
#define GL_FLOAT                          0x1406
#define GL_UNSIGNED_BYTE                  0x1401

/* glSamplerParameteri */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803

/* glSamplerParameteri */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/* glEnable */
#define GL_BLEND                          0x0BE2

/* glBlendFunc */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004