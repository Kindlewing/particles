#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void draw_circle(SDL_Renderer* renderer, vec2 origin, int radius) {
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while(x >= y) {
		SDL_RenderDrawPoint(renderer, origin.x + x, origin.y + y);
		SDL_RenderDrawPoint(renderer, origin.x + y, origin.y + x);
		SDL_RenderDrawPoint(renderer, origin.x - y, origin.y + x);
		SDL_RenderDrawPoint(renderer, origin.x - x, origin.y + y);
		SDL_RenderDrawPoint(renderer, origin.x - x, origin.y - y);
		SDL_RenderDrawPoint(renderer, origin.x - y, origin.y - x);
		SDL_RenderDrawPoint(renderer, origin.x + y, origin.y - x);
		SDL_RenderDrawPoint(renderer, origin.x + x, origin.y - y);

		if(err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}

		if(err > 0) {
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}

int main() {
	int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	SDL_Window* window;
	SDL_Renderer* renderer;

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

	// main loop
	int close_requested = 0;
	while(!close_requested) {
		double current_frame;
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				close_requested = 1;
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
		// render stuff
		draw_circle(renderer, (vec2){50, 50}, 20);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
