#pragma once
#include"Entity.h"
#include<vector>
#include<memory>
#include"Item.h"

const int DefaultPlayerDamage = 1;
const int MAX_INVENTORY_SIZE = 10;

class Player : public Entity {
    private:
        std::vector<ItemStack> inventory;
        std::unique_ptr<Item> on_Hand;
        int xp;
    public:
        Player(const std::string& Name, int startX, int startY, int HP, int Defense, int XP);
        Player();

        void update(int pX, int pY) override;

        char getSymbol() const override;

        int Damage() const override;
        void attack(Entity& target);
        void useItem(int index);
        void addItem(std::unique_ptr<Item> item, int amount); //Takes ownership of items using move
        void equipItem(int index);
        void dropItem(int index);
        void displayInventory() const;
        Item* getItemAt(int index);

        void Effect_Action(EffectType type) override;

        int XP() const;
        int InventorySize() const;
        bool isInventoryFull() const;
};
