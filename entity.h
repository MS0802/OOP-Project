#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    int x, y;
    int hp;

public:
    Entity(int startX, int startY, int health);
    virtual ~Entity() {}

    virtual void update() = 0;
    void move(int dx, int dy);
    void takeDamage(int dmg);
};

#endif
