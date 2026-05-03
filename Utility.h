#pragma once
#include"Item.h"
#include<vector>

class Utility : public Item {
    protected:
        std::vector<std::string> canCraft;
    public:
        Utility(const std::string& ItemName, int stackSize, const std::vector<std::string>& CanCraft);
        Utility(const std::string& ItemName, int stackSize);
        Utility(const Utility& other);
        Utility();

        std::unique_ptr<Item> clone() const override;

        static Utility Wood();
        static Utility Stone();
        static Utility Iron();
        static Utility Titanium();
        static Utility Etherite();
};
