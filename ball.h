#include <raylib.h>
#include "pad.h"

typedef struct {
    Vector2 Position;
    Vector2 Velocity;
    int Height;
    int Width;
} Ball;

void updateBall(Ball* ball, Pad* player1, Pad* player2);
void drawBall(Ball* ball);
