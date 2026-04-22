#pragma once
#include"Tile.h"
#include"Entity.h"
#include"Vector2.h"
#include"Breakable.h"
#include"Unbreakable.h"
#include<vector>
#include<memory>
#include<random>

class Floor;

class Zone{
    private:
        const size_t zoneLength;
        const size_t zoneWidth;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        std::vector<std::unique_ptr<Entity>> entities;
        std::random_device rd;
        std::mt19937 gen;

        bool isIsolated(int x, int y) const;
        bool EntityPresent(int x, int y) const;
        bool isFilled(int x, int y) const;
    public:
        Zone(size_t length, size_t width, const std::vector<std::vector<std::unique_ptr<Tile>>>& Tiles, const std::vector<std::unique_ptr<Entity>>& Entities);

        Zone(size_t length, size_t width);

        std::unique_ptr<Tile> getTile(int x, int y);

        int ZoneLength() const;
        int ZoneWidth() const;

        Vector2 Center() const;

        void ZoneBoundary();

        void ResourcePopulate(int Resource_Amount, ResourceType Type);

        void EntityPopulate(int Entity_Amount, std::unique_ptr<Entity> entity);

        friend class Floor;
};
