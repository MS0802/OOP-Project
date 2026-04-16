#include"Tool.h"
#include"Player.h"

Tool::Tool(const std::string& ToolName, std::string ID, int StackSize, double Durability, const std::vector<std::unique_ptr<Item>>& Can_Break) : 
Item(ToolName, ItemType::TOOL, ID, StackSize), durability(Durability), can_break(Can_Break) {}

Tool::Tool() : 
Item(ItemType::TOOL), durability(0), can_break() {}

void Tool::use(Player& player) {
    //data
}
