#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include "Item.h"

const int DefaultPlayerDamage = 1;

class Player : public Entity {
    private:
        std::vector<ItemStack> inventory;
        std::unique_ptr<Item> On_Hand;
        int xp;
    public:
        Player(const std::string& Name, int startX, int startY, size_t HP, size_t MaxHP, int def, int XP);
        Player();

        void update(int pX, int pY) override;

        char getSymbol() const override;

        int Damage() const override;
        void attack(Entity& target);
        void useItem(int index);
        void addItem(std::unique_ptr<Item> item, int amount); //Takes ownership of items using move

        void Effect_Action(EffectType type);

        int XP() const;
        int InventorySize() const;
};
