#include"Weapon.h"
#include"Player.h"

Weapon::Weapon(const std::string& name, const std::string& id, int dmg, int durability, const std::vector<ItemStack>& Recipie) : 
Item(name, ItemType::WEAPON, id, 1), damage(dmg), durability(durability), Recipie(Recipie) {}
Weapon::Weapon() : 
Item(ItemType::WEAPON), damage(0), durability(0), Recipie() {}

void Weapon::use(Player& player) {
    //logic left...
}

int Weapon::Damage() const { return damage; }
