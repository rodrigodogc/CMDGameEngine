#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <sys/time.h>
#include <Windows.h>
#include <conio.h>
//#include <mmsystem.h>

extern const int   W;
extern const int   H;
extern const float TARGET_FPS;

#define FRAMETIME_US (double)(1E6 / TARGET_FPS)
#define FRAMETIME (double) (FRAMETIME_US / 1E6)

#ifndef TEXT_ENGINE_H
#define TEXT_ENGINE_H
#define PI 3.1415926

// Cores de fonte (Foreground)
#define FG_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define FG_BLACK 0x0
#define FG_BLUE 0x1
#define FG_GREEN 0x2
#define FG_CYAN 0x3
#define FG_RED 0x4
#define FG_MAGENTA 0x5
#define FG_YELLOW 0x6
// Light Collors
#define FG_LIGHTGRAY 0x7
#define FG_DARKGRAY (FG_LIGHTGRAY | FOREGROUND_INTENSITY)
#define FG_LIGHTBLUE (FG_BLUE | FOREGROUND_INTENSITY)
#define FG_LIGHTGREEN (FG_GREEN | FOREGROUND_INTENSITY)
#define FG_LIGHTCYAN (FG_CYAN | FOREGROUND_INTENSITY)
#define FG_LIGHTRED (FG_RED | FOREGROUND_INTENSITY)
#define FG_LIGHTMAGENTA (FG_MAGENTA | FOREGROUND_INTENSITY)
#define FG_LIGHTYELLOW (FG_YELLOW | FOREGROUND_INTENSITY)
#define FG_LIGHTWHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

// Cores de fundo (Background)
#define BG_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define BG_BLACK 0x0
#define BG_BLUE 0x10
#define BG_GREEN 0x20
#define BG_CYAN 0x30
#define BG_RED 0x40
#define BG_MAGENTA 0x50
#define BG_YELLOW 0x60
// Light Collors
#define BG_LIGHTGRAY 0x70
#define BG_DARKGRAY (BG_LIGHTGRAY | BACKGROUND_INTENSITY)
#define BG_LIGHTBLUE (BG_BLUE | BACKGROUND_INTENSITY)
#define BG_LIGHTGREEN (BG_GREEN | BACKGROUND_INTENSITY)
#define BG_LIGHTCYAN (BG_CYAN | BACKGROUND_INTENSITY)
#define BG_LIGHTRED (BG_RED | BACKGROUND_INTENSITY)
#define BG_LIGHTMAGENTA (BG_MAGENTA | BACKGROUND_INTENSITY)
#define BG_LIGHTYELLOW (BG_YELLOW | BACKGROUND_INTENSITY)
#define BG_LIGHTWHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY)


// Key Codes
#define KEY_W     87 
#define KEY_A     65
#define KEY_S     83
#define KET_D     68
#define KEY_UP    38
#define KEY_DOWN  40
#define KEY_LEFT  37
#define KEY_RIGHT 39
#define KEY_SPACE 32

#define true 1
#define false 0

typedef struct {
    /* Parâmetros  */
    float posX,   posY;
    float speedX, speedY;
    int   sizeX,   sizeY;
    /* Interações físicas */
    int isGrounded;
    int allowGravity;
    int allowPhysicalCollision;
    int bounce;
    int active;
} RigidBody;

#define STANDARD_RIGIDBODY (RigidBody) {0, 0, 0, 0, 6, 3, false, true, false, true, true};

typedef struct {
    struct timeval current;
    struct timeval previous;
} TIMER;

// só pra abstrair mais :)
typedef RigidBody PHYSIC_WORLD;
typedef CHAR_INFO GameObject; 
typedef CHAR_INFO FRAME_BUFFER;
typedef HANDLE WINDOW;
typedef HANDLE INPUT_HANDLE;
typedef FILE LOG;
typedef int Color;
typedef double CLOCK;

// Func Headers

CLOCK millis();

CLOCK getDeltaTime(CLOCK *startTimer);

void Delay(unsigned int milliseconds);

void updateDeltaTime(CLOCK *deltaTime, TIMER* timer);

float getFramesPerSecond(CLOCK deltaTime);

void updateTimer(struct timeval *timer);

//typedef int (*updtTimer)();

WINDOW *newWindow();

void WindowConfig(WINDOW window, char title[], int width, int heigth, int bgColor);

void setWindowBGColor(WINDOW window, int color);


FRAME_BUFFER *newFrameBuffer();

PHYSIC_WORLD **newPhysicWorld(int numOfObjects);

GameObject *createRectBox(RigidBody obj, int charCode, Color color);

GameObject *createRectDiamond(RigidBody rb, int charCode, Color color);

void DrawPixel(int x, int y, FRAME_BUFFER *frame, char asciiChar, Color color);

void DrawObject(FRAME_BUFFER *frame, GameObject *go, RigidBody rb);

void Render(WINDOW window, FRAME_BUFFER *frame);

void ClearFrameBuffer(FRAME_BUFFER *frame, Color backgroundColor);

void clearScreen(WINDOW window);

void destroyObject(GameObject *obj, RigidBody *RB);

void addToPhysicWorld(PHYSIC_WORLD **physicWorldRB, int nObjects, ...);

void updatePhysicWorld(PHYSIC_WORLD **physicWorldRB, CLOCK deltaTime, int nObjects, float gravitySpeed, int collideOnBonds);

int Collision(RigidBody *objA, RigidBody *objB);

int toGlobal(int x, int y, int targetWidth);


void playSound(char *filePath);

void playMusic(char *filePath);


int getKeyPressed();

int getKeyDown();

void startKeyboardListner(INPUT_HANDLE handle);

char inputEventListener(INPUT_HANDLE input);

void setCursorPosition(WINDOW window, int x, int y);

LOG *createLogHandle(char logFileName[], int autoclear);

void Log(char logMsg[], LOG *logHandle);

void logToTitle(char logMsg[]);

void closeLogHandle (LOG *logHandle);

int random(int min, int max);

void gameLoopController(double frameCounter, double *actualFrameRate, double targetFPS, double startTime);

#endif