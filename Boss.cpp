#include"Boss.h"
#include"Potion.h"
#include"Utility.h"
#include<algorithm>
#include<cmath>

Boss::Boss(std::string name, int startX, int startY, int hp, int def, std::array<std::unique_ptr<Item>, 3> drops, int XP, int damage, int Regeneration_Factor) : 
Enemy(name, startX, startY, hp, def, std::move(drops), XP, damage, EnemyType::NORMAL), regenerationFactor(Regeneration_Factor) {}

Boss::Boss(const Boss& other) : 
Enemy(other), regenerationFactor(other.regenerationFactor) {}

std::pair<int,int> Boss::calculateAIMove(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) const {
    int dx = player.PosX() - position.x;
    int dy = player.PosY() - position.y;
    int playerDistance = std::max(std::abs(dx), std::abs(dy));

    // Stop moving if player is 2 blocks away or closer
    if(playerDistance <= 2) {
        return {0, 0};
    }

    auto sign = [](int value) {
        return (value > 0) - (value < 0);
    };

    int moveX = 0;
    int moveY = 0;

    if(dx != 0 || dy != 0) {
        if(std::abs(dx) > std::abs(dy)) {
            moveX = sign(dx);
        } else {
            moveY = sign(dy);
        }
    }

    return {moveX, moveY};
}

void Boss::updateAI(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) {
    auto move = calculateAIMove(player, zoneEntities);
    update(move.first, move.second);
}

char Boss::getSymbol() const { return 'B'; }

std::array<std::unique_ptr<Item>, 3> Boss::dropItem() {
    std::array<std::unique_ptr<Item>, 3> RET;
    int items;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);
    items = dist(gen);

    for(int i = 0; i<=items; i++) {
        RET[i] = std::move(drops[i]);
    }

    return RET;
}

std::unique_ptr<Entity> Boss::clone() const {
    return std::make_unique<Boss>(*this);
}

void Boss::specialAttack(Entity& target) {
    target.takeDamage(Damage());
    if(hp < maxHP/2) {
        hp = std::min(hp + regenerationFactor, maxHP);
        
        // Apply special effects when below half HP
        if(name == "Poisonous Stone Golem") {
            target.Effect_Add(Effect(EffectType::POISON, 5, false));
        }
        else if(name == "Etherite Protector") {
            target.Effect_Add(Effect(EffectType::WEAKNESS, 5, false));
            target.Effect_Add(Effect(EffectType::POISON, 5, false));
        }
    }
}

// Factory methods for boss types
Boss Boss::PoisonousStoneGolem(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Utility::Stone().clone();
    drops[1] = Utility::Stone().clone();
    drops[2] = Potion::Resistance().clone();
    
    return Boss("Poisonous Stone Golem", startX, startY, 150, 25, std::move(drops), 100, 30, 10);
}

Boss Boss::EtheriteProtector(int startX, int startY) {
    std::array<std::unique_ptr<Item>, 3> drops;
    drops[0] = Utility::Etherite().clone();
    drops[1] = Utility::Etherite().clone();
    drops[2] = Potion::Strength().clone();
    
    return Boss("Etherite Protector", startX, startY, 150, 25, std::move(drops), 150, 30, 15);
}
