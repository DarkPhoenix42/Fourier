#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "Vector2D.cpp"
#include "../include/json.hpp"
#include "../include/argparse.hpp"
using namespace std;

// Constants
int WIDTH = 800;
int HEIGHT = 800;

// SDL Stuff
SDL_Renderer *renderer = nullptr;
SDL_Window *win = nullptr;
SDL_Event event;
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color YELLOW = {255, 255, 0, 255};

// Global variables
Vector2D origin(WIDTH / 2, HEIGHT / 2);
vector<Vector2D> vecs = {Vector2D(200, 0), Vector2D(0, 0), Vector2D(0, 200)};
int point_buf_size = 100;
SDL_Point *points = new SDL_Point[point_buf_size];
int point_buf_idx = 0;

// Timing
float TIME_PERIOD = 4;
int FPS = 120;

Uint32 fps_timer;
double desired_delta_time = 1000 / FPS;
double delta_time = 0;

void draw_vector(const Vector2D &vec1, const Vector2D &vec2)
{
    SDL_RenderDrawLine(renderer, (int)(vec1.x), (int)(vec1.y), (int)(vec1.x + vec2.x), (int)(vec1.y + vec2.y));
}

void draw_screen()
{
    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);

    // Drawing the vectors
    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.b);
    Vector2D tip(origin);
    for (int i = 0; i < vecs.size(); i++)
    {
        draw_vector(tip, vecs[i]);
        tip += vecs[i];
    }

    // Drawing the points traced
    points[point_buf_idx] = {(int)(tip.x), (int)(tip.y)};
    point_buf_idx++;

    if (point_buf_idx == point_buf_size)
        point_buf_idx = 0;

    SDL_SetRenderDrawColor(renderer, YELLOW.r, YELLOW.g, YELLOW.b, YELLOW.a);
    SDL_RenderDrawPoints(renderer, points, point_buf_size);

    // Presenting the screen
    SDL_RenderPresent(renderer);
}

void handle_events()
{
    // Check if user wants to quit
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);
    }
}
void InitSDL()
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Fourier Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}
void update()
{
    // Rotates each vector in vecs according to it's k value
    int N = (vecs.size() - 1) / 2;
    for (int i = 0; i < vecs.size(); i++)
    {
        int k = i - N;
        vecs[i].rotate_ip(k * 2 * M_PI / (FPS * TIME_PERIOD));
    }
}

int main(int argc, char *argv[])
{
    InitSDL();
    while (true)
    {
        fps_timer = SDL_GetTicks();
        handle_events();
        draw_screen();
        update();

        // Code to restrict FPS to desired FPS
        delta_time = (SDL_GetTicks() - fps_timer);
        if (delta_time < desired_delta_time)
            SDL_Delay((desired_delta_time - delta_time));
    }
}