//
// Created by leola on 07/02/2021.
//

#include "score.h"

void score::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void score::window() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    x = csbi.srWindow.Right * 0.5;
    y = csbi.srWindow.Bottom * 0.5;
}


score::score(int livescore) {
    while (livescore>0) {
        window();
        gotoxy(0 , 0);
        cout << livescore;
        system("cls");
    }
}