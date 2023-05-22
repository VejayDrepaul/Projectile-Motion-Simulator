#include <iostream>
#include <SDL2/SDL.h>
#include <tuple>
#include <cmath>
#include <vector>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 500
#define WINDOW_X 410
#define WINDOW_Y 225
#define BALL_RADIUS 20
#define GRAVITY 9.80665 // Force of gravity
#define FRAME_RATE 60
#define INITIAL_X 0 // only change if ball initial position changes 
#define INITIAL_Y WINDOW_HEIGHT - BALL_RADIUS // only change if ball initial position changes
#define TIME_STEP 0.05

std::tuple<double, double> calculations(double vx, double vy);

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Projectile Motion Simulator", WINDOW_X, WINDOW_Y,
                                            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || window == NULL || !renderer) {
        std::cout << "Something failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    double ball_x = 30;
    double ball_y = INITIAL_Y;
    double initial_velocity = 50; // Adjust the initial velocity as needed
    double initial_angle = 45; // Adjust the initial angle as needed
    double vx = initial_velocity * std::cos(initial_angle * M_PI / 180.0);
    double vy = -initial_velocity * std::sin(initial_angle * M_PI / 180.0);
    int frame_delay = 1000 / FRAME_RATE;

    // Main event loop
    Uint32 frame_start;
    int frame_time;
    bool quit = false;
    SDL_Event event;

    std::vector<std::pair<double, double>> trace_points; // Store the traced points
    trace_points.push_back(std::make_pair(ball_x, ball_y)); // Add initial point

    while (!quit) {
        frame_start = SDL_GetTicks(); // Get the starting time of the frame
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

        std::tuple<double, double> projectile_info = calculations(vx, vy);

        vx = std::get<0>(projectile_info);
        vy = std::get<1>(projectile_info);
        ball_x += vx * TIME_STEP;
        ball_y += vy * TIME_STEP;

        // Check if the ball hits the ground
        if (ball_y + BALL_RADIUS >= WINDOW_HEIGHT) {
            ball_y = WINDOW_HEIGHT - BALL_RADIUS;
            vy = -vy; // Bounce back up with the opposite vertical velocity
        }

        if (ball_x + BALL_RADIUS >= WINDOW_WIDTH) {
            vy = 0;
            vx = 0;
        }

        // Store the current position for tracing
        trace_points.push_back(std::make_pair(ball_x, ball_y));

        // Render the traced points as a line
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
        for (size_t i = 1; i < trace_points.size(); ++i) {
            SDL_RenderDrawLine(renderer, trace_points[i - 1].first, trace_points[i - 1].second,
                                trace_points[i].first, trace_points[i].second);
        }

        // Rendering the ball using the formula x^2 + y^2 = r^2
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int y = -BALL_RADIUS; y <= BALL_RADIUS; ++y) {
            for (int x = -BALL_RADIUS; x <= BALL_RADIUS; ++x) {
                if (x * x + y * y <= BALL_RADIUS * BALL_RADIUS)
                    SDL_RenderDrawPoint(renderer, ball_x + x, ball_y + y);
            }
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Calculate the time it took to process the frame
        frame_time = SDL_GetTicks() - frame_start;
        // Delay the remaining time to maintain the desired frame rate
        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

std::tuple<double, double> calculations(double vx, double vy) {
    vx = vx;
    vy += GRAVITY * TIME_STEP; // update vertical velocity with gravity

    return std::make_tuple(vx, vy);
}