#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(int startX, int startY, int health, int atk);

    void specialMove(Entity& target);
};

#endif
