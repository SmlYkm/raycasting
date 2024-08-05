#include "Draw/Renderer.hpp"
#include "Draw/Raycaster.hpp"

#include <iostream>
#include <cmath>

#define SPRITE_PATH "../assets/wall.png"

namespace Rendering
{
    Renderer::Renderer()
        : map(nullptr), 
          texture(),
          screenWidth(0), screenHeight(0), 
          fov(0.0f), 
          nRays(0), 
          cameraPlaneLen(0.0f)
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

    // src and dest as src and dest rectangles. Since the y and height values are 
    // calculated here, only the src x and src widht are passed as parameters
    void Renderer::drawSpriteColumn(float x, float dist, int srcX, sf::Color& color, Math::Vector2D<float>& hit)
    {
        // Calculate the height of the sprite column on the screen
        float destHeight = ((float)screenHeight) / dist;

        float destWidth = screenWidth / nRays;

        sf::Sprite sprite(texture);
        
        sf::IntRect textureRect(srcX, 0, 1, texture.getSize().y);
        sprite.setTextureRect(textureRect);
        sprite.setScale(destWidth , destHeight / texture.getSize().y);
        sprite.setPosition(x, (screenHeight - destHeight) / 2);

        sprite.setColor(color);

        window.draw(sprite);
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
            float srcX = 0.0f;

            if(verticalHit.lengthSquared() < horizontalHit.lengthSquared()) 
            {
                hit = verticalHit;
                vertical = true;
            }
            else
            {
                hit = horizontalHit;
            }
            float distance = hit * playerDir;

            hit += player->getPosition();
                        
            if(vertical)
            {
                sf::Color color(255, 255, 255, (distance < 1) ? 175 : 175 / distance);
                srcX = (hit.getX() - floor(hit.getX())) * texture.getSize().x;
                drawSpriteColumn(i * screenWidth / nRays, distance, (int) srcX, color, hit);
            }
            else
            {
                sf::Color color(255, 255, 255, (distance < 1) ? 255 : 255 / distance);
                srcX = (hit.getY() - floor(hit.getY())) * texture.getSize().x;
                drawSpriteColumn(i * screenWidth / nRays, distance, (int) srcX, color, hit);
            }            
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
        texture.loadFromFile(SPRITE_PATH);

        window.create(sf::VideoMode(screenWidth, screenHeight), title);
        window.setFramerateLimit(60);
    }

    void Renderer::render()
    {
        window.clear();

        render3d();

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
