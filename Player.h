#include "entity.h";
#include <conio.h>
#include <stack>

class Player:protected Entity{
    private:
    int XP;
    int energy;
    struct position
    {
        int x,y;
        position(int _x=0, int _y=0){
            x=x=_x;
            y=_y;
        }
    };
    position p;
    double health;

    public:

    Player(std::string n,std::string t, position _p,double h,int _XP,int _energy)
        :Entity(n,t){
            health=h;
            XP=_XP;
            energy=_energy;
        }

    //Updates player position
    position Movement(char y){
        if(y == 'w'){
            return p.y+y;
        }
        else if(y == 'a'){
            return p.x-y;
        }
        else if(y == 's'){
            return p.y-y;
        }
        else if(y == 'd'){
            return p.x+y;
        }
    }

    void update(){

    }

    //Handles player level using XP member
    int Levels(){

    }

};