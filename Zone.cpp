#include"Zone.h"

Zone::Zone(size_t length, size_t width, const std::vector<std::vector<std::unique_ptr<Tile>>>& Tiles, const std::vector<std::unique_ptr<Entity>>& Entities) : 
zoneLength(length), zoneWidth(width), tiles(std::move(Tiles)), entities(std::move(Entities)), gen(rd()) {}

Zone::Zone(size_t length, size_t width) : 
zoneLength(length), zoneWidth(width), tiles(length), entities(), gen(rd()) {
    for(auto& row : tiles) {
        row.resize(zoneWidth);
        for(auto& tile : row) {
            tile = std::make_unique<Tile>();
        }
    }
}

std::unique_ptr<Tile> Zone::getTile(int x, int y) {
    if((x < 0 || y < 0) || (x >= zoneLength || y >= zoneWidth)) {
        std::unique_ptr<Tile> RET = std::make_unique<Tile>(TileType::ZONE_BOUNDARY, false, false);
        return RET;
    }
    return std::move(tiles[x][y]);
}

int Zone::ZoneLength() const { return zoneLength; }
int Zone::ZoneWidth() const { return zoneWidth; }
Vector2 Zone::Center() const { return Vector2(zoneLength/2, zoneWidth/2); }

bool Zone::isIsolated(int x, int y) const {
    for(int i = -1; i<=1; i++) {
        for(int j = -1; j<=1; ++j) {
            int nx = x + i;
            int ny = y + j;
            if(nx < 0 || nx > zoneLength || ny < 0 || ny > zoneWidth) { return false; }
            if(tiles[nx][ny]->Type() != TileType::GROUND) { return false; }
        }
    }
    return true;
}

bool Zone::EntityPresent(int x, int y) const {
    for(const auto& e : entities) {
        if(e->PosX() == x && e->posY() == y) { return true; }
    }
    return false;
}

bool Zone::isFilled(int x, int y) const {
    if(x < 0 || x >= zoneLength || y < 0 || y >= zoneWidth) { return true; }
    return (tiles[x][y]->Type() != TileType::GROUND);
}

void Zone::ZoneBoundary() {
    for(int i = 0; i<zoneLength; i++) {
        if(!isFilled(i, 0)) { tiles[i][0]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
        if(!isFilled(i, zoneLength-1)) { tiles[i][zoneLength-1]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
    }
    for(int i = 0; i<zoneWidth; i++) {
        if(!isFilled(0, i)) { tiles[0][i]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
        if(!isFilled(zoneWidth-1, i)) { tiles[zoneWidth-1][i]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
    }
}

void Zone::ResourcePopulate(int Resource_Amount, ResourceType Type) {
    int spawned = 0;
    std::uniform_int_distribution<> distY(1, zoneWidth - 2);
    std::uniform_int_distribution<> distX(1, zoneLength - 2);

    while(spawned < Resource_Amount) {
        int ry = distY(gen);
        int rx = distX(gen);

        if(isIsolated(rx, ry)) {
            tiles[rx][ry]->ReplaceTile(Breakable(Type));
            spawned++;
        }
    }
}

void Zone::EntityPopulate(int Entity_Amount, std::unique_ptr<Entity> entity) {
    int spawned = 0;
    std::uniform_int_distribution<> distY(1, zoneWidth - 2);
    std::uniform_int_distribution<> distX(1, zoneLength - 2);

    while(spawned < Entity_Amount) {
        int ry = distY(gen);
        int rx = distX(gen);

        if(tiles[rx][ry]->Type() == TileType::GROUND && (!EntityPresent(rx, ry))) {
            entities.push_back(std::move(entity));
            spawned++;
        }
    }
}
