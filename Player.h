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
    Player(string name, string type , position _pos, int health,int attackp)
    :Entity(name,type,_pos,health){
        attackPower = attackp;
    }

    void update(int pX,int pY) override{
        p.x = pX;
        p.y = pY;
    }

    char getSymbol()const override;

    void attack(Entity& target);
    void useItem(int index);
    void addItem(std::unique_ptr<Item> item); //Takes ownership of items using move

    void heal(int amount){
        if (amount >=0){
            health += amount;
        }

        //exception handling to be applied
    }

    int getXP()const{
        return XP;
    }
    int getAttackPower()const{
        return attackPower;
    }
    int getInventorySize()const;

    void setXP(int ammount){
        if (amount >=0){
            XP+= amount;
        }

        //exception hadling
    }
};
