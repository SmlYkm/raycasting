#include "Game/Map.hpp"
#include "Game/json.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace Game
{
    // Deallocates the map matrix
    void Map::destroyTiles()
    {
        if(tiles)    // Deallocates allocated memory for the matrix
        {
            for(int i = 0; i < height; i++)
                delete[] tiles[i];

            delete[] tiles;
            tiles = nullptr;
            height = 0;
            width = 0;
        }
    }

    // Loads map from a JSON file, deleting the previous map if it exists
    void Map::load(const char* filePath)
    {
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
        for(int i = 0; i < height; i++)
        {
            tiles[i] = new char[width];
            for(int j = 0; j < width; j++)
            {
                // Assuming each tile is represented as a single character string in JSON
                std::string tileStr = jsonTiles[i][j];
                if (!tileStr.empty())
                    tiles[i][j] = tileStr[0]; // Convert the first character of the string to char
                else
                    tiles[i][j] = ' '; // Default to space if empty or not found
            }
        }

        // File is automatically closed when the ifstream object is destroyed
    }

    // Constructor that loads the map from a JSON file
    Map::Map(const char* filePath)
        : height(0), width(0), tiles(nullptr)
    {
        load(filePath);
    }

    Map::Map() 
        : height(0), width(0), tiles(nullptr) 
    {}

    Map::~Map()
    {
        destroyTiles();
    }

    int Map::getHeight() const 
    { 
        return height; 
    }

    int Map::getWidth() const 
    { 
        return width; 
    }

    // Checks if the position is within the boundaries of the map
    bool Map::positionIsValid(int x, int y) const 
    {
        return x >= 0 && x < width && y >= 0 && y < height && tiles; 
    }

    char Map::getTile(int x, int y) const 
    {
        if(positionIsValid(x, y))
            return tiles[y][x]; 
        return ' ';
    }

    // Checks if the position is a wall, if the position is outside the
    // boundaries of the map, it is considered a wall
    bool Map::isWall(int x, int y) const 
    {
        if(positionIsValid(x, y))
            return tiles[y][x] != ' ';
        return true;    // If the position is invalid, consider it a wall
    }
}