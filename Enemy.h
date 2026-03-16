#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
protected:
    int attackPower;

public:
    Enemy(int startX, int startY, int health, int atk);

    void update() override;
    void attack(Entity& target);
};

#endif
