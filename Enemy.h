#pragma once
#include"Entity.h"
#include"Item.h"
#include<memory>
#include<array>
#include<random>

class Enemy : public Entity {
    protected:
        std::array<std::unique_ptr<Item>, 3> drops;
        int xp;
        int damage;
        const int initialDamage;
    public:
        Enemy(std::string Name, int startX, int startY, int HP, int MaxHP, int Defense, std::array<std::unique_ptr<Item>, 3> Drops, int XP, int Damage);
        Enemy();
        void update(int x, int y) override;
        char getSymbol() const override;

        void attack(Entity& target);
        int Damage() const override;
        int Initial_Damage() const;
        size_t XP() const;

        void Effect_Action() override;

        virtual std::array<std::unique_ptr<Item>, 3> dropItem();
};
