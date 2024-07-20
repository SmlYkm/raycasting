#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Game/Map.hpp"
#include "Game/Player.hpp"

// Used to render topview
#define CELL_SEPARATOR_THICKNESS 1    // Thickness of the grid separator lines

#define FOV M_PI / 3.0f    // Field of view in radians
#define N_RAYS 100    // Number of rays casted from the player

//Singleton
namespace Rendering
{
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
    
    private:
        Renderer();

        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(const Renderer&&) = delete;

        ~Renderer();

    // Debugging and auxiliary methods
        sf::Vector2f mathToSFML(const Math::Vector2f& vec) const;
        sf::Vector2f gridToWindow(const Math::Vector2f& vec) const;
        void drawLine(sf::Vector2f initialPos, sf::Vector2f endingPos, sf::Color color);
        void renderTopView();
        void renderPlayerBall();    // Draws a ball in the player's position
        void castRaysTopView();    // Draws rays from the player's position
        
    // Raycasting methods
        void drawPixelColumn(int x, float dist/*, sf::Color color*/);
        void render3d();    // Renders the 3D view

    public:
        static Renderer& getInstance();
        void init(Game::Map* mp, Game::Player* pl, int width, int height, const char* title);
        void render();
        void pollEvent();
        bool isOpen() const;
    };
}