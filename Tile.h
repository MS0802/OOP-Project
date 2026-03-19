#ifndef TILE_H
#define TILE_H

#include "Item.h"
#include <memory>

enum class TileType{
    FLOOR,
    WALL,
    STAIRS_DOWN,
    DOOR,
    CAVE_ENTRANCE,
    DUNGEON_ENTRANCE,
    SHOP_TILE,
    ZONE_BOUNDARY
};

struct Tile{
    TileType type;
    std::unique_ptr<Item> item;//if nullptr then there's no item on tile
    bool isVisible;

    Tile(TileType t= TileType::WALL):type(t),isVisible(true) {}

    //move constructor to tranfer ownership
    Tile(Tile&&) =default;
    Tile& operator=(Tile&&) =default;
};

#endif
