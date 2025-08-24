#include "TextGameEngine.h"

void updatePhysicWorld(PHYSIC_WORLD **physicWorldRB, CLOCK deltaTime, int nObjects, float gravitySpeed, int collideOnBonds) {
    /* Tudo aqui é rodado a cada frame :) */
    for (int i = 0; i < nObjects; i++) {
        RigidBody *Obj = physicWorldRB[i];
        /* Só aplicar física se estiver ativo */
        if (Obj->active && deltaTime < 0.5 || millis() > 300) {
            // Aplicação da velocidade
            Obj->posX +=  Obj->speedX * deltaTime * 10.0f;
            Obj->posY +=  Obj->speedY * deltaTime * 10.0f;

            if (collideOnBonds) {
                if (Obj->bounce == true) {
                    if (Obj->posX >= W - Obj->sizeX) 
                        Obj->speedX *= -1;
                    else if (Obj->posX <= 0) 
                        Obj->speedX *= -1;

                    if (Obj->posY >= H - Obj->sizeY) 
                        Obj->speedY *= -1;
                    else if (Obj->posY <= 0) 
                        Obj->speedY *= -1;

                    if (Obj->posX < 0) /* Translação para corrigir Bug :) */
                        Obj->posX = 0;
                    else if (Obj->posX > W - (Obj->sizeX))
                        Obj->posX = W - (Obj->sizeX);

                    if (Obj->posY < 0)
                        Obj->posY = 0;
                    else if (Obj->posY > H - (Obj->sizeY))
                        Obj->posY = H - (Obj->sizeY);
                }
            }

            // Aplicação da aceleração gravitacional
            if (Obj->allowGravity == true) {
                if (Obj->posY <= (H - Obj->sizeY)) {
                    Obj->speedY += gravitySpeed * deltaTime * 10.0f;
                } 
                else {
                    Obj->speedY = 0;
                    Obj->posY   = H - Obj->sizeY;
                }
            }

        }
    }
}

void addToPhysicWorld(PHYSIC_WORLD **physicWorldRB, int nObjects, ...) {
    va_list rigidBodies;
    va_start(rigidBodies, nObjects);
    for (int i = 0; i < nObjects; i++) {
        RigidBody *RB = va_arg(rigidBodies, RigidBody*);
        physicWorldRB[i] = RB; 
    }
    va_end(rigidBodies);
}

int Collision(RigidBody *objA, RigidBody *objB) {
    /* Verificação de colisão em X e Y*/
    int colX = (objA->posX + objA->sizeX) >= objB->posX && 
                objA->posX <= (objB->posX + objB->sizeX);

    int colY = (objA->posY + objA->sizeY) >= objB->posY && 
                objA->posY <= (objB->posY + objB->sizeY);

    if (colX && colY && (objA->active && objB->active)) {
        /* à implementar: afastar-se em colisão física */
        if (objA->allowPhysicalCollision && objB->allowPhysicalCollision) {
            objA->speedX *= -1;
            objA->speedY *= -1;
            if (objA->speedX == 0) objA->speedX = 0;
            if (objA->speedY == 0) objA->speedY = 0;
        }
        return 1;
    }
    return 0;
}

PHYSIC_WORLD **newPhysicWorld(int numOfObjects) {
    return (PHYSIC_WORLD**) malloc(numOfObjects * sizeof(RigidBody*));
}