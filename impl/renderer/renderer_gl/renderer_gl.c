#include <dlfcn.h>
#include <app.h>
#include <renderer.h>
#include "renderer_gl.h"
#include <logger.h>

static bool bind_gl(GL* gl);

GL gl;

bool 
renderer_init(void)
{
    
    (void*)app_getglcontext(4,6);
    bind_gl(&gl);
    LOG_INFO("Initialized OpenGL", NULL);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    return false;
}


bool 
render_cloth(struct Cloth*)
{
    return true;
}

void 
renderer_update(void)
{

}

void
renderer_clear(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    app_swapwindow();
}

static bool 
bind_gl(GL* gl)
{
    if(gl->initialized)
    {
        return true;
    }
    
    void* libgl = dlopen("libGL.so",RTLD_LAZY);

    #define REGISTER_GL_FUNC( FUNC ) if((gl->FUNC = dlsym(libgl, #FUNC )) == NULL){LOG_ERROR("Could not bind %s: %s", #FUNC, dlerror());}

    REGISTER_GL_FUNC(glBindBuffer);
    REGISTER_GL_FUNC(glGenBuffers);
    REGISTER_GL_FUNC(glBufferData);
    REGISTER_GL_FUNC(glDrawArrays);
    REGISTER_GL_FUNC(glEnableVertexAttribArray);
    REGISTER_GL_FUNC(glVertexAttribPointer);
    REGISTER_GL_FUNC(glVertexAttribPointer);
    REGISTER_GL_FUNC(glCreateShader);
    REGISTER_GL_FUNC(glLinkProgram);
    REGISTER_GL_FUNC(glUseProgram);
    REGISTER_GL_FUNC(glAttachShader);
    REGISTER_GL_FUNC(glShaderSource);
    REGISTER_GL_FUNC(glCreateProgram);
    REGISTER_GL_FUNC(glDeleteShader);
    REGISTER_GL_FUNC(glCompileShader);
    REGISTER_GL_FUNC(glGetShaderiv);
    REGISTER_GL_FUNC(glGetProgramiv);
    REGISTER_GL_FUNC(glGetStringi);

    GLint numExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    gl->initialized = true;
    return true;

}