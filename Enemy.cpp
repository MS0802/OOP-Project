#include"Enemy.h"

Enemy::Enemy(std::string name, int startX, int startY, size_t hp, size_t MaxHP, int def, std::array<std::unique_ptr<Item>, 3> drops, size_t XP, int damage) : 
Entity(name, startX, startY, hp, MaxHP, def), xp(XP), drops(std::move(drops)), dmg(damage) {}

void Enemy::update(int x, int y) {
    //Will probably be used to implement player tracking AI
    //for now:
    position.x += x;
    position.y += y;
}

char Enemy::getSymbol() const { return 'E'; }
int Enemy::Damage() const { return dmg; }
int Enemy::Defense() const { return def; }
size_t Enemy::XP() const { return xp; }
size_t Enemy::HP() const{return hp;}

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
        e.Time()--;
        switch(type) {
            case EffectType::HEAL:
                break;
        }
    }
}
