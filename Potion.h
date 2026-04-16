#pragma once
#include"Item.h"
#include"Effect.h"

class Potion : public Item {
    protected:
        Effect potionEffect;
    public:
        Potion(const std::string& name, const std::string& id, EffectType effectType, double duration);
        Potion(EffectType type);

        void use(Player& player) override;
};
