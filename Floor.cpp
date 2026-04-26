#include"Floor.h"

Floor::Floor(const std::vector<Zone>& Zones, int FloorNumber, std::unique_ptr<Zone> ActiveZone) : 
zones(Zones), floorNumber(FloorNumber), activeZone(std::move(ActiveZone)), numberOfZones(Zones.size()) {}

Floor::Floor(int FloorNumber, int MAX_Zones) : 
floorNumber(FloorNumber), zones(), activeZone(nullptr), numberOfZones(MAX_Zones) {}

Zone* Floor::ActiveZone() { return activeZone.get(); }
int Floor::FloorNumber() const { return floorNumber; }

void Floor::AddZone(size_t ZoneLength, size_t ZoneWidth) {
    if(zones.size() < numberOfZones) {
        zones.push_back(Zone(ZoneLength, ZoneWidth));
    }
}

void Floor::ZoneBoundary_andExits() {
    for(auto& zone : zones) {
        zone.ZoneBoundary();
        std::uniform_int_distribution<> sideDetermine(0, 3);
        std::uniform_int_distribution<> midSelection(0, 3);
        int side = sideDetermine(zone.gen);
        switch(side) {
            case 0:
                
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
    }
}
