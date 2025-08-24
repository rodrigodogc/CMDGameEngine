#include "TextGameEngine.h"

/* Jeito melhor :) */
int getKeyPressed() {

    //static CLOCK startTime = 0;
    //if (millis() - startTime > 10 && millis() > 200) {
        //startTime = millis();
        for (int key = 0; key <= 255; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                return key;
            }
        } 
    //}
    return -1;
}

int getKeyDown() {

    static CLOCK startTime = 0;
    static CLOCK finalTime = 0;
    static int isPressed = 0;
    
    for (int key = 0; key <= 255; key++) {
        if ((GetAsyncKeyState(key) & 0x8000)) {
            if (millis() - startTime > 10) {
                startTime = millis();
                isPressed = 1;
            }
            return key;
        }
    } 
}


/* Jeito ruim :) */
void startKeyboardListner(INPUT_HANDLE handle) {
    SetConsoleMode(handle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

char inputEventListener(HANDLE input) {
    DWORD nEvents = 0;
    DWORD readedEvents = 0;
    INPUT_RECORD inputRecords[128];
    GetNumberOfConsoleInputEvents(input, &nEvents);
    if (nEvents > 0) {
        ReadConsoleInput(input, inputRecords, 128, &readedEvents);
        for (DWORD i = 0; i < readedEvents; i++) {
            if (inputRecords[i].EventType == KEY_EVENT) {
                KEY_EVENT_RECORD keyEvent = inputRecords[i].Event.KeyEvent;
                if (keyEvent.bKeyDown) {
                    if (keyEvent.wVirtualKeyCode == VK_UP) 
                        return 'U';
                    else if (keyEvent.wVirtualKeyCode == VK_DOWN)
                        return 'D';
                    else if (keyEvent.wVirtualKeyCode == VK_LEFT)
                        return 'L';
                    else if (keyEvent.wVirtualKeyCode == VK_RIGHT)
                        return 'R';
                } 
            }
        }
    }
}

