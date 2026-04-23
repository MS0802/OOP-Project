#pragma once
#include"Enemy.h"

class Boss : public Enemy {
    protected:
        const int regenerationFactor;
    public:
        Boss(std::string name, int startX, int startY, size_t hp, size_t MaxHP, int def, std::array<std::unique_ptr<Item>, 3> drops, size_t XP, int damage, int Regeneration_Factor);
        Boss(const Boss& other);

        char getSymbol()const override;

        void specialAttack(Entity& target);

        std::array<std::unique_ptr<Item>, 3> dropItem() override;
};
