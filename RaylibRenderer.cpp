#include "RaylibRenderer.h"
#include "Game.h"
#include "Breakable.h"
#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include <algorithm>


static const Color COL_GROUND       = {  40,  40,  40, 255 };
static const Color COL_WALL         = {  90,  90,  90, 255 };
static const Color COL_BOUNDARY     = {  60,  60,  60, 255 };
static const Color COL_EXIT         = {   0, 200, 100, 255 };
static const Color COL_TREE         = {  30, 120,  30, 255 };
static const Color COL_STONE        = { 130, 130, 130, 255 };
static const Color COL_IRON         = { 180, 160, 100, 255 };
static const Color COL_TITANIUM     = { 100, 160, 200, 255 };
static const Color COL_BARREL       = { 160, 100,  50, 255 };
static const Color COL_PLAYER       = {   0, 180, 255, 255 };
static const Color COL_ENEMY_NORMAL = { 200,  50,  50, 255 };
static const Color COL_ENEMY_TANK   = { 180,  80,  20, 255 };
static const Color COL_ENEMY_POISON = {  80, 200,  80, 255 };
static const Color COL_ENEMY_HEALER = { 255, 220,   0, 255 };
static const Color COL_ENEMY_WIZARD = { 150,  50, 200, 255 };
static const Color COL_BOSS         = { 220,   0,   0, 255 };
static const Color COL_HUD_BG       = {   0,   0,   0, 180 };
static const Color COL_HP_GREEN     = {   0, 200,  80, 255 };
static const Color COL_HP_RED       = { 200,  50,  50, 255 };
static const Color COL_LOG_BG       = {   0,   0,   0, 160 };


RaylibRenderer::RaylibRenderer()  {}
RaylibRenderer::~RaylibRenderer() {}


void RaylibRenderer::LoadAssets() {
   
    auto load = [](const char* path) -> Texture2D {
        if (FileExists(path)) return LoadTexture(path);
        return Texture2D{};
    };

    // Tiles
    texGround      = load(TilePaths::GROUND);
    texWall        = load(TilePaths::WALL);
    texBoundary    = load(TilePaths::ZONE_BOUNDARY);
    texExit        = load(TilePaths::ZONE_EXIT);
    texTree        = load(TilePaths::TREE);
    texStoneOre    = load(TilePaths::STONE_ORE);
    texIronOre     = load(TilePaths::IRON_ORE);
    texTitaniumOre = load(TilePaths::TITANIUM_ORE);
    texBarrel      = load(TilePaths::BARREL);

    // Entities
    texPlayer      = load(EntityPaths::PLAYER);
    texEnemyNormal = load(EntityPaths::ENEMY_NORMAL);
    texEnemyTank   = load(EntityPaths::ENEMY_TANK);
    texEnemyPoison = load(EntityPaths::ENEMY_POISON);
    texEnemyHealer = load(EntityPaths::ENEMY_HEALER);
    texEnemyWizard = load(EntityPaths::ENEMY_WIZARD);
    texBoss        = load(EntityPaths::BOSS);

    // Item icons
    texIconWood         = load(UIPaths::ICON_WOOD);
    texIconStone        = load(UIPaths::ICON_STONE);
    texIconIron         = load(UIPaths::ICON_IRON);
    texIconTitanium     = load(UIPaths::ICON_TITANIUM);
    texIconEtherite     = load(UIPaths::ICON_ETHERITE);
    texIconPotionHeal   = load(UIPaths::ICON_POTION_HEAL);
    texIconPotionPoison = load(UIPaths::ICON_POTION_POISON);
    texIconPotionStr    = load(UIPaths::ICON_POTION_STR);
    texIconPotionWeak   = load(UIPaths::ICON_POTION_WEAK);
    texIconPotionRes    = load(UIPaths::ICON_POTION_RES);
    texIconPotionVuln   = load(UIPaths::ICON_POTION_VULN);
    texIconSword        = load(UIPaths::ICON_SWORD);
    texIconSpear        = load(UIPaths::ICON_SPEAR);
    texIconAxe          = load(UIPaths::ICON_AXE);
    texIconPickaxe      = load(UIPaths::ICON_PICKAXE);

    assetsLoaded = true;
}


