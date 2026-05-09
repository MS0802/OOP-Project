#pragma once

#include "raylib.h"
#include "Game.h"          // <- REQUIRED for Game type and GameAction enum
#include "Enemy.h"
#include "Boss.h"
#include "Breakable.h"
#include "Weapon.h"
#include "Tool.h"
#include "Potion.h"
#include <string>
#include <vector>


constexpr int TILE_SIZE     = 32;
constexpr int SCREEN_WIDTH  = 1000;
constexpr int SCREEN_HEIGHT = 700;


namespace TilePaths {
    constexpr const char* GROUND        = "Ground.png";
    constexpr const char* WALL          = "wall.png";
    constexpr const char* ZONE_BOUNDARY = "Zone_boundary.png";
    constexpr const char* ZONE_EXIT     = "assets/tiles/exit.png";
    constexpr const char* TREE          = "tree.png";
    constexpr const char* STONE_ORE     = "rock.png";
    constexpr const char* IRON_ORE      = "iron.png";
    constexpr const char* TITANIUM_ORE  = "titanium.png";
    constexpr const char* BARREL        = "barrel.png";
}

namespace EntityPaths {
    constexpr const char* PLAYER       = "player.png";
    constexpr const char* ENEMY_NORMAL = "normal.png";
    constexpr const char* ENEMY_TANK   = "tank.png";
    constexpr const char* ENEMY_POISON = "assets/entities/enemy_poison.png";
    constexpr const char* ENEMY_HEALER = "healer.png";
    constexpr const char* ENEMY_WIZARD = "wizard.png";
    constexpr const char* BOSS         = "boss.png";
}

namespace UIPaths {
    constexpr const char* ICON_WOOD          = "wood.png";
    constexpr const char* ICON_STONE         = "stone.png";
    constexpr const char* ICON_IRON          = "iron_icon.png";
    constexpr const char* ICON_TITANIUM      = "titanium_icon.png";
    constexpr const char* ICON_ETHERITE      = "assets/ui/etherite.png";
    constexpr const char* ICON_POTION_HEAL   = "potion_heal.png";
    constexpr const char* ICON_POTION_POISON = "potion_poison.png";
    constexpr const char* ICON_POTION_STR    = "potion_strength.png";
    constexpr const char* ICON_POTION_WEAK   = "assets/ui/potion_weakness.png";
    constexpr const char* ICON_POTION_RES    = "assets/ui/potion_resistance.png";
    constexpr const char* ICON_POTION_VULN   = "assets/ui/potion_vulnerability.png";
    constexpr const char* ICON_SWORD         = "sword.png";
    constexpr const char* ICON_SPEAR         = "spear.png";
    constexpr const char* ICON_AXE           = "axe.png";
    constexpr const char* ICON_PICKAXE       = "pickaxe.png";
}


class RaylibRenderer {
public:
    RaylibRenderer();
    ~RaylibRenderer();

    void LoadAssets();
    void UnloadAssets();
    void Render(const Game& game);
    GameAction PollInput(int& itemIndex);
    bool ShouldClose() const;

private:
    // ---- tile textures ----
    Texture2D texGround      = {};
    Texture2D texWall        = {};
    Texture2D texBoundary    = {};
    Texture2D texExit        = {};
    Texture2D texTree        = {};
    Texture2D texStoneOre    = {};
    Texture2D texIronOre     = {};
    Texture2D texTitaniumOre = {};
    Texture2D texBarrel      = {};

    // ---- entity textures ----
    Texture2D texPlayer      = {};
    Texture2D texEnemyNormal = {};
    Texture2D texEnemyTank   = {};
    Texture2D texEnemyPoison = {};
    Texture2D texEnemyHealer = {};
    Texture2D texEnemyWizard = {};
    Texture2D texBoss        = {};

    // ---- item icon textures ----
    Texture2D texIconWood         = {};
    Texture2D texIconStone        = {};
    Texture2D texIconIron         = {};
    Texture2D texIconTitanium     = {};
    Texture2D texIconEtherite     = {};
    Texture2D texIconPotionHeal   = {};
    Texture2D texIconPotionPoison = {};
    Texture2D texIconPotionStr    = {};
    Texture2D texIconPotionWeak   = {};
    Texture2D texIconPotionRes    = {};
    Texture2D texIconPotionVuln   = {};
    Texture2D texIconSword        = {};
    Texture2D texIconSpear        = {};
    Texture2D texIconAxe          = {};
    Texture2D texIconPickaxe      = {};

    bool assetsLoaded = false;

    // ---- camera ----
    int viewOffsetX = 0;
    int viewOffsetY = 0;

    // ---- UI state ----
    bool showInventory  = false;
    bool showCraftMenu  = false;
    int  selectedSlot   = 0;
    int  craftSelection = 0;

    // ---- message log ----
    std::vector<std::string> messageLog;
    void PushMessage(const std::string& msg);   // implement if needed

    // ---- private helpers ----
    void UpdateCamera(const Game& game);
    void DrawWorld(const Game& game);
    void DrawTileTexture(int tileX, int tileY, Texture2D& tex, Color fallback);
    void DrawEntityTexture(int tileX, int tileY, Texture2D& tex, Color fallback);
    void DrawHUD(const Game& game);
    void DrawInventory(const Game& game);
    void DrawCraftMenu(const Game& game);
    void DrawMessageLog();

    Texture2D& PickTileTexture(const Tile* tile);
    Texture2D& PickEntityTexture(const Entity* entity);
    Texture2D& PickItemIcon(const Item* item);

    int ScreenX(int tileX) const { return tileX * TILE_SIZE - viewOffsetX; }
    int ScreenY(int tileY) const { return tileY * TILE_SIZE - viewOffsetY; }

    static void DrawScaled(Texture2D& tex, int sx, int sy);
};