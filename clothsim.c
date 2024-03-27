#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "clothsim.h"
#include "app.h"
#include "renderer.h"
#include <logger.h>

static void cloth_init(Cloth*, int, int, int, int, int);
static void cloth_deinit(Cloth*);
static void cloth_update(Cloth*, float);

static bool points_init(Points*, int, int);
static bool points_deinit(Points*);
static bool point_update(Points*, int, int, float, float, Vec2, float);

static bool constraints_init(Constraints*, int, int);
static bool constraint_deinit(Constraints*);
static bool constraint_update(Constraints*, Points*, int, int, float);

static const int WIDTH = 100;
static const int HEIGHT = 50;
static const Vec2 GRAVITY = v2(0,98.1f);

static Cloth cloth;

int main(int argc, char** argv)
{
    
    bool headless;
    int runs = -1;

    int opt;

    while((opt = getopt(argc,argv,"hr:")) != -1)
    {
        switch ((opt))
        {
        case 'h':
            headless = true;
            break;
        case 'r':
            runs = atoi(optarg);
            if(runs == 0 && errno != 0)
            {
                LOG_ERROR("atoi(): %s", strerror(errno));
            }
            break;
        default:
            break;
        }
    }

    

    cloth_init(&cloth,WIDTH,HEIGHT,10,0,0);

    
    if(!headless)
    {
        app_init(&(AppInitDesc){
            .width = 1280,
            .height = 720
        });
        renderer_init();
        while(app_continue())
        {
            renderer_clear();
            cloth_update(&cloth,0.0167);
            render_cloth(&cloth);
            renderer_update();
            app_sleep(16);
        }
    }

    else
    {
        LOG_INFO("Running %d times", runs--);
        do
        {
            
            cloth_update(&cloth,0.0167);
        }while(runs-- > 0);
        
    }

    

    cloth_deinit(&cloth);
    app_deinit();

}

static void
cloth_update(Cloth* cloth, float delta_time)
{
    int x,y;
    y = x = 0;

    //Update points
    for(y = 0; y < cloth->height; y++)
    {
        for(x = 0; x < cloth->width; x++)
        {
            
            point_update(&cloth->points,x,y,delta_time,cloth->drag,GRAVITY,cloth->elasticity);
        }
    }

    //Update constraints
    for(y = 0; y < cloth->height; y++)
    {
        for(x = 0; x < cloth->width; x++)
        {
            
            int c = 0;
            //Each point has two constraints, in memory the live beside each other
            for(c = 0; c < 2;c++)
            {
                //If constraint is there
                
                if(cloth->constraints.active[y][(x * 2) + c])
                {
                    constraint_update(&cloth->constraints,&cloth->points,(x * 2) + c,y,delta_time);
                }
            }
        }
    }

}

static void 
cloth_init(Cloth* cloth, int width, int height, int spacing, int start_x, int start_y)
{
    
    #define SET_POINT(IX, IY, X, Y)\
         (cloth->points.prev_position[IY][IX] = cloth->points.initial_position[IY][IX] = cloth->points.position[IY][IX] = v2(X,Y))

    #define SET_CONSTRAINT(IX, IY, C, A, B)\
        (cloth->constraints.a[IY][(IX * 2) + C] = A);\
        (cloth->constraints.b[IY][(IX * 2) + C] = B);\
        (cloth->constraints.active[IY][(IX * 2) + C] = true)



    int x,y;
    y = x = 0;

    cloth->width = width;
    cloth->height = height;
    cloth->drag = 0.01f;
    cloth->elasticity = 10.0f;

    points_init(&cloth->points, width, height);
    constraints_init(&cloth->constraints, width, height);
    cloth->constraints.length = spacing;
    
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            
            SET_POINT(x,y,start_x + x * spacing, start_y );

            //Pin points that are at the top so that whole thing doesnt fall down
            if(y == 0 && x % 2 == 0)
            {
                cloth->points.pinned[y][x] = true;
            }            
            
            //If point exsists beside current point
            if(x != 0)
            {
                //Add constraint
                SET_CONSTRAINT(x,y,0,iv2(x, y), iv2(x - 1, y));        
                cloth->points.constraint[y][x * 2] = iv2(x * 2,y);
                
            }
            //If point exists above current point
            if(y != 0)
            {
                //Add constraint
                SET_CONSTRAINT(x,y,1,iv2(x,y),iv2(x,y-1));
                cloth->points.constraint[y][(x * 2) + 1] = iv2((x * 2) + 1, y);
            }            
        }
    }
}

