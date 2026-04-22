#pragma once
#include<algorithm>

constexpr int poisonDamage = 2;
constexpr int weaknessValue = 5;
constexpr int vulnerableDefense = 3;

enum class EffectType {
    HEAL,
    POISON,
    POISON_GIVE,
    STRENGTH,
    WEAKNESS,
    WEAKNESS_GIVE,
    RESISTANCE,
    VULNERABLE,
    VULNERABLE_GIVE
};

class Effect {
    protected:
        EffectType type;
        double time;
    public:
        Effect(EffectType type, double time);
        EffectType Effect_Give();
        double& Time();
};
