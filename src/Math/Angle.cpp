#include "Math/Angle.hpp"
#include "Math/Constants.hpp"

namespace Math
{
    Angle::Angle(float ang) 
        : angle(ang) 
    { 
        normalize();
    }

    Angle::~Angle() 
    {}

    float Angle::get()
    {
        return angle;
    }

    void Angle::normalize()    // Returns the angle to the range [0, 2*PI)
    {
        while(angle < 0.0f)
            angle += TWO_PI;
        while(angle >= TWO_PI)
            angle -= TWO_PI;
    }

    bool Angle::lookingRight()
    {
        normalize();    // Normalize the angle to [0, 2*PI)
        return (angle > THREE_HALVES_PI || angle < HALF_PI);
    }

    bool Angle::lookingUp()
    {
        normalize();    // Normalize the angle to [0, 2*PI)
        return (angle < M_PI);
    }

// Operators for basic arithmetic
    Angle Angle::operator=(const Angle& other)
    {
        angle = other.angle;
        return *this;
    }

    Angle Angle::operator=(const float& other)
    {
        angle = other;
        return *this;
    }

    Angle Angle::operator+(const Angle& other) const
    {
        return Angle(angle + other.angle);
    }

    Angle Angle::operator+(const float& other) const
    {
        return Angle(angle + other);
    }

    Angle Angle::operator-(const Angle& other) const
    {
        return Angle(angle - other.angle);
    }

    Angle Angle::operator-(const float& other) const
    {
        return Angle(angle - other);
    }

    Angle Angle::operator*(const Angle& other) const
    {
        return Angle(angle * other.angle);
    }

    Angle Angle::operator*(const float& scalar) const
    {
        return Angle(angle * scalar);
    }

    Angle Angle::operator/(const Angle& other) const
    {
        return Angle(angle / other.angle);
    }

    Angle Angle::operator/(const float& scalar) const
    {
        return Angle(angle / scalar);
    }

// Operators for compound assignment
    Angle& Angle::operator+=(const Angle& other)
    {
        angle += other.angle;
        return *this;
    }

    Angle& Angle::operator+=(const float& other)
    {
        angle += other;
        return *this;
    }

    Angle& Angle::operator-=(const Angle& other)
    {
        angle -= other.angle;
        return *this;
    }

    Angle& Angle::operator-=(const float& other)
    {
        angle -= other;
        return *this;
    }

    Angle& Angle::operator*=(const Angle& other)
    {
        angle *= other.angle;
        return *this;
    }

    Angle& Angle::operator*=(const float& scalar)
    {
        angle *= scalar;
        return *this;
    }

    Angle& Angle::operator/=(const Angle& other)
    {
        angle /= other.angle;
        return *this;
    }

    Angle& Angle::operator/=(const float& scalar)
    {
        angle /= scalar;
        return *this;
    }

// Operators for comparison
    bool Angle::operator==(const Angle& other) const
    {
        return std::abs(angle - other.angle) < FLOAT_EPSILON;
    }

    bool Angle::operator==(const float& other) const
    {
        return std::abs(angle - other) < FLOAT_EPSILON;
    }

    bool Angle::operator!=(const Angle& other) const
    {
        return !(*this == other);
    }

    bool Angle::operator!=(const float& other) const
    {
        return !(*this == other);
    }

    bool Angle::operator<(const Angle& other) const
    {
        return angle < other.angle;
    }

    bool Angle::operator<(const float& other) const
    {
        return angle < other;
    }

    bool Angle::operator>(const Angle& other) const
    {
        return angle > other.angle;
    }

    bool Angle::operator>(const float& other) const
    {
        return angle > other;
    }

    bool Angle::operator<=(const Angle& other) const
    {
        return angle <= other.angle;
    }

    bool Angle::operator<=(const float& other) const
    {
        return angle <= other;
    }

    bool Angle::operator>=(const Angle& other) const
    {
        return angle >= other.angle;
    }

    bool Angle::operator>=(const float& other) const
    {
        return angle >= other;
    }
}