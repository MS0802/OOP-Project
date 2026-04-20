#include"Zone.h"

Zone::Zone(size_t length, size_t width, const std::vector<std::vector<std::unique_ptr<Tile>>>& Tiles, const std::vector<std::unique_ptr<Entity>>& Entities) : 
zoneLength(length), zoneWidth(width), tiles(std::move(Tiles)), entities(std::move(Entities)) {}

std::unique_ptr<Tile> Zone::getTile(int x, int y) {
    if((x < 0 && y < 0) || (x > zoneLength && y > zoneWidth)) {
        std::unique_ptr<Tile> RET = std::make_unique<Tile>(TileType::ZONE_BOUNDARY, false, false);
        return RET;
    }
    return std::move(tiles[x][y]);
}

int Zone::ZoneLength() const { return zoneLength; }
int Zone::ZoneWidth() const { return zoneWidth; }
Vector2 Zone::Center() const { return Vector2(zoneLength/2, zoneWidth/2); }
