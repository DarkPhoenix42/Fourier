#pragma once

#include "Vector2D.hpp"
#include <vector>
#include <math.h>

using namespace std;

/**
 * Calculates the Fourier series coefficients for a given set of points.
 *
 * @param points The input vector of 2D points.
 * @param num_frequencies The number of frequencies to consider in the Fourier series.
 * @param sampling_rate The sampling rate used to discretize the time domain.
 * @return A vector of 2D vectors representing the Fourier series coefficients.
 */
vector<Vector2D> fourier_series(vector<Vector2D> points, int num_frequencies, int sampling_rate)
{
    vector<Vector2D> result;
    double actual_time, angle, dt = 1.0 / sampling_rate;
    for (int k = -num_frequencies; k <= num_frequencies; k++)
    {
        Vector2D sum(0, 0);
        for (int t = 0; t <= sampling_rate; t++)
        {
            actual_time = ((double)t) / sampling_rate;
            int idx = actual_time * points.size();
            if (idx >= points.size())
                idx = points.size() - 1;

            angle = -2 * M_PI * k * actual_time;
            sum += points[idx].rotate(angle) * dt;
        }
        result.push_back(sum);
    }
    return result;
}
