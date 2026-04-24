#include"Potion.h"
#include"Player.h"

Potion::Potion(const std::string& name, const std::string& id, EffectType effectType, double duration, bool canGiveOthers) : 
Item(name, ItemType::POTION, id, 1), potionEffect(effectType, duration, canGiveOthers) {}

Potion::Potion(EffectType type) : 
Item(ItemType::POTION), potionEffect(type, 0, false) {}

void Potion::use(Player& player) {
    //logic left...
}

std::unique_ptr<Item> Potion::clone() const {
    return std::make_unique<Potion>(*this);
}
