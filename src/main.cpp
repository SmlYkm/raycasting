#include "Game/Map.hpp"
#include "Rendering/Renderer.hpp"

#define MAP_PATH "../levels/level3.json"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "raycasting"

#define PLAYER_RADIUS 0.16f

#define FPS 120
#define FOV /*M_PI / 2.25f*/  1.1519173063162575    // Field of view in radians
#define N_RAYS 800    // Number of rays casted from the player

int main(int argc, char* argv[]) {
    Rendering::Renderer& renderer = Rendering::Renderer::getInstance();
    Game::Map map(MAP_PATH);
    Game::Player player(Math::Vector2D<float>(1.5f, 1.5f), &map, PLAYER_RADIUS, M_PI/2.0f, 0.003f/*.0f*/, 0.002f/*.0f*/);

    renderer.initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, FOV, N_RAYS);
    renderer.setMap(&map);
    renderer.setPlayer(&player);
    renderer.setFPSlimit(FPS);

    while(renderer.isRunning()) {   
        renderer.pollEvent();
        renderer.render();
    }

    return 0;
}
