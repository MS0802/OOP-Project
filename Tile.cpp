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
        case TileType::DOOR:
            return std::string("Door");
        case TileType::ZONE_EXIT:
            return std::string("Zone Exit");
        case TileType::ZONE_BOUNDARY:
            return std::string("Boundary");
    }
}

bool Tile::Walkable() const { return walkable; }
bool Tile::Breakable() const { return breakable; }
TileType Tile::Type() const { return type; }

void Tile::ReplaceTile(const Tile& tile, std::unique_ptr<Item>& Dropped_Item) {
    type = tile.type;
    item = std::move(Dropped_Item);
    walkable = tile.walkable;
    breakable = tile.breakable;
}

void Tile::ReplaceTile(const Tile& tile) {
    type = tile.type;
    item = nullptr;
    walkable = tile.walkable;
    breakable = tile.breakable;
}
