#include"Potion.h"
#include"Player.h"

Potion::Potion(const std::string& name, const std::string& id, EffectType effectType, double duration) : 
Item(name, ItemType::POTION, id, 1), potionEffect(effectType, duration) {}
Potion::Potion(EffectType type) : 
Item(ItemType::POTION), potionEffect(type, 0) {}

void Potion::use(Player& player) {
    //logic left...
}
