#include "Math/Physics.hpp"
#include "Math/Constants.hpp"

#include <iostream>

namespace Math
{
    float Physics::deltaTime = 0.0f; // Definition and initialization of the static variable

    sf::Clock Physics::clock;    // Definition of the static variable

    // Handles wall collisions
    void Physics::wallCollisionHandling(Math::Vector2f& position, Game::Map* map, float radius)
    {
        if(map->isWall((int)(position.getX() + radius), (int)position.getY()))    // New x position is not valid
            position.setX(ceil(position.getX()) - radius);

        else if(map->isWall((int)(position.getX() - radius), (int)position.getY()))    // New x position is not valid
            position.setX(floor(position.getX()) + radius);

        if(map->isWall((int)position.getX(), (int)(position.getY() + radius)))    // New y position is not valid
            position.setY(ceil(position.getY()) - radius);

        else if(map->isWall((int)position.getX(), (int)(position.getY() - radius)))    // New y position is not valid
            position.setY(floor(position.getY()) + radius);
    }

    // Updates the player position and checks for wall collisions
    void Physics::updatePosition(Math::Vector2f& position, float velocity, Angle angle, Game::Map* map, float radius)
    {
        Math::Vector2f lastPosition = position;

        position += Math::Vector2f( std::cos(angle.get()), std::sin(angle.get()) ) * velocity * deltaTime;

        // Checks if the new position is within the boundaries of the map
        if(!map->positionIsValid((int)position.getX(), (int)position.getY()))
        {
            position = lastPosition;
            return;
        }

        wallCollisionHandling(position, map, radius);
    }

    // Updates the player view angle
    void Physics::updateAngle(Angle& angle, float angularVelocity)
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