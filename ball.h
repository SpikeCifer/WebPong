#include <raylib.h>

typedef struct {
    Vector2 Position;
    Vector2 Velocity;
    int Height;
    int Width;
} Ball;

void updateBall(Ball* ball);
void drawBall(Ball* ball);
/* bool ballBounces(Ball* ball); */
