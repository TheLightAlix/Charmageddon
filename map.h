#ifndef GIOCO2_0_MAP_H
#define GIOCO2_0_MAP_H

using namespace std;
#include <windows.h>
#include <cmath>

class Map {
protected:
    int screenWidth;
    int screenHeight;
    float xMiddle;
    float roadWidth;
    int startLeftRoad;
    int startRightRoad;
    int carPosition=0;
public:
    Map();
    void setCursor(short,short);
    int getScreenWidth();
    int getScreenHeight();
    void printMap();
    void setAndPrintChar(char,short,short);
    void setAndPrintString(string,short,short);
    void setCarPos(int);
};

#endif //GIOCO2_0_MAP_H
