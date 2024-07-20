#pragma once

namespace Math
{
    class Vector2f
    {
    private:
    // Attributes
        float x;
        float y;
    
    public:
    // Constructors
        Vector2f(float i = 0.0f, float j = 0.0f);
        Vector2f(const Vector2f& other);

    // Destructor
        ~Vector2f();

    // Methods
        float getX() const;
        float getY() const;
        void setX(float i);
        void setY(float j);
        void set(float i, float j);
        void set(const Vector2f& other);

        Vector2f getOrthogonal() const;
        float lengthSquared() const;
        float length() const;
        float distanceSquared(const Vector2f& other) const;
        float distance(const Vector2f& other) const;
        void normalize();
        
        Vector2f operator+(const Vector2f& other) const;
        Vector2f operator-(const Vector2f& other) const;
        Vector2f operator*(float scalar) const;             // multiply by scalar
        float operator*(const Vector2f& other) const;    // dot product
        Vector2f operator/(float scalar) const;
        Vector2f& operator=(const Vector2f& other);
        Vector2f& operator+=(const Vector2f& other);
        Vector2f& operator-=(const Vector2f& other);
        Vector2f& operator*=(float scalar);                 // multiply by scalar
        Vector2f& operator/=(float scalar);                 // divide by scalar
        bool operator==(const Vector2f& other) const;
        bool operator!=(const Vector2f& other) const;
    };
}