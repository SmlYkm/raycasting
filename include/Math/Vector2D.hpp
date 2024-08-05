#pragma once

#include <cmath>
#include <iostream>
#include <ostream>

namespace Math
{
    template <class T>

    // Template class for two-dimensional vectors
    class Vector2D
    {
    private:
        // X and Y components of the two-dimensional vector.
        // Making them public would make the code easier to 
        // work with, more readable and would also avoid 
        // overhead (I think), but since it's considered 
        // bad practice (for reasons I only accept and don't 
        // really understand), I'm keeping them private :)
        T x, y;
    
    public:
        // The constructor uses float values as default parameters
        Vector2D(T xx = 0.0f, T yy = 0.0f) 
            : x(xx), y(yy) 
        {}
        
        ~Vector2D() 
        {}

    // Methods

        const T getX() const 
        { 
            return x; 
        }
        const T getY() const
        {
            return y;
        }
        
        void setX(const T xx)
        {
            x = xx;
        }
        void setY(const T yy)
        {
            y = yy;
        }

        void set(const T xx, const T yy)
        {
            x = xx;
            y = yy;
        }

        void incX(const T xInc)
        {
            x += xInc;
        }
        void incY(const T yInc)
        {
            y += yInc;
        }

        void subX(const T xSub)
        {
            x -= xSub;
        }
        void subY(const T ySub)
        {
            y -= ySub;
        }

        void mulX(const T xMul)
        {
            x *= xMul;
        }
        void mulY(const T yMul)
        {
            y *= yMul;
        }

        void divX(const T xDiv)
        {
            x /= xDiv;
        }
        void divY(const T yDiv)
        {
            y /= yDiv;
        }

        const Vector2D<T> getOrthogonal() const
        {
            return Vector2D<T>(y, -x);
        }

        const T lengthSquared() const
        {
            return x*x + y*y;
        }

        const T length() const
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

        const Vector2D<T> operator+(const Vector2D<T>& other) const
        {
            return Vector2D<T>(x + other.x, y + other.y);
        }
        
        const Vector2D<T> operator-(const Vector2D<T>& other) const
        {
            return Vector2D<T>(x - other.x, y - other.y);
        }

        // Multiplication by scalar
        const Vector2D<T> operator*(T scalar) const             
        {
            return Vector2D<T>(x * scalar, y * scalar);
        }

        // Dot product
        const T operator*(const Vector2D<T>& other) const
        {
            return x * other.x + y * other.y;
        }
        
        // Division by scalar
        const Vector2D<T> operator/(T scalar) const
        {
            return Vector2D<T>(x / scalar, y / scalar);
        }

    // Operators for compound assignment

        const Vector2D<T>& operator=(const Vector2D<T>& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        const Vector2D<T>& operator+=(const Vector2D<T>& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        const Vector2D<T>& operator-=(const Vector2D<T>& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Multiplication by scalar
        const Vector2D<T>& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // Division by scalar
        const Vector2D<T>& operator/=(T scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        const bool operator==(const Vector2D<T>& other) const
        {
            return x == other.x && y == other.y;
        }

        const bool operator!=(const Vector2D<T>& other) const
        {
            return x != other.x || y != other.y;
        }
    };

    template <class T>
    
    const Vector2D<T> operator*(T scalar, const Vector2D<T>& vec) 
    {
        return vec * scalar;
    }

    template <class T>
    
    std::ostream& operator<<(std::ostream& os, const Vector2D<T>& vec) 
    {
        os << "(" << vec.getX() << ", " << vec.getY() << ")";
        return os;
    }
}