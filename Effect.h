#pragma once
#include<algorithm>

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
        double time;
    public:
        Effect(EffectType type, double time);
        EffectType Effect_Give();
        double& Time();
};
