#pragma once
#include"Item.h"
#include<vector>

class Tool : public Item {
    protected:
        double durability;
        std::vector<std::string> canBreakIDs; // Store IDs instead of unique_ptrs
    public:
        Tool(const std::string& itemName, std::string ID, int StackSize, double Durability, const std::vector<std::string>& CanBreakIDs);
        Tool(const Tool& other);
        Tool();
        
        void use(Player& player) override;
        std::unique_ptr<Item> clone() const override;
};
