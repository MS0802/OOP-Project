#pragma once
#include"Zone.h"
#include"Entrance.h"

class Floor{
    protected:
        int floorNumber;
        std::vector<Zone> zones;
        std::unique_ptr<Zone> activeZone;
        const int numberOfZones;
    public:
        Floor(const std::vector<Zone>& Zones, int FloorNumber, std::unique_ptr<Zone> ActiveZone);
        Floor(int FloorNumber, int MAX_Zones);
        
        std::unique_ptr<Zone>& ActiveZone();
        int FloorNumber() const;

        void AddZone(size_t ZoneLength, size_t ZoneWidth);
        void ZoneBoundary_andExits();
};
