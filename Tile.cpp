#include"Tile.h"

Tile::Tile(TileType Type, std::unique_ptr<Item>& Item, bool IsWalkable, bool IsBreakable) : 
type(Type), item(std::move(Item)), walkable(IsWalkable), breakable(IsBreakable) {
    if(walkable) { breakable = false; }
}

Tile::Tile() : 
type(TileType::GROUND), item(nullptr), walkable(true), breakable(false) {}

Tile::Tile(TileType Type, bool IsWalkable, bool IsBreakable) : 
type(Type), item(nullptr), walkable(IsWalkable), breakable(IsBreakable) {
    if(walkable) { breakable = false; }
}

std::string Tile::Name() const {
    switch(type) {
        case TileType::GROUND:
            return std::string("Ground Tile");
        case TileType::WALL:
            return std::string("Wall");
        case TileType::STAIRS_DOWN:
        case TileType::STAIRS_UP:
            return std::string("Stairs");
        case TileType::DOOR:
            return std::string("Door");
        case TileType::CAVE_ENTRANCE:
            return std::string("Cave Entrance");
        case TileType::DUNGEON_ENTRANCE:
            return std::string("Dungeon Entrance");
        case TileType::SHOP_TILE:
            return std::string("Shop");
        case TileType::ZONE_BOUNDARY:
            return std::string("Boundary");
    }
}
