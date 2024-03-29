#ifndef _CLOTHSIM_H
#define _CLOTHSIM_H

#include <stdbool.h>
#include <linalg.h>

struct Constraints;




typedef struct Points
{
    Vec2f** position;
    Vec2f** prev_position;
    Vec2f** initial_position;
    Vec2i** constraint;
    bool** pinned;
    bool** selected;

    int width;
    int height;

} Points;

typedef struct Constraints
{
    Vec2i** a;
    Vec2i** b;
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

#endif //_CLOTHSIM_H