#include"Utility.h"

Utility::Utility(const std::string& ItemName, int stackSize, const std::vector<std::string>& CanCraft) : 
Item(ItemName, ItemType::UTILITY, stackSize), canCraft(CanCraft) {}

Utility::Utility(const std::string& ItemName, int stackSize) : 
Item(ItemName, ItemType::UTILITY, stackSize), canCraft() {}

Utility::Utility(const Utility& other) : 
Item(other), canCraft(other.canCraft) {}

Utility::Utility() : Item(ItemType::UTILITY), canCraft() {}

std::unique_ptr<Item> Utility::clone() const {
    return std::make_unique<Utility>(*this);
}

Utility Utility::Wood() {
    std::vector<std::string> CanCraft({});
    return Utility("Wood", 100, CanCraft);
}

Utility Utility::Stone() {
    std::vector<std::string> CanCraft({});
    return Utility("Stone", 100, CanCraft);
}

Utility Utility::Iron() {
    std::vector<std::string> CanCraft({});
    return Utility("Iron", 100, CanCraft);
}

Utility Utility::Titanium() {
    std::vector<std::string> CanCraft({});
    return Utility("Titanium", 100, CanCraft);
}

Utility Utility::Etherite() {
    std::vector<std::string> CanCraft({});
    return Utility("Etherite", 100, CanCraft);
}
