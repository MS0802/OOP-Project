#pragma once
#include"Item.h"
#include<vector>

class Tool : public Item {
    protected:
        double durability;
        std::vector<std::unique_ptr<Item>> can_break;
    public:
        Tool(const std::string& itemName, std::string ID, int StackSize, double Durability, const std::vector<std::unique_ptr<Item>>& Can_Break);
        Tool();
        void use(Player& player) override;
};
