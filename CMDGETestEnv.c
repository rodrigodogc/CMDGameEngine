#include <stdio.h>
#include <stdlib.h>
#include "TextGameEngine.h"

const int W = 116;  // Largura máxima 116
const int H = 27;   // Altura máxima  27
const float TARGET_FPS = 60.0f;

#define SHOT_SFX "C:\\Users\\rodri\\Desktop\\CMDEngine\\SFX\\shot.wav"

int main() {    

    char debug[100];

    WINDOW window = newWindow();
    WindowConfig(window, "TestEnv", W, H, BG_LIGHTBLUE);

    // controle de fps
    CLOCK frameRate, deltaTime;
    TIMER timer; 

    FRAME_BUFFER *frame = newFrameBuffer();

    /* Variáveis de Física dos GO's */
    RigidBody Box = {posX: 10, posY: H/2, 
                     speedX: 0, speedY: 0, 
                     sizeX: 8, sizeY: 4,
                     isGrounded: false,
                     allowPhysicalCollision: false,
                     allowGravity: false,
                     bounce: false,
                     active: true
                     };
    RigidBody BoxRed = {posX: 10, posY: 10, 
                     speedX: 0, speedY: 0, 
                     sizeX: 8, sizeY: 4,
                     isGrounded: false,
                     allowPhysicalCollision: false,
                     allowGravity: false,
                     bounce: false,
                     active: true
                     };

    int nObjects = 1;
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

            if (keyPressed == KEY_UP) {
                Box.speedY = -5;
            } 
            else if (keyPressed == KEY_DOWN) {
                Box.speedY = 5;
            }
            else {
                Box.speedY = 0;
            }
        
            /*if (getKeyDown() == KEY_LEFT) {
                playSound(SHOT_SFX);
            }*/

            /* Sessão de física */
            updatePhysicWorld(physicWorld, deltaTime, nObjects, 1, true);
            
            /* Sessão de renderização */
            ClearFrameBuffer(frame, BG_BLACK);
            
            DrawObject(frame, BoxObj, Box);

            Render(window, frame);
            /*    Debug     */
            frameRate = getFramesPerSecond(deltaTime);
            sprintf(debug, "FPS: %.2lf   X: %0.2f  Y: %.2f  SpdX: %.2f SpdY: %.2f  isColliding: %d", 
              frameRate, Box.posX, Box.posY, Box.speedX, Box.speedY, isColliding);      

        } 

        else logToTitle(debug);

    }

    return 0;
} 





