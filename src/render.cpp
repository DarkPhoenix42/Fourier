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

Uint32 fps_timer;
int fps_counter = 0;

// Global Variables
Vector2D origin(WIDTH / 2, HEIGHT / 2);
vector<Vector2D> vecs = {Vector2D(200, 0), Vector2D(0, 0), Vector2D(0, 200)};
float TIME_PERIOD = 4;
int FPS = 60;
double desired_delta_time = 1000 / FPS;
double delta_time = 0;

void draw_vector(const Vector2D &origin, const Vector2D &vec)
{
    SDL_RenderDrawLine(renderer, (int)origin.x, (int)origin.y, (int)(origin.x + vec.x), (int)(origin.y + vec.y));
}

void draw_screen()
{
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.b);
    draw_vector(origin, vecs[0]);
    for (int i = 1; i < vecs.size(); i++)
    {
        draw_vector(vecs[i - 1], vecs[i]);
    }

    SDL_RenderPresent(renderer);
}

void handle_events()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);
    }
}
void InitSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Fourier Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}
void update()
{
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
        delta_time = (SDL_GetTicks() - fps_timer);
        if (delta_time < desired_delta_time)
        {
            SDL_Delay((desired_delta_time - delta_time));
        }
    }
}