#include"World.h"

World::World() : 
floors(7), totalFloors(7), activeFloor(nullptr) {}

void World::SetActiveFloor(size_t FloorNumber) {
    FloorNumber--;
    FloorNumber = FloorNumber%7;
    activeFloor = floors[FloorNumber].get();
}

void World::InitializeFloor1() {
    Floor first(1, 2);
    first.AddZone(36, 48);
    first.AddZone(48, 48);
    first.ZoneBoundary_andExits();
    first.activeZone = first.zones[0].get();
    for(int i = 0; i<first.Number_ofZones(); i++) {
        if(i == 0) {
            first.zones[i]->ResourcePopulate(8, ResourceType::TREE);
            first.zones[i]->ResourcePopulate(5, ResourceType::BARREL0);
        }
        else {
            first.zones[i]->ResourcePopulate(15, ResourceType::TREE);
            first.zones[i]->ResourcePopulate(4, ResourceType::STONE);
            first.zones[i]->ResourcePopulate(5, ResourceType::BARREL1);
        }
    }
}
