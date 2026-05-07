#pragma once
#include"World.h"
#include"Player.h"
#include<memory>
#include<string>

enum class GameAction {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    ATTACK,
    BREAK_RESOURCE,
    USE_ITEM,
    EQUIP_ITEM,
    DROP_ITEM,
    OPEN_INVENTORY,
    CRAFT,
    THROW_POTION,
    NONE
};

class Game {
    private:
        std::unique_ptr<World> world;
        std::unique_ptr<Player> player;
        Zone* currentZone;
        int currentFloor;
        int enemyUpdateCounter;
        int playerActionCounter;
        
        Entity* targetEnemy();
        void updateEnemies();
        void craft();
        void throwPotion(int itemIndex);
        void checkCollisions(int newX, int newY);
        bool canMoveTo(int x, int y) const;
        bool canMoveTo(int x, int y, const Entity* ignoreEntity) const;
        
    public:
        Game();
        
        void initialize();
        void tick(GameAction action, int itemIndex = -1);
        
        // Display methods
        void displayZone() const;
        void displayInventory() const;
        void displayPlayerStats() const;
        
        // Getters
        Player* getPlayer() const;
        Zone* getCurrentZone() const;
        int getCurrentFloor() const;
};
