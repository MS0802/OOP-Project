#include"Game.h"
#include"Enemy.h"
#include"Boss.h"
#include<iostream>
#include<iomanip>

Game::Game() : 
world(std::make_unique<World>()), 
player(std::make_unique<Player>("Hero", 5, 5, 100, 10, 0)),
currentZone(nullptr),
currentFloor(1) {}

void Game::initialize() {
    world->InitializeFloors();
    world->SetActiveFloor(1);
    currentZone = world->activeFloor->ActiveZone();
    
    // Place player at center of starting zone
    Vector2 center = currentZone->Center();
    player->move(center.x - player->PosX(), center.y - player->PosY());
}

bool Game::canMoveTo(int x, int y) const {
    Tile* tile = currentZone->getTile(x, y);
    if(!tile) return false;
    if(!tile->Walkable()) return false;
    
    // Check for entity collision
    for(const auto& entity : currentZone->getEntities()) {
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
        // TODO: Handle zone transition
    }
}

void Game::updateEnemies() {
    for(auto& entity : currentZone->getEntities()) {
        // Check if it's an enemy
        Enemy* enemy = dynamic_cast<Enemy*>(entity.get());
        if(enemy && enemy->isAlive()) {
            // Store old position
            int oldX = enemy->PosX();
            int oldY = enemy->PosY();
            
            // Update AI
            enemy->updateAI(*player);
            
            // Check if new position is valid
            int newX = enemy->PosX();
            int newY = enemy->PosY();
            
            if(!canMoveTo(newX, newY)) {
                // Revert move
                enemy->move(oldX - newX, oldY - newY);
            } else {
                // Check if enemy is adjacent to player for attack
                int dx = std::abs(player->PosX() - newX);
                int dy = std::abs(player->PosY() - newY);
                if(dx <= 1 && dy <= 1 && (dx + dy > 0)) {
                    enemy->attack(*player);
                }
            }
            
            // Apply effects
            enemy->Effect_Action(EffectType::HEAL);
        }
    }
    
    // Remove dead enemies
    currentZone->removeDeadEntities();
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
            int minDist = 999;
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
                player->attack(*target);
            }
            break;
        }
        case GameAction::BREAK_RESOURCE: {
            // Check adjacent tiles for breakable resources
            int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
            for(int i = 0; i < 4; i++) {
                int checkX = player->PosX() + dirs[i][0];
                int checkY = player->PosY() + dirs[i][1];
                Tile* tile = currentZone->getTile(checkX, checkY);
                if(tile && tile->Breakable()) {
                    // TODO: Break resource and add to inventory
                    // For now just replace with ground
                    tile->ReplaceTile(Tile());
                }
            }
            break;
        }
        case GameAction::USE_ITEM:
            if(itemIndex >= 0) {
                player->useItem(itemIndex);
            }
            break;
        case GameAction::EQUIP_ITEM:
            if(itemIndex >= 0) {
                player->equipItem(itemIndex);
            }
            break;
        case GameAction::DROP_ITEM:
            if(itemIndex >= 0) {
                player->dropItem(itemIndex);
            }
            break;
        case GameAction::OPEN_INVENTORY:
            displayInventory();
            return; // Don't update game state
        case GameAction::NONE:
            return; // No action, no tick
    }
    
    // Handle movement
    if(moveX != 0 || moveY != 0) {
        int newX = player->PosX() + moveX;
        int newY = player->PosY() + moveY;
        
        if(canMoveTo(newX, newY)) {
            player->update(moveX, moveY);
            checkCollisions(newX, newY);
        }
    }
    
    // Update enemies
    updateEnemies();
    
    // Apply player effects
    player->Effect_Action(EffectType::HEAL);
}

void Game::displayZone() const {
    if(!currentZone) return;
    
    std::cout << "\n=== Zone Display ===" << std::endl;
    
    for(int y = 0; y < currentZone->ZoneWidth(); y++) {
        for(int x = 0; x < currentZone->ZoneLength(); x++) {
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
                        std::cout << '.';
                        break;
                    case TileType::WALL:
                        std::cout << '#';
                        break;
                    case TileType::ZONE_BOUNDARY:
                        std::cout << '=';
                        break;
                    case TileType::ZONE_EXIT:
                        std::cout << 'X';
                        break;
                    case TileType::RESOURCE:
                        std::cout << 'R';
                        break;
                    default:
                        std::cout << '?';
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "===================" << std::endl;
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
    std::cout << "====================" << std::endl;
}

Player* Game::getPlayer() const { return player.get(); }
Zone* Game::getCurrentZone() const { return currentZone; }
int Game::getCurrentFloor() const { return currentFloor; }
