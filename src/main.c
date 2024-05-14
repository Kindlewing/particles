#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct {
	double x;
	double y;

} vec2;

void draw_circle(vec2 origin, double radius) {
	double x = radius;
	double y = origin.y;
}

int main() {
	SDL_Window* window;
	SDL_Renderer* renderer;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Unable to initialize SDL");
		return -1;
	}
	window = SDL_CreateWindow("Particle simulation",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WIDTH,
							  HEIGHT,
							  0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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

		draw_circle((vec2){WIDTH / 2.0, HEIGHT / 2.0}, 30);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
