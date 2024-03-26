#ifndef _CLOTHSIM_H
#define _CLOTHSIM_H

#include <stdbool.h>

struct Constraint;

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

typedef struct Point
{
    Vec2 position;
    Vec2 prev_position;
    Vec2 intial_position;
    struct Constraint* constraints[2];
    size_t num_constraints;
    bool pinned;
    


} Point;

typedef struct Constraint
{
    Point* a;
    Point* b;
    float length;
    bool active;
} Constraint;

typedef struct Cloth
{
    float drag;
    float elasticity;
    int width;
    int height;
    
    Point** points;
    Constraint** constraints;

} Cloth;




#define v2(X,Y) ((Vec2) {.x = X, .y = Y})
#define point(X,Y) ((Point) {.intial_position = v2(X,Y), .position = v2(X,Y), .prev_position = v2(X,Y),.num_constraints = 0, .constraints = {NULL,NULL}})


#endif //_CLOTHSIM_H