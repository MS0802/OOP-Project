#include"Player.h"
#include"Weapon.h"

Player::Player(const std::string& Name, int startX, int startY, int HP, int Defense, int XP) : 
Entity(Name, startX, startY, HP, Defense), xp(XP), inventory(), on_Hand(nullptr) {}

Player::Player() : 
Entity(), xp(0), inventory(), on_Hand(nullptr) {}

void Player::update(int pX, int pY) {
    position.x += pX;
    position.y += pY;
}

char Player::getSymbol() const { return 'P'; }
int Player::Damage() const {
    if(on_Hand != nullptr && on_Hand->Type() == ItemType::WEAPON) {
        Weapon* onhandWeapon = dynamic_cast<Weapon*>(on_Hand.get());
        int dmg = onhandWeapon->Damage();
        return dmg;
    }
    return DefaultPlayerDamage;
}

void Player::attack(Entity& target) {
    //code left
}

void Player::useItem(int index) {
    //code left
}

void Player::addItem(std::unique_ptr<Item> item, int amount) {
    inventory.push_back(ItemStack(std::move(item), amount));
}

void Player::Effect_Action(EffectType type) {
    //effect
}

int Player::XP() const { return xp; }
int Player::InventorySize() const { return inventory.size(); }
