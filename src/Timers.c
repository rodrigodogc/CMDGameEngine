#include <sys/time.h>
#include "TextGameEngine.h"

// Função para obter o tempo decorrido em segundos
void updateDeltaTime(CLOCK *deltaTime, TIMER* timer) { /* Jeito OK :) */
    *deltaTime = (timer->current.tv_sec - timer->previous.tv_sec) +
                 (timer->current.tv_usec - timer->previous.tv_usec) / 1E6;
}

float getFramesPerSecond(CLOCK deltaTime) {
    return (1.0f / deltaTime);
}

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

CLOCK millis() {
    return ((double) clock() * 1000) / CLOCKS_PER_SEC;
}

/* Jeito antigo :) */
/* Controle de Gameloop e FPS */
void gameLoopController(double frameCounter, double *actualFrameRate, double targetFPS, double startTime) {
    static double sleepTime = 0;
    *actualFrameRate = frameCounter / ((millis() - startTime) / 1000);
        if (*actualFrameRate > targetFPS) {
            sleepTime++;
            Delay(sleepTime);
        }  else sleepTime--;
        srand( (unsigned)time(NULL) ); // atualizando a seed
}

CLOCK getDeltaTime(CLOCK *startTimer) {
    CLOCK currentTime = millis();
    CLOCK deltaTime = (currentTime - *startTimer) / CLOCKS_PER_SEC;
    *startTimer = currentTime;
    return deltaTime;
}

void Delay(unsigned int milliseconds) {
    clock_t wait = milliseconds + clock();
    while (wait > clock());
}

void updateTimer(struct timeval *timer) {
    gettimeofday(timer, NULL);
}

//updtTimer updateTimer = gettimeofday;

/*
int mainSample() {
    // Variável para controlar o tempo
    TIMER timer;
    CLOCK deltaTime;
    // Inicializa o tempo anterior
    updateTimer(&timer.previous, NULL);
    // Loop principal do jogo
    while (1) {
        // Obtém o tempo atual
        updateTimer(&timer.current, NULL);
        // Calcula o deltaTime em segundos
        updateDeltaTime(&deltaTime, &timer);
        // Verifica se já passou o tempo necessário para o próximo frame
        
        if (deltaTime >= FRAMETIME) {
            timer.previous = timer.current;
            //updatePhysics(deltaTime);
            // Lógica do jogo e renderização acontecem aqui
            printf("TARGET_FPS: %.2f\n", getFramesPerSecond(deltaTime));
        } 
        
    }
    return 0;
}
*/