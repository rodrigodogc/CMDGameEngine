#include <stdio.h>
#include <stdlib.h>
#include "TextGameEngine.h"

const int W = 116;  // Largura máxima 116 caracteres
const int H = 34;   // Altura máxima  27 caracteres
const float TARGET_FPS = 60.0f;

#define SHOT_SFX "C:\\Users\\rodri\\Desktop\\CMDEngine\\SFX\\shot.wav"

int main() {    

    char debug[100];

    WINDOW window = newWindow();
    WindowConfig(window, "TestEnv", W, H, BG_CYAN);

    // controle de fps
    CLOCK frameRate, deltaTime;
    TIMER timer; 

    FRAME_BUFFER *frame = newFrameBuffer();

    /* Variáveis de Física dos GO's */
    RigidBody Box = {
        posX: 10, 
        posY: H/2, 
        speedX: 5, 
        speedY: 5, 
        sizeX: 8, 
        sizeY: 4,
        isGrounded: false,
        allowPhysicalCollision: false,
        allowGravity: false,
        bounce: true,
        active: true
    };

    const int nObjects = 2;
    PHYSIC_WORLD *physicWorld[nObjects];
    addToPhysicWorld(physicWorld, nObjects, &Box);

    /* Variáveis de GameObjects */
    GameObject *BoxObj = createRectBox(Box, ' ', BG_GREEN);

    int isColliding = 0, keyPressed = 0;
    
    int running = true;
    updateTimer(&timer.current);
    /* Mainloop */ 
    while (running) {  
        updateTimer(&timer.current);
        updateDeltaTime(&deltaTime, &timer);
        if (deltaTime >= FRAMETIME) {
        
            timer.previous = timer.current;

            keyPressed = getKeyPressed();

            if ( getKeyPressed() == KEY_SPACE) {
                playSound(SHOT_SFX);
            } 

            if (keyPressed == KEY_UP && Box.posY > 0) {
                Box.speedY = -5;
            } 
            else if (keyPressed == KEY_DOWN && Box.posY < H - Box.sizeY) {
                Box.speedY = 5;
            }
            else if (keyPressed == KEY_LEFT && Box.posX > 0) {
                Box.speedX = -5;
            }
            else if (keyPressed == KEY_RIGHT && Box.posX < W - Box.sizeX) {
                Box.speedX = 5;
            }
            else {
                //Box.speedX = 0;
                //Box.speedY = 0;
            }
        
            /* Sessão de física */
            updatePhysicWorld(physicWorld, deltaTime, nObjects, 1, true);
            
            /* Sessão de renderização */
            ClearFrameBuffer(frame, BG_BLACK);
            setWindowBGColor(window, BG_WHITE);
            DrawObject(frame, BoxObj, Box);

            Render(window, frame);

            /*    Debug     */
            frameRate = getFramesPerSecond(deltaTime);
            sprintf(debug, "FPS: %.2lf   X: %0.2f  Y: %.2f  velX: %.2f velY: %.2f  colidindo: %s", 
              frameRate, Box.posX, Box.posY, Box.speedX, Box.speedY, isColliding ? "Sim" : "Nao");      

        } 

        else logToTitle(debug);

    }

    return 0;
} 





