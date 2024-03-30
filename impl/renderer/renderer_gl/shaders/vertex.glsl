#version 330 core

layout (location = 0) in vec3 aPos;


uniform mat4 projection;

void main()
{    
    //gl_PointSize = 2.0;
    gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
}