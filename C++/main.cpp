#include <iostream>
#include <SDL2/SDL.h>
#include <tuple>
#include <math.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 500
#define WINDOW_X 410
#define WINDOW_Y 225
#define GRAVITY 9.80665 // Force of gravity
#define INITIAL_X 0
#define INITIAL_y 0

int main(int argc, char *args[]) {
    SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not be initilazied: " << SDL_GetError() << std::endl;
	}
	else {
		window = SDL_CreateWindow("Projectile Motion Simulator", WINDOW_X, WINDOW_Y, 
                                WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);

            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
                SDL_DestroyWindow(window);
                SDL_Quit();
                return -1;
            }

            // setting background color to white
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);

            // drawing of vertical x-axis
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, 10, 10, 10, WINDOW_HEIGHT - 10);
            SDL_RenderPresent(renderer);

            // drawing of horizantal y-axis

			SDL_Event event; 
			bool quit = false; 
			while (quit == false) { 
				while (SDL_PollEvent(&event)) { 
					if (event.type == SDL_QUIT) 
						quit = true; 
				} 
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}

// physics calculations: velocity components and time of flight of projectile
std::tuple<double, double, double> flight_mechanics(double velocity, double angle) {
    double rad = angle * (M_PI / 180);
    double vx = velocity * cos(rad); 
    double vy = velocity * sin(rad);
    double flight_time = (2 * (velocity * sin(rad))) / GRAVITY;

    return std::make_tuple(vx, vy, flight_time);
}

