#include"Tool.h"
#include"Breakable.h"
#include"Utility.h"

Tool::Tool(const std::string& ToolName, int Durability, const std::vector<ResourceType>& CanBreak, std::vector<ItemStack>& Recipe) : 
Item(ToolName, ItemType::TOOL, 1), durability(Durability), canBreak(CanBreak), recipe() {
    recipe.resize(Recipe.size());
    for(int i = 0; i<recipe.size(); i++) { recipe[i] = Recipe[i]; }
}

Tool::Tool(const Tool& other) : 
Item(other), durability(other.durability), canBreak(other.canBreak) {}

Tool::Tool() : 
Item(ItemType::TOOL), durability(0), canBreak() {}

std::unique_ptr<Item> Tool::clone() const {
    return std::make_unique<Tool>(*this);
}

Tool Tool::WoodenAxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 4)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::TREE,
        ResourceType::BARREL1,
        ResourceType::BARREL0
    });
    return Tool("Wooden Axe", DefaultToolHP, CanBreak, Recipe);
}

Tool Tool::WoodenPickaxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 4)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::STONE
    });
    return Tool("Wooden Pickaxe", DefaultToolHP, CanBreak, Recipe);
}

Tool Tool::StoneAxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Stone()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::TREE,
        ResourceType::BARREL1,
        ResourceType::BARREL0,
        ResourceType::BARREL2
    });
    return Tool("Stone Axe", DefaultToolHP*2, CanBreak, Recipe);
}

Tool Tool::StonePickaxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Stone()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::STONE,
        ResourceType::IRON
    });
    return Tool("Stone Pickaxe", DefaultToolHP*2, CanBreak, Recipe);
}

Tool Tool::IronAxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Iron()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::TREE,
        ResourceType::BARREL1,
        ResourceType::BARREL0,
        ResourceType::BARREL2,
        ResourceType::BARREL3
    });
    return Tool("Iron Axe", DefaultToolHP*4, CanBreak, Recipe);
}

Tool Tool::IronPickaxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Iron()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::STONE,
        ResourceType::IRON,
        ResourceType::TITANIUM
    });
    return Tool("Iron Pickaxe", DefaultToolHP*4, CanBreak, Recipe);
}

Tool Tool::TitaniumAxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Titanium()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::TREE,
        ResourceType::BARREL1,
        ResourceType::BARREL0,
        ResourceType::BARREL2,
        ResourceType::BARREL3,
        ResourceType::BARREL4
    });
    return Tool("Titanium Axe", DefaultToolHP*5, CanBreak, Recipe);
}

Tool Tool::TitaniumPickaxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Titanium()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::STONE,
        ResourceType::IRON,
        ResourceType::TITANIUM
    });
    return Tool("Titanium Pickaxe", DefaultToolHP*5, CanBreak, Recipe);
}

Tool Tool::EtheriteAxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Etherite()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::TREE,
        ResourceType::BARREL1,
        ResourceType::BARREL0,
        ResourceType::BARREL2,
        ResourceType::BARREL3,
        ResourceType::BARREL4,
        ResourceType::BARREL5
    });
    return Tool("Etherite Axe", DefaultToolHP*6, CanBreak, Recipe);
}

Tool Tool::EtheritePickaxe() {
    std::vector<ItemStack> Recipe({
        ItemStack(std::make_unique<Utility>(Utility::Wood()), 2),
        ItemStack(std::make_unique<Utility>(Utility::Etherite()), 2)
    });
    std::vector<ResourceType> CanBreak({
        ResourceType::STONE,
        ResourceType::IRON,
        ResourceType::TITANIUM
    });
    return Tool("Etherite Pickaxe", DefaultToolHP*6, CanBreak, Recipe);
}

std::vector<ItemStack> Tool::Recipe() const { return recipe; }
std::vector<ResourceType> Tool::CanBreak() const { return canBreak; }
