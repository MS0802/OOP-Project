#include"Entity.h"

Entity::Entity(std::string Name, int startX, int startY, size_t HP, size_t MaxHP, int def) : 
name(Name), position(startX, startY), hp(HP), maxHP(MaxHP), def(def) {}

Entity::Entity() : position(0, 0), name(), effects(), maxHP(0), hp(0) {}

void Entity::move(int pX, int pY) {
    position.x += pX;
    position.y += pY;
}

void Entity::takeDamage(int dmg) {
    if(dmg > HP()) {
        hp = 0;
    }
    else {
        hp -= dmg;
    }
}

void Entity::Healing(size_t heal) {
    if(heal + HP() > MaxHP()) {
        hp = MaxHP();
    }
    else {
        hp += heal;
    }
}

int Entity::PosX() const { return position.x; }
int Entity::posY() const { return position.y; }
size_t Entity::HP() const { return hp; }
size_t Entity::MaxHP() const { return maxHP; }
std::string Entity::Name() const { return name; }
bool Entity::isAlive() const { return (hp > 0); }
void Entity::Effect_Add(Effect other) {
    if(effects.count(other.Effect_Give())) {
        effects[other.Effect_Give()].Time() += other.Time();
    }
    else {
        effects[other.Effect_Give()] = other;
    }
}
