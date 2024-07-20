#include "Rendering/Raycaster.hpp"
#include "Math/Constants.hpp"

namespace Rendering
{
    // TODO: make it iterative
    Math::Vector2f Raycaster::prolongRay(Math::Vector2f currentPos, Math::Vector2f& delta, Game::Map* map)    
    {
        // If the current position isn't a wall or is outside of the boudaries of the map
        // (isWall also checks boudaries), return the previous position,
        // which is the hit position of the ray
        if(!map->positionIsValid((int)currentPos.getX(), (int)currentPos.getY()) 
           || map->isWall((int)currentPos.getX(), (int)currentPos.getY()))
            return currentPos;
        return prolongRay(currentPos + delta, delta, map);
    }

    Math::Vector2f Raycaster::castHorizontally(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        float x = floor(castingPos.getX()), y;
        float deltaY, deltaX;
        float angularCoef = tan(angle.get());

        if(angle.lookingRight())
        {
            ++x;
            deltaX = 1.0f;
        }
        else
        {
            x -= FLOAT_EPSILON;
            deltaX = -1.0f;
        }

        y = (x - castingPos.getX())*angularCoef + castingPos.getY();
        deltaY = deltaX * angularCoef;

        Math::Vector2f delta(deltaX, deltaY);
        return prolongRay(Math::Vector2f(x, y), delta, map);
    }

    Math::Vector2f Raycaster::castVertically(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        float y = floor(castingPos.getY()), x;
        float angularCoef = tan(angle.get());
        float deltaY, deltaX;

        if(angle.lookingUp())
        {
            ++y;
            deltaY = 1.0f;
        }
        else
        {
            y -= FLOAT_EPSILON;
            deltaY = -1.0f;
        }

        x = (y - castingPos.getY()) / angularCoef + castingPos.getX();    // Line equation used to find the x position
        deltaX = deltaY / angularCoef;

        Math::Vector2f delta(deltaX, deltaY);
        return prolongRay(Math::Vector2f(x, y), delta, map);
    }

    float Raycaster::castedRayDist(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        Math::Vector2f verticalHit = castVertically(castingPos, angle, map) - castingPos;
        Math::Vector2f horizontalHit = castHorizontally(castingPos, angle, map) - castingPos;

        float verticalDist = verticalHit.lengthSquared();
        float horizontalDist = horizontalHit.lengthSquared();

        float dist = (verticalDist < horizontalDist) ? verticalDist : horizontalDist;

        return sqrt(dist);
    }

    Math::Vector2f Raycaster::castRay(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        Math::Vector2f verticalHit = castVertically(castingPos, angle, map) - castingPos;
        Math::Vector2f horizontalHit = castHorizontally(castingPos, angle, map) - castingPos;

        return (verticalHit.lengthSquared() < horizontalHit.lengthSquared()) ? verticalHit : horizontalHit;
    }

    Math::Vector2f Raycaster::castedRayHitPoint(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        return castRay(castingPos, angle, map) + castingPos;
    }
}