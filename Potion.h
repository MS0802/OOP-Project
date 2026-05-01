#pragma once
#include"Item.h"
#include"Effect.h"

class Potion : public Item {
    protected:
        Effect potionEffect;
    public:
        Potion(const std::string& name, EffectType effectType, double duration, bool canGiveOthers);
        Potion(EffectType type);

        void use(Player& player) override;
        std::unique_ptr<Item> clone() const override;

        static Potion SelfHealing();
        static Potion InflictHealing();
        static Potion Poison();
        static Potion Strength();
        static Potion Weakness();
        static Potion Resistance();
        static Potion Vulnerability();
};
