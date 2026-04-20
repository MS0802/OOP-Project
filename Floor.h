#pragma once
#include"Zone.h"

class Floor{
    protected:
        int floorNumber;
        std::vector<Zone> zones;
        std::unique_ptr<Zone> activeZone;
    public:
        Floor(const std::vector<Zone>& Zones, int FloorNumber, std::unique_ptr<Zone> ActiveZone);
        Floor(int FloorNumber);
        
        std::unique_ptr<Zone>& ActiveZone();
        int FloorNumber() const;
};
