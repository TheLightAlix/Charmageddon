//
// Created by leola on 05/02/2021.
//

#ifndef GIOCO_MENU_H
#define GIOCO_MENU_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct list {
    int pz;
    string n;
    int s;
    list *next;
};
typedef list *ptr;

class menu {
protected:
    int x;
    int y;
    ptr h, p;
    void color(int color);
    void window();
    void gotoxy(int x, int y);

public:
    ptr creazione_lista ();
    ptr newscore (ptr h, int nscore, string user);
    void cout_lista (ptr h);
    int scelta_car();
    void post_menu (string user, int score, ptr h);
    string presentazione();

    menu(int counter = 1);

};




#endif //GIOCO_MENU_H
