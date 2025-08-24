#include <stdio.h>
#include <stdlib.h>
#include "TextGameEngine.h"

const int W = 116;  // Largura máxima 116 caracteres
const int H = 34;   // Altura máxima  27 caracteres
const float TARGET_FPS = 60.0f;

int main() {    

    char debug[100];
    int running = true;

    WINDOW window = newWindow();
    WindowConfig(window, "TestEnv", W, H, BG_CYAN);

    // controle de fps
    CLOCK frameRate, deltaTime;
    TIMER timer; 

    FRAME_BUFFER *frame = newFrameBuffer();

    /* Variáveis de Física dos GO's */
    RigidBody Box = {
        posX:  10, posY: H/2, 
        speedX: 0, speedY: 0, 
        sizeX:  8,  sizeY: 4,
        isGrounded: false,
        allowPhysicalCollision: false,
        allowGravity: true,
        bounce: false,
        active: true
    };

    RigidBody Ground = {
        posX:  0, posY: H - 3, 
        speedX: 0, speedY: 0, 
        sizeX: W,  sizeY: 3,
        isGrounded: false,
        allowPhysicalCollision: false,
        allowGravity: false,
        bounce: false,
        active: true
    };

    /* Incicialização da física */
    const int numObjetos = 2;
    PHYSIC_WORLD **physicWorld = newPhysicWorld(numObjetos);
    addToPhysicWorld(physicWorld, numObjetos, &Box, &Ground);

    /* Variáveis de GameObjects */
    GameObject *BoxObj = createRectBox(Box, ' ', BG_RED);
    GameObject *GroundObj = createRectBox(Ground, ' ', BG_GREEN);

    int isColliding = 0, keyPressed = 0;
    
    /* Mainloop */ 
    updateTimer(&timer.previous);
    while (running) {  
        updateTimer(&timer.current);
        updateDeltaTime(&deltaTime, &timer);
        if (deltaTime >= FRAMETIME) {
            timer.previous = timer.current;

            keyPressed = getKeyPressed();

            if ( getKeyPressed() == KEY_SPACE) {
                Box.speedY = -3; // pulo
            }

            if (keyPressed == KEY_LEFT && Box.posX > 0) {
                Box.speedX = -5;
            }
            else if (keyPressed == KEY_RIGHT && Box.posX < W - Box.sizeX) {
                Box.speedX = 5;
            }
            else {
                Box.speedX = 0;
            }
        
            /* Sessão de física */
            updatePhysicWorld(physicWorld, deltaTime, numObjetos, 1, true);
            
            /* Sessão de renderização */
            ClearFrameBuffer(frame, BG_LIGHTBLUE);
            DrawObject(frame, BoxObj, Box);
            DrawObject(frame, GroundObj, Ground);

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





