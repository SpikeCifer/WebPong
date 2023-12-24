#include <raylib.h>

typedef struct {
    int UpButton;
    int DownButton;
} InputScheme ;

typedef struct {
    int ID;
    InputScheme Scheme;
    int Score;
    float Speed;

    Vector2 Position;
    Vector2 Size;
} Pad;

Pad createPad(int upKey, int DownKey, Vector2 Position);
void updatePad(Pad* pad);
void drawPad(Pad* pad);
