#include"Game.h"
#include<iostream>
#include<string>
#include<limits>

void printControls() {
    std::cout << "\n=== Controls ===" << std::endl;
    std::cout << "w/a/s/d - Move up/left/down/right" << std::endl;
    std::cout << "k - Attack nearest enemy" << std::endl;
    std::cout << "b - Break adjacent resource" << std::endl;
    std::cout << "i - Show inventory" << std::endl;
    std::cout << "u [index] - Use item" << std::endl;
    std::cout << "e [index] - Equip item" << std::endl;
    std::cout << "r [index] - Drop item" << std::endl;
    std::cout << "p - Show player stats" << std::endl;
    std::cout << "h - Show controls" << std::endl;
    std::cout << "q - Quit" << std::endl;
    std::cout << "================" << std::endl;
}

int main() {
    Game game;
    game.initialize();
    
    std::cout << "=== OOP Dungeon Game ===" << std::endl;
    std::cout << "Welcome! Each action is a tick." << std::endl;
    printControls();
    
    bool running = true;
    std::string input;
    
    while(running) {
        // Display current zone
        game.displayZone();
        game.displayPlayerStats();
        
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
        
        // Execute action and update game (1 tick)
        game.tick(action, itemIndex);
        
        // Check if player is dead
        if(!game.getPlayer()->isAlive()) {
            std::cout << "\n=== GAME OVER ===" << std::endl;
            std::cout << "You died!" << std::endl;
            running = false;
        }
    }
    
    return 0;
}
