#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "Vector2D.cpp"
#include "../include/json.hpp"
#include "../include/argparse.hpp"
using namespace std;

// Constants
int WIDTH = 1000;
int HEIGHT = 1000;

// SDL Stuff
SDL_Renderer *renderer = nullptr;
SDL_Window *win = nullptr;
SDL_Event event;

// Colors
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color YELLOW = {255, 255, 0, 255};
int MIN_ALPHA = 50;
int MAX_ALPHA = 255;

// Global variables
Vector2D origin(WIDTH / 2, HEIGHT / 2);
vector<Vector2D> vecs = {Vector2D(50, 50), Vector2D(200, 0), Vector2D(0, 0), Vector2D(0, 200), Vector2D(100, 100)};
int point_buf_size = vecs.size() * 50;
vector<Vector2D> points;

// Timing
float TIME_PERIOD = 4;
int fps_counter = 0;
int REFRESH_RATE = 60;
int FPS = 240;
Uint32 fps_timer;
Uint32 draw_timer;

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

    points.push_back(tip);
    if (points.size() > point_buf_size)
    {
        points.erase(points.begin());
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Drawing the points traced
    for (int i = 0; i < points.size() - 1; i++)
    {
        int alpha = MIN_ALPHA + (MAX_ALPHA - MIN_ALPHA) * (float)i / points.size();
        SDL_SetRenderDrawColor(renderer, YELLOW.r, YELLOW.g, YELLOW.b, alpha);
        draw_vector(points[i], points[i + 1] - points[i]);
    }
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
    draw_timer = SDL_GetTicks();
    fps_timer = SDL_GetTicks();
    while (true)
    {
        handle_events();

        if (SDL_GetTicks() - draw_timer > 1000.0 / REFRESH_RATE)
        {
            draw_screen();
            draw_timer = SDL_GetTicks();
        }
        if (SDL_GetTicks() - fps_timer > 1000.0 / FPS)
        {
            fps_timer = SDL_GetTicks();
            update();
        }
    }
}