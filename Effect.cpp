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
