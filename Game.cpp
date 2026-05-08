#include"Game.h"
#include"Enemy.h"
#include"Boss.h"
#include"Tool.h"
#include"Weapon.h"
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<limits>

Game::Game(const std::string& playerName) : 
world(std::make_unique<World>()), 
player(std::make_unique<Player>(playerName, 5, 5, 100, 10, 0)),
currentZone(nullptr),
currentFloor(1),
enemyUpdateCounter(0),
playerActionCounter(0),
hasKilled(false),
hasBroken(false) {}

void Game::initialize() {
    world->InitializeFloors();
    world->SetActiveFloor(1);
    if(world->activeFloor) {
        currentZone = world->activeFloor->ActiveZone();
        currentFloor = world->activeFloor->FloorNumber();
    }
    
    // Place player at center of starting zone
    if(currentZone) {
        Vector2 center = currentZone->Center();
        player->move(center.x - player->PosX(), center.y - player->PosY());
    }
}

bool Game::canMoveTo(int x, int y) const {
    return canMoveTo(x, y, nullptr);
}

bool Game::canMoveTo(int x, int y, const Entity* ignoreEntity) const {
    Tile* tile = currentZone->getTile(x, y);
    if(!tile) return false;
    if(!tile->Walkable()) return false;
    
    // Check for entity collision, ignoring one entity if requested
    for(const auto& entity : currentZone->getEntities()) {
        if(ignoreEntity && entity.get() == ignoreEntity) {
            continue;
        }
        if(entity->PosX() == x && entity->PosY() == y) {
            return false;
        }
    }
    
    return true;
}

void Game::checkCollisions(int newX, int newY) {
    Tile* tile = currentZone->getTile(newX, newY);
    if(!tile) return;
    
    // Check if stepping on zone exit
    if(tile->Type() == TileType::ZONE_EXIT) {
        if(handleFinalFloorExit()) {
            return;
        }

        if(world->activeFloor && world->activeFloor->NextZone()) {
            currentZone = world->activeFloor->ActiveZone();
            Vector2 center = currentZone->Center();
            player->move(center.x - player->PosX(), center.y - player->PosY());
            std::cout << "You move into the next zone." << std::endl;
        } else if(world->NextFloor()) {
            currentFloor = world->activeFloor->FloorNumber();
            currentZone = world->activeFloor->ActiveZone();
            if(currentZone) {
                Vector2 center = currentZone->Center();
                player->move(center.x - player->PosX(), center.y - player->PosY());
            }
            std::cout << "You descend to floor " << currentFloor << "." << std::endl;
        } else {
            std::cout << "You have reached the final floor." << std::endl;
        }
    }
}

bool Game::isFinalFloorFinalZone() const {
    if(!world->activeFloor) {
        return false;
    }

    return currentFloor == world->TotalFloors() &&
           world->activeFloor->ActiveZoneIndex() == world->activeFloor->Number_ofZones() - 1;
}

bool Game::handleFinalFloorExit() const {
    if(!isFinalFloorFinalZone()) {
        return false;
    }

    bool bossAlive = false;
    for(const auto& entity : currentZone->getEntities()) {
        Boss* boss = dynamic_cast<Boss*>(entity.get());
        if(boss) {
            bossAlive = boss->isAlive();
            break;
        }
    }

    if(bossAlive) {
        if(hasKilled) {
            std::cout << "Neutral Ending: You have escaped the Etherite Mines but with your hands stained!" << std::endl;
            exit(0);
        } else {
            if(player->InventorySize() == 0 && !hasBroken) {
                std::cout << "Escaper\'s Ending: You have escaped only, that\'s it. You didn\'t even play the game properly... What\'s wrong with you!" << std::endl;
                exit(0);
            }
            else if(player->InventorySize() == 0) {
                std::cout << "Weird Ending: You weirdo! You emptied your inventory and for what? Why?" << std::endl;
                exit(0);
            }
            else {
                std::cout << "Pacifist Ending: You spare the Etherite Protector and leave the mines in it\'s protection!" << std::endl;
                exit(0);
            }
        }
    } else {
        std::cout << "Greedy Ending: You have slain the Etherite Protector and claimed the Etherite mines for yourself!" << std::endl;
        exit(0);
    }

    return true;
}

