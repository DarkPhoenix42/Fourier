#pragma once
#include <iostream>
#include "utils.hpp"

using namespace std;

class FourierRenderer
{
private:
    SDL_Renderer *renderer;
    vector<Vector2D> *vecs;
    Vector2D origin;
    vector<Vector2D> points;
    int point_buf_size;
    int fps;
    double time_period;

public:
    FourierRenderer() = default;
    FourierRenderer(SDL_Renderer *renderer, vector<Vector2D> *vecs, const Vector2D &origin, const int fps, const double time_period, const int point_buf_size)
    {
        this->renderer = renderer;
        this->vecs = vecs;
        this->fps = fps;
        this->time_period = time_period;
        this->point_buf_size = point_buf_size;
        this->origin = origin;
    }
    void update()
    {
        // Rotates each vector in vecs according to it's k value
        int N = (vecs->size() - 1) / 2;
        for (int i = 0; i < vecs->size(); i++)
        {
            int k = i - N;
            (*vecs)[i].rotate_ip(k * 2 * M_PI / (fps * time_period));
        }
    }
    void draw()
    {
        // Drawing the vectors
        SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.b);
        Vector2D tip(origin);
        int N = (vecs->size() - 1) / 2;
        draw_vector(renderer, origin, (*vecs)[N]);
        tip += (*vecs)[N];
        for (int i = 1; i <= N; i++)
        {
            draw_vector(renderer, tip, (*vecs)[N + i]);
            tip += (*vecs)[N + i];
            draw_vector(renderer, tip, (*vecs)[N - i]);
            tip += (*vecs)[N - i];
        }

        points.push_back(tip);
        if (points.size() > point_buf_size)
        {
            points.erase(points.begin());
        }
        draw_curve(renderer, points, YELLOW, 100, 255);
    }
};
