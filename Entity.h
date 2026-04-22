#pragma once
#include"Vector2.h"
#include<string>
#include<unordered_map>
#include<memory>
#include"Effect.h"

class Entity {
    protected:
        Vector2 position;
        int hp;
        const int maxHP;
        std::string name;
        std::unordered_map<EffectType, Effect> effects;
        const int initialDefense;
        int defense;

        Entity(std::string Name, int startX, int startY, int health, int MaxHP, int Defense);
        Entity();
    public:
        virtual ~Entity() = default;

        virtual void update(int pX,int pY) = 0;
        void move(int dx, int dy);
        void takeDamage(int dmg);
        void Healing(int heal);
        virtual int Damage() const = 0;
        virtual int Defense() const = 0;
        virtual void Effect_Action() = 0;
        virtual void Effect_Add(Effect other);

        int PosX() const;
        int posY() const;
        int HP() const;
        int MaxHP() const;
        int Defense() const;
        int Initial_Defense() const;
        bool isAlive() const;
        std::string Name() const;
        virtual char getSymbol() const = 0;
};
