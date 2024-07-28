#pragma once

#include "Game/Player.hpp"
#include "Game/Map.hpp"

namespace Rendering
{
    class Raycaster
    {
    private:
        Raycaster() = delete;    // Prevents instantiation

        static Math::Vector2f prolongRay(Math::Vector2f currentPos, Math::Vector2f delta, Game::Map* map);    // Prolongs ray till it hits a wall
        static Math::Vector2f castHorizontally(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map);
        static Math::Vector2f castVertically(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map);
 
        static Math::Vector2f snapRayToWall(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map);    // Prolongs ray to the next grid (fist iteration of the algorithm)

    public:
        static Math::Vector2f castedRayVec(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map);
        static float castedRayDist(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map);
        static Math::Vector2f castedRayHitPoint(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map);
    };
}