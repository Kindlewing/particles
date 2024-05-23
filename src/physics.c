#include "physics.h"

void update(particle *particles, SDL_Point *points, double dt) {
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		points[i].x = particles[i].position.x;
		points[i].y = particles[i].position.y;
	}
}
