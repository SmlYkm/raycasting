#include "Math/Physics.hpp"
#include "Math/Constants.hpp"

#include <iostream>

namespace Math
{
    Uint32 Physics::deltaTime = 0; 

    Uint32 Physics::previousTime = 0;

    Uint32 Physics::currentTime = 0;

    bool Physics::checkCollision(float x, float y, Game::Map* map, float radius)
    {
        return ((map->isWall((int)(x + radius), (int)(y + radius))) ||
                (map->isWall((int)(x - radius), (int)(y + radius))) ||
                (map->isWall((int)(x + radius), (int)(y - radius))) ||
                (map->isWall((int)(x - radius), (int)(y - radius))));
    }

    // Updates the player position and checks for wall collisions
    void Physics::updatePosition(Math::Vector2D<float>& position, float velocity, float angle, Game::Map* map, float radius)
    {
        float yPos = std::sin(angle) * velocity * (float)deltaTime + position.getY();
        float xPos = std::cos(angle) * velocity * (float)deltaTime + position.getX();

        if(!checkCollision(xPos, position.getY(), map, radius)) 
            position.setX(xPos);
        else if(xPos > position.getX())    
            position.setX(ceil(position.getX()) - radius - FLOAT_EPSILON);
        else    
            position.setX(floor(position.getX()) + radius + FLOAT_EPSILON);
        
        if(!checkCollision(position.getX(), yPos, map, radius))    
            position.setY(yPos);
        else if(yPos > position.getY())   
            position.setY(ceil(position.getY()) - radius - FLOAT_EPSILON);
        else  
            position.setY(floor(position.getY()) + radius + FLOAT_EPSILON);
    }

    // Updates the player view angle
    void Physics::updateAngle(float& angle, float angularVelocity) 
    {
        angle += angularVelocity * (float)deltaTime;
    }

    // Updates elapsed time between frames
    const Uint32 Physics::updateDeltaTime()
    {      
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime);
        previousTime = currentTime;

        return deltaTime;
    }
}