/**
 * @file main.cpp
 * @brief This file contains the main function and supporting functions for the Fourier Series Visualizer program.
 */

#include <iostream>
#include "Vector2D.hpp"
#include "renderer.hpp"
#include "sdl_utils.hpp"
#include "file_dump_utils.hpp"
#include "fourier.hpp"
#include "json.hpp"
#include "argparse.hpp"

using namespace std;

int width, height;
Vector2D origin; /**< The origin point of the coordinate system. */

SDL_Window *win;
SDL_Renderer *renderer;
SDL_Event event;

int refresh_rate = 60;
int fps = 60;
double refresh_delta, fps_delta;
Uint32 fps_timer;
Uint32 draw_timer;

double time_period = 5.0;
int point_buf_len, num_freq, sampling_rate;

string filename;
bool to_render = false; /**< Flag indicating whether to render the curve or take input from the user. */

/**
 * @brief Loads the parameters from the configuration file config.json.
 */
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
    time_period = config["time_period"];

    refresh_delta = 1000.0 / refresh_rate;
    fps_delta = 1000.0 / fps;
    point_buf_len = ((double)config["point_buf_multiplier"]) * fps * time_period;
}

/**
 * @brief Parses the command-line arguments.
 */
void parse_args(int argc, char *argv[])
{
    // TODO : Add description
    argparse::ArgumentParser parser("Fourier Series Visualizer");
    parser.add_description("");

    parser.add_argument("--input", "-i")
        .default_value("../curves/curve.bin")
        .nargs(1)
        .help("The file to write the curve to after taking input.");

    parser.add_argument("--render", "-r")
        .default_value("../curves/curve.bin")
        .nargs(1)
        .help("The file to load the curve to render.");

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
    {
        to_render = true;
        filename = parser.get<string>("--render");
    }
    else
    {
        cerr << "One of -r or -i flags must be used!" << endl;
        exit(0);
    }
}

/**
 * @brief Renders the Fourier series.
 *
 * @param vecs The vector of fourier series coefficients for the curve.
 */
void render(vector<Vector2D> &vecs)
{
    FourierRenderer fourier_renderer(renderer, &vecs, origin, fps, time_period, point_buf_len);
    while (true)
    {
        handle_quit(event);
        if (SDL_GetTicks() - draw_timer > refresh_delta)
        {
            clear_screen(renderer);
            fourier_renderer.draw();
            SDL_RenderPresent(renderer);
            draw_timer = SDL_GetTicks();
        }
        if (SDL_GetTicks() - fps_timer > fps_delta)
        {
            fourier_renderer.update();
            fps_timer = SDL_GetTicks();
        }
    }
}

/**
 * @brief Takes input from the user to create the curve.
 */
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
            draw_curve(renderer, points, RED);
            SDL_RenderPresent(renderer);
            draw_timer = SDL_GetTicks();
        }
        if (SDL_GetTicks() - fps_timer < fps_delta)
            continue;

        fps_timer = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                exit(0);

            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                for (auto &p : points)
                    p -= origin;

                cout << points.size() << " from curve were sampled." << endl;
                write_curve_to_file(filename, points);
                exit(0);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                is_mouse_pressed = true;

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
    cout << "Loaded parameters from config.json" << endl;
    parse_args(argc, argv);
    cout << "Parsed command-line arguments" << endl;
    InitSDL(win, renderer, width, height);

    fps_timer = SDL_GetTicks();
    draw_timer = SDL_GetTicks();
    if (to_render)
    {
        vector<Vector2D> points;
        load_curve_from_file(filename, &points);
        vector<Vector2D> vecs = fourier_series(points, num_freq, sampling_rate);
        render(vecs);
    }
    else
        take_input();
}
