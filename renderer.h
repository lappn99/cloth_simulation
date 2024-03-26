#ifndef _CLOTHSIM_RENDERER_H
#define _CLOTHSIM_RENDERER_H

#include <stdbool.h>

struct Cloth;


bool renderer_init(void);

bool render_cloth(struct Cloth*);
void renderer_update(void);
void renderer_clear(void);


#endif //_CLOTHSIM_RENDERER_H