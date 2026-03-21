#include<string>

class Entity {
protected:
    int x, y;
    int hp;

public:
    Entity(int startX, int startY, int health)
        :x(startX), y(startY),hp(health){}
    virtual ~Entity() {}

    virtual void update(int pX,int pY) = 0;

    void move(int dx=0, int dy=0){
        x=x+dx;
        y=y+dy;
    }

    void takeDamage(int dmg){
        if(dmg>hp){
         hp=hp-dmg;
         return;
            }
        hp=0;
        return;
    }

    int getX() const{
        return x;
    }
    int getY() const{
        return y;
    }
    int getHP() const{
        return hp;
    }
    bool isAlive() const{
        if(hp>0)    return true;
        else        return false;
    }
    virtual char getSymbol() const = 0;
};