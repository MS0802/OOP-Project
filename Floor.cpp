#include"Floor.h"
#include<algorithm>

Floor::Floor(std::vector<std::unique_ptr<Zone>>& Zones, int FloorNumber, Zone* ActiveZone) : 
zones(std::move(Zones)), floorNumber(FloorNumber), activeZone(ActiveZone), activeZoneIndex(0), numberOfZones(Zones.size()) {}

Floor::Floor(int FloorNumber, int MAX_Zones) : 
floorNumber(FloorNumber), zones(), activeZone(nullptr), activeZoneIndex(0), numberOfZones(MAX_Zones) {}

Zone* Floor::ActiveZone() { return activeZone; }
int Floor::ActiveZoneIndex() const { return activeZoneIndex; }
bool Floor::SetActiveZone(int index) {
    if(index < 0 || index >= zones.size()) {
        return false;
    }
    activeZoneIndex = index;
    activeZone = zones[index].get();
    return true;
}
bool Floor::NextZone() {
    return SetActiveZone(activeZoneIndex + 1);
}

int Floor::FloorNumber() const { return floorNumber; }
int Floor::Number_ofZones() const { return numberOfZones; }

void Floor::AddZone(size_t ZoneLength, size_t ZoneWidth) {
    if(zones.size() < numberOfZones) {
        zones.push_back(std::make_unique<Zone>(ZoneLength, ZoneWidth));
        if(zones.size() == 1) {
            activeZone = zones[0].get();
            activeZoneIndex = 0;
        }
    }
}

void Floor::ZoneBoundary_andExits() {
    for(auto& zone : zones) {
        zone->ZoneBoundary();
        std::vector<int> sides = {0, 1, 2, 3};
        std::shuffle(sides.begin(), sides.end(), zone->gen);
        
        for(int i = 0; i<2; i++) {
            int side = sides[i];
            int exitCount = std::uniform_int_distribution<>(1, 4)(zone->gen);
            int startPos, endPos;
            
            if(side == 0 || side == 1) {
                int maxStart = zone->ZoneWidth() - 2 - exitCount;
                if(maxStart < 0) {
                    continue;
                }
                int startX = std::uniform_int_distribution<>(0, maxStart)(zone->gen);
                startPos = startX + 2;
                endPos = startPos + (exitCount - 1);
                int row = ((side == 0) ? 0 : zone->ZoneLength()-1);
                for(int x = startPos; x <= endPos; ++x) {
                    zone->tiles[row][x]->ReplaceTile(Entrance(TileType::ZONE_EXIT));
                }
            }
            else {
                int maxStart = zone->ZoneLength() - 2 - exitCount;
                if(maxStart < 0) {
                    continue;
                }
                int startY = std::uniform_int_distribution<>(0, maxStart)(zone->gen);
                startPos = startY + 2;
                endPos = startPos + (exitCount - 1);
                int col = ((side == 2) ? 0 : zone->ZoneWidth()-1);
                for(int y = startPos; y <= endPos; ++y) {
                    zone->tiles[y][col]->ReplaceTile(Entrance(TileType::ZONE_EXIT));
                }
            }
            if(floorNumber == 1) {
                break;
            }
        }
    }
}
