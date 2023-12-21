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

void updatePad(Pad* pad);
void drawPad(Pad* pad);
