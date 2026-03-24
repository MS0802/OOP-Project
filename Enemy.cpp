class Enemy : public Entity {
protected:
    int attackPower;

public:
    Enemy(string n ,string typ, position _pos, int h,  int atk)
        :Entity(n, typ, _pos,h){   
            attackPower = atk;
    }

    void update() override;
    void attack(Entity& target);
};
