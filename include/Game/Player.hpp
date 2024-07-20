#pragma once

#include "Math/Vector2f.hpp"
#include "Math/Angle.hpp"

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
    
    public:
        Player(Math::Vector2f pos = Math::Vector2f(0.0f, 0.0f), 
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