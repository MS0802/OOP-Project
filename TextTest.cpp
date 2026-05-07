#include"Game.h"
#include<iostream>
#include<string>
#include<limits>

void printControls() {
    std::cout << "\n________________________________________" << std::endl;
    std::cout << "|           CONTROLS MENU              |" << std::endl;
    std::cout << "|--------------------------------------|" << std::endl;
    std::cout << "| MOVEMENT                             |" << std::endl;
    std::cout << "| w - Move up      | a - Move left     |" << std::endl;
    std::cout << "| s - Move down    | d - Move right    |" << std::endl;
    std::cout << "|                                      |" << std::endl;
    std::cout << "| COMBAT                               |" << std::endl;
    std::cout << "| k - Attack nearest enemy             |" << std::endl;
    std::cout << "| t [index] - Throw potion at enemy    |" << std::endl;
    std::cout << "|                                      |" << std::endl;
    std::cout << "| RESOURCES                            |" << std::endl;
    std::cout << "| b - Break adjacent resource          |" << std::endl;
    std::cout << "| c - Craft tools/weapons              |" << std::endl;
    std::cout << "|                                      |" << std::endl;
    std::cout << "| INVENTORY                            |" << std::endl;
    std::cout << "| i - Show inventory                   |" << std::endl;
    std::cout << "| u [index] - Use/Drink item           |" << std::endl;
    std::cout << "| e [index] - Equip weapon/tool        |" << std::endl;
    std::cout << "| r [index] - Drop item                |" << std::endl;
    std::cout << "|                                      |" << std::endl;
    std::cout << "| INFO                                 |" << std::endl;
    std::cout << "| p - Show player stats                |" << std::endl;
    std::cout << "| h - Show this help                   |" << std::endl;
    std::cout << "| q - Quit game                        |" << std::endl;
    std::cout << "________________________________________" << std::endl;
}

int main() {
    Game game;
    game.initialize();
    
    std::cout << "=== OOP Dungeon Game ===" << std::endl;
    std::cout << "Welcome! Each action is a tick." << std::endl;
    printControls();
    
    bool running = true;
    std::string input;
    bool showZone = true;
    
    while(running) {
        if(showZone) {
            game.displayZone();
        }
        
        std::cout << "\nEnter command: ";
        std::getline(std::cin, input);
        
        if(input.empty()) continue;
        
        GameAction action = GameAction::NONE;
        int itemIndex = -1;
        
        // Parse input
        char cmd = input[0];
        switch(cmd) {
            case 'w':
                action = GameAction::MOVE_UP;
                break;
            case 's':
                action = GameAction::MOVE_DOWN;
                break;
            case 'a':
                action = GameAction::MOVE_LEFT;
                break;
            case 'd':
                action = GameAction::MOVE_RIGHT;
                break;
            case 'k':
                action = GameAction::ATTACK;
                break;
            case 'b':
                action = GameAction::BREAK_RESOURCE;
                break;
            case 'i':
                action = GameAction::OPEN_INVENTORY;
                break;
            case 'u':
                action = GameAction::USE_ITEM;
                if(input.length() > 2) {
                    itemIndex = input[2] - '0';
                }
                break;
            case 'e':
                action = GameAction::EQUIP_ITEM;
                if(input.length() > 2) {
                    itemIndex = input[2] - '0';
                }
                break;
            case 'r':
                action = GameAction::DROP_ITEM;
                if(input.length() > 2) {
                    itemIndex = input[2] - '0';
                }
                break;
            case 'c':
                action = GameAction::CRAFT;
                break;
            case 't':
                action = GameAction::THROW_POTION;
                if(input.length() > 2) {
                    itemIndex = input[2] - '0';
                }
                break;
            case 'p':
                game.displayPlayerStats();
                continue;
            case 'h':
                printControls();
                continue;
            case 'q':
                std::cout << "Thanks for playing!" << std::endl;
                running = false;
                continue;
            default:
                std::cout << "Unknown command. Press 'h' for help." << std::endl;
                continue;
        }
        
        // Execute action and update game (1 tick for non-inventory actions)
        game.tick(action, itemIndex);
        
        // Determine whether next loop should redraw the board
        switch(action) {
            case GameAction::OPEN_INVENTORY:
            case GameAction::USE_ITEM:
            case GameAction::EQUIP_ITEM:
            case GameAction::DROP_ITEM:
                showZone = false;
                break;
            default:
                showZone = true;
                break;
        }
        
        // Check if player is dead
        if(!game.getPlayer()->isAlive()) {
            std::cout << "\n=== GAME OVER ===" << std::endl;
            std::cout << "You died!" << std::endl;
            running = false;
        }
    }
    
    return 0;
}
