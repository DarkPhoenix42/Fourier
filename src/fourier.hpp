#include "Vector2D.hpp"
#include "utils.hpp"
#include <vector>
#include <math.h>

using namespace std;

/**
 * @param numFrequenciees if this is k then the return value will have size 2*k+1
 * @param samplingRate the dt in the integration will be 1/samplingRate
 */
vector<Vector2D> fourier_series(vector<Vector2D> points, int numFrequencies, int samplingRate)
{
    vector<Vector2D> result;
    double actualTime;
    int index;
    double angle, dt = 1.0 / samplingRate;
    for (int k = -numFrequencies; k <= numFrequencies; k++)
    {
        Vector2D sum = Vector2D(0, 0);
        for (int t = 0; t <= samplingRate; t++)
        {
            actualTime = ((double)t) / samplingRate;
            index = actualTime * points.size();
            angle = -2 * M_PI * k * actualTime;
            sum += points[index].rotate(angle) * dt;
        }
        result.push_back(sum);
    }
    return result;
}
