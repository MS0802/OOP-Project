#include"Weapon.h"
#include"Player.h"

Weapon::Weapon(const std::string& name, const std::string& id, int dmg, int durability, const std::vector<ItemStack>& Recipe) : 
Item(name, ItemType::WEAPON, id, 1), damage(dmg), durability(durability), Recipe(Recipe) {}

Weapon::Weapon(const Weapon& other) : 
Item(other), damage(other.damage), durability(other.durability), Recipe(other.Recipe) {}

Weapon::Weapon() : 
Item(ItemType::WEAPON), damage(0), durability(0), Recipe() {}

void Weapon::use(Player& player) {
    //logic left...
}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}

int Weapon::Damage() const { return damage; }
