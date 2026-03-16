#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
    int healAmt;

public:
    Potion(const std::string& name, int heal);

    void use(Player& player) override;
};

#endif
