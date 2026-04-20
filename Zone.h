#pragma once

#include "Tile.h"
#include "entity.h"
#include <vector>
#include <array>
#include <memory>

class Zone{
    private:
        constexpr size_t zoneLength;
        constexpr size_t zoneWidth;
        std::array<std::array<std::unique_ptr<Tiles>,zoneWidth>, zoneLength> tiles;
        std::vector<std::unique_ptr<Entity>> entities;
        

    public:
    Zone(int zx,int zy);

    Tile& getTile(int localX,int localY);
    const Tile& getTile(int localX,int localY) const;

    bool isWalkable(int localX,int localY) const;

    int getZoneX() const;
    int getZoneY() const;

    //global coordinates of this zone's top left side
    int globalOriginX() const; //returns zoneX * ZONE_w
    int globalOriginY() const; //returns zoneY * ZONE_h

};

#endif