void RaylibRenderer::UnloadAssets() {
    auto unload = [](Texture2D& t) { if (t.id) UnloadTexture(t); };

    unload(texGround);      unload(texWall);         unload(texBoundary);
    unload(texExit);        unload(texTree);          unload(texStoneOre);
    unload(texIronOre);     unload(texTitaniumOre);   unload(texBarrel);

    unload(texPlayer);      unload(texEnemyNormal);   unload(texEnemyTank);
    unload(texEnemyPoison); unload(texEnemyHealer);   unload(texEnemyWizard);
    unload(texBoss);

    unload(texIconWood);    unload(texIconStone);     unload(texIconIron);
    unload(texIconTitanium);unload(texIconEtherite);
    unload(texIconPotionHeal); unload(texIconPotionPoison);
    unload(texIconPotionStr);  unload(texIconPotionWeak);
    unload(texIconPotionRes);  unload(texIconPotionVuln);
    unload(texIconSword);   unload(texIconSpear);
    unload(texIconAxe);     unload(texIconPickaxe);
}

bool RaylibRenderer::ShouldClose() const { return WindowShouldClose(); }


void RaylibRenderer::PushMessage(const std::string& msg) {
    messageLog.push_back(msg);
    if (messageLog.size() > 5) messageLog.erase(messageLog.begin());
}


void RaylibRenderer::UpdateCamera(const Game& game) {
    const Player* p = game.getPlayer();
    viewOffsetX = p->PosX() * TILE_SIZE - SCREEN_WIDTH  / 2 + TILE_SIZE / 2;
    viewOffsetY = p->PosY() * TILE_SIZE - SCREEN_HEIGHT / 2 + TILE_SIZE / 2;
}


Texture2D& RaylibRenderer::PickTileTexture(const Tile* tile) {
    if (!tile) return texGround;
    switch (tile->Type()) {
        case TileType::GROUND:        return texGround;
        case TileType::WALL:          return texWall;
        case TileType::ZONE_BOUNDARY: return texBoundary;
        case TileType::ZONE_EXIT:     return texExit;
        case TileType::RESOURCE: {
            const Breakable* b = dynamic_cast<const Breakable*>(tile);
            if (!b) return texGround;
            switch (b->Type()) {
                case ResourceType::TREE:     return texTree;
                case ResourceType::STONE:    return texStoneOre;
                case ResourceType::IRON:     return texIronOre;
                case ResourceType::TITANIUM: return texTitaniumOre;
                default:                     return texBarrel;
            }
        }
        default: return texGround;
    }
}

Texture2D& RaylibRenderer::PickEntityTexture(const Entity* entity) {
    if (!entity) return texEnemyNormal;
    if (dynamic_cast<const Boss*>(entity))  return texBoss;
    const Enemy* e = dynamic_cast<const Enemy*>(entity);
    if (e) {
        switch (e->Type()) {
            case EnemyType::TANK:   return texEnemyTank;
            case EnemyType::POISON: return texEnemyPoison;
            case EnemyType::HEALER: return texEnemyHealer;
            case EnemyType::WIZARD: return texEnemyWizard;
            default:                return texEnemyNormal;
        }
    }
    return texEnemyNormal;
}

