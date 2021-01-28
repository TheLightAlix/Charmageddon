#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void menu () {
    int Set [] = {7, 7, 7}; //colors
    int counter = 2;
    char key;

    for (int i=0; ;) {

        gotoxy(10,15);
        color(Set[0]);
        cout << "1. Play now!";

        gotoxy(10,16);
        color(Set[1]);
        cout << "2. Top 10 Records";

        gotoxy(10,17);
        color(Set[2]);
        cout << "3. About";

        key = _getch();

        if (key == 72 && (counter >= 2 && counter <= 3)) { //72 = up arrow key
            counter --;
        }

        if (key == 80 && (counter >= 1 && counter <= 2)) { //80 = down arrow key
            counter ++;
        }

        if (key == '\r') { //carriage return = enter key

            system("cls");

            if (counter == 1) {
                cout << "Menu 1 is Open";
            }

            if (counter == 2) {
                cout << "Menu 2 is Open";
            }

            if (counter == 3)
            {
                cout << "Menu 3 is Open";
            }
        }

        Set[0] = 7; //colore default
        Set[1] = 7;
        Set[2] = 7;

        if (counter == 1) {
            Set[0] = 32; //verde
        }
        if (counter == 2) {
            Set[1] = 32; //verde
        }
        if (counter == 3) {
            Set[2] = 32; //verde
        }


    }
}

int main() {

    menu();

    return 0;
}
