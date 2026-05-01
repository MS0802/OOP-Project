#include"Item.h"

Item::Item(const std::string& itemName, ItemType type, const size_t& StackSize) : 
name(itemName), type(type), stackSize(StackSize) {}

Item::Item(ItemType type) : 
type(type), name(), stackSize(0) {}

Item::Item(const Item& other) : 
type(other.Type()), name(other.Name()), stackSize(other.StackSize()) {}

std::string Item::Name() const { return name; }
size_t Item::StackSize() const { return stackSize; }
ItemType Item::Type() const { return type; }

ItemStack::ItemStack(std::unique_ptr<Item> item, size_t size) : 
item(std::move(item)), size(size) {}

ItemStack::ItemStack(const ItemStack& other) : 
item(other.item ? other.item->clone() : nullptr), size(other.size) {}

void ItemStack::operator=(const ItemStack& other) {
    item = (other.item ? other.item->clone() : nullptr);
    size = other.size;
}
