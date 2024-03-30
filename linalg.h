#ifndef _CLOTHSIM_LINALG_H
#define _CLOTHSIM_LINALG_H

typedef struct Vec2f
{
    union
    {
        struct
        {
            float x;
            float y;

        };
        float raw[2];
    };
} Vec2f;

typedef struct Vec3f
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        float raw[3];
    };
} Vec3f;

typedef struct Vec4f
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        float raw[4];
    };
} Vec4f;


typedef struct Vec2i
{
    union
    {
        struct
        {
            int x;
            int y;

        };
        int raw[2];
    };
} Vec2i;

typedef struct Mat4f
{
    union
    {
        struct
        {
            Vec4f x;
            Vec4f y;
            Vec4f z;
            Vec4f w;
        };
        float raw[16];
    } ;
} Mat4f;



#define v2f(X,Y) ((Vec2f) {.x = X, .y = Y})
#define v3f(X,Y,Z) ((Vec3f) {.x = X, .y = Y, .z = Z})
#define v4f(X,Y,Z,W) ((Vec4f) {.x = X, .y = Y, .z = Z, .w = W})
#define v2i(X,Y) ((Vec2i){.x = X, .y = Y})

#define mat4f(X,Y,Z,W) ((Mat4f) {.x = X, .y = Y, .z = Z, .w = W})


Mat4f orthographic(float, float, float, float, float, float);

#endif //_CLOTHSIM_LINALG_H