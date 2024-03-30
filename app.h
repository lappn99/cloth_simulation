#ifndef _CLOTHSIM_APP_H
#define _CLOTHSIM_APP_H

#include <stdbool.h>

#include <linalg.h>

typedef struct 
{
    int width;
    int height;
} AppInitDesc;

bool app_init(AppInitDesc*);
void app_deinit(void);
bool app_continue(void);

void* app_getwindow(void);
void app_sleep(unsigned int);

Vec2i app_getmouseposition(void);
bool app_mousebuttonleft(void);
bool app_mousebuttonright(void);

float app_getticks(void);
float app_getdeltatime(void);

#ifdef RENDERER_USE_GL
void* app_getglcontext(int, int);
void app_swapwindow(void);
#endif

#endif //_CLOTHSIM_APP_H