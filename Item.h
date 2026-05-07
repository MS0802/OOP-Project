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
        const size_t stackSize;

        Item(const std::string& itemName, ItemType type, const size_t& StackSize);
        Item(ItemType type);
        Item(const Item& other);
    public:
        virtual ~Item() {}
        
        std::string Name() const;
        size_t StackSize() const;
        ItemType Type() const;
        
        virtual void use(Player& player) {}  // Default implementation does nothing
        virtual std::unique_ptr<Item> clone() const = 0;
};

struct ItemStack {
    std::unique_ptr<Item> item;
    size_t amount;
    ItemStack(std::unique_ptr<Item> Item, size_t Amount);
    ItemStack(const ItemStack& other);
    ItemStack();
    void operator=(const ItemStack& other);
};
