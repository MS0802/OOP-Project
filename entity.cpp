#include<string>

class Entity{
    private:
    std::string name;
    std::string type;
    
public:

    //constructor
    Entity(std::string n,std::string t, position _p,double h)
        : name(n), type(t), p(_p), health(h){}
    
    //Pure virtual render and update functions
    void virtual update()=0;
    void virtual render()=0;

    //currently thinking of using default destructor
    ~Entity()=default;
};
