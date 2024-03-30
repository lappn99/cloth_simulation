#include "linalg.h"

Mat4f 
orthographic(float left, float right, 
    float top, float bottom, 
    float near, float far)
{
    return mat4f(
        v4f(2.f / (right - left), 0.f,0.f,0.f),
        v4f(0.f, 2.f / (top-bottom),0.f,0.f),
        v4f(0.f,0.f,1.f,0.f),
        v4f(-((right + left)/(right - left)), -((top + bottom)/(top-bottom)),-((far + near)/(far-near)),1.f)
    );
}
