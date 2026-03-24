#include "Entity.h"
#include <vector>
#include <memory>
#include "Item.h"

class Player : public Entity {
private:
    std::vector<std::unique_ptr<Item>> inventory;
    int XP=0;
    int attackPower;

public:
    Player(int x, int y,int health, int maxhealth ,int attackp){}

    void update(int pX,int pY) override{}

    char getSymbol()const override;

    void attack(Entity& target);
    void useItem(int index);
    void addItem(std::unique_ptr<Item> item); //Takes ownership of items using move

    void heal(int amount){}

    int getXP()const{}
    int getAttackPower()const{}
    int getInventorySize()const;

    void setXP(int amount){}
};
