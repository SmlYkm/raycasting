#pragma once

#include "Game/Player.hpp"
#include "Game/Map.hpp"

namespace Rendering
{
    class Raycaster
    {
    private:
        Raycaster() = delete;    // Prevents instantiation

        static Math::Vector2D<float> prolongRay(Math::Vector2D<float> currentPos, Math::Vector2D<float> delta, Game::Map* map);    // Prolongs ray till it hits a wall
 
    public:
        static Math::Vector2D<float> castHorizontally(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map);
        static Math::Vector2D<float> castVertically(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map);
    };
}