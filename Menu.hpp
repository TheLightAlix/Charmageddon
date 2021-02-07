//
// Created by leola on 07/02/2021.
//


#ifndef GIOCO_MENU_H
#define GIOCO_MENU_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cmath>
#include "GameState.cpp"

using namespace std;

struct list {
    int pz;
    string n;
    int s;
    list *next;
};
typedef list *ptr;

class Menu {
protected:
    char key;
    bool controllo = false;
    int x;
    int y;
    ptr h, p;
    void color(int color);
    int counter;
    void window();
    void gotoxy(int x, int y);
    int scelta;

public:
    ptr creazione_lista ();
    ptr newscore (ptr h, int nscore, string user);
    void cout_lista (ptr h);
    int scelta_car();
    int get_scelta();
    void post_menu (string user, int score, ptr h);
    string presentazione();

    Menu();

    void crea_menu(GameState *MyGameState);

};




#endif //GIOCO_MENU_H

