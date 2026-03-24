class Player : public Entity {
private:
    string name;
    std::vector<std::unique_ptr<Item>> inventory;
    int XP=0;
    int attackPower;

public:
    Player(string n, string typ, position _pos, double h, double maxh, int attackp)
    :Entity(n, typ, _pos, h, maxh){
        attackPower = attackp;
    }

    void update(int pX,int pY) {  // cant be overridden because base class update has no parameters
        p.x = pX;
        p.y = pY;
    }

    char getSymbol() const{
        return 'P';
    }

    void attack(Entity& target){
        if (target.gethealth() >0 && attackPower>0 ){
            int h;
            h = target.gethealth() - attackPower;
            if (h<0){
                // remove the enemy dunno how

                if (target.gettype() == "mage"){
                    XP += 10; //not sure
                }
                else if (target.gettype() == "warrior"){
                    XP += 15;
                }
                else if (target.gettype() == "bomber"){
                    XP += 5;
                }
                // code if more types

            }
            else{
                target.sethealth(h);
            }
        }
    }

    void useItem(int index);
    void addItem(std::unique_ptr<Item> item); //Takes ownership of items using move

    void heal(int amount){
        if (amount >= 0){
            if (health + amount > maxhealth){
                health = maxhealth;
            }
            else{
                health += amount;
            }

        }
        //else{
            //exception handling to be applied
        //}
    }

    int getXP()const{
        return XP;
    }
    int getAttackPower()const{
        return attackPower;
    }
    int getInventorySize()const;

    void setXP(int amount){
        if (amount >=0){
            XP+= amount;
        }

        //exception handling
    }
};
