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
    PFNGLDRAWARRAYSEXTPROC              glDrawArrays;
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
    PFNGLGETPROGRAMIVPROC               glGetProgramiv;
    PFNGLGETSTRINGIPROC                 glGetStringi;
    bool initialized;

} GL;

#endif //_CLOTHSIM_RENDERER_GL_H