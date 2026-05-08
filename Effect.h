#pragma once
#include<algorithm>
#include<iostream>

constexpr int healingValue = 10;
constexpr int poisonDamage = 10;
constexpr int strengthValue = 5;
constexpr int weaknessValue = 5;
constexpr int resistanceValue = 5;
constexpr int vulnerableDefense = 5;

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
        friend std::ostream& operator<<(std::ostream& os, const Effect& effect);
};
