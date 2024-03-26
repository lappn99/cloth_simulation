#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <app.h>
#include <logger.h>

static SDL_Window* window;

bool 
app_init(AppInitDesc* desc)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG_ERROR("Could not init SDL2",NULL);
        return false;
    }

    window = SDL_CreateWindow("Cloth simulation", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        desc->width, desc->height, SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        LOG_ERROR("Could not creat SDL2 window", NULL);
        return false;
    }
    return true;


}

void
app_deinit(void)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool 
app_continue(void)
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        switch(ev.type)
        {
            case SDL_QUIT:
                return false;
        }
    }
    return true;
}

void* 
app_getwindow(void)
{
    return window;
}


void 
app_sleep(unsigned int ms)
{
    SDL_Delay(ms);
}