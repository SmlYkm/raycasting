#include "Rendering/Raycaster.hpp"
#include "Math/Constants.hpp"

namespace Rendering {
    bool Raycaster::hitIsVertical(false);

    const bool Raycaster::hitWasVertical() { return hitIsVertical; }

    Math::Vector2D<float> Raycaster::castRay(const Math::Vector2D<float>& castingPos,const Math::Vector2D<float>& cameraPoint, Game::Map* map) {
        float slope = (cameraPoint.getY() - castingPos.getY()) / ((cameraPoint.getX() - castingPos.getX()));   

        //
        // Vertical Axis
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
        // Horizontal Axis
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
}