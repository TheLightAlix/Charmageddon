//
// Created by leola on 07/02/2021.
//

#ifndef SCORE_SCORE_H
#define SCORE_SCORE_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class score {
protected:
    int x;
    int y;
    void gotoxy(int x, int y);
    void window();
public:
    score(int livescore=64272);
};


#endif //SCORE_SCORE_H
