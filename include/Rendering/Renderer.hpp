#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cmath>
#include <vector>

#include "Game/Map.hpp"
#include "Game/Player.hpp"

namespace Rendering {
    // As defaut, the FPS is limited to 60 in the init function.
    class Renderer {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        Game::Map* map; 
        Game::Player* player; 
        
        int screenWidth;
        int screenHeight;

        float pixelColumnWidth;

        Uint32 fps;
        Uint32 frameDelay;

        float fov;    // Field of view in radians
        int nRays;    // Number of rays casted from the player
        float cameraPlaneLen;

        bool running;

    private:
        Renderer();

        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(const Renderer&&) = delete;

        ~Renderer();
        
    // Raycasting related methods
        void drawPixelColumn(float x, float dist);
        void drawSpriteColumn(float x, float dist, int srcX);
        void drawSpriteColumnBatch(const std::vector<SDL_FRect>& destRects, const std::vector<int>& srcXs, float dist);
        void render3d();

    public:
        static Renderer& getInstance();
        void setMap(Game::Map* mp);
        void setPlayer(Game::Player* pl);
        void setFPSlimit(int limit = 60);
        void initWindow(const int width, const int height, 
                        const char* title = " ", 
                        const float fieldOfView = (float)M_PI/2.0f, 
                        const int raysN = 100);

        void render();
        void pollEvent();
        const bool isRunning() const;
    };
}