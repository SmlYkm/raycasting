#pragma once

#include "Math/Vector2f.hpp"
#include "Math/Angle.hpp"

#include <SFML/System/Clock.hpp>

namespace Math
{
    class Physics
    {
    private:
        static float deltaTime;    // Time between frames
        static sf::Clock clock;    // Used to calculate the time between frames

    public:
        Physics() = delete;    // Prevents instantiation

        static void updatePosition(Math::Vector2f& position, float velocity, Angle angle);
        static void updateAngle(Angle& angle, float angularVelocity);
    
        static void updateDeltaTime();
    };
}