Texture2D& RaylibRenderer::PickItemIcon(const Item* item) {
    if (!item) return texIconWood;
    const std::string& n = item->Name();
    if      (n == "Wood")                          return texIconWood;
    else if (n == "Stone")                         return texIconStone;
    else if (n == "Iron")                          return texIconIron;
    else if (n == "Titanium")                      return texIconTitanium;
    else if (n == "Etherite")                      return texIconEtherite;
    else if (n == "Healing Potion"
          || n == "Inflicting Healing Potion")      return texIconPotionHeal;
    else if (n == "Poison Potion")                  return texIconPotionPoison;
    else if (n == "Strength Potion")                return texIconPotionStr;
    else if (n == "Weakness Potion")                return texIconPotionWeak;
    else if (n == "Resistance Potion")              return texIconPotionRes;
    else if (n == "Vulnerability Potion")           return texIconPotionVuln;
    else if (n.find("Sword")   != std::string::npos) return texIconSword;
    else if (n.find("Spear")   != std::string::npos) return texIconSpear;
    else if (n.find("Axe")     != std::string::npos) return texIconAxe;
    else if (n.find("Pickaxe") != std::string::npos) return texIconPickaxe;
    return texIconWood;
}


void RaylibRenderer::DrawScaled(Texture2D& tex, int sx, int sy) {
    Rectangle src  = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { (float)sx, (float)sy, (float)TILE_SIZE, (float)TILE_SIZE };
    DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);
}

void RaylibRenderer::DrawTileTexture(int tileX, int tileY, Texture2D& tex, Color fallback) {
    int sx = ScreenX(tileX), sy = ScreenY(tileY);
    if (sx + TILE_SIZE < 0 || sx > SCREEN_WIDTH ||
        sy + TILE_SIZE < 0 || sy > SCREEN_HEIGHT) return;   // cull offscreen

    if (tex.id != 0) DrawScaled(tex, sx, sy);
    else             DrawRectangle(sx, sy, TILE_SIZE, TILE_SIZE, fallback);
}

void RaylibRenderer::DrawEntityTexture(int tileX, int tileY, Texture2D& tex, Color fallback) {
    int sx = ScreenX(tileX), sy = ScreenY(tileY);
    if (tex.id != 0) DrawScaled(tex, sx, sy);
    else             DrawRectangle(sx + 4, sy + 4, TILE_SIZE - 8, TILE_SIZE - 8, fallback);
}


void RaylibRenderer::DrawWorld(const Game& game) {
    const Zone* zone = game.getCurrentZone();
    if (!zone) return;

    // Tiles
    for (int y = 0; y < zone->ZoneLength(); y++) {
        for (int x = 0; x < zone->ZoneWidth(); x++) {
            const Tile* tile = const_cast<Zone*>(zone)->getTile(x, y);
            Texture2D& tex = PickTileTexture(tile);

            Color fb = COL_GROUND;
            if (tile) switch (tile->Type()) {
                case TileType::WALL:          fb = COL_WALL;     break;
                case TileType::ZONE_BOUNDARY: fb = COL_BOUNDARY; break;
                case TileType::ZONE_EXIT:     fb = COL_EXIT;     break;
                case TileType::RESOURCE: {
                    const Breakable* b = dynamic_cast<const Breakable*>(tile);
                    if (b) switch (b->Type()) {
                        case ResourceType::TREE:     fb = COL_TREE;     break;
                        case ResourceType::STONE:    fb = COL_STONE;    break;
                        case ResourceType::IRON:     fb = COL_IRON;     break;
                        case ResourceType::TITANIUM: fb = COL_TITANIUM; break;
                        default:                     fb = COL_BARREL;   break;
                    }
                    break;
                }
                default: break;
            }
            DrawTileTexture(x, y, tex, fb);
        }
    }

    // Enemies / bosses
    for (const auto& entity : zone->getEntities()) {
        if (!entity->isAlive()) continue;
        Texture2D& tex = PickEntityTexture(entity.get());

        Color fb = COL_ENEMY_NORMAL;
        const Enemy* e = dynamic_cast<const Enemy*>(entity.get());
        if (dynamic_cast<const Boss*>(entity.get()))  fb = COL_BOSS;
        else if (e) switch (e->Type()) {
            case EnemyType::TANK:   fb = COL_ENEMY_TANK;   break;
            case EnemyType::POISON: fb = COL_ENEMY_POISON; break;
            case EnemyType::HEALER: fb = COL_ENEMY_HEALER; break;
            case EnemyType::WIZARD: fb = COL_ENEMY_WIZARD; break;
            default: break;
        }
        DrawEntityTexture(entity->PosX(), entity->PosY(), tex, fb);
    }

    // Player
    {
        const Player* p = game.getPlayer();
        DrawEntityTexture(p->PosX(), p->PosY(), texPlayer, COL_PLAYER);
    }
}


