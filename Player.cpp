#include"Player.h"
#include"Weapon.h"
#include"Potion.h"
#include"Tool.h"
#include<iostream>
#include<algorithm>

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
    int totalDamage = Damage();
    
    // Check for strength effect
    if(effects.count(EffectType::STRENGTH)) {
        totalDamage += strengthValue;
    }
    
    target.takeDamage(totalDamage);
}

bool Player::canAttack(const Entity& target) const {
    int dx = std::abs(position.x - target.PosX());
    int dy = std::abs(position.y - target.PosY());
    int distance = std::max(dx, dy);
    return distance <= PLAYER_ATTACK_RANGE;
}

void Player::useItem(int index, int amt) {
    if(index < 0 || index >= inventory.size()) {
        return;
    }
    
    if(inventory[index].item == nullptr) {
        return;
    }
    
    ItemType type = inventory[index].item->Type();
    
    switch(type) {
        case ItemType::POTION: {
            Potion* potion = dynamic_cast<Potion*>(inventory[index].item.get());
            if(potion) {
                potion->use(*this);
                inventory[index].amount--;
                if(inventory[index].amount <= 0) {
                    inventory.erase(inventory.begin() + index);
                }
            }
            break;
        }
        case ItemType::WEAPON:
        case ItemType::TOOL:
            equipItem(index);
            break;
        case ItemType::UTILITY:
            if(amt) {
                if(amt < inventory[index].amount) {
                    inventory[index].amount -= amt;
                }
                else if (amt == inventory[index].amount) {
                    inventory.erase(inventory.begin() + index);
                }
            }
            break;
    }
}

void Player::useItem(Entity* target, int index) {
    if(index < 0 || index >= inventory.size()) {
        return;
    }
    
    if(inventory[index].item == nullptr) {
        return;
    }
    
    if(inventory[index].item->Type() == ItemType::POTION) {
        Potion* potion = dynamic_cast<Potion*>(inventory[index].item.get());
        if(potion) {
            potion->use(target);
            inventory[index].amount--;
            if(inventory[index].amount <= 0) {
                inventory.erase(inventory.begin() + index);
            }
        }
    }
}

void Player::equipItem(int index) {
    if(index < 0 || index >= inventory.size()) {
        return;
    }
    
    if(inventory[index].item == nullptr) {
        return;
    }
    
    ItemType type = inventory[index].item->Type();
    if(type != ItemType::WEAPON && type != ItemType::TOOL) {
        return;
    }
    
    // Swap with currently equipped item
    if(on_Hand != nullptr) {
        std::unique_ptr<Item> temp = std::move(on_Hand);
        on_Hand = inventory[index].item->clone();
        inventory[index].item = std::move(temp);
    } else {
        on_Hand = inventory[index].item->clone();
        inventory[index].amount--;
        if(inventory[index].amount <= 0) {
            inventory.erase(inventory.begin() + index);
        }
    }
}

void Player::dropItem(int index) {
    if(index < 0 || index >= inventory.size()) {
        return;
    }
    
    inventory.erase(inventory.begin() + index);
}

void Player::displayInventory() const {
    for(size_t i = 0; i < inventory.size(); i++) {
        if(inventory[i].item) {
            std::cout << "[" << i << "] " << inventory[i].item->Name() 
                     << " x" << inventory[i].amount << std::endl;
        }
    }
}

Item* Player::getItemAt(int index) {
    if(index < 0 || index >= inventory.size()) {
        return nullptr;
    }
    return inventory[index].item.get();
}

void Player::addItem(std::unique_ptr<Item> item, int amount) {
    if(item == nullptr || amount <= 0) return;
    
    // Check if inventory is full
    if(inventory.size() >= MAX_INVENTORY_SIZE) {
        return;
    }
    
    // Try to stack with existing items
    for(auto& stack : inventory) {
        if(stack.item && stack.item->Name() == item->Name() && 
           stack.amount < stack.item->StackSize()) {
            int spaceLeft = stack.item->StackSize() - stack.amount;
            int toAdd = std::min(spaceLeft, amount);
            stack.amount += toAdd;
            amount -= toAdd;
            
            if(amount <= 0) return;
        }
    }
    
    // Add new stack if there's still items left
    if(amount > 0 && inventory.size() < MAX_INVENTORY_SIZE) {
        inventory.push_back(ItemStack(std::move(item), amount));
    }
}

void Player::Effect_Action(EffectType type) {
    std::vector<EffectType> toRemove;
    
    for(auto& effectPair : effects) {
        EffectType effectType = effectPair.first;
        Effect& e = effectPair.second;
        
        if(e.Can_Give() || e.Time() == 0) { 
            if(e.Time() == 0) {
                toRemove.push_back(effectType);
            }
            continue; 
        }
        
        e.Time()--;
        
        switch(effectType) {
            case EffectType::HEAL:
                Healing(healingValue);
                break;
            case EffectType::POISON:
                takeDamage(poisonDamage);
                break;
            case EffectType::STRENGTH:
                // Strength is applied in Damage() calculation
                break;
            case EffectType::WEAKNESS:
                // Weakness is applied in Damage() calculation
                break;
            case EffectType::RESISTANCE:
                if(defense == initialDefense) {
                    defense += resistanceValue;
                }
                break;
            case EffectType::VULNERABLE:
                if(defense == initialDefense) {
                    if(defense - vulnerableDefense <= 0) { defense = 0; }
                    else { defense -= vulnerableDefense; }
                }
                break;
        }
    }
    
    // Remove expired effects
    for(const auto& effectType : toRemove) {
        effects.erase(effectType);
    }
}

int Player::XP() const { return xp; }
int Player::InventorySize() const { return inventory.size(); }
bool Player::isInventoryFull() const { return inventory.size() >= MAX_INVENTORY_SIZE; }
std::unordered_map<EffectType, Effect> Player::Effects() const { return effects; }

const std::vector<ItemStack>& Player::getInventory() const { return inventory; }
const Item* Player::getEquippedItem() const { return on_Hand.get(); }
