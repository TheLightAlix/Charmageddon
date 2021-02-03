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
    void setCursor(short,short); //mette il cursore ad una determinata coordinata
    int getScreenWidth();
    int getScreenHeight();
    void printMap(); //stampa tutta la mappa
    void setAndPrintChar(char,short,short); //stampa un carattere ad una determinata coordinata x e y
    void setAndPrintString(string,short,short); // stampa un stringa ad una determinata coordinata x e y
    void setCarPos(int);
};

#endif //GIOCO2_0_MAP_H
