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

#define v2f(X,Y) ((Vec2f) {.x = X, .y = Y})
#define v3f(X,Y,Z) ((Vec3f) {.x = X, .y = Y, .z = Z})
#define v2i(X,Y) ((Vec2i){.x = X, .y = Y})


#endif //_CLOTHSIM_LINALG_H