//
// Created by Lorenzo on 02/02/2021.
//


#include "Map.h"
Map::Map() {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    screenWidth = csbi.srWindow.Right;
    screenHeight = csbi.srWindow.Bottom;
    xMiddle = 0.5;
    roadWidth = 0.85;
    startLeftRoad = (xMiddle-roadWidth/2)*screenWidth;
    startRightRoad = (xMiddle+roadWidth/2)*screenWidth;
}
void Map::setCursor(short x,short y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
void Map::setAndPrintChar(char c,short x, short y) {
    setCursor(x,y);
    cout<<c;
}

void Map::setAndPrintStrCol(string str[],int length, short x, short y, colours col=WHITE) {
    switch(col) {
            case BLUE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            break;
        case GREEN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            break;
        case RED:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            break;
        default: ;
    }
    //stampa per prima l'ultima riga(dello sprite), poi la penultima etc etc
    for(int i = 0; i < length;i++){
        setCursor(x,y-i);
        cout<<str[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}
void Map::printMap() {
    for(int y = screenHeight;y >= screenHeight/2.3;y--){ //il 2.3 serve per dare più di metà schermo alla strada
        for (int x = 0;x <= screenWidth;x++){
            if(x == (startLeftRoad+screenHeight-y)){
                setAndPrintChar('/',x,y);
            }
            else if(x == (startRightRoad-screenHeight+y)){
                setAndPrintChar('\\',x,y);
            }
        }
    }
}

void Map::setCarPos(int x) {
    carPosition = x;
}
int Map::getScreenWidth() {
    return screenWidth;
}
int Map::getScreenHeight() {
    return screenHeight;
}
