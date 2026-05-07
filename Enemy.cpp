#include"Enemy.h"
#include"Boss.h"
#include"Potion.h"
#include"Utility.h"
#include<cmath>
#include<climits>

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int Defense, std::array<std::unique_ptr<Item>, 3> Drops, int XP, int Damage, EnemyType type) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), drops(std::move(Drops)), damage(Damage), initialDamage(Damage), enemyType(type), hasAttackedPlayer(false) {}

Enemy::Enemy() : 
Entity(), drops(), xp(0), damage(0), initialDamage(0), enemyType(EnemyType::NORMAL), hasAttackedPlayer(false) {}

Enemy::Enemy(const Enemy& other) : 
Entity(other.Name(), other.PosX(), other.PosY(), other.HP(), other.Defense()), xp(other.XP()), damage(other.Damage()), initialDamage(other.Initial_Damage()), enemyType(other.Type()), hasAttackedPlayer(other.hasAttackedPlayer), drops() {
    for(int i = 0; i<3; i++) {
        if(other.drops[i]) {
            drops[i] = other.drops[i]->clone();
        }
    }
}

Enemy::Enemy(std::string Name, int startX, int startY, int HP, int Defense, int XP, int Damage, const std::array<std::unique_ptr<Item>, 3>& Drops, EnemyType type) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), damage(Damage), initialDamage(Damage), enemyType(type), hasAttackedPlayer(false), drops() {
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

std::pair<int,int> Enemy::calculateAIMove(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) const {
    auto isPlayerNear = [&]() {
        int dx = player.PosX() - position.x;
        int dy = player.PosY() - position.y;
        int dist = std::max(std::abs(dx), std::abs(dy));
        return dist <= 5;
    };

    int dx = player.PosX() - position.x;
    int dy = player.PosY() - position.y;
    int playerDistance = std::max(std::abs(dx), std::abs(dy));

    // Stop moving if player is right next to enemy
    if(playerDistance <= 1) {
        return {0, 0};
    }

    auto chooseClosestAlly = [&]() -> const Entity* {
        const Entity* bestBoss = nullptr;
        const Entity* bestEnemy = nullptr;
        int bestBossDist = INT_MAX;
        int bestEnemyDist = INT_MAX;

        for(const auto& entity : zoneEntities) {
            if(entity.get() == this) {
                continue;
            }
            if(!entity) {
                continue;
            }

            const Boss* boss = dynamic_cast<const Boss*>(entity.get());
            const Enemy* otherEnemy = dynamic_cast<const Enemy*>(entity.get());
            if(boss) {
                int dist = std::max(std::abs(position.x - boss->PosX()), std::abs(position.y - boss->PosY()));
                if(dist < bestBossDist) {
                    bestBossDist = dist;
                    bestBoss = boss;
                }
            } else if(otherEnemy) {
                int dist = std::max(std::abs(position.x - otherEnemy->PosX()), std::abs(position.y - otherEnemy->PosY()));
                if(dist < bestEnemyDist) {
                    bestEnemyDist = dist;
                    bestEnemy = otherEnemy;
                }
            }
        }

        return bestBoss ? bestBoss : bestEnemy;
    };

    if (!isPlayerNear()) {
        // Move randomly
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(-1, 1);
        int moveX, moveY;
        do {
            moveX = dist(rng);
            moveY = dist(rng);
        } while (moveX == 0 && moveY == 0);
        return {moveX, moveY};
    }

    // Player is near, approach or special behavior
    int moveX = 0;
    int moveY = 0;

    auto sign = [](int value) {
        return (value > 0) - (value < 0);
    };

    switch (enemyType) {
        case EnemyType::NORMAL:
        case EnemyType::TANK:
        case EnemyType::POISON:
        case EnemyType::WIZARD:
            if (std::abs(dx) > std::abs(dy)) {
                moveX = sign(dx);
            } else if (std::abs(dy) > 0) {
                moveY = sign(dy);
            }
            break;

        case EnemyType::HEALER: {
            const Entity* ally = chooseClosestAlly();
            if (ally) {
                int playerDist = std::max(std::abs(dx), std::abs(dy));
                if (playerDist <= 3) {
                    moveX = -sign(dx);
                    moveY = -sign(dy);
                } else {
                    int adx = ally->PosX() - position.x;
                    int ady = ally->PosY() - position.y;
                    if (std::abs(adx) > std::abs(ady)) {
                        moveX = sign(adx);
                    } else if (std::abs(ady) > 0) {
                        moveY = sign(ady);
                    }
                }
            } else {
                moveX = -sign(dx);
                moveY = -sign(dy);
            }
            break;
        }
    }

    return {moveX, moveY};
}

void Enemy::updateAI(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) {
    auto move = calculateAIMove(player, zoneEntities);
    update(move.first, move.second);
}

bool Enemy::HasAttackedPlayer() const {
    return hasAttackedPlayer;
}

void Enemy::MarkAttackedPlayer() {
    hasAttackedPlayer = true;
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
    return Enemy("Normal Enemy", startX, startY, 50, 5, std::move(drops), 10, 15, EnemyType::NORMAL);
}

Enemy Enemy::Tank(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Utility::Stone().clone();
    drops[1] = Potion::Resistance().clone();
    drops[2] = nullptr;
    return Enemy("Tank", startX, startY, 70, 15, std::move(drops), 15, 20, EnemyType::TANK);
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
    
    Enemy wizardEnemy("Wizard", startX, startY, 40, 5, std::move(drops), 15, 11, EnemyType::WIZARD);
    // Add permanent weakness and vulnerability effects
    wizardEnemy.Effect_Add(Effect(EffectType::WEAKNESS, 999999, true));
    wizardEnemy.Effect_Add(Effect(EffectType::VULNERABLE, 999999, true));
    return wizardEnemy;
}
