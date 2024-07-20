#pragma once

namespace Math
{
    class Angle
    {
    private:
        float angle;    // Angle in radians
    
    public:
        Angle(float ang = 0.0f);
        ~Angle();

        float get();
        void normalize();    // Returns the angle to the range [0, 2*PI)
        bool lookingRight();
        bool lookingUp();

    // Operators for basic arithmetic
        Angle operator=(const Angle& other);
        Angle operator=(const float& other);

        Angle operator+(const Angle& other) const;
        Angle operator+(const float& other) const;
        
        Angle operator-(const Angle& other) const;
        Angle operator-(const float& other) const;

        Angle operator*(const Angle& other) const;
        Angle operator*(const float& scalar) const;

        Angle operator/(const Angle& other) const;
        Angle operator/(const float& scalar) const;
    
    // Operators for compound assignment
        Angle& operator+=(const Angle& other);
        Angle& operator+=(const float& other);
        
        Angle& operator-=(const Angle& other);
        Angle& operator-=(const float& other);

        Angle& operator*=(const Angle& other);
        Angle& operator*=(const float& scalar);

        Angle& operator/=(const Angle& other);
        Angle& operator/=(const float& scalar);

    // Operators for comparison
        bool operator==(const Angle& other) const;
        bool operator==(const float& other) const;

        bool operator!=(const Angle& other) const;
        bool operator!=(const float& other) const;

        bool operator<(const Angle& other) const;
        bool operator<(const float& other) const;

        bool operator>(const Angle& other) const;
        bool operator>(const float& other) const;

        bool operator<=(const Angle& other) const;
        bool operator<=(const float& other) const;

        bool operator>=(const Angle& other) const;
        bool operator>=(const float& other) const;
    };
}