#pragma once

#include "Game/Player.hpp"
#include "Game/Map.hpp"

namespace Rendering {
    // Utility class for raycasting functions
    class Raycaster {
    private:
        static bool hitIsVertical;    // True if the hit is vertical and false if not

    private:
        // Prevents instantiation
        Raycaster() = delete;    
        Raycaster(const Raycaster&) = delete;
        Raycaster(Raycaster&&) = delete;
        Raycaster& operator=(const Raycaster&) = delete;
        Raycaster& operator=(const Raycaster&&) = delete;

        static Math::Vector2D<float> prolongRay(Math::Vector2D<float> currentPos, Math::Vector2D<float> delta, Game::Map* map);    // Prolongs ray till it hits a wall
 
    public:
        static Math::Vector2D<float> castHorizontally(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map);
        static Math::Vector2D<float> castVertically(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map);
        static Math::Vector2D<float> castRay(const Math::Vector2D<float>& castingPos, const Math::Vector2D<float>& cameraPoint, Game::Map* map);
    
        static const bool hitWasVertical();
    };
}