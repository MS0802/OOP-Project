#ifndef ZONE_H
#define ZONE_H

#include "Tile.h"
#include <vector>

//dimensions of Zone
const int ZONE_w =20;
const int ZONE_h =20;

class Zone{
    private:
    std::vector<std::vector<Tile>> tiles;
    int zoneX, zoneY;//Zone's position in the floor

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