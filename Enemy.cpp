#include"Enemy.h"
#include"Potion.h"
#include"Utility.h"

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int Defense, std::array<std::unique_ptr<Item>, 3> Drops, int XP, int Damage, EnemyType type) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), drops(std::move(Drops)), damage(Damage), initialDamage(Damage), enemyType(type), tickCounter(0) {}

Enemy::Enemy() : 
Entity(), drops(), xp(0), damage(0), initialDamage(0), enemyType(EnemyType::NORMAL), tickCounter(0) {}

Enemy::Enemy(const Enemy& other) : 
Entity(other.Name(), other.PosX(), other.PosY(), other.HP(), other.Defense()), xp(other.XP()), damage(other.Damage()), initialDamage(other.Initial_Damage()), enemyType(other.Type()), tickCounter(0), drops() {
    for(int i = 0; i<3; i++) {
        if(other.drops[i]) {
            drops[i] = other.drops[i]->clone();
        }
    }
}

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int Defense, int XP, int Damage, const std::array<std::unique_ptr<Item>, 3>& Drops, EnemyType type) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), damage(Damage), initialDamage(Damage), enemyType(type), tickCounter(0), drops() {
    for(int i = 0; i<3; i++) {
        if(Drops[i]) {
            drops[i] = Drops[i]->clone();
        }
    }
}

void Enemy::update(int x, int y) {
    position.x += x;
    position.y += y;
}

void Enemy::updateAI(const Entity& player) {
    tickCounter++;
    
    int dx = player.PosX() - position.x;
    int dy = player.PosY() - position.y;
    int absDx = std::abs(dx);
    int absDy = std::abs(dy);
    
    int moveX = 0, moveY = 0;
    
    switch(enemyType) {
        case EnemyType::NORMAL:
        case EnemyType::TANK:
        case EnemyType::POISON:
            // Move towards player (aggressive)
            if(absDx > absDy) {
                moveX = (dx > 0) ? 1 : -1;
            } else if(absDy > 0) {
                moveY = (dy > 0) ? 1 : -1;
            }
            break;
            
        case EnemyType::HEALER:
            // Move away from player (slow - every 2 ticks)
            if(tickCounter % 2 == 0) {
                if(absDx < 5 || absDy < 5) {
                    if(absDx > absDy) {
                        moveX = (dx > 0) ? -1 : 1;
                    } else if(absDy > 0) {
                        moveY = (dy > 0) ? -1 : 1;
                    }
                }
            }
            break;
            
        case EnemyType::WIZARD:
            // Hit once then run away
            if(absDx <= 1 && absDy <= 1) {
                // Too close, run away
                if(absDx > absDy) {
                    moveX = (dx > 0) ? -1 : 1;
                } else {
                    moveY = (dy > 0) ? -1 : 1;
                }
            } else if(absDx <= 3 && absDy <= 3) {
                // In range for effect, move to attack
                if(absDx > absDy) {
                    moveX = (dx > 0) ? 1 : -1;
                } else {
                    moveY = (dy > 0) ? 1 : -1;
                }
            }
            break;
    }
    
    update(moveX, moveY);
}

char Enemy::getSymbol() const { return 'E'; }
int Enemy::Damage() const { return damage; }
int Enemy::Initial_Damage() const { return initialDamage; }
size_t Enemy::XP() const { return xp; }
EnemyType Enemy::Type() const { return enemyType; }

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
    return Enemy("Normal Enemy", startX, startY, 50, 5, std::move(drops), 10, 10, EnemyType::NORMAL);
}

Enemy Enemy::Tank(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Utility::Stone().clone();
    drops[1] = Potion::Resistance().clone();
    drops[2] = nullptr;
    return Enemy("Tank", startX, startY, 70, 15, std::move(drops), 15, 10, EnemyType::TANK);
}

Enemy Enemy::Poison(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Potion::Poison().clone();
    drops[1] = Utility::Wood().clone();
    drops[2] = nullptr;
    
    Enemy poisonEnemy("Poison Enemy", startX, startY, 40, 5, std::move(drops), 12, 2, EnemyType::POISON);
    // Add permanent poison effect
    poisonEnemy.Effect_Add(Effect(EffectType::POISON, 999999, true));
    return poisonEnemy;
}

Enemy Enemy::Healer(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Potion::SelfHealing().clone();
    drops[1] = Potion::InflictHealing().clone();
    drops[2] = nullptr;
    
    Enemy healerEnemy("Healer", startX, startY, 40, 5, std::move(drops), 8, 0, EnemyType::HEALER);
    // Add permanent healing effect for others
    healerEnemy.Effect_Add(Effect(EffectType::HEAL, 999999, true));
    return healerEnemy;
}

Enemy Enemy::Wizard(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Potion::Weakness().clone();
    drops[1] = Potion::Vulnerability().clone();
    drops[2] = Utility::Iron().clone();
    
    Enemy wizardEnemy("Wizard", startX, startY, 40, 5, std::move(drops), 15, 5, EnemyType::WIZARD);
    // Add permanent weakness and vulnerability effects
    wizardEnemy.Effect_Add(Effect(EffectType::WEAKNESS, 999999, true));
    wizardEnemy.Effect_Add(Effect(EffectType::VULNERABLE, 999999, true));
    return wizardEnemy;
}
