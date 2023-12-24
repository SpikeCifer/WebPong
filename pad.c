#include "pad.h"
#include <raylib.h>

int pad_counter = 0;

Pad createPad(int UpButton, int DownButton, Vector2 Position) {
    Pad newPad = {
        .ID = ++pad_counter,
        .Scheme = {UpButton, DownButton},
        .Score = 0,
        .Speed = 70.0,

        .Position = Position,
        .Size = {5, 50}
    };

    return newPad;
}

void updatePad(Pad* pad) {
    if (IsKeyDown(pad->Scheme.UpButton)) {
        pad->Position.y -= GetFrameTime() * pad->Speed;
        
        // If the pad passes the top, draw it at the bottom
        if (pad->Position.y + pad->Size.y < 0) {
            pad->Position.y = GetScreenHeight();
        }
    }

    if (IsKeyDown(pad->Scheme.DownButton)) {
        pad->Position.y += GetFrameTime() * pad->Speed;

        // If the pad passes the bottom, draw it at the top
        if (pad->Position.y - pad->Size.y > GetScreenHeight()) {
            pad->Position.y = 0;
        }
    }
}

void drawPad(Pad *pad) {
    DrawRectangle(pad->Position.x, pad->Position.y - (pad->Size.y / 2), 
                  pad->Size.x, pad->Size.y, WHITE);
}
