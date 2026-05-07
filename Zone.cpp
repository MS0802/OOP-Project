#include"Zone.h"
#include<algorithm>

Zone::Zone(size_t length, size_t width, std::vector<std::vector<std::unique_ptr<Tile>>> Tiles, std::vector<std::unique_ptr<Entity>> Entities) : 
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

Tile* Zone::getTile(int x, int y) {
    if((x < 0 || y < 0) || (x >= zoneWidth || y >= zoneLength)) {
        return nullptr;
    }
    return tiles[y][x].get();
}

int Zone::ZoneLength() const { return zoneLength; }
int Zone::ZoneWidth() const { return zoneWidth; }
Vector2 Zone::Center() const { return Vector2(zoneWidth/2, zoneLength/2); }

bool Zone::isIsolated(int x, int y) const {
    for(int i = 0; i<1; i++) {
        for(int j = 0; j<1; ++j) {
            int nx = x + i;
            int ny = y + j;
            if(nx < 0 || nx >= zoneWidth || ny < 0 || ny >= zoneLength) { return false; }
            if(tiles[ny][nx]->Type() != TileType::GROUND) { return false; }
        }
    }
    return true;
}

bool Zone::EntityPresent(int x, int y) const {
    for(const auto& e : entities) {
        if(e->PosX() == x && e->PosY() == y) { return true; }
    }
    return false;
}

bool Zone::isFilled(int x, int y) const {
    if(x < 0 || x >= zoneWidth || y < 0 || y >= zoneLength) { return true; }
    return (tiles[y][x]->Type() != TileType::GROUND);
}

