#include<string>

class Weapon : public Item {
private:
    int damage;

public:
    Weapon(const std::string& name, int dmg)
    :Item(name){
        damage = dmg;
    }

    void use(Player& player) override;
};
