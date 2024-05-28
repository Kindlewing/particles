#include "physics.h"
#include "defs.h"
#include "vec_math.h"

#define G 6.67430e-11

void update(particle *particles, SDL_Point *points, double dt) {
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		apply_forces(&particles[i], particles, dt);
		particles[i].position.x += particles[i].velocity.x * dt;
		particles[i].position.y += particles[i].velocity.y * dt;
		// update visual particle position
		points[i].x = (int)particles[i].position.x;
		points[i].y = (int)particles[i].position.y;
	}
}

void apply_forces(particle *p, particle *particles, double dt) {
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		particle other = particles[i];
		if(p->id == other.id) {
			continue;
		}
		vec2 direction = sub(other.position, p->position);
		double dis = distance(other.position, p->position);
		if(dis < EPSILON) {
			continue;
		}
		direction = normalize(direction);
		double sqr_dist = sqr_magnitude(sub(other.position, p->position));
		vec2 force =
			mult_scaler(direction, G * p->mass * other.mass / sqr_dist);

		p->velocity.x += force.x / p->mass;
		p->velocity.y += force.y / p->mass;
	}
}
