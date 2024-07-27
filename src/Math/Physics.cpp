#include "Math/Physics.hpp"
#include "Math/Constants.hpp"

namespace Math
{
    float Physics::deltaTime = 0.0f; // Definition and initialization of the static variable

    sf::Clock Physics::clock;    // Definition of the static variable

    void Physics::updatePosition(Math::Vector2f& position, float velocity, Angle angle, Game::Map* map)
    {
        Math::Vector2f lastPosition = position;
        position += Math::Vector2f( std::cos(angle.get()), std::sin(angle.get()) ) * velocity * deltaTime;
        if(!map->positionIsValid((int)position.getX(), (int)position.getY()))
            position = lastPosition;
        else if(map->isWall((int)position.getX(), (int)position.getY()))
        {
            if(!map->isWall((int)lastPosition.getX(), (int)position.getY()))
                position.setX(lastPosition.getX());
            else if(!map->isWall((int)position.getX(), (int)lastPosition.getY()))
                position.setY(lastPosition.getY());
            else 
                position = lastPosition;
        }
    }

    void Physics::updateAngle(Angle& angle, float angularVelocity)
    {
        angle += angularVelocity * deltaTime;
    }

    void Physics::updateDeltaTime()
    {
        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();
    }
}