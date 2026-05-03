#include"Breakable.h"

Breakable::Breakable(ResourceType Type) : 
Tile(TileType::RESOURCE, false, true), type(Type) {}
#include"Breakable.h"
#include"Utility.h"
#include"Weapon.h"
#include"Tool.h"
#include"Potion.h"

Breakable::Breakable(ResourceType Type) : 
Tile(TileType::RESOURCE, false, true), type(Type), rd(), gen(rd), drop() {
    std::uniform_int_distribution<> dist(0,2);
    int amt = dist(gen);
    switch(type) {
        case ResourceType::TREE:
            drop = ItemStack(Utility::Wood().clone(), amt);
            break;
        case ResourceType::STONE:
            drop = ItemStack(Utility::Stone().clone(), amt);
            break;
        case ResourceType::IRON:
            drop = ItemStack(Utility::Iron().clone(), amt);
            break;
        case ResourceType::TITANIUM:
            drop = ItemStack(Utility::Titanium().clone(), amt);
            break;
        case ResourceType::BARREL0:
            switch(amt) {
                case 0:
                    drop = ItemStack(Tool::WoodenAxe().clone(), 1);
                    break;
                case 1:
                    drop = ItemStack(Utility::Wood().clone(), 1);
                    break;
                case 2:
                    drop = ItemStack(Utility::Wood().clone(), 2);
                    break;
            }
            break;
        case ResourceType::BARREL1:
            switch(amt) {
                case 0:
                    drop = ItemStack(Tool::WoodenPickaxe().clone(), 1);
                    break;
                case 1:
                    drop = ItemStack(Utility::Stone().clone(), 1);
                    break;
                case 2:
                    drop = ItemStack(Potion::SelfHealing().clone(), 1);
                    break;
            }
            break;
        case ResourceType::BARREL2:
            switch(amt) {
                case 0:
                    drop = ItemStack(Tool::IronAxe().clone(), 1);
                    break;
                case 1:
                    drop = ItemStack(Potion::Vulnerability().clone(), 1);
                    break;
                case 2:
                    drop = ItemStack(Potion::Resistance().clone(), 1);
                    break;
            }
            break;
        case ResourceType::BARREL3:
            switch(amt) {
                case 0:
                    drop = ItemStack(Utility::Etherite().clone(), 1);
                    break;
                case 1:
                    drop = ItemStack(Utility::Etherite().clone(), 1);
                    break;
                case 2:
                    drop = ItemStack(Potion::Weakness().clone(), 1);
                    break;
            }
            break;
        case ResourceType::BARREL4:
            switch(amt) {
                case 0:
                    drop = ItemStack(Potion::SelfHealing().clone(), 1);
                    break;
                case 1:
                    drop = ItemStack(Utility::Etherite().clone(), 2);
                    break;
                case 2:
                    drop = ItemStack(Utility::Etherite().clone(), 2);
                    break;
            }
            break;
        case ResourceType::BARREL5:
            switch(amt) {
                case 0:
                    drop = ItemStack(Potion::Poison().clone(), 1);
                    break;
                case 1:
                    drop = ItemStack(Potion::Resistance().clone(), 1);
                    break;
                case 2:
                    drop = ItemStack(Potion::Strength().clone(), 1);
                    break;
            }
            break;
    }
}
