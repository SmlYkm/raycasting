#include "Game/Player.hpp"
#include "Math/Physics.hpp"

#include <SFML/Graphics.hpp>

namespace Game
{
    Player::Player(Math::Vector2f pos, Game::Map* mp, float rad, float ang, float vel, float angVel)
        : position(pos), map(mp), radius(rad), angle(ang), velocity(vel), angularVelocity(angVel)
    {}

    Player::~Player()
    {}

    const Math::Vector2f& Player::getPosition() const
    {
        return position;
    }

    void Player::setPosition(const Math::Vector2f& pos)
    {
        position = pos;
    }

    void Player::normalizeAngle()
    {
        angle.normalize();
    }

    Math::Angle Player::getAngle() const
    {
        return angle;
    }

    void Player::setAngle(float ang)
    {
        angle = ang;
    }

    // TODO: add strafing (or not)
    void Player::handleInput()    // Keyboard input
    {
        // Since more than one key can be pressed at the same time,
        // we need to check each key separately
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            Math::Physics::updatePosition(position, velocity, angle, map, radius);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            Math::Physics::updatePosition(position, -velocity, angle, map, radius);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Math::Physics::updateAngle(angle, -angularVelocity);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Math::Physics::updateAngle(angle, angularVelocity);
    }
}