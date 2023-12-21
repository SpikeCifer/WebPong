#include <raylib.h>
#include <stdbool.h>
#include "ball.h"

typedef struct {
    Pad left_player;
    Pad right_player;
    Ball ball;
} GameData;

bool goal_scored(Ball* ball, Pad* pad) {
    bool bounce = ball->Position.y > pad->Position.y - pad->Size.y &&
        ball->Position.y < pad->Position.y + pad->Size.y; 

    if (pad->ID == 1) {
        return !bounce && ball->Position.x - (int) ball->Width/2 < pad->Position.x;
    } else if (pad->ID == 2) {
        return !bounce && ball->Position.x + (int) ball->Width/2 > pad->Position.x;
    }
    return false;
}

void update(GameData* game) {
    Ball* ball = &game->ball;
    Pad* left_player = &game->left_player; 
    Pad* right_player = &game->right_player;

    updateBall(ball, left_player, right_player);
    updatePad(left_player);
    updatePad(right_player);

    // Update Score
    if (goal_scored(ball, left_player)) 
    {
        game->right_player.Score++;
        ball->Position.x = GetScreenWidth()/2.f;
        ball->Position.y = GetScreenWidth()/2.f;
        ball->Velocity.x = 70.0; 
        ball->Velocity.y = 70.0; 
    } 

    if (goal_scored(ball, right_player)) 
    {
        game->left_player.Score++;
        ball->Position.x = GetScreenWidth()/2.f;
        ball->Position.y = GetScreenWidth()/2.f;
        ball->Velocity.x = -50.0; 
        ball->Velocity.y = 70.0; 
    }
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
    DrawText(TextFormat("%d", game->left_player.Score), 
             halfScreen - halfScreen/2,
             10, 30, LIGHTGRAY);

    DrawText(TextFormat("%d", game->right_player.Score), 
             halfScreen + halfScreen/2,
             10, 30, LIGHTGRAY);

    drawBall(&game->ball);

    drawPad(&game->left_player);
    drawPad(&game->right_player);
    EndDrawing();
}

GameData initGame() {
    Pad left_player = {
        .ID = 1,
        .Scheme = {.UpButton = KEY_UP, .DownButton = KEY_DOWN},
        .Score = 0,
        .Speed = 70.0,

        .Position = {5, GetScreenHeight()/2.0},
        .Size = {5, 50},
    };

    Pad right_player = {
        .ID = 2,
        .Scheme = {.UpButton = KEY_K, .DownButton = KEY_J},
        .Score = 0,
        .Speed = 70.0,

        .Position = {GetScreenWidth() - 10, GetScreenHeight()/2.0},
        .Size = {5, 50},
    };

    Ball ball = {
        .Position = {GetScreenWidth()/2.f, GetScreenHeight()/2.f},
        .Velocity = {-70.0, 70.0},
        .Width = 20,
        .Height = 20,
    };

    GameData game = {
        .ball = ball,
        .left_player = left_player,
        .right_player = right_player,
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
