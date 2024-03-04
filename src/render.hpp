#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.hpp"
#include "../include/json.hpp"
#include "../include/argparse.hpp"
using namespace std;

// Constants
int WIDTH = 1000;
int HEIGHT = 1000;

int MIN_ALPHA = 50;
int MAX_ALPHA = 255;

// SDL Stuff
SDL_Renderer *renderer = nullptr;
SDL_Window *win = nullptr;
SDL_Event event;

// Colors
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color YELLOW = {255, 255, 0, 255};

void draw_vector(const Vector2D &vec1, const Vector2D &vec2)
{
    SDL_RenderDrawLine(renderer, (int)(vec1.x), (int)(vec1.y), (int)(vec1.x + vec2.x), (int)(vec1.y + vec2.y));
}

void draw_curve(const vector<Vector2D> &points)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Drawing the points traced
    for (int i = 0; i < points.size() - 1; i++)
    {
        int alpha = MIN_ALPHA + (MAX_ALPHA - MIN_ALPHA) * (float)i / points.size();
        SDL_SetRenderDrawColor(renderer, YELLOW.r, YELLOW.g, YELLOW.b, alpha);
        draw_vector(points[i], points[i + 1] - points[i]);
    }
}

void InitSDL()
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Fourier Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}
