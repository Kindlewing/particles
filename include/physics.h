#ifndef PHYSICS_H
#define PHYSICS_H

#include "defs.h"
#include <SDL2/SDL_rect.h>

void update(particle *particles, SDL_Point *points, double dt);
void apply_forces(particle *p, particle *particles, double dt);
double distance(vec2 pos_x, vec2 pos_y);

#endif
