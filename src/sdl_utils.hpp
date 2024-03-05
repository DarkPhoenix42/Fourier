#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.hpp"

using namespace std;

// Colors
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color YELLOW = {255, 255, 0, 255};

/**
 * @brief Draws a vector using the SDL renderer.
 *
 * @param renderer The SDL renderer to use.
 * @param vec1 The starting point of the vector.
 * @param vec2 The ending point of the vector.
 */
void inline draw_vector(SDL_Renderer *renderer, const Vector2D &vec1, const Vector2D &vec2)
{
    SDL_RenderDrawLine(renderer, (int)(vec1.x), (int)(vec1.y), (int)(vec1.x + vec2.x), (int)(vec1.y + vec2.y));
}

/**
 * @brief Draws a curve using a series of points on the SDL renderer.
 *
 * @param renderer The SDL renderer to draw on.
 * @param points The vector of points that make up the curve.
 * @param color The color of the curve.
 * @param min_alpha The minimum alpha value for the curve (default: 255).
 * @param max_alpha The maximum alpha value for the curve (default: 255).
 */
void draw_curve(SDL_Renderer *renderer, const vector<Vector2D> &points, SDL_Color color, int min_alpha = 255, int max_alpha = 255)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Drawing the points traced
    for (int i = 0; i < (int)points.size() - 1; i++)
    {
        int alpha = min_alpha + (max_alpha - min_alpha) * (float)i / points.size();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
        draw_vector(renderer, points[i], points[i + 1] - points[i]);
    }
}

/**
 * @brief Clears the SDL renderer by filling it with black color.
 *
 * @param renderer The SDL renderer to clear.
 */
void clear_screen(SDL_Renderer *renderer)
{
    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);
}

/**
 * @brief Handles the quit event by exiting the program when the window is closed.
 */
void handle_quit(SDL_Event &event)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0);
        }
    }
}

/**
 * @brief Initializes the SDL library, creates a window, and creates a renderer.
 *
 * @param win The SDL window to create.
 * @param renderer The SDL renderer to create.
 * @param width The width of the window.
 * @param height The height of the window.
 */
void InitSDL(SDL_Window *&win, SDL_Renderer *&renderer, int width, int height)
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Fourier Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}
