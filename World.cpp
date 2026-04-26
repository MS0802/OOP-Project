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
    first.AddZone(50, 50);
    
}
