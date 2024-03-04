#include <iostream>
#include <math.h>

using namespace std;

class Vector2D
{
public:
    double x, y;
    Vector2D() = default;
    Vector2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    Vector2D operator+(const Vector2D &v)
    {
        return Vector2D(x + v.x, y + v.y);
    }
    Vector2D operator-(const Vector2D &v)
    {
        return Vector2D(x - v.x, y - v.y);
    }
    Vector2D operator*(const double &s)
    {
        return Vector2D(x * s, y * s);
    }
    Vector2D operator/(const double &s)
    {
        return Vector2D(x / s, y / s);
    }
    double dot(const Vector2D &v)
    {
        return x * v.x + y * v.y;
    }
    void rotate_ip(const double &angle)
    {
        double back_up_x = this->x;
        this->x = this->x * cos(angle) + this->y * sin(angle);
        this->y = -back_up_x * sin(angle) + this->y * cos(angle);
    }
};
