#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    int x, y;
    int hp;

public:
    Entity(int startX, int startY, int health);
    virtual ~Entity() {}

    virtual void update(int pX,int pY) = 0;
    void move(int dx, int dy);
    void takeDamage(int dmg);

    int getX() const;
    int getY() const;
    int getHP() const;
    bool isAlive() const;
    virtual char getSymbol() const = 0;
};

#endif
