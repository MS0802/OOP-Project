#pragma once
#include<algorithm>

constexpr int healingValue = 2;
constexpr int poisonDamage = 2;
constexpr int strengthValue = 5;
constexpr int weaknessValue = 5;
constexpr int resistanceValue = 3;
constexpr int vulnerableDefense = 3;

enum class EffectType {
    HEAL,
    POISON,
    STRENGTH,
    WEAKNESS,
    RESISTANCE,
    VULNERABLE
};

class Effect {
    protected:
        EffectType type;
        bool canGive;
        double time;
    public:
        Effect(EffectType type, double time, bool Can_Give_Others);
        Effect(const Effect& other);
        Effect(); // Default constructor
        
        EffectType Effect_Give() const;
        double& Time();
        bool Can_Give() const;
};
