#include "Draw/Raycaster.hpp"
#include "Math/Constants.hpp"

namespace Rendering
{
    // Prolongs ray till it hits a wall or goes outside of the map
    Math::Vector2D<float> Raycaster::prolongRay(Math::Vector2D<float> currentPos, Math::Vector2D<float> delta, Game::Map* map)    
    {
        // If the current position isn't a wall and isn't outside of the boudaries of the map
        while(map->positionIsValid((int)currentPos.getX(), (int)currentPos.getY()) 
              && !map->isWall((int)currentPos.getX(), (int)currentPos.getY()))
            currentPos += delta;
        return currentPos;
    }

    // Casts the ray snapping it horizontally(the name might be inverted)
    // to the next grid till it hits a wall and returns the position of the hit,
    Math::Vector2D<float> Raycaster::castHorizontally(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map)
    {
        // Variables used to calculate the first iteration of the algorithm
        float x = floor(castingPos.getX()), y;
        float deltaY, deltaX;    // Increment values
        float angularCoef = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));

        if(cameraPoint.getX() > castingPos.getX())    // If looking right
        {
            ++x;
            deltaX = 1.0f;
        }
        else    // If looking left
        {
            x -= FLOAT_EPSILON;
            deltaX = -1.0f;
        }

        // Line equation used to find the y position in the first iteration
        y = (x - castingPos.getX())*angularCoef + castingPos.getY();
        deltaY = deltaX * angularCoef;

        return prolongRay(Math::Vector2D<float>(x, y), Math::Vector2D<float>(deltaX, deltaY), map);
    }

    // Casts the ray snapping it vertically(the name might be inverted)
    // to the next grid till it hits a wall and returns the position of the hit,
    Math::Vector2D<float> Raycaster::castVertically(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map)
    {
        // Variables used to calculate the first iteration of the algorithm
        float y = floor(castingPos.getY()), x;
        float deltaY, deltaX;    // Increment values
        float angularCoef = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));

        if(cameraPoint.getY() > castingPos.getY())    // If looking up
        {
            ++y;
            deltaY = 1.0f;
        }
        else    // If looking down
        {
            y -= FLOAT_EPSILON;
            deltaY = -1.0f;
        }

        // Line equation used to find the x position in the first iteration
        x = (y - castingPos.getY()) / angularCoef + castingPos.getX();    // this line and the following could be passed as function pointers,
        deltaX = deltaY / angularCoef;                                    // so I could use the same function to cast horizontally and vertically

        // Increments x and y values by the delta values till the ray hits a wall
        return prolongRay(Math::Vector2D<float>(x, y), Math::Vector2D<float>(deltaX, deltaY), map);
    }
}