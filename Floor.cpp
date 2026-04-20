#include"Floor.h"

Floor::Floor(const std::vector<Zone>& Zones, int FloorNumber, std::unique_ptr<Zone> ActiveZone) : 
zones(Zones), floorNumber(FloorNumber), activeZone(std::move(ActiveZone)) {}

Floor::Floor(int FloorNumber) : 
floorNumber(FloorNumber), zones(), activeZone(nullptr) {}

std::unique_ptr<Zone>& Floor::ActiveZone() { return std::move(activeZone); }
int Floor::FloorNumber() const { return floorNumber; }
