#include "Rendering/Raycaster.hpp"
#include "Math/Constants.hpp"

namespace Rendering
{
    // Prolongs ray till it hits a wall or goes outside of the map
    Math::Vector2f Raycaster::prolongRay(Math::Vector2f currentPos, Math::Vector2f delta, Game::Map* map)    
    {
        // If the current position isn't a wall and isn't outside of the boudaries of the map
        while(map->positionIsValid((int)currentPos.getX(), (int)currentPos.getY()) 
           && !map->isWall((int)currentPos.getX(), (int)currentPos.getY()))
            currentPos += delta;
        return currentPos;
    }

    // Casts the ray snapping it horizontally(the name might be inverted)
    // to the next grid till it hits a wall and returns the position of the hit,
    Math::Vector2f Raycaster::castHorizontally(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        // Variables used to calculate the first iteration of the algorithm
        float x = floor(castingPos.getX()), y;
        float deltaY, deltaX;    // Increment values
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

        // Line equation used to find the y position in the first iteration
        y = (x - castingPos.getX())*angularCoef + castingPos.getY();
        deltaY = deltaX * angularCoef;

        return prolongRay(Math::Vector2f(x, y), Math::Vector2f(deltaX, deltaY), map);
    }

    // Casts the ray snapping it vertically(the name might be inverted)
    // to the next grid till it hits a wall and returns the position of the hit,
    Math::Vector2f Raycaster::castVertically(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        // Variables used to calculate the first iteration of the algorithm
        float y = floor(castingPos.getY()), x;
        float angularCoef = tan(angle.get());
        float deltaY, deltaX;    // Increment values

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

        // Line equation used to find the x position in the first iteration
        x = (y - castingPos.getY()) / angularCoef + castingPos.getX();
        deltaX = deltaY / angularCoef;

        // Increments x and y values by the delta values till the ray hits a wall
        return prolongRay(Math::Vector2f(x, y), Math::Vector2f(deltaX, deltaY), map);
    }

    // Returns distance from the casting position to the wall
    float Raycaster::castedRayDist(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        Math::Vector2f verticalHit = castVertically(castingPos, angle, map) - castingPos;
        Math::Vector2f horizontalHit = castHorizontally(castingPos, angle, map) - castingPos;

        float verticalDist = verticalHit.lengthSquared();
        float horizontalDist = horizontalHit.lengthSquared();

        // Returns the smallest distance, which is the actual distance to the wall
        float dist = (verticalDist < horizontalDist) ? verticalDist : horizontalDist;

        return sqrt(dist);
    }

    // Casts the ray and returns the vector from the player position to the hit point
    Math::Vector2f Raycaster::castedRayVec(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        Math::Vector2f verticalHit = castVertically(castingPos, angle, map) - castingPos;
        Math::Vector2f horizontalHit = castHorizontally(castingPos, angle, map) - castingPos;

        // Returns the smallest vector, which is the one that is snapped to the wall
        return (verticalHit.lengthSquared() < horizontalHit.lengthSquared()) ? verticalHit : horizontalHit;
    }

    // Returns the coordinates of the hit point of the ray (NOT the vector from the player position to the hit point)
    Math::Vector2f Raycaster::castedRayHitPoint(Math::Vector2f castingPos, Math::Angle angle, Game::Map* map)
    {
        return castedRayVec(castingPos, angle, map) + castingPos;
    }
}