#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class PLayer;

class Weapon : public Item {
private:
    int damage;

public:
    Weapon(const std::string& name, int dmg);

    void use(Player& player) override;
};

#endif
