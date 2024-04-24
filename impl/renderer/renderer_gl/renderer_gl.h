#ifndef _CLOTHSIM_RENDERER_GL_H
#define _CLOTHSIM_RENDERER_GL_H

#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glx.h>

typedef struct GL
{   
    
    PFNGLBINDBUFFERPROC                 glBindBuffer;
    PFNGLGENBUFFERSPROC                 glGenBuffers;
    PFNGLBUFFERDATAPROC                 glBufferData;
    PFNGLBUFFERSUBDATAPROC              glBufferSubData;
    PFNGLDRAWARRAYSEXTPROC              glDrawArrays;
    PFNGLDRAWRANGEELEMENTSPROC          glDrawRangeElements;
    PFNGLDRAWELEMENTSBASEVERTEXPROC     glDrawElementsBaseVertex;
    PFNGLDRAWELEMENTSINDIRECTPROC       glDrawElementsIndirect;
    PFNGLDRAWARRAYSINDIRECTPROC         glDrawArraysIndirect;
    PFNGLENABLEVERTEXATTRIBARRAYPROC    glEnableVertexAttribArray;
    PFNGLVERTEXATTRIBPOINTERPROC        glVertexAttribPointer;
    PFNGLCREATESHADERPROC               glCreateShader;
    PFNGLDELETESHADERPROC               glDeleteShader;
    PFNGLLINKPROGRAMPROC                glLinkProgram;
    PFNGLUSEPROGRAMPROC                 glUseProgram;
    PFNGLATTACHSHADERPROC               glAttachShader;
    PFNGLSHADERSOURCEPROC               glShaderSource;
    PFNGLCOMPILESHADERPROC              glCompileShader;
    PFNGLCREATEPROGRAMPROC              glCreateProgram;
    PFNGLGETSHADERIVPROC                glGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC           glGetShaderInfoLog;
    PFNGLGETPROGRAMIVPROC               glGetProgramiv;
    PFNGLGETSTRINGIPROC                 glGetStringi;
    PFNGLUNIFORMMATRIX4FVPROC           glUniformMatrix4fv;
    PFNGLGETUNIFORMLOCATIONPROC         glGetUniformLocation;
    PFNGLGENVERTEXARRAYSPROC            glGenVertexArrays;
    PFNGLBINDVERTEXARRAYPROC            glBindVertexArray;
    bool initialized;

} GL;

#endif //_CLOTHSIM_RENDERER_GL_H