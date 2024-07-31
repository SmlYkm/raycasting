#pragma once

#include <cmath>

namespace Math
{
    template <class T>

    // Template class for two-dimensional vectors
    class Vector2D
    {
    private:
        // X and Y components of the two-dimensional vector
        T x, y;
    
    public:
        // The constructor uses float values as default parameters
        Vector2D(T xx = 0.0f, T yy = 0.0f) 
            : x(xx), y(yy) 
        {}
        
        ~Vector2D() 
        {}

    // Methods

        T getX() const 
        { 
            return x; 
        }
        T getY() const
        {
            return y;
        }
        
        void setX(T xx)
        {
            x = xx;
        }
        void setY(T yy)
        {
            y = yy;
        }

        void set(T xx, T yy)
        {
            x = xx;
            y = yy;
        }

        Vector2D<T> getOrthogonal() const
        {
            return Vector2D<T>(y, -x);
        }

        T lengthSquared() const
        {
            return x*x + y*y;
        }

        T length() const
        {
            return sqrt(x*x + y*y);
        }

        void normalize()
        {
            T len = length();
            x /= len;
            y /= len;
        }
    
    // Operators for basic arithmetic

        Vector2D<T> operator+(const Vector2D<T>& other) const
        {
            return Vector2D<T>(x + other.x, y + other.y);
        }
        
        Vector2D<T> operator-(const Vector2D<T>& other) const
        {
            return Vector2D<T>(x - other.x, y - other.y);
        }

        // Multiplication by scalar
        Vector2D<T> operator*(T scalar) const             
        {
            return Vector2D<T>(x * scalar, y * scalar);
        }

        // Dot product
        T operator*(const Vector2D<T>& other) const
        {
            return x * other.x + y * other.y;
        }
        
        // Division by scalar
        Vector2D<T> operator/(T scalar) const
        {
            return Vector2D<T>(x / scalar, y / scalar);
        }

    // Operators for compound assignment

        Vector2D<T>& operator=(const Vector2D<T>& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        Vector2D<T>& operator+=(const Vector2D<T>& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2D<T>& operator-=(const Vector2D<T>& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Multiplication by scalar
        Vector2D<T>& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // Division by scalar
        Vector2D<T>& operator/=(T scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vector2D<T>& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2D<T>& other) const
        {
            return x != other.x || y != other.y;
        }
    };
}