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
    
    const std::string& getName()const;//will probably use in render for inventory display
    virtual void use(Player& player) = 0;
};

#endif