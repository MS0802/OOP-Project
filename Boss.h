#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(int startX, int startY, int health, int atk);

    char getSymbol()const override;
    void specialAttack(Entity& target);
    std::unique_ptr<Item> dropItem() override;//Always drops something rare (cant be nullptr by default)
};

#endif
