#pragma once
#include"Tile.h"
#include"Entity.h"
#include"Vector2.h"
#include"Breakable.h"
#include"Unbreakable.h"
#include<vector>
#include<memory>
#include<random>
#include<functional>

class Floor;

class Zone{
    bool isIsolated(int x, int y) const;
    bool EntityPresent(int x, int y) const;
    bool isFilled(int x, int y) const;

    bool IsNearWall(int x, int y) const;
    void ClearNearExit(int x, int y);
    protected:
        const size_t zoneLength;
        const size_t zoneWidth;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        std::vector<std::unique_ptr<Entity>> entities;
        std::random_device rd;
        std::mt19937 gen;
    public:
        Zone(size_t length, size_t width, std::vector<std::vector<std::unique_ptr<Tile>>> Tiles, std::vector<std::unique_ptr<Entity>> Entities);

        Zone(size_t length, size_t width);

        Tile* getTile(int x, int y);

        int ZoneLength() const;
        int ZoneWidth() const;

        Vector2 Center() const;

        void ZoneBoundary();

        void ResourcePopulate(int Resource_Amount, ResourceType Type);

        void EntityPopulate(int Entity_Amount, std::function<std::unique_ptr<Entity>(int, int)> entityFactory);

        void WallPopulate(int Number_of_Walls, TileType type = TileType::GROUND);
        
        std::vector<std::unique_ptr<Entity>>& getEntities();
        const std::vector<std::unique_ptr<Entity>>& getEntities() const;
        void removeDeadEntities();

        friend class Floor;
};
