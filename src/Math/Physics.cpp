#include "Math/Physics.hpp"
#include "Math/Constants.hpp"

namespace Math
{
    float Physics::deltaTime = 0.0f; // Definition and initialization of the static variable

    sf::Clock Physics::clock;    // Definition of the static variable

    void Physics::updatePosition(Math::Vector2f& position, float velocity, Angle angle)
    {
        position += Math::Vector2f( std::cos(angle.get()), std::sin(angle.get()) ) * velocity * deltaTime;
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