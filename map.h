
#ifndef GIOCO2_0_MAP_H
#define GIOCO2_0_MAP_H

using namespace std;
#include <windows.h>
#include <cmath>

enum colours {
    BLUE,
    GREEN,
    RED,
    WHITE
};

class Map {
protected:
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int screenWidth;
    int screenHeight;
    float xMiddle;
    float roadWidth;
    int startLeftRoad;
    int startRightRoad;
    int carPosition=0; //posizione più a sinistra dell'auto.
public:
    Map();
    void setCursor(short,short);
    int getScreenWidth();
    int getScreenHeight();
    void printMap();
    void setAndPrintChar(char,short,short);
    void setAndPrintStrCol(string[],int,short,short,colours);
    void setCarPos(int);
};

#endif //GIOCO2_0_MAP_H
