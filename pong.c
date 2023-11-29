#include <raylib.h>
#include "ball.h"
#include "pad.h"

typedef struct {
    Pad player1;
    Pad player2;
    Ball ball;
} GameData;

void update(GameData* game) {
    updateBall(&game->ball);
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

    // Draw Scores
    int halfScreen = GetScreenWidth()/2;
    DrawText(TextFormat("%d", game->player1.Score), halfScreen - halfScreen/2,
                10, 30, LIGHTGRAY);

    DrawText(TextFormat("%d", game->player2.Score), halfScreen + halfScreen/2,
                10, 30, LIGHTGRAY);

    // Draw Ball
    drawBall(&game->ball);
    drawPad(&game->player1);
    drawPad(&game->player2);
    EndDrawing();
}

void initWindow() {
    // Create the window
    const int width = 800;
    const int height = 450;
    const char* title = "Pong over the Web";
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

GameData initGame() {
    Pad player1 = {
        .Scheme = {},
        .Score = 0,
        .Speed = 4.0,

        .Position = {5, GetScreenHeight()/2.0},
        .Size = {5, 40},
    };

    Pad player2 = {
        .Scheme = {},
        .Score = 0,
        .Speed = 5.0,

        .Position = {GetScreenWidth() - 5, GetScreenHeight()/2.0},
        .Size = {5, 40},
    };

    Ball ball = {
        .Position = {GetScreenWidth()/2.f, GetScreenHeight()/2.f},
        .Velocity = {15.0, 0},
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
    initWindow();
    GameData game = initGame();

    while(!WindowShouldClose()) {
        update(&game);
        draw(&game);
    }

    CloseWindow();
    return 0;
}