void Game::updateEnemies() {
    for(auto& entity : currentZone->getEntities()) {
        // Check if it's an enemy
        Enemy* enemy = dynamic_cast<Enemy*>(entity.get());
        if(enemy && enemy->isAlive()) {
            // Determine intended AI move
            auto move = enemy->calculateAIMove(*player, currentZone->getEntities());
            int oldX = enemy->PosX();
            int oldY = enemy->PosY();

            auto attemptMove = [&](int moveX, int moveY) {
                enemy->update(moveX, moveY);
                int newX = enemy->PosX();
                int newY = enemy->PosY();
                if(canMoveTo(newX, newY, enemy)) {
                    return true;
                }
                enemy->move(oldX - newX, oldY - newY);
                return false;
            };

            bool moved = attemptMove(move.first, move.second);
            if(!moved && (move.first != 0 || move.second != 0)) {
                std::vector<std::pair<int,int>> alternatives;
                for(int dx = -1; dx <= 1; dx++) {
                    for(int dy = -1; dy <= 1; dy++) {
                        if(dx == 0 && dy == 0) continue;
                        alternatives.emplace_back(dx, dy);
                    }
                }

                std::sort(alternatives.begin(), alternatives.end(), [&](const auto& a, const auto& b) {
                    int scoreA = a.first * move.first + a.second * move.second;
                    int scoreB = b.first * move.first + b.second * move.second;
                    return scoreA > scoreB;
                });

                for(const auto& alt : alternatives) {
                    if(alt == move) continue;
                    if(attemptMove(alt.first, alt.second)) {
                        moved = true;
                        break;
                    }
                }
            }

            int newX = enemy->PosX();
            int newY = enemy->PosY();
            int dx = std::abs(player->PosX() - newX);
            int dy = std::abs(player->PosY() - newY);
            if(dx <= 1 && dy <= 1 && (dx + dy > 0)) {
                enemy->attack(*player);
                if(enemy->Type() == EnemyType::WIZARD) {
                    enemy->MarkAttackedPlayer();
                }
            }

            // Apply effects
            enemy->Effect_Action(EffectType::HEAL);
        }
    }

    // Remove dead enemies
    currentZone->removeDeadEntities();
}

Entity* Game::targetEnemy() {
    Vector2 playerPos(player->PosX(), player->PosY());
    Entity* closestEnemy = nullptr;
    int minDist = 999;
    for(auto& entity : currentZone->getEntities()) {
        Enemy* enemy = dynamic_cast<Enemy*>(entity.get());
        if(enemy && enemy->isAlive()) {
            Vector2 enemyPos(enemy->PosX(), enemy->PosY());
            int dist = std::max(std::abs(playerPos.x - enemyPos.x), std::abs(playerPos.y - enemyPos.y));
            if(dist < minDist) {
                minDist = dist;
                closestEnemy = enemy;
            }
        }
    }
    return closestEnemy;
}

