#pragma once
#include"Item.h"
#include<vector>

constexpr int DefaultSwordDmg = 5;
constexpr int DefaultSpearDmg = 4;

constexpr int DefaultSwordHP = 4;
constexpr int DefaultSpearHP = 5;

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
