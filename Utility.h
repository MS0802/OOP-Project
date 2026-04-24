#pragma once
#include"Item.h"
#include<vector>

class Utility : public Item {
    protected:
        std::vector<std::string> canCraftIDs; // Store IDs instead of unique_ptrs
    public:
        Utility(const std::string& ItemName, std::string ID, int stackSize, const std::vector<std::string>& canCraftIDs);
        Utility(const std::string& ItemName, std::string ID, int stackSize);
        Utility(const Utility& other);
        Utility();

        void use(Player& player) override;
        std::unique_ptr<Item> clone() const override;
};