void Game::craft() {
    int craftIdx;
    std::cout<<"What do you wish to craft?\n"
    <<"01. Wooden Pickaxe\n"
    <<"02. Wooden Axe\n"
    <<"03. Wooden Sword\n"
    <<"04. Wooden Spear\n"
    <<"05. Stone Pickaxe\n"
    <<"06. Stone Axe\n"
    <<"07. Stone Sword\n"
    <<"08. Stone Spear\n"
    <<"09. Iron Pickaxe\n"
    <<"10. Iron Axe\n"
    <<"11. Iron Sword\n"
    <<"12. Iron Spear\n"
    <<"13. Titanium Pickaxe\n"
    <<"14. Titanium Axe\n"
    <<"15. Titanium Sword\n"
    <<"16. Titanium Spear\n"
    <<"17. Etherite Pickaxe\n"
    <<"18. Etherite Axe\n"
    <<"19. Etherite Sword\n"
    <<"20. Etherite Spear\n"
    <<"Choice: ";
    if(!(std::cin >> craftIdx)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Crafting canceled." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::unique_ptr<Item> crafting_item;

    switch(craftIdx) {
        case 1:
            crafting_item = std::make_unique<Tool>(Tool::WoodenPickaxe());
            break;
        case 2:
            crafting_item = std::make_unique<Tool>(Tool::WoodenAxe());
            break;
        case 3:
            crafting_item = std::make_unique<Weapon>(Weapon::WoodenSword());
            break;
        case 4:
            crafting_item = std::make_unique<Weapon>(Weapon::WoodenSpear());
            break;
        case 5:
            crafting_item = std::make_unique<Tool>(Tool::StonePickaxe());
            break;
        case 6:
            crafting_item = std::make_unique<Tool>(Tool::StoneAxe());
            break;
        case 7:
            crafting_item = std::make_unique<Weapon>(Weapon::StoneSword());
            break;
        case 8:
            crafting_item = std::make_unique<Weapon>(Weapon::StoneSpear());
            break;
        case 9:
            crafting_item = std::make_unique<Tool>(Tool::IronPickaxe());
            break;
        case 10:
            crafting_item = std::make_unique<Tool>(Tool::IronAxe());
            break;
        case 11:
            crafting_item = std::make_unique<Weapon>(Weapon::IronSword());
            break;
        case 12:
            crafting_item = std::make_unique<Weapon>(Weapon::IronSpear());
            break;
        case 13:
            crafting_item = std::make_unique<Tool>(Tool::TitaniumPickaxe());
            break;
        case 14:
            crafting_item = std::make_unique<Tool>(Tool::TitaniumAxe());
            break;
        case 15:
            crafting_item = std::make_unique<Weapon>(Weapon::TitaniumSword());
            break;
        case 16:
            crafting_item = std::make_unique<Weapon>(Weapon::TitaniumSpear());
            break;
        case 17:
            crafting_item = std::make_unique<Tool>(Tool::EtheritePickaxe());
            break;
        case 18:
            crafting_item = std::make_unique<Tool>(Tool::EtheriteAxe());
            break;
        case 19:
            crafting_item = std::make_unique<Weapon>(Weapon::EtheriteSword());
            break;
        case 20:
            crafting_item = std::make_unique<Weapon>(Weapon::EtheriteSpear());
            break;
        default:
            std::cout << "Invalid craft selection." << std::endl;
            return;
    }

    std::vector<ItemStack> recipe;
    if(auto toolptr = dynamic_cast<Tool*>(crafting_item.get())) {
        recipe = toolptr->Recipe();
    } else if(auto weaponptr = dynamic_cast<Weapon*>(crafting_item.get())) {
        recipe = weaponptr->Recipe();
    } else {
        std::cout << "Unable to craft this item." << std::endl;
        return;
    }

    if(recipe.empty()) {
        player->addItem(crafting_item->clone(), 1);
        std::cout << crafting_item->Name() << " crafted." << std::endl;
        return;
    }

    std::vector<int> tempAmounts(player->getInventory().size());
    for(int i = 0; i < player->getInventory().size(); i++) {
        tempAmounts[i] = static_cast<int>(player->getInventory()[i].amount);
    }

    std::vector<std::pair<int, int>> ingredient_slots;
    for(const auto& ingredient : recipe) {
        int needed = static_cast<int>(ingredient.amount);
        for(int i = 0; i < player->getInventory().size() && needed > 0; i++) {
            const auto& invItem = player->getInventory()[i];
            if(!invItem.item || invItem.item->Name() != ingredient.item->Name()) {
                continue;
            }

            int take = std::min(needed, tempAmounts[i]);
            if(take <= 0) {
                continue;
            }

            tempAmounts[i] -= take;
            needed -= take;

            bool merged = false;
            for(auto& slotAmount : ingredient_slots) {
                if(slotAmount.first == i) {
                    slotAmount.second += take;
                    merged = true;
                    break;
                }
            }
            if(!merged) {
                ingredient_slots.emplace_back(i, take);
            }
        }

        if(needed > 0) {
            std::cout << "Missing required ingredients for " << crafting_item->Name() << "." << std::endl;
            return;
        }
    }

    std::sort(ingredient_slots.begin(), ingredient_slots.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    for(const auto& slotAmount : ingredient_slots) {
        player->useItem(slotAmount.first, slotAmount.second);
    }

    player->addItem(crafting_item->clone(), 1);
    std::cout << crafting_item->Name() << " crafted." << std::endl;
}

void Game::throwPotion(int itemIndex) {
    if(itemIndex < 0 || itemIndex >= player->InventorySize()) {
        return;
    }
    
    Entity* target = targetEnemy();
    if(!target) {
        return;
    }

    Item* item = player->getItemAt(itemIndex);
    if(!item || item->Type() != ItemType::POTION) {
        return;
    }

    bool wasAlive = target->isAlive();
    player->useItem(target, itemIndex);
    if(wasAlive && !target->isAlive()) {
        hasKilled = true;
    }
}

void Game::tick(GameAction action, int itemIndex) {
    int moveX = 0, moveY = 0;
    
    switch(action) {
        case GameAction::MOVE_UP:
            moveY = -1;
            break;
        case GameAction::MOVE_DOWN:
            moveY = 1;
            break;
        case GameAction::MOVE_LEFT:
            moveX = -1;
            break;
        case GameAction::MOVE_RIGHT:
            moveX = 1;
            break;
        case GameAction::ATTACK: {
            // Find enemies in range and attack closest
            Entity* target = nullptr;
            int minDist = PLAYER_ATTACK_RANGE + 1;
            for(auto& entity : currentZone->getEntities()) {
                int dx = std::abs(player->PosX() - entity->PosX());
                int dy = std::abs(player->PosY() - entity->PosY());
                int dist = std::max(dx, dy);
                if(dist <= PLAYER_ATTACK_RANGE && dist < minDist) {
                    target = entity.get();
                    minDist = dist;
                }
            }
            if(target) {
                bool wasAlive = target->isAlive();
                player->attack(*target);
                if(wasAlive && !target->isAlive()) {
                    hasKilled = true;
                }
                Boss* bossTarget = dynamic_cast<Boss*>(target);
                if(bossTarget && bossTarget->isAlive()) {
                    std::cout<<*bossTarget<<std::endl;
                }
                Enemy* enemyTarget = dynamic_cast<Enemy*>(target);
                if(enemyTarget && enemyTarget->isAlive() && !bossTarget) {
                    std::cout<<*enemyTarget<<std::endl;
                }
            }
            break;
        }
        case GameAction::BREAK_RESOURCE: {
            // Check adjacent tiles for breakable resources
            int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
            bool broke_something = false;
            bool found_breakable = false;
            const Item* equipped = player->getEquippedItem();
            const Tool* tool = nullptr;
            if(equipped && equipped->Type() == ItemType::TOOL) {
                tool = dynamic_cast<const Tool*>(equipped);
            }

            for(int i = 0; i < 4; i++) {
                int checkX = player->PosX() + dirs[i][0];
                int checkY = player->PosY() + dirs[i][1];
                Tile* tile = currentZone->getTile(checkX, checkY);
                if(tile && tile->Breakable()) {
                    Breakable* resource = dynamic_cast<Breakable*>(tile);
                    if(resource) {
                        found_breakable = true;
                        ResourceType resType = resource->Type();
                        bool canBreak = false;

                        if(tool == nullptr) {
                            if(resType == ResourceType::BARREL0) {
                                canBreak = true;
                            }
                        } else {
                            for(const auto& allowed : tool->CanBreak()) {
                                if(allowed == resType) {
                                    canBreak = true;
                                    break;
                                }
                            }
                        }

                        if(!canBreak) {
                            continue;
                        }

                        // Get the drop and add to inventory
                        ItemStack& drop = resource->Drop();
                        if(drop.item && drop.amount > 0) {
                            player->addItem(std::move(drop.item), drop.amount);
                            std::cout << "Collected resource!" << std::endl;
                            hasBroken = true;
                        }
                        // Replace with ground
                        tile->ReplaceTile(Tile());
                        broke_something = true;
                        break;
                    }
                }
            }

            if(!broke_something) {
                if(found_breakable && tool == nullptr) {
                    std::cout << "You need a tool equipped to break that resource." << std::endl;
                } else if(found_breakable) {
                    std::cout << "Your equipped tool cannot break any adjacent resource." << std::endl;
                } else {
                    std::cout << "No breakable resource nearby!" << std::endl;
                }
                return; // Don't count as a tick
            }

            playerActionCounter++;
            if(playerActionCounter >= 5) {
                playerActionCounter = 0;
                player->Healing(5);
                std::cout << "You feel a surge of vitality!" << std::endl;
            }
            break;
        }
        case GameAction::USE_ITEM:
            if(itemIndex >= 0) {
                player->useItem(itemIndex);
            }
            displayPlayerStats();
            return; // Inventory actions do not count as a tick
        case GameAction::EQUIP_ITEM:
            if(itemIndex >= 0) {
                player->equipItem(itemIndex);
            }
            return; // Inventory actions do not count as a tick
        case GameAction::DROP_ITEM:
            if(itemIndex >= 0) {
                player->dropItem(itemIndex);
            }
            return; // Inventory actions do not count as a tick
        case GameAction::OPEN_INVENTORY:
            displayInventory();
            return; // Don't update game state
        case GameAction::CRAFT:
            craft();
            return; // Crafting handles its own updates
        case GameAction::THROW_POTION:
            throwPotion(itemIndex);
            break;
        case GameAction::NONE:
            return; // No action, no tick
    }
    
    // Handle movement
    if(moveX != 0 || moveY != 0) {
        int newX = player->PosX() + moveX;
        int newY = player->PosY() + moveY;
        
        if(canMoveTo(newX, newY)) {
            player->update(moveX, moveY);
            playerActionCounter++;
            if(playerActionCounter >= 5) {
                playerActionCounter = 0;
                player->Healing(5);
                std::cout << "You feel a surge of vitality!" << std::endl;
            }
            checkCollisions(newX, newY);
        }
    }
    
    // Update enemies every 2 ticks
    enemyUpdateCounter++;
    if (enemyUpdateCounter % 2 == 0) {
        updateEnemies();
    }
    
    // Apply player effects
    player->Effect_Action(EffectType::HEAL);
}

void Game::displayZone() const {
    if(!currentZone) return;
    
    std::cout << "\n_";
    for(int x = 0; x < currentZone->ZoneWidth(); x++) std::cout << "_";
    std::cout << "_" << std::endl;
    
    for(int y = 0; y < currentZone->ZoneLength(); y++) {
        std::cout << "|";
        for(int x = 0; x < currentZone->ZoneWidth(); x++) {
            // Check if player is here
            if(player->PosX() == x && player->PosY() == y) {
                std::cout << 'P';
                continue;
            }
            
            // Check if any entity is here
            bool entityFound = false;
            for(const auto& entity : currentZone->getEntities()) {
                if(entity->PosX() == x && entity->PosY() == y) {
                    std::cout << entity->getSymbol();
                    entityFound = true;
                    break;
                }
            }
            if(entityFound) continue;
            
            // Display tile
            Tile* tile = currentZone->getTile(x, y);
            if(tile) {
                switch(tile->Type()) {
                    case TileType::GROUND:
                        std::cout << ' ';
                        break;
                    case TileType::WALL:
                        std::cout << '#';
                        break;
                    case TileType::ZONE_BOUNDARY:
                        std::cout << '#';
                        break;
                    case TileType::ZONE_EXIT:
                        std::cout << 'X';
                        break;
                    case TileType::RESOURCE: {
                        Breakable* resource = dynamic_cast<Breakable*>(tile);
                        if(resource) {
                            switch(resource->Type()) {
                                case ResourceType::TREE:
                                    std::cout << 't';
                                    break;
                                case ResourceType::STONE:
                                    std::cout << 's';
                                    break;
                                case ResourceType::IRON:
                                    std::cout << 'i';
                                    break;
                                case ResourceType::TITANIUM:
                                    std::cout << 'T';
                                    break;
                                case ResourceType::BARREL0:
                                case ResourceType::BARREL1:
                                case ResourceType::BARREL2:
                                case ResourceType::BARREL3:
                                case ResourceType::BARREL4:
                                case ResourceType::BARREL5:
                                    std::cout << 'b';
                                    break;
                            }
                        } else {
                            std::cout << 'R';
                        }
                        break;
                    }
                }
            }
        }
        std::cout << "|" << std::endl;
    }
    
    std::cout << "_";
    for(int x = 0; x < currentZone->ZoneWidth(); x++) std::cout << "_";
    std::cout << "_" << std::endl;
}

void Game::displayInventory() const {
    std::cout << "\n=== INVENTORY ===" << std::endl;
    std::cout << "Equipped: " << (player->getEquippedItem() ? player->getEquippedItem()->Name() : "Nothing") << std::endl;
    std::cout << "\nItems (" << player->InventorySize() << "/" << MAX_INVENTORY_SIZE << "):" << std::endl;
    
    const auto& inv = player->getInventory();
    for(size_t i = 0; i < inv.size(); i++) {
        if(inv[i].item) {
            std::cout << "[" << i << "] " << inv[i].item->Name() 
                     << " x" << inv[i].amount << std::endl;
        }
    }
    std::cout << "=================" << std::endl;
}

void Game::displayPlayerStats() const {
    std::cout << "\n=== Player Stats ===" << std::endl;
    std::cout << "Name: " << player->Name() << std::endl;
    std::cout << "HP: " << player->HP() << "/" << player->MaxHP() << std::endl;
    std::cout << "Defense: " << player->Defense() << std::endl;
    std::cout << "Damage: " << player->Damage() << std::endl;
    std::cout << "XP: " << player->XP() << std::endl;
    std::cout << "Position: (" << player->PosX() << ", " << player->PosY() << ")" << std::endl;
    std::cout << "Effects:\n";
    if(player->Effects().empty()) {
        std::cout << " None";
    } else {
        for(const auto& [type, effect] : player->Effects()) {
            std::cout << effect << std::endl;
        }
    }
    std::cout << "====================" << std::endl;
}

Player* Game::getPlayer() const { return player.get(); }
Zone* Game::getCurrentZone() const { return currentZone; }
int Game::getCurrentFloor() const { return currentFloor; }
