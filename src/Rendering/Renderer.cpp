#include "Rendering/Renderer.hpp"
#include "Rendering/Raycaster.hpp"

#include <iostream>

namespace Rendering
{
    Renderer::Renderer()
        : map(nullptr), screenWidth(0), screenHeight(0), fov(0.0f), nRays(0), cameraPlaneLen(0.0f)
    {}

    Renderer::~Renderer()
    {}


    // Draws a column of pixels
    void Renderer::drawPixelColumn(float x, float dist, sf::Color color)
    {
        float height = ((float)screenHeight) / dist;
        sf::RectangleShape rect(sf::Vector2f(screenWidth/nRays, height));
        rect.setFillColor(color);
        rect.setPosition(sf::Vector2f(x, (screenHeight - height) / 2));
        window.draw(rect);
    }

    // Draws columns of pixels taking into account the distance of the wall
    void Renderer::render3d()
    {
        player->normalizeAngle();

        Math::Vector2D<float> playerDir = Math::Vector2D<float>(std::cos(player->getAngle()), std::sin(player->getAngle()));
        Math::Vector2D<float> cameraPlane = playerDir.getOrthogonal() * cameraPlaneLen;
        Math::Vector2D<float> increment = cameraPlane * 2.0f / (nRays - 1);
        Math::Vector2D<float> cameraPoint = player->getPosition() + playerDir + cameraPlane;

        for(int i = 0; i < nRays; ++i, cameraPoint -= increment)
        {
            Math::Vector2D<float> verticalHit = Raycaster::castVertically(player->getPosition(), cameraPoint, map) - player->getPosition();
            Math::Vector2D<float> horizontalHit = Raycaster::castHorizontally(player->getPosition(), cameraPoint, map) - player->getPosition();
            Math::Vector2D<float> hit;

            bool vertical = false;

            if(verticalHit.lengthSquared() < horizontalHit.lengthSquared()) 
            {
                hit = verticalHit;
                vertical = true;
            }
            else
                hit = horizontalHit;

            float distance = hit * playerDir;
            sf::Color color(0, vertical ? 255 : 245, 0, 255 / (distance+1));            
            drawPixelColumn(i * screenWidth / nRays, distance, color);
        } 
    }

    Renderer& Renderer::getInstance()
    {
        static Renderer instance;
        return instance;
    }

    void Renderer::init(Game::Map* mp, Game::Player* pl, int width, int height, const char* title, float fieldOfView, int raysN)
    {
        map = mp;
        player = pl;
        screenWidth = width;
        screenHeight = height;
        fov = fieldOfView;
        nRays = raysN;
        cameraPlaneLen = std::tan(fieldOfView / 2.0f);

        window.create(sf::VideoMode(screenWidth, screenHeight), title);
        window.setFramerateLimit(60);
    }

    void Renderer::render()
    {
        window.clear();


        // debug();
        /* 3D CODE */
        render3d();
        
        /* TOPVIEW CODE */
        // renderTopView();
        // castRaysTopView();
        // renderPlayerBall();

        window.display();
    }

    void Renderer::pollEvent()
    {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();
        
        player->handleInput();
    }

    bool Renderer::isOpen() const
    {
        return window.isOpen();
    }

    void Renderer::setFPSlimit(unsigned int fps)
    {
        window.setFramerateLimit(fps);
    }
}