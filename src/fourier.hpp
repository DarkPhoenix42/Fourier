#include "Vector2D.hpp"
#include <vector>
#include <math.h>

using namespace std;

/**
 * @param num_frequencies if this is k then the return value will have size 2*k+1
 * @param sampling_rate the dt in the integration will be 1/sampling_rate
 */
vector<Vector2D> fourier_series(vector<Vector2D> points, int num_frequencies, int sampling_rate)
{
    vector<Vector2D> result;
    int idx;
    double actual_time, angle, dt = 1.0 / sampling_rate;
    for (int k = -num_frequencies; k <= num_frequencies; k++)
    {
        Vector2D sum = Vector2D(0, 0);
        for (int t = 0; t <= sampling_rate; t++)
        {
            actual_time = ((double)t) / sampling_rate;
            idx = actual_time * points.size();
            angle = -2 * M_PI * k * actual_time;
            sum += points[idx].rotate(angle) * dt;
        }
        result.push_back(sum);
    }
    return result;
}
