#include <iostream>
#include "Vector2D.hpp"
#include "renderer.hpp"
#include "utils.hpp"
#include "fourier.hpp"
#include "../include/json.hpp"

using namespace std;
int width = 800;
int height = 800;
Vector2D origin;

int num_freq = 10, sampling_rate = 1000;
SDL_Window *win;
SDL_Renderer *renderer;
SDL_Event event;

int refresh_rate = 60;
int fps = 60;
double refresh_delta, fps_delta;
Uint32 fps_timer;
Uint32 draw_timer;

void handle_events()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(win);
            SDL_Quit();
            exit(0);
        }
    }
}
void update(FourierRenderer &fourier_renderer)
{
    fourier_renderer.update();
}
void draw_screen(FourierRenderer &fourier_renderer)
{
    clear_screen(renderer);
    fourier_renderer.draw();
    SDL_RenderPresent(renderer);
}
void load_args()
{

    // Configuration
    nlohmann::json config;
    fstream config_file;

    config_file.open("../config.json", ios::in);
    config_file >> config;
    config_file.close();

    width = config["width"];
    height = config["height"];

    origin.x = width / 2;
    origin.y = height / 2;

    fps = config["fps"];
    refresh_rate = config["refresh_rate"];
    num_freq = config["num_frequencies"];
    sampling_rate = config["sampling_rate"];
    refresh_delta = 1000.0 / refresh_rate;
    fps_delta = 1000.0 / fps;
}
int main()
{
    load_args();
    InitSDL(win, renderer, width, height);
    vector<Vector2D> points;
    int num_points = 1000;
    for (int i = 0; i < num_points; i++)
    {
        double x = 250 + 200 * cos(2 * M_PI * i / num_points);
        double y = 100 + 100 * sin(2 * M_PI * i / num_points);
        points.push_back(Vector2D(x, y));
    }
    vector<Vector2D> vecs = fourier_series(points, num_freq, sampling_rate);
    FourierRenderer fourier_renderer(renderer, &vecs, origin, fps, 5, 150);
    draw_timer = SDL_GetTicks();
    fps_timer = SDL_GetTicks();
    while (true)
    {
        handle_events();
        if (SDL_GetTicks() - draw_timer > refresh_delta)
        {
            draw_screen(fourier_renderer);
            draw_timer = SDL_GetTicks();
        }
        if (SDL_GetTicks() - fps_timer > fps_delta)
        {
            fps_timer = SDL_GetTicks();
            update(fourier_renderer);
        }
    }
}