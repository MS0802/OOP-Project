class Entity{
protected:
    string name;
    string type;
    struct position
    {
        int x,y;
        position(int _x, int _y){
            x =_x;
            y=_y;
        }
    };
    position p;
    double health;
    double maxhealth;
    
public:

    //constructor
    Entity(string n,string typ, position _p,double h, double maxh)
        :name(n) , type(typ) ,p(_p), health(h) , maxhealth(maxh){}
    
    //Pure virtual render and update functions
    virtual void update()=0;
    virtual void render()=0;

    virtual void sethealth(int h){
        if (h >0){
            health = h;
        }
    }

    virtual int gethealth(){
        return health;
    }

    virtual string gettype(){
        return type;
    }


    //currently thinking of using default destructor
    ~Entity()=default;
};
