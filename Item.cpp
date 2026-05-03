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

ItemStack::ItemStack(std::unique_ptr<Item> Item, size_t Amount) : 
item(std::move(Item)), amount(Amount) {}

ItemStack::ItemStack(const ItemStack& other) : 
item(other.item ? other.item->clone() : nullptr), amount(other.amount) {}

ItemStack::ItemStack() : item(nullptr), amount(0) {}

void ItemStack::operator=(const ItemStack& other) {
    item = (other.item ? other.item->clone() : nullptr);
    amount = other.amount;
}
