#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Game/Map.hpp"
#include "Game/Player.hpp"

namespace Rendering
{
    // Singleton class.
    // As defaut, the FPS is limited to 60 in the init function.
    class Renderer
    {
    private:
        sf::RenderWindow window;

        // Both map, and player are aggregations, thus,
        // they ARE NOT deleted together with Renderer
        Game::Map* map; 
        Game::Player* player; 
        
        // Screen dimensions.
        // Since the calculations envolving them are simple,
        // using a Math::Vector2f is not necessary.
        int screenWidth;
        int screenHeight;

        float fov;    // Field of view in radians
        int nRays;    // Number of rays casted from the player
        float cameraPlaneLen;    // Length of the camera plane
    
    private:
        Renderer();

        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(const Renderer&&) = delete;

        ~Renderer();
        
    // Raycasting methods
        void drawPixelColumn(float x, float dist, sf::Color color);
        void render3d();

    public:
        static Renderer& getInstance();
        void init(Game::Map* mp, Game::Player* pl, 
                  int width, int height, const char* title = " ", 
                  float fieldOfView = M_PI / 2.0f, int raysN = 100);
        void render();
        void pollEvent();
        bool isOpen() const;
        void setFPSlimit(unsigned int fps);
    };
}