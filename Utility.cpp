#include"Utility.h"
#include"Player.h"

Utility::Utility(const std::string& ItemName, std::string ID, int stackSize, std::vector<std::unique_ptr<Item>> canCraft) : 
Item(ItemName, ItemType::UTILITY, ID, stackSize), can_Craft(canCraft) {}

Utility::Utility(const std::string& ItemName, std::string ID, int stackSize) : 
Item(ItemName, ItemType::UTILITY, ID, stackSize), can_Craft() {}

Utility::Utility() : Item(ItemType::UTILITY), can_Craft() {}

void Utility::use(Player& player) {
    //logic left
}
