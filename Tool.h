#pragma once
#include"Item.h"
#include<vector>

constexpr int DefaultToolHP = 10;

enum class ResourceType;

class Breakable;

class Tool : public Item {
    protected:
        int durability;
        std::vector<ResourceType> canBreak;
        std::vector<ItemStack> recipe;
    public:
        Tool(const std::string& itemName, int Durability, const std::vector<ResourceType>& CanBreak, std::vector<ItemStack>& Recipie);
        Tool(const Tool& other);
        Tool();
        
        std::unique_ptr<Item> clone() const override;

        std::vector<ItemStack> Recipe() const;
        std::vector<ResourceType> CanBreak() const;

        static Tool WoodenAxe();
        static Tool WoodenPickaxe();
        static Tool StoneAxe();
        static Tool StonePickaxe();
        static Tool IronAxe();
        static Tool IronPickaxe();
        static Tool TitaniumAxe();
        static Tool TitaniumPickaxe();
        static Tool EtheriteAxe();
        static Tool EtheritePickaxe();
};
