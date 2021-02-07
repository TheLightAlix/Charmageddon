#include <iostream>
#include <windows.h>
#include "Player.hpp"
#include "GameState.hpp"




using namespace std;

void ShowConsoleCursor(bool showFlag);




int main() {
    ShowConsoleCursor(false);
    GameState* MyGame = new GameState();
    MyGame->SetGameState(MENU);







    return 0;
}


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}