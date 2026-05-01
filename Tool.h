#pragma once
#include"Item.h"
#include<vector>

class Tool : public Item {
    protected:
        double durability;
        std::vector<std::string> canBreak; // Store Names instead of unique_ptrs
        std::vector<ItemStack> recipe;
    public:
        Tool(const std::string& itemName, double Durability, const std::vector<std::string>& CanBreak, std::vector<ItemStack>& Recipie);
        Tool(const Tool& other);
        Tool();
        
        void use(Player& player) override;
        std::unique_ptr<Item> clone() const override;
};
