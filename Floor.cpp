#include"Floor.h"

Floor::Floor(const std::vector<Zone>& Zones, int FloorNumber, std::unique_ptr<Zone> ActiveZone) : 
zones(Zones), floorNumber(FloorNumber), activeZone(std::move(ActiveZone)), numberOfZones(Zones.size()) {}

Floor::Floor(int FloorNumber, int MAX_Zones) : 
floorNumber(FloorNumber), zones(), activeZone(nullptr), numberOfZones(MAX_Zones) {}

std::unique_ptr<Zone>& Floor::ActiveZone() { return std::move(activeZone); }
int Floor::FloorNumber() const { return floorNumber; }

void Floor::AddZone(size_t ZoneLength, size_t ZoneWidth) {
    if(zones.size() < numberOfZones) {
        zones.push_back(Zone(ZoneLength, ZoneWidth));
    }
}

void Floor::ZoneBoundary_andExits() {
    for(auto& zone : zones) {
        for(int j = zone.Center().x; j < zone.ZoneLength(); j++) {
            if(j%2) { zone.tiles[j][0]->ReplaceTile(Entrance(TileType::ZONE_EXIT)); }
            else { zone.tiles[j][zone.ZoneWidth()-1]->ReplaceTile(Entrance(TileType::ZONE_EXIT)); }
        }
        if(floorNumber != 1) {
            for(int j = zone.Center().y; j < zone.ZoneWidth(); j++) {
                if(j%2) { zone.tiles[0][j]->ReplaceTile(Entrance(TileType::ZONE_EXIT)); }
                else { zone.tiles[zone.ZoneLength()-1][j]->ReplaceTile(Entrance(TileType::ZONE_EXIT)); }
            }
        }
    }
}
