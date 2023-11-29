#include <raylib.h>
#include "pad.h"

typedef struct {
    Vector2 Position;
    Vector2 Velocity;
    int Height;
    int Width;
} Ball;

void updateBall(Ball* ball);
void drawBall(Ball* ball);
bool doesBallBounceOnPad(Ball* ball, Pad* pad); 
