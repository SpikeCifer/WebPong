#include "ball.h"
#include <raylib.h>

void updateBall(Ball* ball) {
    ball->Position.x += GetFrameTime() * ball->Velocity.x;
    ball->Position.y += GetFrameTime() * ball->Velocity.y;
}

void drawBall(Ball* ball) {
    DrawRectangle(ball->Position.x - 5, 
                  ball->Position.y - 5, 
                  ball->Width, 
                  ball->Height, 
                  WHITE);
}
