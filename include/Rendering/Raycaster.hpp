#pragma once

#include "Game/Player.hpp"
#include "Game/Map.hpp"

namespace Rendering {
    // Utility class for raycasting functions
    class Raycaster {
    private:
        static bool hitIsVertical;

    private:
        // Prevents instantiation
        Raycaster() = delete;    
        Raycaster(const Raycaster&) = delete;
        Raycaster(Raycaster&&) = delete;
        Raycaster& operator=(const Raycaster&) = delete;
        Raycaster& operator=(const Raycaster&&) = delete;

    public:
        static const bool hitWasVertical();
        static Math::Vector2D<float> castRay(const Math::Vector2D<float>& castingPos, const Math::Vector2D<float>& cameraPoint, Game::Map* map);
    };
}