void RaylibRenderer::DrawHUD(const Game& game) {
    const Player* p = game.getPlayer();
    int hx = 10, hy = 10;

    DrawRectangle(hx - 4, hy - 4, 220, 90, COL_HUD_BG);
    DrawRectangleLines(hx - 4, hy - 4, 220, 90, DARKGRAY);

    // HP bar
    int barW = 200, barH = 14;
    float hpRatio = (p->MaxHP() > 0) ? (float)p->HP() / p->MaxHP() : 0.f;
    Color hpColor = (hpRatio > 0.5f) ? COL_HP_GREEN : (hpRatio > 0.25f ? ORANGE : COL_HP_RED);
    DrawRectangle(hx, hy, barW, barH, DARKGRAY);
    DrawRectangle(hx, hy, (int)(barW * hpRatio), barH, hpColor);
    DrawRectangleLines(hx, hy, barW, barH, GRAY);
    std::string hpText = "HP: " + std::to_string(p->HP()) + " / " + std::to_string(p->MaxHP());
    DrawText(hpText.c_str(), hx + 2, hy, barH, WHITE);

    hy += barH + 4;
    DrawText(("Floor: " + std::to_string(game.getCurrentFloor())).c_str(), hx, hy,      12, LIGHTGRAY);
    DrawText(("DEF: "   + std::to_string(p->Defense())).c_str(),           hx, hy + 14, 12, LIGHTGRAY);
    DrawText(("ATK: "   + std::to_string(p->Damage())).c_str(),            hx, hy + 28, 12, LIGHTGRAY);
    DrawText(("XP: "    + std::to_string(p->XP())).c_str(),                hx, hy + 42, 12, LIGHTGRAY);

    // Equipped item (top-right)
    {
        const Item* eq = p->getEquippedItem();
        std::string eqStr = "Equipped: " + (eq ? eq->Name() : "None");
        int tw = MeasureText(eqStr.c_str(), 12);
        DrawRectangle(SCREEN_WIDTH - tw - 16, 6, tw + 12, 20, COL_HUD_BG);
        DrawText(eqStr.c_str(), SCREEN_WIDTH - tw - 10, 10, 12, YELLOW);
    }

    // Controls hint (bottom)
    DrawText("[WASD] Move  [K] Attack  [B] Break  [I] Inventory  [C] Craft  [Q] Quit",
             10, SCREEN_HEIGHT - 18, 11, GRAY);
}


