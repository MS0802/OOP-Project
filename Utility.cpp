#include"Utility.h"
#include"Player.h"

Utility::Utility(const std::string& ItemName, int stackSize, const std::vector<std::string>& CanCraft) : 
Item(ItemName, ItemType::UTILITY, stackSize), canCraft(CanCraft) {}

Utility::Utility(const std::string& ItemName, int stackSize) : 
Item(ItemName, ItemType::UTILITY, stackSize), canCraft() {}

Utility::Utility(const Utility& other) : 
Item(other), canCraft(other.canCraft) {}

Utility::Utility() : Item(ItemType::UTILITY), canCraft() {}

void Utility::use(Player& player) {
    //logic left
}

std::unique_ptr<Item> Utility::clone() const {
    return std::make_unique<Utility>(*this);
}
