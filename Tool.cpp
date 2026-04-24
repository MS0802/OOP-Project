#include"Tool.h"
#include"Player.h"

Tool::Tool(const std::string& ToolName, std::string ID, int StackSize, double Durability, const std::vector<std::string>& CanBreakIDs) : 
Item(ToolName, ItemType::TOOL, ID, StackSize), durability(Durability), canBreakIDs(CanBreakIDs) {}

Tool::Tool(const Tool& other) : 
Item(other), durability(other.durability), canBreakIDs(other.canBreakIDs) {}

Tool::Tool() : 
Item(ItemType::TOOL), durability(0), canBreakIDs() {}

void Tool::use(Player& player) {
    //data
}

std::unique_ptr<Item> Tool::clone() const {
    return std::make_unique<Tool>(*this);
}
