#include"Tool.h"
#include"Player.h"

Tool::Tool(const std::string& ToolName, double Durability, const std::vector<std::string>& CanBreak, std::vector<ItemStack>& Recipe) : 
Item(ToolName, ItemType::TOOL, 1), durability(Durability), canBreak(CanBreak), recipe() {
    recipe.resize(Recipe.size());
    for(int i = 0; i<recipe.size(); i++) { recipe[i] = Recipe[i]; }
}

Tool::Tool(const Tool& other) : 
Item(other), durability(other.durability), canBreak(other.canBreak) {}

Tool::Tool() : 
Item(ItemType::TOOL), durability(0), canBreak() {}

void Tool::use(Player& player) {
    //data
}

std::unique_ptr<Item> Tool::clone() const {
    return std::make_unique<Tool>(*this);
}
