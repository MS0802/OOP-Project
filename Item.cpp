#include"Item.h"

Item::Item(const std::string& itemName, ItemType type, std::string ID, const size_t& StackSize) : 
name(itemName), type(type), id(ID), stackSize(StackSize) {}

Item::Item(ItemType type) : 
type(type), name(), id(), stackSize(0) {}

std::string Item::Name() const { return name; }
std::string Item::ID() const { return id; }
size_t Item::StackSize() const { return stackSize; }
ItemType Item::Type() const { return type; }

ItemStack::ItemStack(std::unique_ptr<Item> item, size_t size) : 
item(std::move(item)), size(size) {}
