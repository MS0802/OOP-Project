#include"Utility.h"
#include"Player.h"

Utility::Utility(const std::string& ItemName, std::string ID, int stackSize, const std::vector<std::string>& canCraftIDs) : 
Item(ItemName, ItemType::UTILITY, ID, stackSize), canCraftIDs(canCraftIDs) {}

Utility::Utility(const std::string& ItemName, std::string ID, int stackSize) : 
Item(ItemName, ItemType::UTILITY, ID, stackSize), canCraftIDs() {}

Utility::Utility(const Utility& other) : 
Item(other), canCraftIDs(other.canCraftIDs) {}

Utility::Utility() : Item(ItemType::UTILITY), canCraftIDs() {}

void Utility::use(Player& player) {
    //logic left
}

std::unique_ptr<Item> Utility::clone() const {
    return std::make_unique<Utility>(*this);
}
