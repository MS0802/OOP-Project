#include"World.h"

World::World() : 
floors(7), totalFloors(7), activeFloor(nullptr) {}

void World::SetActiveFloor(size_t FloorNumber) {
    FloorNumber--;
    FloorNumber = FloorNumber%7;
    activeFloor; 
}
