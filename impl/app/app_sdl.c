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
    SDL_SetHint(SDL_HINT_RENDER_VSYNC,"1");
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

Vec2i 
app_getmouseposition(void)
{
    Vec2i position;
    SDL_GetMouseState(&position.x, &position.y);
    return position;
}

bool 
app_mousebuttonleft(void)
{
    return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) != 0;
}

bool 
app_mousebuttonright(void)
{
    return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_RMASK) != 0;
}

float 
app_getticks(void)
{
    return (float)SDL_GetTicks();
}

float 
app_getdeltatime(void)
{

    static float start = 0.0f;
    static float end = 0.0f;
    
    if(start == 0.0f)
    {
        start = app_getticks();
        return 0.0f;
    }

    end = app_getticks();

    float dt = end - start;

    start = app_getticks();

    return dt;

}