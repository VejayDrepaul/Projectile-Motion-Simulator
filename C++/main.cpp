#include <iostream>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 500
#define WINDOW_X 410
#define WINDOW_Y 225
#define BALL_RADIUS 20
#define GRAVITY 9.80665 // Force of gravity
#define INITIAL_X 0
#define INITIAL_y 0

int main(int argc, char *args[]) {
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Projectile Motion Simulator", WINDOW_X, WINDOW_Y, 
                                            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || window == NULL || !renderer) {
        std::cout << "Something failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Main event loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
                quit = true;
        }

        // Setting background color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Rendering in the x-axis and y-axis 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderDrawLine(renderer, 10, 5, 10, WINDOW_HEIGHT - 10);
        SDL_RenderDrawLine(renderer, 10, WINDOW_HEIGHT - 10, 1195, WINDOW_HEIGHT - 10);

        // Rendering the ball using the formula x^2 + y^2 = r^2
        for (int y = -BALL_RADIUS; y <= BALL_RADIUS; ++y) {
            for (int x = -BALL_RADIUS; x <= BALL_RADIUS; ++x) {
                if (x * x + y * y <= BALL_RADIUS * BALL_RADIUS) 
                    SDL_RenderDrawPoint(renderer, 30 + x, (WINDOW_HEIGHT - 30) + y);
            }
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
