#include "TextGameEngine.h"

void WindowConfig(HANDLE window, char title[], int width, int heigth, Color defaultBGColor) {
    
    SetConsoleTitle(title);
    SetConsoleOutputCP(CP_UTF8);
    setWindowBGColor(window, defaultBGColor);
    
    SMALL_RECT Size = {0, 0, width-1, heigth-1};
    COORD Buffer = {width, heigth};

    SetConsoleWindowInfo(window, TRUE, &Size);
    SetConsoleScreenBufferSize(window, Buffer);  
    
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(window, &cursorInfo);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(window, FALSE, &fontInfo);
    //fontInfo.dwFontSize.X = fontInfo.dwFontSize.X * 1.5;
    //fontInfo.dwFontSize.Y = 1;
    wcscpy_s(fontInfo.FaceName, LF_FACESIZE, L"Consolas"); // Fonte Terminal
    SetCurrentConsoleFontEx(window, FALSE, &fontInfo);
}

void setWindowBGColor(WINDOW window, Color color) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(window, &consoleInfo);
    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0xFF0F; // Limpa os bits referentes à cor de fundo
    attributes |= (color << 4); // Define a nova cor de fundo
    SetConsoleTextAttribute(window, attributes);
}

WINDOW *newWindow() {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

void setCursorPosition(HANDLE window, int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(window, coord);
}
