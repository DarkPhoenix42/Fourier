#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.hpp"
using namespace std;

// Colors
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color YELLOW = {255, 255, 0, 255};

void draw_vector(SDL_Renderer *renderer, const Vector2D &vec1, const Vector2D &vec2)
{
    SDL_RenderDrawLine(renderer, (int)(vec1.x), (int)(vec1.y), (int)(vec1.x + vec2.x), (int)(vec1.y + vec2.y));
}
void draw_curve(SDL_Renderer *renderer, const vector<Vector2D> &points, SDL_Color color, int min_alpha = 255, int max_alpha = 255)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Drawing the points traced
    for (int i = 0; i < points.size() - 1; i++)
    {
        int alpha = min_alpha + (max_alpha - min_alpha) * (float)i / points.size();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
        draw_vector(renderer, points[i], points[i + 1] - points[i]);
    }
}

void clear_screen(SDL_Renderer *renderer)
{
    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);
}

void InitSDL(SDL_Window *&win, SDL_Renderer *&renderer, int width, int height)
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Fourier Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

bool write_curve_to_file(const vector<Vector2D> &points, const string &filename)
{
    ofstream out_file;
    out_file.open(filename);
    if (!out_file)
    {
        cerr << "An error occured while trying to create" << filename << endl;
        return false;
    }
    out_file.write((char *)&points[0], points.size() * sizeof(Vector2D));
    out_file.close();
    return true;
}

vector<Vector2D> *load_curve_from_file(const string &filename)
{
    ifstream in_file;
    in_file.open(filename);
    if (!in_file)
    {
        cerr << "An error occured while trying to read" << filename << endl;
        return nullptr;
    }
    vector<Vector2D> *vecs = new vector<Vector2D>();
    while (in_file)
    {
        Vector2D current;
        in_file.read((char *)&current, sizeof(Vector2D));
        vecs->push_back(current);
    }
    in_file.close();
    return vecs;
}