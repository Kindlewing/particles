#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void draw_particle(SDL_Renderer *renderer, particle particle) {
	SDL_RenderDrawPoint(renderer, particle.position.x, particle.position.y);
}

void update_particle(particle *particle, double dt) {
	particle->position.y += dt;
	if(particle->position.y / 2 > HEIGHT) {
		particle->position.y = HEIGHT;
	}
}

int main() {
	int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	SDL_Window *window;
	SDL_Renderer *renderer;

	particle particles[PARTICLE_COUNT * sizeof(particle)];

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
	}

	// main loop
	int close_requested = 0;
	char title[128];
	double delta = 0.00001;
	uint64_t prev_frame_time = SDL_GetTicks64();
	int frame_count = 0;

	while(!close_requested) {
		SDL_Event event;

		if(frame_count % 60 == 0) {
			snprintf(title, 128, "Particle simulation | FPS: %f", 1.0 / delta);
			SDL_SetWindowTitle(window, title);
		}

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				close_requested = 1;
				break;
			}
		}

		delta = SDL_GetTicks64() - prev_frame_time;
		while(delta < 1.0 / TARGET_FPS) {
			delta = SDL_GetTicks64() - prev_frame_time;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
		draw_particle(renderer, particles[4]);
		SDL_RenderPresent(renderer);

		prev_frame_time = SDL_GetTicks64();
		frame_count++;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
