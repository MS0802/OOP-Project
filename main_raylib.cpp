

#include "raylib.h"
#include "Game.h"
#include "RaylibRenderer.h"
#include <iostream>

int main() {
    // ---- window ----
    InitWindow(1000, 700, "Dungeon Game");
    SetTargetFPS(60);

    // ---- game + renderer ----
    Game game;
    game.initialize();

    RaylibRenderer renderer;
    renderer.LoadAssets();

    // ---- main loop ----
    while (!renderer.ShouldClose()) {
        int itemIndex = -1;
        GameAction action = renderer.PollInput(itemIndex);

        if (action != GameAction::NONE) {
            game.tick(action, itemIndex);
        }

        renderer.Render(game);

        if (!game.getPlayer()->isAlive()) {
            // Simple game-over: draw one last frame then wait
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER", SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 - 20, 40, RED);
            DrawText("Press ESC to quit", SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 + 30, 20, GRAY);
            EndDrawing();
            while (!WindowShouldClose()) {}
            break;
        }
    }

    renderer.UnloadAssets();
    CloseWindow();
    return 0;
}
