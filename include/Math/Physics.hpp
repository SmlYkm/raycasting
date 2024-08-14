#pragma once

#include "Math/Vector2D.hpp"
#include "Game/Map.hpp"

#include <SDL2/SDL.h>

namespace Math
{
    class Physics
    {
    private:
        static Uint32 deltaTime;    // Time between frames
        static Uint32 previousTime;    // Used to calculate the time between frames
        static Uint32 currentTime;

        // Prevents instantiation
        Physics() = delete;
        Physics(const Physics&) = delete;
        Physics& operator=(const Physics&) = delete;
    
    public:
        static bool checkCollision(float x, float y, Game::Map* map, float radius);

        static void updatePosition(Math::Vector2D<float>& position, float velocity, float angle, Game::Map* map, float rad = 0.0f);
        static void updateAngle(float& angle, float angularVelocity);
    
        static const Uint32 updateDeltaTime();
    };
}