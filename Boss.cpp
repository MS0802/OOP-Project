#include"Boss.h"
#include"Potion.h"
#include"Utility.h"
#include<algorithm>

Boss::Boss(std::string name, int startX, int startY, int hp, int def, std::array<std::unique_ptr<Item>, 3> drops, int XP, int damage, int Regeneration_Factor) : 
Enemy(name, startX, startY, hp, def, std::move(drops), XP, damage, EnemyType::NORMAL), regenerationFactor(Regeneration_Factor) {}

Boss::Boss(const Boss& other) : 
Enemy(other), regenerationFactor(other.regenerationFactor) {}

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
