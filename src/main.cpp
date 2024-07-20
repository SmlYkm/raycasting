#include "Game/Map.hpp"
#include "Rendering/Renderer.hpp"
#include "Math/Physics.hpp"

#define MAP_PATH "../levels/level1.json"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Raycaster"

int main()
{
    Rendering::Renderer& renderer = Rendering::Renderer::getInstance();
    Game::Map map(MAP_PATH);
    Game::Player player(Math::Vector2f(1.5f, 1.5f), 0.0f, 3.0f, 2.0f);

    renderer.init(&map, &player, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

    sf::Event event;
    while(renderer.isOpen())
    {   
        Math::Physics::updateDeltaTime();
        renderer.pollEvent();
        renderer.render();
    }

    return 0;
}