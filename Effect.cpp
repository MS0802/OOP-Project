#include"Effect.h"

Effect::Effect(EffectType type, double time) : 
type(type), time(std::max(time, 0.0)) {}

EffectType Effect::Effect_Give() { return type; }

double& Effect::Time() { return time; }
