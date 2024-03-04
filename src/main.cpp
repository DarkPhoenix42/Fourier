#include <iostream>
#include "Vector2D.hpp"
#include "renderer.hpp"
#include "sdl_utils.hpp"
#include "file_dump_utils.hpp"
#include "fourier.hpp"
#include "../include/json.hpp"
#include "../include/argparse.hpp"

using namespace std;

int width = 800;
int height = 800;
Vector2D origin;

SDL_Window *win;
SDL_Renderer *renderer;
SDL_Event event;

int refresh_rate = 60;
int fps = 60;
double refresh_delta, fps_delta;
Uint32 fps_timer;
Uint32 draw_timer;

double time_period = 5.0;
int point_buf_len = 100, num_freq = 10, sampling_rate = 1000;

string filename = "../curves/curve.bin";

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
void load_params()
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
    point_buf_len = 0.25 * time_period * fps;
}

void parse_args(int argc, char *argv[])
{
    argparse::ArgumentParser parser("Fourier Series Visualizer");
    parser.add_description("A program to simulate Reaction Diffusion using the Gray-Scott model. Give initial parameters as arguments or edit the config.json file.");

    parser.add_argument("--input", "-i")
        .default_value("../curves/curve.bin")
        .nargs(1)
        .help("Set the width of the simulation.");

    parser.add_argument("--render", "-r")
        .default_value("../curves/curve.bin")
        .nargs(1)
        .help("Set the height of the simulation.");

    try
    {
        parser.parse_args(argc, argv);
    }
    catch (const runtime_error &err)
    {
        cout << err.what() << endl;
        cout << parser;
        exit(0);
    }
    if (parser.is_used("--input"))
        filename = parser.get<string>("--input");
    else if (parser.is_used("--render"))
        filename = parser.get<string>("--render");
    else
    {
        cerr << "One of -r or -i flags must be used!" << endl;
        exit(0);
    }
}
void render(vector<Vector2D> &vecs)
{
    FourierRenderer fourier_renderer(renderer, &vecs, origin, fps, time_period, 10000);
    draw_timer = SDL_GetTicks();
    fps_timer = SDL_GetTicks();
    while (true)
    {
        handle_quit(event);
        if (SDL_GetTicks() - draw_timer > refresh_delta)
        {
            clear_screen(renderer);
            fourier_renderer.draw();
            present_screen(renderer);
            draw_timer = SDL_GetTicks();
        }
        if (SDL_GetTicks() - fps_timer > fps_delta)
        {
            update(fourier_renderer);
            fps_timer = SDL_GetTicks();
        }
    }
}

void take_input()
{
    vector<Vector2D> points;
    bool is_mouse_pressed = false;
    Vector2D mouse;
    while (true)
    {
        if (SDL_GetTicks() - draw_timer > refresh_delta)
        {
            clear_screen(renderer);
            draw_curve(renderer, points, YELLOW);
            present_screen(renderer);
            draw_timer = SDL_GetTicks();
        }
        if (SDL_GetTicks() - fps_timer < fps_delta)
        {
            continue;
        }
        fps_timer = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit(0);
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                for (auto &p : points)
                {
                    p -= origin;
                }
                cout << "Points: " << points.size() << endl;
                vector<Vector2D> vecs = fourier_series(points, num_freq, sampling_rate);
                write_curve_to_file(filename, vecs);
                exit(0);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                is_mouse_pressed = true;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                mouse.x = event.motion.x;
                mouse.y = event.motion.y;
            }
        }
        if (is_mouse_pressed)
            points.push_back(mouse);
    }
}

int main(int argc, char *argv[])
{
    load_params();
    // parse_args(argc, argv);
    InitSDL(win, renderer, width, height);
    fps_timer = SDL_GetTicks();
    draw_timer = SDL_GetTicks();
    // take_input();
    vector<Vector2D> vecs;
    load_curve_from_file(filename, &vecs);
    render(vecs);
}