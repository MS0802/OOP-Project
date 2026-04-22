#pragma once
#include"Vector2.h"
#include<string>
#include<unordered_map>
#include<memory>
#include"Effect.h"

class Entity {
    protected:
        Vector2 position;
        size_t hp;
        const size_t maxHP;
        std::string name;
        std::unordered_map<EffectType, Effect> effects;
        int def;

        Entity(std::string Name, int startX, int startY, size_t health, size_t MaxHP, int def);
        Entity();
    public:
        virtual ~Entity() = default;

        virtual void update(int pX,int pY) = 0;
        void move(int dx, int dy);
        void takeDamage(int dmg);
        void Healing(size_t heal);
        virtual int Damage() const = 0;
        virtual int Defense() const = 0;
        virtual void Effect_Action() = 0;
        virtual void Effect_Add(Effect other);

        int PosX() const;
        int posY() const;
        size_t HP() const;
        size_t MaxHP() const;
        bool isAlive() const;
        std::string Name() const;
        virtual char getSymbol() const = 0;
};
