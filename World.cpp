#include"World.h"
#include"Enemy.h"
#include"Boss.h"

World::World() : 
floors(5), totalFloors(5), activeFloor(nullptr) {}

void World::SetActiveFloor(size_t FloorNumber) {
    if(FloorNumber == 0 || FloorNumber > totalFloors) {
        activeFloor = nullptr;
        return;
    }
    activeFloor = floors[FloorNumber - 1].get();
}

bool World::NextFloor() {
    if(!activeFloor) {
        return false;
    }
    int next = activeFloor->FloorNumber() + 1;
    if(next > static_cast<int>(totalFloors)) {
        return false;
    }
    SetActiveFloor(next);
    return true;
}

int World::TotalFloors() const {
    return static_cast<int>(totalFloors);
}

void World::InitializeFloor1() {
    auto floor = std::make_unique<Floor>(1, 2);
    floor->AddZone(18, 18);
    floor->AddZone(24, 24);
    floor->ZoneBoundary_andExits();
    floor->activeZone = floor->zones[0].get();
    for(int i = 0; i<floor->Number_ofZones(); i++) {
        if(i == 0) {
            floor->zones[i]->ResourcePopulate(8, ResourceType::TREE);
            floor->zones[i]->ResourcePopulate(6, ResourceType::BARREL0);
        }
        else {
            floor->zones[i]->ResourcePopulate(15, ResourceType::TREE);
            floor->zones[i]->ResourcePopulate(4, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(5, ResourceType::BARREL1);
        }
    }
    floors[0] = std::move(floor);
}

void World::InitializeFloor2() {
    auto floor = std::make_unique<Floor>(2, 2);
    floor->AddZone(24, 24);
    floor->AddZone(24, 24);
    floor->ZoneBoundary_andExits();
    floor->activeZone = floor->zones[0].get();
    for(int i = 0; i<floor->Number_ofZones(); i++) {
        if(i == 0) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(8, ResourceType::STONE);
            floor->zones[i]->EntityPopulate(4, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Normal(Px, Py)); 
            });
        }
        else {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(8, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(4, ResourceType::IRON);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Normal(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
        }
    }
    floors[1] = std::move(floor);
}

void World::InitializeFloor3() {
    auto floor = std::make_unique<Floor>(3, 3);
    floor->AddZone(24, 24);
    floor->AddZone(24, 24);
    floor->AddZone(30, 30);
    floor->ZoneBoundary_andExits();
    floor->activeZone = floor->zones[0].get();
    for(int i = 0; i<floor->Number_ofZones(); i++) {
        if(i == 0) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(8, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(3, ResourceType::IRON);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Poison(Px, Py)); 
            });
        }
        else if(i == 1) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(8, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(3, ResourceType::IRON);
            floor->zones[i]->ResourcePopulate(5, ResourceType::BARREL2);
            floor->zones[i]->EntityPopulate(3, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Poison(Px, Py)); 
            });
        }
        else {
            floor->zones[i]->WallPopulate(6);
            floor->zones[i]->EntityPopulate(3, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Poison(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(1, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Boss>(Boss::PoisonousStoneGolem(Px, Py)); 
            });
        }
    }
    floors[2] = std::move(floor);
}

void World::InitializeFloor4() {
    auto floor = std::make_unique<Floor>(4, 3);
    floor->AddZone(24, 24);
    floor->AddZone(24, 24);
    floor->AddZone(24, 24);
    floor->ZoneBoundary_andExits();
    floor->activeZone = floor->zones[0].get();
    for(int i = 0; i<floor->Number_ofZones(); i++) {
        if(i == 0) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(10, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(4, ResourceType::IRON);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Healer(Px, Py)); 
            });
        }
        else if(i == 1) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(10, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(2, ResourceType::TITANIUM);
            floor->zones[1]->ResourcePopulate(3, ResourceType::BARREL3);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Healer(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Poison(Px, Py)); 
            });
        }
        else {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(10, ResourceType::STONE);
            floor->zones[i]->ResourcePopulate(3, ResourceType::TITANIUM);
            floor->zones[i]->ResourcePopulate(3, ResourceType::BARREL4);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Poison(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Healer(Px, Py)); 
            });
        }
    }
    floors[3] = std::move(floor);
}

void World::InitializeFloor5() {
    auto floor = std::make_unique<Floor>(5, 4);
    floor->AddZone(24, 24);
    floor->AddZone(18, 18);
    floor->AddZone(24, 24);
    floor->AddZone(30, 30);
    floor->ZoneBoundary_andExits();
    floor->activeZone = floor->zones[0].get();
    for(int i = 0; i<floor->Number_ofZones(); i++) {
        if(i == 0) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Wizard(Px, Py)); 
            });
        }
        else if(i == 1) {
            floor->zones[i]->ResourcePopulate(8, ResourceType::TREE);
            floor->zones[i]->EntityPopulate(1, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Healer(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Poison(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Wizard(Px, Py)); 
            });
        }
        else if(i == 2) {
            floor->zones[i]->WallPopulate(5);
            floor->zones[i]->ResourcePopulate(3, ResourceType::BARREL4);
            floor->zones[i]->ResourcePopulate(2, ResourceType::BARREL5);
            
            floor->zones[i]->EntityPopulate(3, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Tank(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Healer(Px, Py)); 
            });
        }
        else {
            floor->zones[i]->WallPopulate(6);
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Healer(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(2, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Enemy>(Enemy::Wizard(Px, Py)); 
            });
            floor->zones[i]->EntityPopulate(1, [](int Px, int Py) -> std::unique_ptr<Entity> { 
                return std::make_unique<Boss>(Boss::EtheriteProtector(Px, Py)); 
            });
        }
    }
    floors[4] = std::move(floor);
}

void World::InitializeFloors() {
    InitializeFloor1();
    InitializeFloor2();
    InitializeFloor3();
    InitializeFloor4();
    InitializeFloor5();
}
