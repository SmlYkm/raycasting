#pragma once 

namespace Game {
    class Map {
    private:
        int height;
        int width;
        char** tiles;
    
    private:
        void destroyTiles();
        
    public:
        void load(const char* filePath);
        Map(const char* filePath = nullptr);
        ~Map();

        const int getHeight() const;
        const int getWidth() const;
        const bool positionIsValid(const int x, const int y) const;
        const char getTile(const int x, const int y) const;
        const bool isWall(const int x, const int y) const;
    };
}