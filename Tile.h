#pragma once
#include"Item.h"
#include<string>

enum class TileType{
    GROUND,
    WALL,
    STAIRS_DOWN,
    STAIRS_UP,
    DOOR,
    CAVE_ENTRANCE,
    DUNGEON_ENTRANCE,
    SHOP_TILE,
    ZONE_BOUNDARY,
    RESOURCE
};

struct Tile{
    protected:
        TileType type;
        std::unique_ptr<Item> item;//if nullptr then there's no item on tile
        bool walkable;
        bool breakable;
    public:
        Tile(TileType Type, std::unique_ptr<Item>& Item, bool IsWalkable, bool IsBreakable);
        Tile();
        Tile(TileType Type, bool IsWalkable, bool IsBreakable);
        
        virtual std::string Name() const;
};
