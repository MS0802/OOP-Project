#pragma once
#include"Enemy.h"

class Boss : public Enemy {
    protected:
        const int regenerationFactor;
    public:
        Boss(std::string name, int startX, int startY, int hp, int def, std::array<std::unique_ptr<Item>, 3> drops, int XP, int damage, int Regeneration_Factor);
        Boss(const Boss& other);

        char getSymbol()const override;

        void specialAttack(Entity& target);

        std::array<std::unique_ptr<Item>, 3> dropItem() override;
};
