#pragma once

#include "Math/Vector2D.hpp"

#include "Game/Map.hpp"

namespace Game
{
    class Player
    {
    private:
        Math::Vector2D<float> position;
        float angle;    // Angle in radians
        
        // Player has no acceleration
        float velocity;
        float angularVelocity;

        float radius;    // Used for collision detection

        Game::Map* map;
    
    public:
        Player(Math::Vector2D<float> pos = Math::Vector2D<float>(0.0f, 0.0f),
               Game::Map* mp = nullptr, 
               float radius = 0.25f,
               float ang = 0.0f, 
               float vel = 0.0f, 
               float angVel = 0.0f);
        ~Player();

        const Math::Vector2D<float>& getPosition() const;
        void setPosition(const Math::Vector2D<float>& pos);
        void normalizeAngle();
        const float getAngle() const;
        void setAngle(const float ang);

        void handleInput();    // Keyboard input
    };
}