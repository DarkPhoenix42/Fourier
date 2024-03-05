#pragma once
#include "sdl_utils.hpp"

using namespace std;

class FourierRenderer
/**
 * @class FourierRenderer
 * @brief A class that handles rendering of Fourier vectors.
 */
{
private:
    SDL_Renderer *renderer;  /**< The SDL renderer used for drawing. */
    vector<Vector2D> *vecs;  /**< A pointer to the vector of Fourier vectors. */
    Vector2D origin;         /**< The origin point for drawing the vectors. */
    vector<Vector2D> points; /**< A buffer for storing the points of the drawn curve. */
    int point_buf_size;      /**< The maximum size of the points buffer. */
    int fps;                 /**< The frames per second for animation. */
    double time_period;      /**< The time period for animation. */

public:
    /**
     * @brief Default constructor for FourierRenderer.
     */
    FourierRenderer() = default;

    /**
     * @brief Constructor for FourierRenderer.
     * @param renderer The SDL renderer used for drawing.
     * @param vecs A pointer to the vector of Fourier coefficient vectors.
     * @param origin The origin point for drawing the vectors.
     * @param fps The frames per second for animation.
     * @param time_period The time period for animation.
     * @param point_buf_size The maximum size of the points buffer.
     */
    FourierRenderer(SDL_Renderer *renderer, vector<Vector2D> *vecs, const Vector2D &origin, const int fps, const double time_period, const int point_buf_size)
    {
        this->renderer = renderer;
        this->vecs = vecs;
        this->fps = fps;
        this->time_period = time_period;
        this->point_buf_size = point_buf_size;
        this->origin.x = origin.x;
        this->origin.y = origin.y;
    }

    /**
     * @brief Updates the Fourier vectors by rotating each vector according to its k value.
     */
    void update()
    {
        int N = (vecs->size() - 1) / 2;
        for (int i = 0; i < (int)vecs->size(); i++)
        {
            int k = i - N;
            (*vecs)[i].rotate_ip(k * 2 * M_PI / (fps * time_period));
        }
    }

    /**
     * @brief Draws the Fourier vectors and the curve.
     */
    void draw()
    {
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
        if ((int)points.size() > point_buf_size)
            points.erase(points.begin());

        draw_curve(renderer, points, YELLOW, 100, 255);
    }
};
