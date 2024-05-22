#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"

void update_particle(particle *particle, double dt) {
	particle->position.x += dt * 400;
	particle->position.y += dt * 400;
	if(particle->position.x > WIDTH) {
		particle->position.x = rand() % WIDTH;
	}
	if(particle->position.y > HEIGHT) {
		particle->position.y = rand() % HEIGHT;
	}
}

int main() {
	int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	SDL_Window *window;
	SDL_Renderer *renderer;

	particle particles[PARTICLE_COUNT];
	SDL_Point points[PARTICLE_COUNT];

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}
	window = SDL_CreateWindow("Particle simulation",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WIDTH,
							  HEIGHT,
							  0);
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if(window == NULL) {
		printf("Error creating window");
		SDL_Quit();
		return -1;
	}

	if(renderer == NULL) {
		printf("Error renderer creation");
		return -1;
	}

	for(int i = 0; i < PARTICLE_COUNT; i++) {
		particle p = {0};
		p.position = (vec2){rand() % WIDTH, rand() % HEIGHT};
		p.radius = 1;
		p.mass = rand() % 10;
		p.velocity = (vec2){0, 0};
		particles[i] = p;
		points[i] = (SDL_Point){p.position.x, p.position.y};
	}

	// main loop
	int close_requested = 0;
	char title[128];
	time time = {0};
	time.frame_count = 0;
	double freq_inv = 1.0 / (double)SDL_GetPerformanceFrequency();
	uint64_t last_frame_time = SDL_GetPerformanceCounter();

	while(!close_requested) {
		SDL_Event event;
		uint64_t current_frame_time = SDL_GetPerformanceCounter();
		time.dt =
			(float)((double)current_frame_time - last_frame_time) * freq_inv;

		if(time.frame_count % 60 == 0) {
			snprintf(title,
					 128,
					 "Particle simulation | FPS: %d",
					 (int)(1.0 / time.dt));
			SDL_SetWindowTitle(window, title);
		}

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				close_requested = 1;
				break;
			}
		}

		for(int i = 0; i < PARTICLE_COUNT; i++) {
			update_particle(&particles[i], time.dt);
			points[i].x = particles[i].position.x;
			points[i].y = particles[i].position.y;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
		SDL_RenderDrawPoints(renderer, points, PARTICLE_COUNT);
		SDL_RenderPresent(renderer);
		last_frame_time = current_frame_time;
		time.frame_count++;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
