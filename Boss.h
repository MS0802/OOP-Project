#pragma once
#include"Enemy.h"
#include<vector>
#include<iostream>

class Boss : public Enemy {
    protected:
        const int regenerationFactor;
    public:
        Boss(std::string name, int startX, int startY, int hp, int def, std::array<std::unique_ptr<Item>, 3> drops, int XP, int damage, int Regeneration_Factor);
        Boss(const Boss& other);

        char getSymbol()const override;

        void specialAttack(Entity& target);

        std::pair<int,int> calculateAIMove(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) const override;

        std::array<std::unique_ptr<Item>, 3> dropItem() override;
        
        // Clone method for creating copies
        std::unique_ptr<Entity> clone() const override;
        
        void updateAI(const Entity& player, const std::vector<std::unique_ptr<Entity>>& zoneEntities) override;
        
        // Static factory methods for boss types
        static Boss PoisonousStoneGolem(int startX, int startY);
        static Boss EtheriteProtector(int startX, int startY);

        friend std::ostream& operator<<(std::ostream& os, const Boss& boss);
};
