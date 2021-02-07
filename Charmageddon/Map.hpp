//
// Created by TheLi on 31/01/2021.
//

#ifndef CHARMAGEDDON_MAP_HPP
#define CHARMAGEDDON_MAP_HPP


#include <windows.h>
#include <cmath>
#include <iostream>

using namespace std;

enum colours {
    BLUE,
    RED,
    GREEN,
    OCHRE,
    VIOLET,
    CYAN,
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
    int getSLR();
    int getSRR();
};





#endif //CHARMAGEDDON_MAP_HPP
