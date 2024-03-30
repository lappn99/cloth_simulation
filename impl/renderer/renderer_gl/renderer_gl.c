#include <alloca.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <app.h>
#include <clothsim.h>
#include <renderer.h>
#include "renderer_gl.h"
#include <logger.h>
#include <linalg.h>

static bool bind_gl(GL* gl);

GL gl;

static GLuint create_shader(const char*, GLenum);

static GLuint vbo;
static GLuint shader_program;
static GLuint vao;


bool 
renderer_init(void)
{
    GLuint vertex_shader;
    GLuint fragment_shader;

    (void*)app_getglcontext(3,3);
    bind_gl(&gl);
    LOG_INFO("Initialized OpenGL", NULL);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    gl.glGenBuffers(1, &vbo);
    gl.glGenVertexArrays(1,&vao);

    vertex_shader = create_shader("./impl/renderer/renderer_gl/shaders/vertex.glsl", GL_VERTEX_SHADER);
    fragment_shader = create_shader("./impl/renderer/renderer_gl/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    
    shader_program = gl.glCreateProgram();
    gl.glAttachShader(shader_program, vertex_shader);
    gl.glAttachShader(shader_program, fragment_shader);

    gl.glLinkProgram(shader_program);

    int success;
    gl.glGetProgramiv(shader_program,GL_LINK_STATUS, &success);
    if(!success)
    {
        LOG_ERROR("Could not link program", NULL);
    }

    gl.glDeleteShader(vertex_shader);
    gl.glDeleteShader(fragment_shader);
    glEnable(GL_PROGRAM_POINT_SIZE);


    return true;
}


bool 
render_cloth(struct Cloth* cloth)
{
    glClear(GL_COLOR_BUFFER_BIT);
    int x,y;
    y = x = 0;
    Vec2i window_size = app_getwindowsize();
    //glViewport(0,window_size.y,window_size.x,window_size.y);
    Mat4f orthographic_matrix = orthographic(0,window_size.x,0,window_size.y,-1.f,1.f);
    gl.glBindVertexArray(vao);
    gl.glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl.glBufferData(GL_ARRAY_BUFFER, 
        (cloth->height * cloth->width) * sizeof(Vec3f),
        NULL,GL_DYNAMIC_DRAW);
    
    for(y = 0; y < cloth->height; y++)
    {
        
        int offset = (y * cloth->width) * sizeof(Vec3f);
        Vec3f* row = cloth->points.position[y];
        gl.glBufferSubData(GL_ARRAY_BUFFER,offset,cloth->width * sizeof(Vec3f),row);
        
    }
    
    GLint uniform_loc = gl.glGetUniformLocation(shader_program,"projection");

    gl.glUseProgram(shader_program);
    gl.glUniformMatrix4fv(uniform_loc,1,GL_FALSE,orthographic_matrix.raw);
    gl.glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    gl.glEnableVertexAttribArray(0);

    gl.glDrawArrays(GL_POINTS,0,cloth->height * cloth->width);
    gl.glBindBuffer(GL_ARRAY_BUFFER,0);
    gl.glBindVertexArray(0);
    return true;
}

void 
renderer_update(void)
{
    app_swapwindow();
}

void
renderer_clear(void)
{
    
    
}

static GLuint 
create_shader(const char* path, GLenum shader_type)
{
    GLuint shader;
    int fd = open(path,O_RDONLY);
    if(fd < 0)
    {
        LOG_ERROR("open(): %s", strerror(errno));
        return 0;
    }

    off_t size = lseek(fd,0,SEEK_END);
    if(size < 0)
    {
        LOG_ERROR("lseek(): %s", strerror(errno));
        return 0;
    }

    lseek(fd,0,SEEK_SET);

    char* shader_src = alloca(size * sizeof(char));

    read(fd, shader_src,sizeof(char) * (size + 1));
    shader_src[size] = '\0';


    
    shader = gl.glCreateShader(shader_type);
    gl.glShaderSource(shader,1,(const char**)&shader_src,NULL);
    gl.glCompileShader(shader);

    int success;
    char info_log[512];
    gl.glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        gl.glGetShaderInfoLog(shader, 512, NULL, info_log);
        LOG_ERROR("Error compiling %s:\n%s ", path,info_log);
    }

    return shader;
    

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
    REGISTER_GL_FUNC(glBufferSubData);
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
    REGISTER_GL_FUNC(glGetShaderInfoLog);
    REGISTER_GL_FUNC(glGetUniformLocation);
    REGISTER_GL_FUNC(glUniformMatrix4fv);
    REGISTER_GL_FUNC(glGenVertexArrays);
    REGISTER_GL_FUNC(glBindVertexArray);

    GLint numExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    gl->initialized = true;
    return true;

}

