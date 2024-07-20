#pragma once 

namespace Game
{
    class Map
    {
    private:
        int height;
        int width;
        char** tiles;
    
    private:
        void destroyTiles();
        
    public:
        void load(const char* filePath);
        Map(const char* filePath);
        Map();
        ~Map();

        int getHeight() const;
        int getWidth() const;
        bool positionIsValid(int x, int y) const;
        char getTile(int x, int y) const;
        bool isWall(int x, int y) const;
    };
}