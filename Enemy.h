#pragma once
#include"Entity.h"
#include"Item.h"
#include<memory>
#include<array>
#include<random>

class Enemy : public Entity {
    protected:
        std::array<std::unique_ptr<Item>, 3> drops;
        size_t xp;
        int dmg;
    public:
        Enemy(std::string name, int startX, int startY, size_t hp, size_t MaxHP, int def, std::array<std::unique_ptr<Item>, 3> drops, size_t XP, int damage);
        void update(int x, int y) override;
        char getSymbol() const override;

        void attack(Entity& target);
        int Damage() const override;
        int Defense() const override;
        size_t XP() const;

        void Effect_Action() override;


        virtual std::array<std::unique_ptr<Item>, 3> dropItem();
};
