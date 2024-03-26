#ifndef _CLOTHSIM_APP_H
#define _CLOTHSIM_APP_H

#include <stdbool.h>

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




#endif //_CLOTHSIM_APP_H