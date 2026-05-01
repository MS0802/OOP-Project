#include"Potion.h"
#include"Player.h"

Potion::Potion(const std::string& name, EffectType effectType, double duration, bool canGiveOthers) : 
Item(name, ItemType::POTION, 1), potionEffect(effectType, duration, canGiveOthers) {}

Potion::Potion(EffectType type) : 
Item(ItemType::POTION), potionEffect(type, 0, false) {}

void Potion::use(Player& player) {
    //logic left...
}

std::unique_ptr<Item> Potion::clone() const {
    return std::make_unique<Potion>(*this);
}

Potion Potion::SelfHealing() { return Potion("Healing Potion", EffectType::HEAL, 10, false); }
Potion Potion::InflictHealing() { return Potion("Inflicting Healing Potion", EffectType::HEAL, 1, true); }
Potion Potion::Poison() { return Potion("Poison Potion", EffectType::POISON, 1, true); }
Potion Potion::Strength() { return Potion("Strength Potion", EffectType::STRENGTH, 10, false); }
Potion Potion::Weakness() { return Potion("Weakness Potion", EffectType::WEAKNESS, 1, true); }
Potion Potion::Resistance() { return Potion("Resistance Potion", EffectType::RESISTANCE, 10, false); }
Potion Potion::Vulnerability() { return Potion("Vulnerability Potion", EffectType::VULNERABLE, 1, true); }
