#include"Weapon.h"
#include"Player.h"

Weapon::Weapon(const std::string& name, int dmg, int durability, const std::vector<ItemStack>& Recipe) : 
Item(name, ItemType::WEAPON, 1), damage(dmg), durability(durability), recipe(Recipe.size()) {
    for(int i = 0; i<Recipe.size(); i++) { recipe[i] = Recipe[i];  }
}

Weapon::Weapon(const Weapon& other) : 
Item(other), damage(other.damage), durability(other.durability), recipe(other.recipe) {}

Weapon::Weapon() : 
Item(ItemType::WEAPON), damage(0), durability(0), recipe() {}

void Weapon::use(Player& player) {
    //logic left...
}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}

int Weapon::Damage() const { return damage; }
