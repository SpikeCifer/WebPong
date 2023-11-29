#include <raylib.h>
#include "ball.h"

typedef struct {
    Pad player1;
    Pad player2;
    Ball ball;
} GameData;

void update(GameData* game) {
    updateBall(&game->ball);
    updatePad(&game->player1);
    updatePad(&game->player2);
}

void draw(GameData* game) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw the Middle Line
    Vector2 lineStart = {.x = (GetScreenWidth() / 2.f), .y = 5};
    Vector2 lineEnd = {
        .x = (GetScreenWidth() / 2.f), 
        .y = (GetScreenHeight() - 5.f)
    };
    DrawLineEx(lineStart, lineEnd, 4, LIGHTGRAY);

    int halfScreen = GetScreenWidth()/2;
    // Draw Scores
    DrawText(TextFormat("%d", game->player1.Score), 
             halfScreen - halfScreen/2,
             10, 30, LIGHTGRAY);

    DrawText(TextFormat("%d", game->player2.Score), 
             halfScreen + halfScreen/2,
             10, 30, LIGHTGRAY);

    drawBall(&game->ball);

    drawPad(&game->player1);
    drawPad(&game->player2);
    EndDrawing();
}

GameData initGame() {
    Pad player1 = {
        .Scheme = {.UpButton = KEY_UP, .DownButton = KEY_DOWN},
        .Score = 0,
        .Speed = 70.0,

        .Position = {5, GetScreenHeight()/2.0},
        .Size = {5, 50},
    };

    Pad player2 = {
        .Scheme = {.UpButton = KEY_K, .DownButton = KEY_J},
        .Score = 0,
        .Speed = 70.0,

        .Position = {GetScreenWidth() - 10, GetScreenHeight()/2.0},
        .Size = {5, 50},
    };

    Ball ball = {
        .Position = {GetScreenWidth()/2.f, GetScreenHeight()/2.f},
        .Velocity = {50.0, 70.0},
        .Width = 20,
        .Height = 20,
    };

    GameData game = {
        .ball = ball,
        .player1 = player1,
        .player2 = player2,
    };

    return game;
}

int main() {
    // Create the window
    const int width = 800;
    const int height = 450;
    const char* title = "Pong over the Web";
    InitWindow(width, height, title);
    SetTargetFPS(60);

    GameData game = initGame();

    while(!WindowShouldClose()) {
        update(&game);
        draw(&game);
    }

    CloseWindow();
    return 0;
}
