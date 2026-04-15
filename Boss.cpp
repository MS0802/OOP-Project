#include"Boss.h"

Boss::Boss(std::string name, int startX, int startY, size_t hp, size_t MaxHP, int def, std::array<std::unique_ptr<Item>, 3> drops, size_t XP, int damage) : 
Enemy(name, startX, startY, hp, MaxHP, def, std::move(drops), XP, damage) {}

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

void Boss::specialAttack(Entity& target) {
    //special attack code
    //for now:
    target.takeDamage(Damage());
}
