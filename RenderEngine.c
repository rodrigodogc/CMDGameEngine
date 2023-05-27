#include "TextGameEngine.h"

GameObject *createRectBox(RigidBody rb, int charCode, Color color) {
    GameObject *boxObject = (CHAR_INFO*) malloc(rb.sizeX * rb.sizeY * sizeof(CHAR_INFO));
    for (int i = 0; i < rb.sizeX * rb.sizeY; i++) {
        boxObject[i].Char.UnicodeChar = charCode;
        boxObject[i].Attributes =  color;
    }
    return boxObject;
} 

GameObject *createRectDiamond(RigidBody rb, int charCode, Color color) {
    
    GameObject *diamondObject = (CHAR_INFO*) malloc(rb.sizeX * rb.sizeY * sizeof(CHAR_INFO));

    int spaces = rb.sizeX / 2;
    int hashes = 1;

    for (int i = 0; i < rb.sizeX; i++) {
        for (int j = 0; j < spaces; j++) {
            diamondObject[i * rb.sizeY + j].Char.UnicodeChar = ' ';
            diamondObject[i * rb.sizeY + j].Attributes = color;
        }
        for (int j = spaces; j < spaces + hashes; j++) {
            diamondObject[i * rb.sizeY + j].Char.UnicodeChar = charCode;
            diamondObject[i * rb.sizeY + j].Attributes = color;
        }
        if (i < rb.sizeX / 2.0) {
            spaces--;
            hashes += 2;
        } else {
            spaces++;
            hashes -= 2;
        }
    }

    return diamondObject;
}

FRAME_BUFFER *newFrameBuffer() {
    FRAME_BUFFER *fBuffer = malloc(W * H * sizeof(CHAR_INFO));
    ClearFrameBuffer(fBuffer, BG_BLACK);
    return fBuffer;
}

void DrawPixel(int x, int y, FRAME_BUFFER *frame, char asciiChar, Color color) {
    frame[toGlobal(x, y, W)].Char.UnicodeChar = asciiChar;
    frame[toGlobal(x, y, W)].Attributes = color;
}

void DrawObject(FRAME_BUFFER *frame, GameObject *go, RigidBody rb) {
    if (rb.active == 1) {
        for (int x = 0; x < rb.sizeX; x++) {
            for(int y = 0; y < rb.sizeY; y++) {
            /* Transposição de coordenadas :) */
            frame[toGlobal(rb.posX + x, rb.posY + y, W)].Char.UnicodeChar = go[toGlobal(x, y, rb.sizeX)].Char.UnicodeChar;
            frame[toGlobal(rb.posX + x, rb.posY + y, W)].Attributes = go[toGlobal(x, y, rb.sizeX)].Attributes;
            }
        }
    }
}


void Render(WINDOW window, FRAME_BUFFER *frame) {
    SMALL_RECT destRect = {0, 0, W - 1, H - 1};
    WriteConsoleOutput(window, frame, (COORD){W, H}, (COORD){0, 0}, &destRect);
}

void ClearFrameBuffer(FRAME_BUFFER *frame, Color backgroundColor) {
    for (int i = 0; i < W * H; i++) {
        frame[i].Char.UnicodeChar = ' ';
        frame[i].Attributes = backgroundColor;
    }
}

void destroyObject(GameObject *obj, RigidBody *RB) {
    RB->active = 0;
    RB->allowGravity = 0;
    RB->allowPhysicalCollision = 0;
    RB->posX = 0 - RB->sizeX;  
    RB->posY = 0 - RB->sizeY;
    RB->speedX = 0; RB->speedY = 0;
}

void clearScreen(HANDLE window) {
    DWORD charsWritten;
    FillConsoleOutputCharacter(window, ' ', (H) * (W), (COORD){0, 0}, &charsWritten);
}

int toGlobal(int x, int y, int targetWidth) {
    return (x + (y * targetWidth));
}