#pragma once
#include<algorithm>

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
