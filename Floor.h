#ifndef FLOOR_H
#define FLOOR_H

#include "Zone.h"
#include "Enemy.h"
#include <vector>
#include <string>

class Floor{
    private:
    std::vector<std::vector<Zone>> zones;
    std::vector<Enemy*> enemies; //global coordinates (not per zone)
    int zonesWide, zonesHigh;
    int floorNumber;
    

    public:
    Floor(const std::string& filename,int floorNum) {};
    ~Floor(){};

    Tile& getTile(int globalX,int globalY);
    bool isWalkable(int globalX,int globalY);

    Zone& getZone(int zx, int zy);
    Zone& getZoneAt(int globalX,int globalY);

    std::vector<Enemy*>& getEnemies();
    void addEnemy(Enemy* e);
    void removeDeadEnemies();

    int getFloorNumber() const;


};

#endif