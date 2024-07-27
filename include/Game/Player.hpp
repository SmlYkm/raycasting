#pragma once

#include "Math/Vector2f.hpp"
#include "Math/Angle.hpp"

#include "Game/Map.hpp"

namespace Game
{
    class Player
    {
    private:
        Math::Vector2f position;
        Math::Angle angle;    // Angle in radians
        
        // Player has no acceleration
        float velocity;
        float angularVelocity;

        float radius;    // Used for collision detection

        Game::Map* map;
    
    public:
        Player(Math::Vector2f pos = Math::Vector2f(0.0f, 0.0f),
               Game::Map* mp = nullptr, 
               float radius = 0.25f,
               float ang = 0.0f, 
               float vel = 0.0f, 
               float angVel = 0.0f);
        ~Player();

        const Math::Vector2f& getPosition() const;
        void setPosition(const Math::Vector2f& pos);
        void normalizeAngle();
        Math::Angle getAngle() const;
        void setAngle(float ang);

        void handleInput();    // Keyboard input
    };
}