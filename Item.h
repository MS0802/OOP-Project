#pragma once
#include<string>
#include<memory>

class Player;

enum class ItemType {
    UTILITY,
    POTION,
    WEAPON,
    TOOL
};

class Item {
    protected:
        std::string name;
        ItemType type;
        std::string id;
        size_t stackSize;

        Item(const std::string& itemName, ItemType type, std::string ID, int StackSize);
        Item(ItemType type);
    public:
        virtual ~Item() {}
        
        std::string Name() const; //will probably use in render for inventory display
        std::string ID() const;
        size_t StackSize() const;
        ItemType Type() const;
        
        virtual void use(Player& player) = 0;
};

struct ItemStack {
    std::unique_ptr<Item> item;
    size_t size;
    ItemStack(std::unique_ptr<Item> item, size_t size);
};
