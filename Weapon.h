#pragma once
#include"Item.h"
#include<vector>

class Weapon : public Item {
    protected:
        int damage;
        int durability;
        std::vector<ItemStack> recipe;
    public:
        Weapon(const std::string& name, int dmg, int durability, const std::vector<ItemStack>& Recipe);
        Weapon(const Weapon& other);
        Weapon();

        void use(Player& player) override;
        std::unique_ptr<Item> clone() const override;
        int Damage() const;
};
