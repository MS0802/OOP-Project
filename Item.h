#ifndef ITEM_H
#define ITEM_H

#include <string>
class Player;

class Item {
protected:
    std::string name;

public:
    Item(const std::string& itemName);
    virtual ~Item() {}

    virtual void use(Player& player) = 0;
};

#endif