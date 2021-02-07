//
// Created by Lorenzo on 07/02/2021.
//

#ifndef CHARMAGEDDON_MENU_H
#define CHARMAGEDDON_MENU_H


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

class Menu {
protected:
    char key;
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

    int crea_menu();

};

#endif //CHARMAGEDDON_MENU_H
