#include "pad.h"
#include <raylib.h>

void updatePad(Pad* pad) {
    int height = GetScreenHeight();

    if (IsKeyDown(pad->Scheme.UpButton)) {
        pad->Position.y += GetFrameTime() * pad->Speed;
        // If the pad passes the max height, draw it at the bottom
        if (pad->Position.y / 2 + pad->Size.y > height) {
            pad->Position.y = 0;
        }
    }

    if (IsKeyDown(pad->Scheme.DownButton)) {
        pad->Position.y += GetFrameTime() * pad->Speed;
        // If the pad passes the min height, draw it at the top
        if (pad->Position.y - pad->Size.y / 2 < 0) {
            pad->Position.y = height;
        }
    }
}

void drawPad(Pad *pad) {
    DrawRectangle(pad->Position.x, pad->Position.y - (pad->Size.y / 2), 
                  pad->Size.x, pad->Size.y, WHITE);
}
