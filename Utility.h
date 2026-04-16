#pragma once
#include"Item.h"
#include<vector>

class Utility : public Item {
    protected:
        std::vector<std::unique_ptr<Item>> can_Craft;
    public:
        Utility(const std::string& ItemName, std::string ID, int stackSize, std::vector<std::unique_ptr<Item>> canCraft);
        Utility(const std::string& ItemName, std::string ID, int stackSize);
        Utility();

        void use(Player& player) override;
};
