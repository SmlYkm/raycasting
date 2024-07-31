#include "Math/Physics.hpp"
#include "Math/Constants.hpp"

#include <iostream>

namespace Math
{
    float Physics::deltaTime = 0.0f; // Definition and initialization of the static variable

    sf::Clock Physics::clock;    // Definition of the static variable

    // Handles wall collisions
    bool Physics::checkCollision(float x, float y, Game::Map* map, float radius)
    {
        // isWall also checks boudaries, so buffer overflows don't occur
        return ((map->isWall((int)(x + radius), (int)(y + radius))) ||
                (map->isWall((int)(x - radius), (int)(y + radius))) ||
                (map->isWall((int)(x + radius), (int)(y - radius))) ||
                (map->isWall((int)(x - radius), (int)(y - radius))));
    }

    // Updates the player position and checks for wall collisions
    void Physics::updatePosition(Math::Vector2D<float>& position, float velocity, float angle, Game::Map* map, float radius)
    {
        float yPos = std::sin(angle) * velocity * deltaTime + position.getY();
        float xPos = std::cos(angle) * velocity * deltaTime + position.getX();

        if(!checkCollision(xPos, position.getY(), map, radius))    // If position is valid
            position.setX(xPos);
        // If not, place it in the last valid position
        else if(xPos > position.getX())    // If the player is moving right
            position.setX(ceil(position.getX()) - radius - FLOAT_EPSILON);
        else
            position.setX(floor(position.getX()) + radius + FLOAT_EPSILON);
        
        if(!checkCollision(position.getX(), yPos, map, radius))    // If position is valid
            position.setY(yPos);
        // If not, place it in the last valid position
        else if(yPos > position.getY())    // If the player is moving down
            position.setY(ceil(position.getY()) - radius - FLOAT_EPSILON);
        else
            position.setY(floor(position.getY()) + radius + FLOAT_EPSILON);
    }

    // Updates the player view angle
    void Physics::updateAngle(float& angle, float angularVelocity) 
    {
        angle += angularVelocity * deltaTime;
    }

    // Updates elapsed time between frames
    void Physics::updateDeltaTime()
    {
        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asMicroseconds();
    }
}