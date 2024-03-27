#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <app.h>
#include <clothsim.h>
#include <renderer.h>
#include <logger.h>


static SDL_Renderer* renderer;

bool 
renderer_init(void)
{
    SDL_Window* window = (SDL_Window*)app_getwindow();
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        LOG_ERROR("Could not create SDL Renderer: %s",SDL_GetError());
        return false;
    }
    return true;
}


bool 
render_cloth(Cloth* cloth)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    int x,y;
    y = x = 0;
    for(y = 0; y < cloth->height; y++)
    {
        for(x = 0; x < cloth->width; x++)
        {
            
            int c = 0;
            for(c = 0; c < 2;c++)
            {
                if(cloth->constraints.active[y][(x * 2) + c])
                {
                    IVec2 a = cloth->constraints.a[y][(x * 2) + c];
                    IVec2 b = cloth->constraints.b[y][(x * 2) + c];

                    Vec2 a_pos = cloth->points.position[a.y][a.x];
                    Vec2 b_pos = cloth->points.position[b.y][b.x];

                    SDL_RenderDrawLine(renderer, a_pos.x, a_pos.y, b_pos.x, b_pos.y);
                    
                    
                }
                
            }
        }
    }

    return true;

}

void 
renderer_update(void)
{
    
    SDL_RenderPresent(renderer);
}

void
renderer_clear(void)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
}
