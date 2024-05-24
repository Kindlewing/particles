#include "physics.h"
#include "defs.h"
#include "vec_math.h"

#define G 6.67430e-11
#define EPSILON 1e-10 // Small value to prevent division by zero

void update(particle *particles, SDL_Point *points, double dt) {
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i].position.x += particles[i].velocity.x * dt;
		particles[i].position.y += particles[i].velocity.y * dt;
		apply_forces(&particles[i], particles, dt);
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
		vec2 f =
			mult_scaler(direction, G * ((p->mass * other.mass) / (dis * dis)));
		p->velocity.x += (f.x / p->mass) * dt;
		p->velocity.y += (f.y / p->mass) * dt;
	}
}

double distance(vec2 pos_a, vec2 pos_b) {
	double dx = pos_a.x - pos_b.x;
	double dy = pos_a.y - pos_b.y;
	return sqrt(dx * dx + dy * dy);
}
