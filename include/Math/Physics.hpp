#pragma once

#include "Math/Vector2D.hpp"
#include "Game/Map.hpp"

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

        static bool checkCollision(float x, float y, Game::Map* map, float radius);

        static void updatePosition(Math::Vector2D<float>& position, float velocity, float angle, Game::Map* map, float rad = 0.0f);
        static void updateAngle(float& angle, float angularVelocity);
    
        static void updateDeltaTime();
    };
}