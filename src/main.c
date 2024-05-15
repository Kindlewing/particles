#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void draw_particle(SDL_Renderer *renderer, particle particle) {
	SDL_RenderDrawPoint(renderer, particle.position.x, particle.position.y);
}

int main() {
	int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	SDL_Window *window;
	SDL_Renderer *renderer;

	int num_particles = 10000;
	particle *particles;

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

	particles = malloc(sizeof(particle) * num_particles);
	for(int i = 0; i < num_particles; i++) {
		particle p = {0};
		p.position = (vec2){rand() % WIDTH, rand() % HEIGHT};
		p.radius = 1;
		p.mass = rand() % 10;
		p.velocity = (vec2){0, 0};
		particles[i] = p;
	}

	// main loop
	int close_requested = 0;

	double dt = 0.000001f;
	double last_frame_time = SDL_GetTicks();
	uint32_t frame_start;
	int total_frames = 0;

	char title[512];

	while(!close_requested) {
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				close_requested = 1;
				break;
			}
		}

		if(total_frames % TARGET_FPS == 0) {
			sprintf(title, "Particle simulation | FPS : %-4.0f", 1.0 / dt);
			SDL_SetWindowTitle(window, title);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
		// render stuff
		for(int i = 0; i < num_particles; i++) {
			draw_particle(renderer, particles[i]);
		}
		SDL_RenderPresent(renderer);

		// timing
		dt = (SDL_GetTicks() - last_frame_time) / 1000.0;
		while(dt < 1.0 / TARGET_FPS) {
			dt = SDL_GetTicks() - last_frame_time;
		}
		last_frame_time = SDL_GetTicks();
		total_frames++;
	}

	free(particles);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
