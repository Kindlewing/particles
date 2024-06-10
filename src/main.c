#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stime.h"
#include "physics.h"
#include "defs.h"

int main() {
	srand(time(0));
	int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	SDL_Window *window;
	SDL_Renderer *renderer;

	particle *particles;
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
							  SDL_WINDOW_FULLSCREEN);
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

	particles = malloc(PARTICLE_COUNT * sizeof(particle));
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		particle p = {0};
		p.position = (vec2){rand() % WIDTH, rand() % HEIGHT};
		p.mass = rand() % 100000;
		p.id = i;
		p.velocity = (vec2){rand() % 100, rand() % 100};
		particles[i] = p;
		points[i] = (SDL_Point){p.position.x, p.position.y};
	}

	// main loop
	int close_requested = 0;
	char title[128];
	stime time = {0};
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
				continue;
			}
		}

		update(particles, points, time.dt);
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