void Zone::ZoneBoundary() {
    for(int y = 0; y<zoneLength; y++) {
        if(!isFilled(0, y)) { tiles[y][0]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
        if(!isFilled(zoneWidth-1, y)) { tiles[y][zoneWidth-1]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
    }
    for(int x = 0; x<zoneWidth; x++) {
        if(!isFilled(x, 0)) { tiles[0][x]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
        if(!isFilled(x, zoneLength-1)) { tiles[zoneLength-1][x]->ReplaceTile(Unbreakable(TileType::ZONE_BOUNDARY)); }
    }
}

void Zone::ResourcePopulate(int Resource_Amount, ResourceType Type) {
    int spawned = 0;
    std::uniform_int_distribution<> distX(1, zoneWidth - 2);
    std::uniform_int_distribution<> distY(1, zoneLength - 2);

    while(spawned < Resource_Amount) {
        int rx = distX(gen);
        int ry = distY(gen);

        if(!isFilled(rx, ry)) {
            tiles[ry][rx] = std::make_unique<Breakable>(Type);
            spawned++;
        }
    }
}

void Zone::EntityPopulate(int Entity_Amount, std::function<std::unique_ptr<Entity>(int, int)> entityFactory) {
    int spawned = 0;
    std::uniform_int_distribution<> distX(1, zoneWidth - 2);
    std::uniform_int_distribution<> distY(1, zoneLength - 2);

    while(spawned < Entity_Amount) {
        int rx = distX(gen);
        int ry = distY(gen);

        if(tiles[ry][rx]->Type() == TileType::GROUND && (!EntityPresent(rx, ry))) {
            std::unique_ptr<Entity> newEntity = entityFactory(rx, ry);
            if(newEntity) {
                entities.push_back(std::move(newEntity));
                spawned++;
            }
        }
    }
}

bool Zone::IsNearWall(int x, int y) const {
    for(int ny = y-1; ny<=y+1; ny++) {
        for(int nx = x-1; nx<=x+1; nx++) {
            if(nx >= 0 && nx < ZoneWidth() && ny >= 0 && ny < ZoneLength()) {
                if(tiles[ny][nx]->Type() == TileType::WALL) { return true; }
            }
        }
    }
    return false;
}

void Zone::ClearNearExit(int x, int y) {
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 1 && nx < ZoneWidth()-1 && ny >= 1 && ny < ZoneLength()-1) {
            if(tiles[ny][nx]->Type() == TileType::WALL) {
                tiles[ny][nx]->ReplaceTile(Tile());
            }
        }
    }
}

void Zone::WallPopulate(int Number_of_Walls, TileType type) {
    if(tiles.empty() || tiles[0].empty()) { return; }
    
    std::uniform_int_distribution<> distBool(0, 1);
    std::uniform_int_distribution<> distSide(0, 3);
    std::uniform_int_distribution<> distX(2, ZoneWidth() - 3);
    std::uniform_int_distribution<> distY(2, ZoneLength() - 3);

    for(int w = 0; w < Number_of_Walls; w++) {
        int startX, startY;
        int dx = 0, dy = 0;
        int side = distSide(gen);

        switch(side) {
            case 0:
                startX = distX(gen);
                startY = 1;
                dy = 1;
                break;
            case 1:
                startX = distX(gen);
                startY = ZoneLength()-2;
                dy = -1;
                break;
            case 2:
                startX = 1;
                startY = distY(gen);
                dx = 1;
                break;
            case 3:
                startX = ZoneWidth()-2;
                startY = distY(gen);
                dx = -1;
                break;
        }

        if(tiles[startY][startX]->Type() != TileType::GROUND || IsNearWall(startX, startY)) {
            --w;
            continue;
        }

        int maxLength = ((dx != 0) ? ZoneWidth()-2 : ZoneLength()-2);
        int length = std::uniform_int_distribution<>(5, std::max(5, (int)(maxLength * 0.7)))(gen);
        int doorIndex = std::uniform_int_distribution<>(1, length - 2)(gen);

        bool crashed = false;
        int currX = startX;
        int currY = startY;

        for(int i = 0; i<length; i++) {
            int nx = startX + (i*dx);
            int ny = startY + (i*dy);

            if(nx <= 0 || nx >= ZoneWidth()-1 || ny <= 0 || ny >= ZoneLength()-1 || 
            tiles[ny][nx]->Type() == TileType::WALL || tiles[ny][nx]->Type() == TileType::ZONE_BOUNDARY) {
                crashed = true;
                break;
            }

            if(i == doorIndex) {
                tiles[ny][nx]->ReplaceTile(Tile());
            }
            else {
                tiles[ny][nx]->ReplaceTile(Unbreakable(TileType::WALL));
            }
            currX = nx;
            currY = ny;
        }

        if(!crashed) {
            int turnDx = 0, turnDy = 0;
            if (dx != 0) { turnDy = (distBool(gen) ? 1 : -1); }
            else { turnDx = (distBool(gen) ? 1 : -1); }

            int turnSteps = 0;
            while(true) {
                int nx = currX + turnDx;
                int ny = currY + turnDy;

                if (nx <= 0 || nx >= ZoneWidth() - 1 || ny <= 0 || ny >= ZoneLength() - 1 || 
                tiles[ny][nx]->Type() == TileType::WALL || tiles[ny][nx]->Type() == TileType::ZONE_BOUNDARY) {
                    break;
                }
                if(turnSteps > 0 && turnSteps%5 == 0) { tiles[ny][nx]->ReplaceTile(Tile()); }
                else { tiles[ny][nx]->ReplaceTile(Unbreakable(TileType::WALL)); }
                
                currX = nx;
                currY = ny;
                turnSteps++;
            }
        }
    }

    for(int y = 0; y < ZoneLength(); y++) {
        for(int x = 0; x < ZoneWidth(); x++) {
            if(tiles[y][x]->Type() == TileType::ZONE_EXIT) {
                ClearNearExit(x, y);
            }
        }
    }
}

std::vector<std::unique_ptr<Entity>>& Zone::getEntities() {
    return entities;
}

const std::vector<std::unique_ptr<Entity>>& Zone::getEntities() const {
    return entities;
}

void Zone::removeDeadEntities() {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](const std::unique_ptr<Entity>& e) { return !e->isAlive(); }),
        entities.end()
    );
}
