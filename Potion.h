#pragma once
#include"Item.h"
#include"Effect.h"

class Entity;  // Forward declaration

class Potion : public Item {
    protected:
        Effect potionEffect;
    public:
        Potion(const std::string& name, EffectType effectType, double duration, bool canGiveOthers);
        Potion(EffectType type);

        void use(Player& player) override;
        void use(Entity* e);
        std::unique_ptr<Item> clone() const override;

        static Potion SelfHealing();
        static Potion InflictHealing();
        static Potion Poison();
        static Potion Strength();
        static Potion Weakness();
        static Potion Resistance();
        static Potion Vulnerability();

        bool operator==(const Potion& other) {
            return (potionEffect.Can_Give() == other.potionEffect.Can_Give() && potionEffect.Effect_Give() == other.potionEffect.Effect_Give());
        }
};
