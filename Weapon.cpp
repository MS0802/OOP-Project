#include"Weapon.h"

Weapon::Weapon(const std::string& name, int Damage, int durability, const std::vector<ItemStack>& Recipe) : 
Item(name, ItemType::WEAPON, 1), damage(Damage), durability(durability), recipe(Recipe.size()) {
    for(int i = 0; i<Recipe.size(); i++) { recipe[i] = Recipe[i];  }
}

Weapon::Weapon(const Weapon& other) : 
Item(other), damage(other.damage), durability(other.durability), recipe(other.recipe) {}

Weapon::Weapon() : 
Item(ItemType::WEAPON), damage(0), durability(0), recipe() {}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}

int Weapon::Damage() const { return damage; }

Weapon Weapon::WoodenSword() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Wooden Sword", DefaultSwordDmg, DefaultSwordHP, Recipe);
}

Weapon Weapon::WoodenSpear() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Wooden Spear", DefaultSpearDmg, DefaultSpearHP, Recipe);
}

Weapon Weapon::StoneSword() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Stone Sword", DefaultSwordDmg*2, DefaultSwordHP*2, Recipe);
}

Weapon Weapon::StoneSpear() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Stone Spear", DefaultSpearDmg*2, DefaultSpearHP*2, Recipe);
}

Weapon Weapon::IronSword() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Iron Sword", DefaultSwordDmg*4, DefaultSwordHP*4, Recipe);
}

Weapon Weapon::IronSpear() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Iron Spear", DefaultSpearDmg*4, DefaultSpearHP*4, Recipe);
}

Weapon Weapon::TitaniumSword() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Titanium Sword", DefaultSwordDmg*5, DefaultSwordHP*5, Recipe);
}

Weapon Weapon::TitaniumSpear() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Titanium Spear", DefaultSpearDmg*5, DefaultSpearHP*5, Recipe);
}

Weapon Weapon::EtheriteSword() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Etherite Sword", DefaultSwordDmg*7, DefaultSwordHP*6, Recipe);
}

Weapon Weapon::EtheriteSpear() {
    std::vector<ItemStack> Recipe({});
    return Weapon("Etherite Spear", DefaultSpearDmg*7, DefaultSpearHP*6, Recipe);
}
