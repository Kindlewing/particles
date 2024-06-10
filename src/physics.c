#include "physics.h"
#include "defs.h"
#include "vec_math.h"

#define G 6.67430e-11

vec2 calculate_force(particle *p, particle *particles, double dt) {
	vec2 force = {0};
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
		force = mult_scaler(direction, G * p->mass * other.mass / sqr_dist);

		force.x /= p->mass;
		force.y /= p->mass;
	}
	return force;
}

void update(particle *particles, SDL_Point *points, double dt) {
	for(int i = 0; i < PARTICLE_COUNT; ++i) {
		vec2 force = calculate_force(&particles[i], particles, dt);
		particles[i].velocity.x += force.x * dt;
		particles[i].velocity.y += force.y * dt;

		particles[i].position.x += particles[i].velocity.x * dt;
		particles[i].position.y += particles[i].velocity.y * dt;

		points[i].x = particles[i].position.x;
		points[i].y = particles[i].position.y;
	}
}