void RaylibRenderer::DrawInventory(const Game& game) {
    if (!showInventory) return;

    const Player* p = game.getPlayer();
    const auto& inv = p->getInventory();

    int panelW = 320, panelH = 400;
    int px = (SCREEN_WIDTH  - panelW) / 2;
    int py = (SCREEN_HEIGHT - panelH) / 2;

    DrawRectangle(px, py, panelW, panelH, { 20, 20, 20, 230 });
    DrawRectangleLines(px, py, panelW, panelH, WHITE);
    DrawText("INVENTORY  [I to close]", px + 8, py + 8, 14, WHITE);

    std::string eqStr = "Equipped: " + (p->getEquippedItem() ? p->getEquippedItem()->Name() : "None");
    DrawText(eqStr.c_str(), px + 8, py + 28, 12, YELLOW);

    int slotSize = 44, cols = 5;
    int startX = px + 8, startY = py + 50;

    for (int i = 0; i < (int)inv.size(); i++) {
        int sx = startX + (i % cols) * (slotSize + 4);
        int sy = startY + (i / cols) * (slotSize + 4);

        bool selected = (i == selectedSlot);
        DrawRectangle(sx, sy, slotSize, slotSize, { 50, 50, 50, 255 });
        DrawRectangleLines(sx, sy, slotSize, slotSize, selected ? YELLOW : GRAY);

        if (inv[i].item) {
            Texture2D& icon = PickItemIcon(inv[i].item.get());
            if (icon.id != 0) {
                Rectangle src  = { 0, 0, (float)icon.width, (float)icon.height };
                Rectangle dest = { (float)(sx + 4), (float)(sy + 4),
                                   (float)(slotSize - 8), (float)(slotSize - 8) };
                DrawTexturePro(icon, src, dest, {0,0}, 0.0f, WHITE);
            } else {
                
                Color c = WHITE;
                switch (inv[i].item->Type()) {
                    case ItemType::WEAPON:  c = RED;    break;
                    case ItemType::TOOL:    c = ORANGE; break;
                    case ItemType::POTION:  c = PURPLE; break;
                    case ItemType::UTILITY: c = GREEN;  break;
                }
                DrawRectangle(sx + 8, sy + 8, slotSize - 16, slotSize - 16, c);
            }
            DrawText(("x" + std::to_string(inv[i].amount)).c_str(), sx + 2, sy + slotSize - 14, 11, WHITE);
            if (selected) {
                DrawText(inv[i].item->Name().c_str(), px + 8, py + panelH - 48, 12, WHITE);
                DrawText("[U] Use  [E] Equip  [R] Drop", px + 8, py + panelH - 28, 11, LIGHTGRAY);
            }
        }
    }

    if (inv.empty())
        DrawText("(empty)", px + 8, startY + 10, 12, DARKGRAY);
}


static const char* CRAFT_ITEMS[] = {
    "Wooden Pickaxe","Wooden Axe","Wooden Sword","Wooden Spear",
    "Stone Pickaxe","Stone Axe","Stone Sword","Stone Spear",
    "Iron Pickaxe","Iron Axe","Iron Sword","Iron Spear",
    "Titanium Pickaxe","Titanium Axe","Titanium Sword","Titanium Spear",
    "Etherite Pickaxe","Etherite Axe","Etherite Sword","Etherite Spear"
};
static const int CRAFT_COUNT = 20;

void RaylibRenderer::DrawCraftMenu(const Game& game) {
    if (!showCraftMenu) return;

    int panelW = 280, panelH = 480;
    int px = (SCREEN_WIDTH  - panelW) / 2;
    int py = (SCREEN_HEIGHT - panelH) / 2;

    DrawRectangle(px, py, panelW, panelH, { 20, 20, 20, 230 });
    DrawRectangleLines(px, py, panelW, panelH, WHITE);
    DrawText("CRAFT  [C to close]", px + 8, py + 8, 14, WHITE);

    for (int i = 0; i < CRAFT_COUNT; i++) {
        int iy = py + 34 + i * 21;
        bool sel = (i == craftSelection);
        if (sel) DrawRectangle(px + 4, iy - 1, panelW - 8, 19, { 60, 60, 120, 255 });
        DrawText((std::to_string(i + 1) + ". " + CRAFT_ITEMS[i]).c_str(),
                 px + 10, iy, 13, sel ? YELLOW : WHITE);
    }
    DrawText("[UP/DOWN] Select  [ENTER] Craft", px + 8, py + panelH - 22, 11, LIGHTGRAY);
}

