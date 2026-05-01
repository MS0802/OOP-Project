#pragma once
#include"Item.h"
#include<vector>

class Utility : public Item {
    protected:
        std::vector<std::string> canCraft; // Store Names instead of unique_ptrs
    public:
        Utility(const std::string& ItemName, int stackSize, const std::vector<std::string>& CanCraft);
        Utility(const std::string& ItemName, int stackSize);
        Utility(const Utility& other);
        Utility();

        void use(Player& player) override;
        std::unique_ptr<Item> clone() const override;
};
