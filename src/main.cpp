#include "Game/Map.hpp"
#include "Draw/Renderer.hpp"
#include "Math/Physics.hpp"

#define MAP_PATH "../levels/level3.json"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "raycasting"

#define PLAYER_RADIUS 0.16f

#define FPS 60
#define FOV M_PI / 2.25f // 1.1519173063162575    // Field of view in radians
#define N_RAYS 640    // Number of rays casted from the player

int main()
{
    Rendering::Renderer& renderer = Rendering::Renderer::getInstance();
    Game::Map map(MAP_PATH);
    Game::Player player(Math::Vector2D<float>(1.5f, 1.5f), &map, PLAYER_RADIUS, M_PI/2.0f, 0.000003f/*.0f*/, 0.000002f/*.0f*/);

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
