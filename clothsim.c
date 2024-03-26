#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clothsim.h"
#include "app.h"
#include "renderer.h"

static void cloth_init(Cloth*, int, int, int, int, int);
static void cloth_deinit(Cloth*);
static void cloth_update(Cloth*, float);

static void point_create(Point*);
static bool point_addconstraint(Point*, Constraint*, size_t);
static bool point_update(Point*, float, float, Vec2, float);

static bool constraint_update(Constraint*, float);

static Cloth cloth;

static const int WIDTH = 100;
static const int HEIGHT = 50;
static const Vec2 GRAVITY = v2(0,98.1f);

int main()
{
    cloth_init(&cloth,WIDTH,HEIGHT,10,0,0);

    app_init(&(AppInitDesc){
        .width = 1280,
        .height = 720
    });
    renderer_init();
    
    while(app_continue())
    {
        app_sleep(10);
        renderer_clear();
        cloth_update(&cloth,0.016);
        render_cloth(&cloth);
        renderer_update();
    }

    cloth_deinit(&cloth);
    app_deinit();

}

static void
cloth_update(Cloth* cloth, float delta_time)
{
    int x,y,c;
    c = y = x = 0;
    for(y = 0; y < cloth->height; y++)
    {
        for(x = 0; x < cloth->width; x++)
        {
            Point* point = &cloth->points[y][x];
            point_update(point,delta_time,cloth->drag,GRAVITY,cloth->elasticity);
        }

    }
    for(y = 0; y < cloth->height; y++)
    {
        for(x = 0; x < cloth->width; x++)
        {
            Point point = cloth->points[y][x];
            //SDL_RenderDrawPoint(renderer,point.position.x, point.position.y);
            int c = 0;
            for(c = 0; c < 2;c++)
            {
                Constraint* constraint;
                if((constraint = &cloth->constraints[y][(x * 2) + c])->a != NULL)
                {
                    constraint_update(constraint,delta_time);
                }
            }
           

        }
    }
}

static void 
cloth_init(Cloth* cloth, int width, int height, int spacing, int start_x, int start_y)
{
    
    int x,y;
    y = x = 0;

    cloth->points = malloc(sizeof(Point*) * (height));
    cloth->constraints = malloc(sizeof(Constraint*) * (height));
    cloth->width = width;
    cloth->height = height;
    cloth->drag = 0.01f;
    cloth->elasticity = 10.0f;

    for(y = 0; y < height; y++)
    {
        cloth->points[y] = malloc(sizeof(Point) * width);
        cloth->constraints[y] = malloc((sizeof(Constraint) * 2) * (width));
        memset(cloth->constraints[y], 0, (sizeof(Constraint) * 2) * (width));
    }


    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            cloth->points[y][x] = point(start_x + x * spacing, start_y );
           
            
            Point* point = &cloth->points[y][x];
            
            point->pinned = false;

            if(y == 0 && x % 2 == 0)
            {
                point->pinned = true;
            }            
            
            if(x != 0)
            {
                Point* left_point = &cloth->points[y][x - 1];
                cloth->constraints[y][x * 2] = (Constraint){.a = &cloth->points[y][x], .b = left_point};
                Constraint* constraint = &cloth->constraints[y][x * 2];
                constraint->length = spacing;
                constraint->active = true;
                point_addconstraint(point,constraint,0);
                point_addconstraint(left_point,constraint,0);
                
            }
            if(y != 0)
            {
                Point* up_point = &cloth->points[y - 1][x];
                cloth->constraints[y][(x * 2) + 1] = (Constraint){.a = &cloth->points[y][x], .b = up_point};
                Constraint* constraint = &cloth->constraints[y][(x * 2) + 1];
                constraint->length = spacing;
                constraint->active = true;
                point_addconstraint(point,constraint,1);
                point_addconstraint(up_point,constraint,1);
            }



            
        }
    }
    

}


static void 
cloth_deinit(Cloth* cloth)
{

}

static bool 
point_addconstraint(Point* point, Constraint* constraint, size_t i)
{
    if(i >= 2)
    {
        return false;
    }
    point->constraints[i] = constraint;
    point->num_constraints = i + 1;

    return true;
}

static bool 
point_update(Point* point, float delta_time, float drag, Vec2 acceleration, float elasticity)
{
    

    Vec2 pos = point->position;
    Vec2 velocity = v2(pos.x - point->prev_position.x, pos.y - point->prev_position.y);
    Vec2 next_pos = v2(
        pos.x + velocity.x * (1.0f - drag) + acceleration.x * (1.0f - drag) * (delta_time * delta_time),
        pos.y + velocity.y * (1.0f - drag) + acceleration.y * (1.0f - drag) * (delta_time * delta_time)
    );

    if(point->pinned)
    {
        point->position = point->intial_position;
        return true;
    }

    point->prev_position = pos;
    point->position = next_pos;

    return true;
}

static bool 
constraint_update(Constraint* constraint, float delta_time)
{
    
    Vec2 diff = v2(
        constraint->a->position.x - constraint->b->position.x,
        constraint->a->position.y - constraint->b->position.y
    );  

    float d = sqrtf(diff.x * diff.x + diff.y * diff.y);
    float difference_scalar = (constraint->length - d) / d;

    Vec2 translation = v2(
        diff.x * 0.5 * difference_scalar,
        diff.y * 0.5 * difference_scalar
    );
    
    constraint->a->position.x += translation.x;
    constraint->a->position.y += translation.y;

    constraint->b->position.x -= translation.x;
    constraint->b->position.y -= translation.y;

    return true;


}