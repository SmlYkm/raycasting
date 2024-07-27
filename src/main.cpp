#include "Game/Map.hpp"
#include "Rendering/Renderer.hpp"
#include "Math/Physics.hpp"

#define MAP_PATH "../levels/level2.json"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Raycaster"

#define PLAYER_RADIUS 0.16f

#define FPS 60
#define FOV M_PI / 2.5f    // Field of view in radians
#define N_RAYS 100    // Number of rays casted from the player

int main()
{
    Rendering::Renderer& renderer = Rendering::Renderer::getInstance();
    Game::Map map(MAP_PATH);
    Game::Player player(Math::Vector2f(1.5f, 1.5f), &map, PLAYER_RADIUS, 0.0f, 0.000003f/*.0f*/, 0.000002f/*.0f*/);

    renderer.init(&map, &player, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, FOV, N_RAYS);
    renderer.setFPSlimit(FPS);

    sf::Event event;
    while(renderer.isOpen())
    {   
        Math::Physics::updateDeltaTime();
        renderer.pollEvent();
        renderer.render();
    }

    return 0;
}