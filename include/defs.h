#ifndef DEFS_H
#define DEFS_H

#define WIDTH 1920
#define HEIGHT 1080
#define PARTICLE_COUNT 1000

typedef struct {
	int x;
	int y;
} vec2;

typedef struct {
	vec2 position;
	vec2 velocity;
	double mass;
	int radius;
} particle;

#endif // !DEFS_H
