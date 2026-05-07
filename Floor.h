#pragma once
#include"Zone.h"
#include"Entrance.h"

class World;

class Floor{
    protected:
        int floorNumber;
        std::vector<std::unique_ptr<Zone>> zones;
        Zone* activeZone;
        int activeZoneIndex;
        const int numberOfZones;
    public:
        Floor(std::vector<std::unique_ptr<Zone>>& Zones, int FloorNumber, Zone* ActiveZone);
        Floor(int FloorNumber, int MAX_Zones);
        
        Zone* ActiveZone();
        int ActiveZoneIndex() const;
        bool SetActiveZone(int index);
        bool NextZone();
        int FloorNumber() const;
        int Number_ofZones() const;

        void AddZone(size_t ZoneLength, size_t ZoneWidth);
        void ZoneBoundary_andExits();

        friend class World;
};
