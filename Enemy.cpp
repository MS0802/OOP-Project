class Enemy : public Entity {
protected:
    int attackPower;

public:
    Enemy(int startX, int startY, int h,int maxh, int atk)
    :Entity(startX,startY,h,maxh){
        attackPower = atk;
    }

    void update(int X,int Y) override{//Will probably be used to implement player tracking AI

    }
    char getSymbol()const override{
        return 'E';
    }
    
    void attack(Entity& target){
        if (attackPower > target.getHP()){
            target.sethp(0);

        }
    }

    int getAttackPower()const{
        return attackPower;
    }

    virtual std::unique_ptr<Item> dropItem();//returns nullptr by default
};
