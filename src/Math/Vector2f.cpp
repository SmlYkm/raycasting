#include "Math/Vector2f.hpp"
#include "Math/Constants.hpp"

#include <stdexcept>

namespace Math
{
// constructors and destructors
    Vector2f::Vector2f(float i, float j)
        : x(i), y(j) // i and j as unit vectors in x and y coordinates respectively
    {}
    
    Vector2f::Vector2f(const Vector2f& other)
        : x(other.x), y(other.y)
    {}

    Vector2f::~Vector2f()
    {}

// setters and getters
    float Vector2f::getX() const
    {
        return x;
    }

    float Vector2f::getY() const
    {
        return y;
    }

    void Vector2f::setX(float i)
    {
        x = i;
    }

    void Vector2f::setY(float j)
    {
        y = j;
    }

    void Vector2f::set(float i, float j)
    {
        x = i;
        y = j;
    }

    void Vector2f::set(const Vector2f& other)
    {
        x = other.x;
        y = other.y;
    }

    Vector2f Vector2f::getOrthogonal() const
    {
        return Vector2f(-y, x);
    }

// methods
    float Vector2f::lengthSquared() const
    {
        return x * x + y * y;
    }

    float Vector2f::length() const
    {
        return std::sqrt(lengthSquared());
    }

    float Vector2f::distanceSquared(const Vector2f& other) const
    {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }

    float Vector2f::distance(const Vector2f& other) const
    {
        return std::sqrt(distanceSquared(other));
    }

    void Vector2f::normalize()
    {
        float len = length();
        if (len > FLOAT_EPSILON)
        {
            x /= len;
            y /= len;
        }
        else
            throw std::invalid_argument("Division by zero");

    }

// operators
    Vector2f Vector2f::operator+(const Vector2f& other) const
    {
        return Vector2f(x + other.x, y + other.y);
    }

    Vector2f Vector2f::operator-(const Vector2f& other) const
    {
        return Vector2f(x - other.x, y - other.y);
    }

    Vector2f Vector2f::operator*(float scalar) const    // multiply by scalar
    {
        return Vector2f(x * scalar, y * scalar);
    }

    float Vector2f::operator*(const Vector2f& other) const    // dot product
    {
        return x * other.x + y * other.y;
    }

    Vector2f Vector2f::operator/(float scalar) const    // divide by scalar
    {
        if(std::abs(scalar) < FLOAT_EPSILON)
            throw std::invalid_argument("Division by zero");
        return Vector2f(x / scalar, y / scalar);
    }

    Vector2f& Vector2f::operator=(const Vector2f& other) 
    {
        if(this != &other) 
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Vector2f& Vector2f::operator+=(const Vector2f& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2f& Vector2f::operator-=(const Vector2f& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2f& Vector2f::operator*=(float scalar)    // multiply by scalar
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2f& Vector2f::operator/=(float scalar)
    {
        if(std::abs(scalar) < FLOAT_EPSILON)
            throw std::invalid_argument("Division by zero");
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool Vector2f::operator==(const Vector2f& other) const
    {
        return std::abs(x - other.x) < FLOAT_EPSILON && std::abs(y - other.y) < FLOAT_EPSILON;
    }

    bool Vector2f::operator!=(const Vector2f& other) const
    {
        return !(*this == other);
    }
}