class Entity{
protected:
    int x,y;
    int health;
    int maxhealth;
    
public:

    //constructor
    Entity(int startX, int startY, int h, int maxh){
        x = startX;
        y = startY;
        health = h;
        maxhealth = maxh;
    }
    
    virtual ~Entity() {}

    virtual void update(int pX,int pY) = 0;
    void move(int dx, int dy){
        x = x + dx;
        y = y + dy;
    }
    
    void takeDamage(int dmg){
        if (dmg < health ){
            health = health - dmg;
        }
        else{
            health =0;
            // how to remove player?
        }
    }

    int getX() const{
        return x;
    }
    int getY() const{
        return y;
    }
    int getHP() const{
        return health;
    }
    bool isAlive() const{
        if (health >0){
            return true;
        }
        else {
            return false;
        }
    }
    virtual char getSymbol() const = 0;
};
