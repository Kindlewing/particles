#ifndef DEFS_H
#define DEFS_H

#define WIDTH 3440
#define HEIGHT 1440
#define TARGET_FPS 60
#define PARTICLE_COUNT 10

typedef struct {
	double x;
	double y;
} vec2;

typedef struct {
	vec2 position;
	vec2 velocity;
	double mass;
} particle;

#endif // !DEFS_H
