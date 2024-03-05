#pragma once
#include <math.h>

using namespace std;

/**
 * @brief Represents a 2D vector.
 */
class Vector2D
{
public:
    double x, y;

    /**
     * @brief Default constructor.
     */
    Vector2D() = default;

    /**
     * @brief Constructor that initializes the vector with given x and y values.
     * @param x The x-coordinate of the vector.
     * @param y The y-coordinate of the vector.
     */
    Vector2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    /**
     * @brief Copy constructor.
     * @param v The vector to be copied.
     */
    Vector2D(const Vector2D &v)
    {
        this->x = v.x;
        this->y = v.y;
    }

    /**
     * @brief Overloaded addition operator.
     * @param v The vector to be added.
     * @return The sum of the two vectors.
     */
    Vector2D operator+(const Vector2D &v)
    {
        return Vector2D(x + v.x, y + v.y);
    }

    /**
     * @brief Overloaded addition assignment operator.
     * @param v The vector to be added.
     * @return Reference to the modified vector.
     */
    Vector2D operator+=(const Vector2D &v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    /**
     * @brief Overloaded subtraction operator.
     * @param v The vector to be subtracted.
     * @return The difference between the two vectors.
     */
    Vector2D operator-(const Vector2D &v) const
    {
        return Vector2D(x - v.x, y - v.y);
    }

    /**
     * @brief Overloaded subtraction assignment operator.
     * @param v The vector to be subtracted.
     * @return Reference to the modified vector.
     */
    Vector2D operator-=(const Vector2D &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    /**
     * @brief Overloaded multiplication operator.
     * @param s The scalar value to multiply the vector by.
     * @return The scaled vector.
     */
    Vector2D operator*(const double &s)
    {
        return Vector2D(x * s, y * s);
    }

    /**
     * @brief Overloaded multiplication assignment operator.
     * @param s The scalar value to multiply the vector by.
     * @return Reference to the modified vector.
     */
    Vector2D operator*=(const double &s)
    {
        this->x *= s;
        this->y *= s;
        return *this;
    }

    /**
     * @brief Overloaded division operator.
     * @param s The scalar value to divide the vector by.
     * @return The scaled vector.
     */
    Vector2D operator/(const double &s)
    {
        return Vector2D(x / s, y / s);
    }

    /**
     * @brief Overloaded division assignment operator.
     * @param s The scalar value to divide the vector by.
     * @return Reference to the modified vector.
     */
    Vector2D operator/=(const double &s)
    {
        this->x /= s;
        this->y /= s;
        return *this;
    }

    /**
     * @brief Calculates the magnitude of the vector.
     * @return The magnitude of the vector.
     */
    double magnitude()
    {
        return sqrt(x * x + y * y);
    }

    /**
     * @brief Normalizes the vector.
     * @return The normalized vector.
     */
    Vector2D normalize()
    {
        double mag = magnitude();
        return Vector2D(x / mag, y / mag);
    }

    /**
     * @brief Calculates the dot product of two vectors.
     * @param v The vector to calculate the dot product with.
     * @return The dot product of the two vectors.
     */
    double dot(const Vector2D &v)
    {
        return x * v.x + y * v.y;
    }

    /**
     * @brief Rotates the vector in place by a given angle.
     * @param angle The angle in radians by which to rotate the vector.
     */
    void rotate_ip(const double &angle)
    {
        double back_up_x = this->x;
        this->x = this->x * cos(angle) + this->y * sin(angle);
        this->y = -back_up_x * sin(angle) + this->y * cos(angle);
    }

    /**
     * @brief Rotates the vector by a given angle.
     * @param angle The angle (in radians) by which to rotate the vector.
     * @return The rotated vector.
     */
    Vector2D rotate(const double angle)
    {
        return Vector2D(x * cos(angle) + y * sin(angle), -x * sin(angle) + y * cos(angle));
    }
};
