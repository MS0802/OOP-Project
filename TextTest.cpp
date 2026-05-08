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
    std::cout << "| m - Tile legend                      |" << std::endl;
    std::cout << "| q - Quit game                        |" << std::endl;
    std::cout << "________________________________________" << std::endl;
}

void printTiles() {
    std::cout << "\nTILE LEGEND:" << std::endl;
    std::cout << "P - Player" << std::endl;
    std::cout << "E - Enemy" << std::endl;
    std::cout << "B - Boss" << std::endl;
    std::cout << "# - Wall" << std::endl;
    std::cout << "t - Tree" << std::endl;
    std::cout << "s - Stone" << std::endl;
    std::cout << "i - Iron" << std::endl;
    std::cout << "T - Titanium" << std::endl;
    std::cout << "0 - Barrel0" << std::endl;
    std::cout << "1 - Barrel1 (can be broken with Wooden Axe)" << std::endl;
    std::cout << "2 - Barrel2 (can be broken with Stone Axe)" << std::endl;
    std::cout << "3 - Barrel3 (can be broken with Iron Axe)" << std::endl;
    std::cout << "4 - Barrel4 (can be broken with Titanium Axe)" << std::endl;
    std::cout << "5 - Barrel5 (can be broken with Etherite Axe)" << std::endl;
    std::cout << "X - Exit" << std::endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    std::cout << "=== The Etherite Mines ===" << std::endl;
    std::cout << "Long ago... a human lived and thrived!" << std::endl
    << "But one day, their boss assigned them a task..." << std::endl
    << "The task was to find the legendary Etherite..." << std::endl
    << "And to kill the Etherite Protector since it guarded the mines" << std::endl
    << "One Etherite... Powerful enough and extremely expensive..." << std::endl
    << "Then the human understood that they don\'t have to give it..." << std::endl
    << "They can just take it for themselves!" << std::endl
    << "And so, the human ventured into the mines..." << std::endl
    << "To find the Etherite and become the richest and most powerful human in history!" 
    << std::endl << std::endl << std::endl;

    std::cout << "Enter Human\'s name: ";
    std::string name;
    std::getline(std::cin, name);

    Game game(name);
    game.initialize();

    std::cout << "\nPress enter to continue...";
    std::cin.get();
    clearScreen();

    printTiles();
    printControls();
    std::cout << "\nPress enter to continue...";
    std::cin.get();
    
    bool running = true;
    std::string input;
    bool showZone = true;
    
    while(running) {
        if(showZone) {
            clearScreen();
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
                clearScreen();
                game.displayPlayerStats();
                std::cout << "\nPress enter to continue...";
                std::cin.get();
                continue;
            case 'h':
                clearScreen();
                printControls();
                std::cout << "\nPress enter to continue...";
                std::cin.get();
                continue;
            case 'm':
                clearScreen();
                printTiles();
                std::cout << "\nPress enter to continue...";
                std::cin.get();
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
            case GameAction::ATTACK:
                std::cout << "\nPress enter to continue...";
                std::cin.get();
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