void RaylibRenderer::DrawMessageLog() {
    int logH = 14 * (int)messageLog.size() + 10;
    int logY = SCREEN_HEIGHT - 22 - logH;
    DrawRectangle(4, logY, SCREEN_WIDTH / 2, logH, COL_LOG_BG);
    for (int i = 0; i < (int)messageLog.size(); i++) {
        float alpha = 0.5f + 0.5f * ((float)(i + 1) / messageLog.size());
        Color c = { 220, 220, 220, (unsigned char)(255 * alpha) };
        DrawText(messageLog[i].c_str(), 8, logY + 5 + i * 14, 12, c);
    }
}


void RaylibRenderer::Render(const Game& game) {
    UpdateCamera(game);

    BeginDrawing();
    ClearBackground({ 10, 10, 10, 255 });

    DrawWorld(game);
    DrawHUD(game);
    DrawInventory(game);
    DrawCraftMenu(game);
    DrawMessageLog();

    EndDrawing();
}


GameAction RaylibRenderer::PollInput(int& itemIndex) {
    itemIndex = -1;

    // ---- CRAFT MENU ----
    if (showCraftMenu) {
        if (IsKeyPressed(KEY_C) || IsKeyPressed(KEY_ESCAPE)) { showCraftMenu = false; return GameAction::NONE; }
        if (IsKeyPressed(KEY_UP))    craftSelection = std::max(0, craftSelection - 1);
        if (IsKeyPressed(KEY_DOWN))  craftSelection = std::min(CRAFT_COUNT - 1, craftSelection + 1);
        if (IsKeyPressed(KEY_ENTER)) {
            itemIndex = craftSelection + 1;
            showCraftMenu = false;
            return GameAction::CRAFT;
        }
        return GameAction::NONE;
    }

    // ---- INVENTORY ----
    if (showInventory) {
        if (IsKeyPressed(KEY_I) || IsKeyPressed(KEY_ESCAPE)) { showInventory = false; return GameAction::NONE; }
        if (IsKeyPressed(KEY_LEFT))  selectedSlot = std::max(0, selectedSlot - 1);
        if (IsKeyPressed(KEY_RIGHT)) selectedSlot++;
        if (IsKeyPressed(KEY_UP))    selectedSlot = std::max(0, selectedSlot - 5);
        if (IsKeyPressed(KEY_DOWN))  selectedSlot += 5;
        if (IsKeyPressed(KEY_U)) { itemIndex = selectedSlot; return GameAction::USE_ITEM;    }
        if (IsKeyPressed(KEY_E)) { itemIndex = selectedSlot; return GameAction::EQUIP_ITEM;  }
        if (IsKeyPressed(KEY_R)) { itemIndex = selectedSlot; return GameAction::DROP_ITEM;   }
        if (IsKeyPressed(KEY_T)) { itemIndex = selectedSlot; return GameAction::THROW_POTION;}
        return GameAction::NONE;
    }

    // ---- GAMEPLAY ----
    if (IsKeyPressed(KEY_I)) { showInventory = true;  return GameAction::OPEN_INVENTORY; }
    if (IsKeyPressed(KEY_C)) { showCraftMenu = true; craftSelection = 0; return GameAction::NONE; }
    if (IsKeyPressed(KEY_W)) return GameAction::MOVE_UP;
    if (IsKeyPressed(KEY_S)) return GameAction::MOVE_DOWN;
    if (IsKeyPressed(KEY_A)) return GameAction::MOVE_LEFT;
    if (IsKeyPressed(KEY_D)) return GameAction::MOVE_RIGHT;
    if (IsKeyPressed(KEY_K)) return GameAction::ATTACK;
    if (IsKeyPressed(KEY_B)) return GameAction::BREAK_RESOURCE;
    if (IsKeyPressed(KEY_T)) {
        for (int k = KEY_ZERO; k <= KEY_NINE; k++)
            if (IsKeyDown(k)) { itemIndex = k - KEY_ZERO; break; }
        return GameAction::THROW_POTION;
    }
    return GameAction::NONE;
}
