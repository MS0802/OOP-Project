#include"Enemy.h"

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int MaxHP, int Defense, std::array<std::unique_ptr<Item>, 3> Drops, int XP, int Damage) : 
Entity(Name, startX, startY, HP, MaxHP, Defense), xp(XP), drops(std::move(Drops)), damage(Damage), initialDamage(Damage) {}

Enemy::Enemy() : 
Entity(), drops(), xp(0), damage(0), initialDamage(0) {}

Enemy::Enemy(const Enemy& other) : 
Entity(other.Name(), other.PosX(), other.PosY(), other.HP(), other.MaxHP(), other.Defense()), xp(other.XP()), damage(other.Damage()), initialDamage(other.Initial_Damage()), drops() {
    for(int i = 0; i<3; i++) {
        drops[i] = std::make_unique<Item>(*other.drops[i]);
    }
}

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int MaxHP, int Defense, int XP, int Damage, const std::array<std::unique_ptr<Item>, 3>& Drops) : 
Entity(Name, startX, startY, HP, MaxHP, Defense), xp(XP), damage(Damage), initialDamage(Damage), drops() {
    for(int i = 0; i<3; i++) {
        drops[i] = std::make_unique<Item>(*Drops[i]);
    }
}

void Enemy::update(int x, int y) {
    //Will probably be used to implement player tracking AI
    //for now:
    position.x += x;
    position.y += y;
}

char Enemy::getSymbol() const { return 'E'; }
int Enemy::Damage() const { return damage; }
int Enemy::Initial_Damage() const { return initialDamage; }
size_t Enemy::XP() const { return xp; }

void Enemy::attack(Entity& target) { target.takeDamage(Damage()); }

std::array<std::unique_ptr<Item>, 3> Enemy::dropItem() {
    std::array<std::unique_ptr<Item>, 3> RET;
    int items;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    items = dist(gen);

    for(int i = 0; i<items; i++) {
        RET[i] = std::move(drops[i]);
    }

    return RET;
}

void Enemy::Effect_Action() {
    for(auto& [type, e] : effects) {
        if(e.Can_Give() || e.Time() == 0) { continue; }
        e.Time()--;
        switch(type) {
            case EffectType::HEAL:
                Healing(healingValue);
                break;
            case EffectType::POISON:
                takeDamage(poisonDamage);
                break;
            case EffectType::STRENGTH:
                if(damage == initialDamage) {
                    damage += strengthValue;
                }
                break;
            case EffectType::WEAKNESS:
                if(damage == initialDamage) {
                    if(damage - weaknessValue <= 0) { damage = 0; }
                    else { damage -= weaknessValue; }
                }
                break;
            case EffectType::RESISTANCE:
                if(defense == initialDefense) {
                    defense += resistanceValue;
                }
                break;
            case EffectType::VULNERABLE:
                if(defense == initialDefense) {
                    if(defense - vulnerableDefense <= 0) { defense = 0; }
                    else { defense -= vulnerableDefense; }
                }
                break;
        }
    }
}
