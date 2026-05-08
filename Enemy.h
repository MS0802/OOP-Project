#pragma once
#include"Entity.h"
#include"Item.h"
#include<memory>
#include<array>
#include<random>
#include<vector>
#include<utility>
#include<iostream>

enum class EnemyType {
    NORMAL,
    TANK,
    POISON,
    HEALER,
    WIZARD
};

class Enemy : public Entity {
    protected:
        std::array<std::unique_ptr<Item>, 3> drops;
        int xp;
        int damage;
        const int initialDamage;
        EnemyType enemyType;
        bool hasAttackedPlayer;
    public:
        Enemy(std::string Name, int startX, int startY, int HP, int Defense, std::array<std::unique_ptr<Item>, 3> Drops, int XP, int Damage, EnemyType type);
        Enemy();
        Enemy(const Enemy& other);
        Enemy(std::string Name, int startX, int startY, int HP, int Defense, int XP, int Damage, const std::array<std::unique_ptr<Item>, 3>& Drops, EnemyType type);

        void update(int x, int y) override;
        virtual void updateAI(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities);
        virtual std::pair<int,int> calculateAIMove(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) const;
        bool HasAttackedPlayer() const;
        void MarkAttackedPlayer();
        char getSymbol() const override;

        void attack(Entity& target);
        int Damage() const override;
        int Initial_Damage() const;
        size_t XP() const;
        EnemyType Type() const;

        void Effect_Action(EffectType type) override;

        virtual std::array<std::unique_ptr<Item>, 3> dropItem();
        
        // Clone method for creating copies
        virtual std::unique_ptr<Entity> clone() const;
        
        // Static factory methods for enemy types
        static Enemy Normal(int startX, int startY);
        static Enemy Tank(int startX, int startY);
        static Enemy Poison(int startX, int startY);
        static Enemy Healer(int startX, int startY);
        static Enemy Wizard(int startX, int startY);

        friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
};
