#include"World.h"

World::World() : 
floors(7), totalFloors(7), activeFloor(nullptr) {}

void World::SetActiveFloor(size_t FloorNumber) {
    FloorNumber--;
    FloorNumber = FloorNumber%7;
    activeFloor = floors[FloorNumber].get();
}

void World::InitializeFloor1() {
    Floor first(1, 5);
    first.AddZone(48, 48);
    first.AddZone(36, 48);
    first.AddZone(48, 54);
    first.AddZone(18, 18);
    first.AddZone(36, 36);
    first.ZoneBoundary_andExits();
    first.activeZone = first.zones[0].get();
    for(int i = 0; i<first.Number_ofZones(); i++) {
        if(i == 0) { first.zones[i]->ResourcePopulate(15, ResourceType::TREE); }
        else if(i == 1) {
            //build unbreakable stone cave walls
            first.zones[i]->ResourcePopulate(8, ResourceType::STONE);
            first.zones[i]->ResourcePopulate(3, ResourceType::IRON);
        }
        else if(i == 2) {
            //build a cavern
            first.zones[i]->ResourcePopulate(15, ResourceType::TREE);
            first.zones[i]->ResourcePopulate(5, ResourceType::STONE);
        }
        else if(i == 3) {
            //build shop tiles and walls
        }
        else if(i == 4) {
            //build dungeon walls & rooms
        }
    }
}
