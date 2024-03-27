#ifndef _CLOTHSIM_H
#define _CLOTHSIM_H

#include <stdbool.h>

struct Constraints;

typedef struct Vec2
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
} Vec2;

typedef struct IVec2
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
} IVec2;


typedef struct Points
{
    Vec2** position;
    Vec2** prev_position;
    Vec2** initial_position;
    IVec2** constraint;
    bool** pinned;

    int width;
    int height;

} Points;

typedef struct Constraints
{
    IVec2** a;
    IVec2** b;
    bool** active;

    float length;
    int width;
    int height;

} Constraints;

typedef struct Cloth
{
    float drag;
    float elasticity;
    int width;
    int height;
    
    Points points;
    Constraints constraints;

} Cloth;

#define v2(X,Y) ((Vec2) {.x = X, .y = Y})
#define iv2(X,Y) ((IVec2){.x = X, .y = Y})
//#define point(X,Y) ((Point) {.intial_position = v2(X,Y), .position = v2(X,Y), .prev_position = v2(X,Y), .constraints = {NULL,NULL}})


#endif //_CLOTHSIM_H