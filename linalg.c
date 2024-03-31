#include <math.h>

#include "linalg.h"
#define PI   3.14159265358979323846264338327950288
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

Mat4f 
perspective(float width, float height, float fov, float near, float far)
{

    float aspect = width / height;
    float t = near * tanf(fov * (PI/360.0f));
    float b = -t;
    float r = b * aspect;
    float l = -r;
    float n = near;
    float f = far;

    return mat4f(
        v4f((2*n)/(r - l),0.f,(r+l)/(r-l),0.f),
        v4f(0.f,(2*n)/(b-t),(t+b)/(b-t),0.f),
        v4f(0.f,0.f,-(f + n) / (f - n),(-2 * f * n) / (f - n)),
        v4f(0.f,0.f,-1.f,0.f)
    );

}
