//
// Created by Lorenzo on 02/02/2021.
//

#include "Map.h"
Map::Map() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    screenWidth=csbi.srWindow.Right;
    screenHeight=csbi.srWindow.Bottom;
    xMiddle=0.5;
    roadWidth=0.85;
    startLeftRoad=(xMiddle-roadWidth/2)*screenWidth;
    startRightRoad=(xMiddle+roadWidth/2)*screenWidth;
}
void Map::setCursor(short x,short y) {
    COORD position;
    position.X=x;
    position.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
void Map::setAndPrintChar(char c,short x, short y) {
    setCursor(x,y);
    cout<<c;
}
void Map::setAndPrintString(string st,short x,short y) {
    setCursor(x,y);
    cout<<st;
}
void Map::printMap() {
    for(int y=screenHeight;y>=screenHeight/2.3;y--){
        for (int x=0;x<=screenWidth;x++){
            if(x==(startLeftRoad+screenHeight-y)){
                setAndPrintChar('/',x,y);
            }
            else if(x==startRightRoad-screenHeight+y){
                setAndPrintChar('\\',x,y);
            }
        }
    }
    setCursor(screenWidth,screenHeight);
}

void Map::setCarPos(int x) {
    carPosition=x;
}
int Map::getScreenWidth() {
    return screenWidth;
}
int Map::getScreenHeight() {
    return screenHeight;
}
