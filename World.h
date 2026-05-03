#pragma once
#include"Floor.h"
#include"Player.h"
#include<fstream>
#include<sstream>

class World {
    private:
        void InitializeFloor1();
        void InitializeFloor2();
        void InitializeFloor3();
        void InitializeFloor4();
        void InitializeFloor5();
    protected:
        std::vector<std::unique_ptr<Floor>> floors;
        const size_t totalFloors;
        Floor* activeFloor;
    public:
        World();

        void InitializeFloors();
        void SetActiveFloor(size_t FloorNumber);
};
