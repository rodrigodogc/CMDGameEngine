#include "TextGameEngine.h"
//#include <pthread.h>

void playSound(char *filePath) {

    static CLOCK startTime = 0;

    if (millis() - startTime > 200) {
        //PlaySoundA((LPCSTR) filePath, NULL, SND_ASYNC);
        startTime = millis();
    }
}

/*void *playMusicAsync(void *arg) {
    char *filePath = (char*) arg;
    PlaySoundA((LPCSTR) filePath, NULL, SND_ASYNC);
    return NULL;
}*/

void playMusic(char *filePath) {

    //PlaySoundA((LPCSTR) filePath, NULL, SND_ASYNC);
    //pthread_t musicThread;
    //pthread_create(&musicThread, NULL, playMusicAsync, (void*) filePath);

}