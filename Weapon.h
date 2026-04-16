#pragma once
#include"Item.h"
#include<vector>

class Weapon : public Item {
    protected:
        int damage;
        int durability;
        std::vector<ItemStack> Recipie;
    public:
        Weapon(const std::string& name, const std::string& id, int dmg, int durability, const std::vector<ItemStack>& Recipie);
        Weapon();

        void use(Player& player) override;
        int Damage() const;
};
