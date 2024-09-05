#include "Rendering/Renderer.hpp"
#include "Rendering/Raycaster.hpp"
#include "Math/Physics.hpp"

#include <iostream>
#include <cmath>

#define SPRITE_PATH "../assets/wall.png"

namespace Rendering {
    Renderer::Renderer()
        : window(nullptr),
          renderer(nullptr),
          texture(nullptr),
          map(nullptr),
          player(nullptr),
          screenWidth(800),
          screenHeight(600),
          pixelColumnWidth(8.0f),
          fps(60),
          frameDelay(16),
          fov(0.0f),
          nRays(100),
          cameraPlaneLen(1.0f),
          running(false)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
            std::cout << "failed to init sdl\n";
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) 
            std::cout << "failed to init png subsystem\n";
    }

    Renderer::~Renderer() {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        IMG_Quit();
        SDL_Quit();
    }

    void Renderer::drawPixelColumn(float x, float dist) {
        float height = ((float)screenHeight) / dist;
        SDL_Rect rect = {(int)x, (int)((screenHeight - height) / 2), screenWidth/nRays, (int)height};
        SDL_RenderFillRect(renderer, &rect);
    }

    void Renderer::drawSpriteColumn(float x, float dist, int srcX) {
        float destHeight = ((float)screenHeight) / dist;
        SDL_FRect dest = {x, (float)(screenHeight - destHeight) / 2.0f, pixelColumnWidth, destHeight};
        SDL_Rect src = {srcX, 0, 1, 64};

        Uint8 colorMod = (Uint8) (255.0f/(dist+1.0f));
        SDL_SetTextureColorMod(texture, colorMod, colorMod, colorMod);
        SDL_RenderCopyF(renderer, texture, &src, &dest);
    }

    // Draws columns of pixels taking into account the distance of the wall
    void Renderer::render3d() {
        player->normalizeAngle();

        Math::Vector2D<float> playerDir = Math::Vector2D<float>(std::cos(player->getAngle()), std::sin(player->getAngle()));
        Math::Vector2D<float> cameraPlane = playerDir.getOrthogonal() * cameraPlaneLen;
        Math::Vector2D<float> increment = cameraPlane * 2.0f / (nRays - 1);
        Math::Vector2D<float> cameraPlanePoint = player->getPosition() + playerDir + cameraPlane;

        for(int i = 0; i < nRays; ++i, cameraPlanePoint -= increment) {
            Math::Vector2D<float> hit = Raycaster::castRay(player->getPosition(), cameraPlanePoint, map);

            float perpDist = (hit-player->getPosition()) * playerDir;
                        
            int srcX = (hit.getY() - floor(hit.getY())) * 64;
            if(Raycaster::hitWasVertical())
                srcX = (hit.getX() - floor(hit.getX())) * 64;
            
            drawSpriteColumn(i * pixelColumnWidth, perpDist, srcX);   
        } 
    }

    Renderer& Renderer::getInstance() {
        static Renderer instance;
        return instance;
    }

    void Renderer::setMap(Game::Map* mp) { map = mp; }

    void Renderer::setPlayer(Game::Player* pl) { player = pl; }

    void Renderer::setFPSlimit(int limit) {
        fps = limit;
        frameDelay = 1000/fps;
    }

    void Renderer::initWindow(const int width, const int height, const char* title, const float fieldOfView, const int raysN) {
        screenHeight = height;
        screenWidth = width;

        window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  width, height, 
                                  SDL_WINDOW_SHOWN);        
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        fov = fieldOfView;
        nRays = raysN;
        cameraPlaneLen = std::tan(fieldOfView / 2.0f);
        pixelColumnWidth = (float)screenWidth / (float)nRays;
        
        running = true;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        SDL_Surface* surface = IMG_Load(SPRITE_PATH);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void Renderer::render() {
        SDL_RenderClear(renderer);

        render3d();

        SDL_RenderPresent(renderer);

        Uint32 deltaTime = Math::Physics::updateDeltaTime();

        if(deltaTime < frameDelay)
            SDL_Delay(frameDelay - deltaTime);
    }

    void Renderer::pollEvent() {
        static SDL_Event event;
        while (SDL_PollEvent(&event)) 
            if (event.type == SDL_QUIT)
                running = false;
        
        player->handleInput();
    }

    const bool Renderer::isRunning() const { return running; }
}
