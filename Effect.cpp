#include"Effect.h"

Effect::Effect(EffectType type, double time, bool Can_Give_Others) : 
type(type), time(std::max(time, 0.0)), canGive(Can_Give_Others) {}

Effect::Effect(const Effect& other) : 
type(other.type), canGive(other.canGive), time(other.time) {}

Effect::Effect() : 
type(EffectType::HEAL), time(0.0), canGive(false) {}

EffectType Effect::Effect_Give() const { return type; }

double& Effect::Time() { return time; }

bool Effect::Can_Give() const { return canGive; }

std::ostream& operator<<(std::ostream& os, const Effect& effect) {
    os << "Effect Type: ";
    switch(effect.type) {
        case EffectType::HEAL:
            os << "Heal";
            break;
        case EffectType::POISON:
            os << "Poison";
            break;
        case EffectType::STRENGTH:
            os << "Strength";
            break;
        case EffectType::WEAKNESS:
            os << "Weakness";
            break;
        case EffectType::RESISTANCE:
            os << "Resistance";
            break;
        case EffectType::VULNERABLE:
            os << "Vulnerable";
            break;
    }
    os << ", Time Remaining: " << effect.time << " seconds" 
       << (effect.canGive ? ", Can Give to Others" : "");
    return os;
}
