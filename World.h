#pragma once
#include"Floor.h"
#include"Player.h"

class World {
    private:
        void InitializeFloor1();
    protected:
        std::vector<std::unique_ptr<Floor>> floors;
        const size_t totalFloors;
        Floor* activeFloor;
    public:
        World();

        void InitializeFloors();
        void SetActiveFloor(size_t FloorNumber);
};