static bool
points_init(Points* points, int width, int height)
{
    points->initial_position = malloc(sizeof(Vec2*) * height);
    points->position = malloc(sizeof(Vec2*) * height);
    points->prev_position = malloc(sizeof(Vec2*) * height);
    points->constraint = malloc(sizeof(IVec2*) * height);
    points->pinned = malloc(sizeof(bool*) * height);

    for(int y = 0; y < height; y++)
    {
        points->initial_position[y] = calloc(width,sizeof(Vec2));
        points->position[y] = calloc(width,sizeof(Vec2) );
        points->prev_position[y] = calloc(width, sizeof(Vec2));
        points->constraint[y] = calloc(width, (sizeof(IVec2) * 2));
        points->pinned[y] = calloc(width, sizeof(bool));            
    }

    return true;
}

static bool 
points_deinit(Points* points)
{
    

    for(int y = 0; y < points->height; y++)
    {
        free(points->initial_position[y]);
        free(points->position[y]);
        free(points->prev_position[y]);
        free(points->constraint[y]);
        free(points->pinned[y]);            
    }

    free(points->initial_position);
    free(points->position);
    free(points->prev_position);
    free(points->constraint);
    free(points->pinned);

    return true;
}

static bool 
constraints_init(Constraints* constraints, int width, int height)
{

    constraints->width = width;
    constraints->height = height;

    constraints->a = malloc(height * sizeof(IVec2*));
    constraints->b = malloc(height * sizeof(IVec2*));
    constraints->active = malloc(height * sizeof(bool*));

    for(int y = 0; y < height; y++)
    {

        constraints->a[y] = calloc(width, (sizeof(IVec2) * 2));
        constraints->b[y] = calloc(width, (sizeof(IVec2) * 2));
        constraints->active[y] = calloc(width, (sizeof(bool) * 2));
    }

    return true;

}

static bool 
constraint_deinit(Constraints* constraints)
{
    int height = constraints->height;
    
    for(int y = 0; y < height; y++)
    {
        free(constraints->a[y]);
        free(constraints->b[y]);

        free(constraints->active[y]);
    }

    free(constraints->a);
    free(constraints->b);
   
    free(constraints->active);
    return true;
}

static void 
cloth_deinit(Cloth* cloth)
{
    points_deinit(&cloth->points);
    constraint_deinit(&cloth->constraints);
}

static bool 
point_update(Points* points, int x, int y, float delta_time, float drag, Vec2 acceleration, float elasticity)
{

    //Verlet integration
    
    Vec2 pos = points->position[y][x];
    Vec2 prev = points->prev_position[y][x];
    Vec2 velocity = v2(pos.x - prev.x, pos.y - prev.y);
    Vec2 next_pos = v2(
        pos.x + velocity.x * (1.0f - drag) + acceleration.x * (1.0f - drag) * (delta_time * delta_time),
        pos.y + velocity.y * (1.0f - drag) + acceleration.y * (1.0f - drag) * (delta_time * delta_time)
    );

    if(points->pinned[y][x])
    {
        points->position[y][x] = points->initial_position[y][x];
        return true;
    }

    points->prev_position[y][x] = pos;
    points->position[y][x] = next_pos;

    return true;
}

static bool 
constraint_update(Constraints* constraint, Points* points, int x, int y, float delta_time)
{
    //Satisfy constraints

    Vec2 *a_pos = &points->position[constraint->a[y][x].y][constraint->a[y][x].x];
    Vec2 *b_pos = &points->position[constraint->b[y][x].y][constraint->b[y][x].x];

    Vec2 diff = v2(
        (*a_pos).x - (*b_pos).x,
        (*a_pos).y - (*b_pos).y
    );  

    float d = sqrtf(diff.x * diff.x + diff.y * diff.y);
    float difference_scalar = (constraint->length - d) / d;

    Vec2 translation = v2(
        diff.x * 0.5 * difference_scalar,
        diff.y * 0.5 * difference_scalar
    );
    
    a_pos->x += translation.x;
    a_pos->y += translation.y;

    b_pos->x -= translation.x;
    b_pos->y -= translation.y;

    return true;
}