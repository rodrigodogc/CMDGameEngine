#include "TextGameEngine.h"

LOG *createLogHandle(char logFileName[], int autoclear) {
    LOG *log;
    if (autoclear == 1) {
        log = fopen(logFileName, "w");
    }
    else {
        log = fopen(logFileName, "a");
    }
    return log;
}

void Log(char logMsg[], LOG *logHandle) {
    static long int logCounter = 1;
    fprintf(logHandle, "%ld > %s\n", logCounter++, logMsg);
} 

void logToTitle(char logMsg[]) {
    SetConsoleTitle(logMsg);
}

void closeLogHandle (LOG *logHandle) {
    fclose(logHandle);
}
