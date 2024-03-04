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
    for (int k = -numFrequencies; k <= numFrequencies; k++)
    {
        Vector2D sum = Vector2D(0, 0);
        for (int t = 0; t <= samplingRate; t++)
        {
            sum += (points[(int)((points.size()) * (((double)t) / samplingRate))].rotate(-2 * M_PI * k * t / samplingRate)) * ();
        }
        result.push_back(sum);
    }
    return result;
}
