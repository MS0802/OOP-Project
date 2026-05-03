#include"Enemy.h"
#include"Potion.h"
#include"Utility.h"

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int Defense, std::array<std::unique_ptr<Item>, 3> Drops, int XP, int Damage) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), drops(std::move(Drops)), damage(Damage), initialDamage(Damage) {}

Enemy::Enemy() : 
Entity(), drops(), xp(0), damage(0), initialDamage(0) {}

Enemy::Enemy(const Enemy& other) : 
Entity(other.Name(), other.PosX(), other.PosY(), other.HP(), other.Defense()), xp(other.XP()), damage(other.Damage()), initialDamage(other.Initial_Damage()), drops() {
    for(int i = 0; i<3; i++) {
        if(other.drops[i]) {
            drops[i] = other.drops[i]->clone();
        }
    }
}

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int Defense, int XP, int Damage, const std::array<std::unique_ptr<Item>, 3>& Drops) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), damage(Damage), initialDamage(Damage), drops() {
    for(int i = 0; i<3; i++) {
        if(Drops[i]) {
            drops[i] = Drops[i]->clone();
        }
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

void Enemy::Effect_Action(EffectType Type) {
    std::vector<EffectType> toRemove;
    
    for(auto& effectPair : effects) {
        EffectType type = effectPair.first;
        Effect& e = effectPair.second;
        
        if(e.Can_Give() || e.Time() == 0) { 
            if(e.Time() == 0) {
                toRemove.push_back(type);
            }
            continue; 
        }
        
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
    
    // Remove expired effects
    for(const auto& effectType : toRemove) {
        effects.erase(effectType);
    }
}

std::unique_ptr<Entity> Enemy::clone() const {
    return std::make_unique<Enemy>(*this);
}

// Factory methods for enemy types
Enemy Enemy::Normal(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Utility::Wood().clone();
    drops[1] = Potion::SelfHealing().clone();
    drops[2] = nullptr;
    return Enemy("Normal Enemy", startX, startY, 50, 5, std::move(drops), 10, 10);
}

Enemy Enemy::Tank(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Utility::Stone().clone();
    drops[1] = Potion::Resistance().clone();
    drops[2] = nullptr;
    return Enemy("Tank", startX, startY, 70, 15, std::move(drops), 15, 10);
}

Enemy Enemy::Poison(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Potion::Poison().clone();
    drops[1] = Utility::Wood().clone();
    drops[2] = nullptr;
    
    Enemy poisonEnemy("Poison Enemy", startX, startY, 40, 5, std::move(drops), 12, 2);
    // Add permanent poison effect
    poisonEnemy.Effect_Add(Effect(EffectType::POISON, 999999, true));
    return poisonEnemy;
}

Enemy Enemy::Healer(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Potion::SelfHealing().clone();
    drops[1] = Potion::InflictHealing().clone();
    drops[2] = nullptr;
    
    Enemy healerEnemy("Healer", startX, startY, 40, 5, std::move(drops), 8, 0);
    // Add permanent healing effect for others
    healerEnemy.Effect_Add(Effect(EffectType::HEAL, 999999, true));
    return healerEnemy;
}

Enemy Enemy::Wizard(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Potion::Weakness().clone();
    drops[1] = Potion::Vulnerability().clone();
    drops[2] = Utility::Iron().clone();
    
    Enemy wizardEnemy("Wizard", startX, startY, 40, 5, std::move(drops), 15, 5);
    // Add permanent weakness and vulnerability effects
    wizardEnemy.Effect_Add(Effect(EffectType::WEAKNESS, 999999, true));
    wizardEnemy.Effect_Add(Effect(EffectType::VULNERABLE, 999999, true));
    return wizardEnemy;
}
