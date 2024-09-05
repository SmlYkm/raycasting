#include "Game/Map.hpp"
#include "Game/json.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace Game {
    // Deallocates the map matrix
    void Map::destroyTiles() {
        if(tiles) {
            for(int i = 0; i < height; i++)
                delete[] tiles[i];

            delete[] tiles;
            tiles = nullptr;
            height = 0;
            width = 0;
        }
    }

    // Loads map from a JSON file, deleting the previous map if it exists
    void Map::load(const char* filePath) {
        destroyTiles();

        std::ifstream file(filePath);
        if(!file.is_open())
            throw std::runtime_error("Could not open map file");

        nlohmann::json jsonObj;
        file >> jsonObj; // Parse the JSON from the file

        auto jsonTiles = jsonObj["tiles"];
        height = jsonTiles.size();
        width = jsonTiles.empty() ? 0 : jsonTiles[0].size();

        tiles = new char*[height];
        for(int i = 0; i < height; i++) {
            tiles[i] = new char[width];
            for(int j = 0; j < width; j++) {
                // Assuming each tile is represented as a single character string in JSON
                std::string tileStr = jsonTiles[i][j];
                if (!tileStr.empty())
                    tiles[i][j] = tileStr[0]; // Convert the first character of the string to char
                else
                    tiles[i][j] = ' '; // Default to space if empty or not found
            }
        }
    }

    Map::Map(const char* filePath)
        : height(0), 
          width(0), 
          tiles(nullptr)
    {
        if(filePath)
            load(filePath);
    }

    Map::~Map() { 
        destroyTiles(); 
    }

    const int Map::getHeight() const { return height; }

    const int Map::getWidth() const { return width; }

    // Checks if the position is within the boundaries of the map
    const bool Map::positionIsValid(const int x, const int y) const {
        return x >= 0 && x < width && y >= 0 && y < height && tiles; 
    }

    const char Map::getTile(const int x, const int y) const {
        if(positionIsValid(x, y))
            return tiles[y][x]; 
        return ' ';
    }

    // Checks if the position is a wall, if the position isn't invalid, it's considered a wall
    const bool Map::isWall(const int x, const int y) const {
        if(positionIsValid(x, y))
            return tiles[y][x] != ' ';
        return true;
    }
}