#pragma once
#include"Tile.h"
#include"entity.h"
#include"Vector2.h"
#include<vector>
#include<memory>

class Zone{
    private:
        size_t zoneLength;
        size_t zoneWidth;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        std::vector<std::unique_ptr<Entity>> entities;
    public:
        Zone(size_t length, size_t width, const std::vector<std::vector<std::unique_ptr<Tile>>>& Tiles, const std::vector<std::unique_ptr<Entity>>& Entities);

        std::unique_ptr<Tile> getTile(int x, int y);

        int ZoneLength() const;
        int ZoneWidth() const;

        Vector2 Center() const;

        //rest of the functions are not complete yet
};
