#include "ball.h"
#include <raylib.h>

Ball createBall() {
    Ball ball = {
        .Position = {GetScreenWidth()/2.f, GetScreenHeight()/2.f},
        .Velocity = {-70.0, 70.0},
        .Width = 20,
        .Height = 20,
    };
    return ball;
}

void updateBall(Ball* ball, Pad* player1, Pad* player2) {
    ball->Velocity.x += 0.001 * ball->Velocity.x;
    ball->Velocity.y += 0.001 * ball->Velocity.y;
    ball->Position.x += GetFrameTime() * ball->Velocity.x;
    ball->Position.y += GetFrameTime() * ball->Velocity.y;

    // Check if ball bounces on top or bottom
    if (ball->Position.y - (int)ball->Height/2 < 0 || // Better effect on top bounce
        ball->Position.y + ball->Height > GetScreenHeight()) {
        ball->Velocity.y = -ball->Velocity.y;
    }

    if (ball->Position.x - (int)ball->Width/2 < 0 || // Better effect on top bounce
        ball->Position.x + ball->Width > GetScreenWidth()) {
        ball->Velocity.x = -ball->Velocity.x;
    }
}

void drawBall(Ball* ball) {
    DrawRectangle(ball->Position.x - 5, 
                  ball->Position.y - 5, 
                  ball->Width, 
                  ball->Height, 
                  WHITE);
}
