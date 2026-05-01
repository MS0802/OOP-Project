#include"Entity.h"
#include<algorithm>

Entity::Entity(std::string Name, int startX, int startY, int HP, int def) : 
name(Name), position(startX, startY), hp(HP), maxHP(HP), defense(def), initialDefense(def) {}

Entity::Entity() : 
position(0, 0), name(), effects(), maxHP(0), hp(0), defense(0), initialDefense(0) {}

Entity::Entity(const Entity& other) : 
position(other.position), name(other.Name()), effects(other.effects), maxHP(other.MaxHP()), hp(other.HP()), defense(other.Defense()), initialDefense(other.Initial_Defense()) {}

void Entity::move(int pX, int pY) {
    position.x += pX;
    position.y += pY;
}

void Entity::takeDamage(int dmg) {
    int actualDamage = std::max(0, dmg - defense);
    if(actualDamage >= hp) {
        hp = 0;
    }
    else {
        hp -= actualDamage;
    }
}

void Entity::Healing(int heal) {
    if(heal + HP() > MaxHP()) {
        hp = MaxHP();
    }
    else {
        hp += heal;
    }
}

int Entity::PosX() const { return position.x; }
int Entity::PosY() const { return position.y; }
int Entity::HP() const { return hp; }
int Entity::MaxHP() const { return maxHP; }
std::string Entity::Name() const { return name; }
bool Entity::isAlive() const { return (hp > 0); }
int Entity::Defense() const { return defense; }
int Entity::Initial_Defense() const { return initialDefense; }
void Entity::Effect_Add(Effect other) {
    if(effects.count(other.Effect_Give())) {
        effects[other.Effect_Give()].Time() += other.Time();
    }
    else {
        effects[other.Effect_Give()] = other;
    }
}
