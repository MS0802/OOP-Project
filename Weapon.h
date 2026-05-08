#pragma once
#include"Item.h"
#include<vector>

constexpr int DefaultSwordDmg = 10;
constexpr int DefaultSpearDmg = 9;

constexpr int DefaultSwordHP = 9;
constexpr int DefaultSpearHP = 10;

class Weapon : public Item {
    protected:
        int damage;
        int durability;
        std::vector<ItemStack> recipe;
    public:
        Weapon(const std::string& name, int Damage, int durability, const std::vector<ItemStack>& Recipe);
        Weapon(const Weapon& other);
        Weapon();

        std::unique_ptr<Item> clone() const override;
        int Damage() const;
        std::vector<ItemStack> Recipe() const;

        static Weapon WoodenSword();
        static Weapon WoodenSpear();
        static Weapon StoneSword();
        static Weapon StoneSpear();
        static Weapon IronSword();
        static Weapon IronSpear();
        static Weapon TitaniumSword();
        static Weapon TitaniumSpear();
        static Weapon EtheriteSword();
        static Weapon EtheriteSpear();
};
