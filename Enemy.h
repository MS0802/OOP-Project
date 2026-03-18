#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Item.h"
#include <memory>

class Enemy : public Entity {
protected:
    int attackPower;

public:
    Enemy(int startX, int startY, int health, int atk);

    void update(int X,int Y) override;//Will probably be used to implement player tracking AI
    char getSymbol()const override;


    void attack(Entity& target);
    int getAttackPower()const;

    virtual std::unique_ptr<Item> dropItem();//returns nullptr by default
};

#endif
