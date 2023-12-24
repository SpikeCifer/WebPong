#include <raylib.h>
#include <stdbool.h>
#include "ball.h"

typedef struct {
    Pad left_player;
    Pad right_player;
    Ball ball;
} GameData;

// The bounce logic could be cleaner
bool goal_scored(Ball* ball, Pad* pad) {
    bool bounce = pad->Position.y - pad->Size.y < ball->Position.y && 
        ball->Position.y < pad->Position.y + pad->Size.y; 

    if (pad->ID == 1) {
        return !bounce && ball->Position.x - (int) ball->Width/2 < pad->Position.x;
    } else if (pad->ID == 2) {
        return !bounce && ball->Position.x + (int) ball->Width/2 > pad->Position.x;
    }
    return false;
}

void updateScore(GameData* game) {
    if (goal_scored(&game->ball, &game->left_player)) {
        game->right_player.Score++;

        game->ball.Position.x = GetScreenWidth()/2.f;
        game->ball.Position.y = GetScreenWidth()/2.f;
        game->ball.Velocity.x = 70.0; 
        game->ball.Velocity.y = 70.0; 
    } 
    
    if (goal_scored(&game->ball, &game->right_player)) {
        game->left_player.Score++;

        game->ball.Position.x = GetScreenWidth()/2.f;
        game->ball.Position.y = GetScreenWidth()/2.f;
        game->ball.Velocity.x = -70.0; 
        game->ball.Velocity.y = 70.0; 
    }
}

void update(GameData* game) {
    Ball* ball = &game->ball;
    Pad* left_player = &game->left_player; 
    Pad* right_player = &game->right_player;

    updateBall(ball, left_player, right_player);
    updatePad(left_player);
    updatePad(right_player);
    updateScore(game);
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
             halfScreen - halfScreen/2, 10, 30, LIGHTGRAY);

    DrawText(TextFormat("%d", game->right_player.Score), 
             halfScreen + halfScreen/2, 10, 30, LIGHTGRAY);

    drawBall(&game->ball);
    drawPad(&game->left_player);
    drawPad(&game->right_player);
    EndDrawing();
}

int main() {
    // Create the window
    const int width = 800;
    const int height = 450;
    const char* title = "Pong over the Web";
    InitWindow(width, height, title);
    SetTargetFPS(60);

    // Initialize the Game
    Vector2 left_player_position = {5, GetScreenHeight()/2.0};
    Vector2 right_player_position= {GetScreenWidth() - 10, GetScreenHeight()/2.0};

    GameData game = {
        .ball = createBall(),
        .left_player = createPad(KEY_UP, KEY_DOWN,  left_player_position),
        .right_player = createPad(KEY_K, KEY_J,  right_player_position),
    };

    // Run the Game Loop
    while(!WindowShouldClose()) {
        update(&game);
        draw(&game);
    }

    CloseWindow();
    return 0;
}
