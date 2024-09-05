#include "Rendering/Raycaster.hpp"
#include "Math/Constants.hpp"

namespace Rendering {
    bool Raycaster::hitIsVertical(false);

    // Prolongs ray till it hits a wall or goes outside of the map
    Math::Vector2D<float> Raycaster::prolongRay(Math::Vector2D<float> currentPos, Math::Vector2D<float> delta, Game::Map* map) {
        while(!map->isWall((int)currentPos.getX(), (int)currentPos.getY()))
            currentPos += delta;
        return currentPos;
    }

    Math::Vector2D<float> Raycaster::castVertically(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map) {
        float x, y = floor(castingPos.getY());
        float deltaX, deltaY;
        float angularCoef = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));

        if(cameraPoint.getY() > castingPos.getY()) {    // Facing upward
            ++y;
            deltaY = 1.0f;
        } else {                                        // Facing downward
            y -= FLOAT_EPSILON;
            deltaY = -1.0f;
        }

        // Line equation used to find the x position in the first iteration
        x = (y - castingPos.getY()) / angularCoef + castingPos.getX();
        deltaX = deltaY / angularCoef;                                    

        return prolongRay(Math::Vector2D<float>(x, y), Math::Vector2D<float>(deltaX, deltaY), map);
    }

    Math::Vector2D<float> Raycaster::castHorizontally(Math::Vector2D<float> castingPos, Math::Vector2D<float> cameraPoint, Game::Map* map){
        float x = floor(castingPos.getX()), y;
        float deltaX, deltaY;
        float angularCoef = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));

        if(cameraPoint.getX() > castingPos.getX()) {    // Facing right
            ++x;
            deltaX = 1.0f;
        }
        else {                                          // Facing left
            x -= FLOAT_EPSILON;
            deltaX = -1.0f;
        }

        // Line equation used to find the y position in the first iteration
        y = (x - castingPos.getX())*angularCoef + castingPos.getY();
        deltaY = deltaX * angularCoef;

        return prolongRay(Math::Vector2D<float>(x, y), Math::Vector2D<float>(deltaX, deltaY), map);
    }

    Math::Vector2D<float> Raycaster::castRay(const Math::Vector2D<float>& castingPos,const Math::Vector2D<float>& cameraPoint, Game::Map* map) {
        float slope = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));   

        //
        // Vertical
        //

        float verticalX, verticalY = floor(castingPos.getY()) + 1.0f;
        float verticalDeltaX, verticalDeltaY = 1.0f;

        if(cameraPoint.getY() < castingPos.getY()) {    // Facing downward
            verticalY -= (FLOAT_EPSILON + 1.0f);
            verticalDeltaY = -1.0f;
        }

        // Line equation used to find the x position in the first iteration
        verticalX = (verticalY - castingPos.getY()) / slope + castingPos.getX();
        verticalDeltaX = verticalDeltaY / slope;

        //
        // Horizontal
        //

        float horizontalX = floor(castingPos.getX()) + 1.0f, horizontalY;
        float horizontalDeltaX = 1.0f, horizontalDeltaY;

        if(cameraPoint.getX() < castingPos.getX()) {    // Facing right
            horizontalX -= (FLOAT_EPSILON + 1.0f);
            horizontalDeltaX = -1.0f;
        }
    
        // Line equation used to find the y position in the first iteration
        horizontalY = (horizontalX - castingPos.getX())*slope + castingPos.getY();
        horizontalDeltaY = horizontalDeltaX * slope;

        //
        // DDA
        //

        Math::Vector2D<float> horizontalDelta(horizontalDeltaX, horizontalDeltaY);
        Math::Vector2D<float> verticalDelta(verticalDeltaX, verticalDeltaY);

        Math::Vector2D<float> verticalPos(verticalX, verticalY);
        Math::Vector2D<float> horizontalPos(horizontalX, horizontalY);

        Math::Vector2D<float> hitPos;
        
        do {
            if((horizontalPos-castingPos) < (verticalPos-castingPos)) {
                hitPos = horizontalPos;
                horizontalPos += horizontalDelta;
                hitIsVertical = false;
            } else {
                hitPos = verticalPos;
                verticalPos += verticalDelta;
                hitIsVertical = true;
            }
        } while(!map->isWall((int)hitPos.getX(), (int)hitPos.getY()));

        return hitPos;
    }

    const bool Raycaster::hitWasVertical() { return hitIsVertical; }
}