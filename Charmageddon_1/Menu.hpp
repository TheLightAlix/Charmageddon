//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_MENU_HPP
#define CHARMAGEDDON_1_MENU_HPP

#include <Windows.h>
#include <iostream>
#include "Map.hpp"
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;


struct lista {
    int pz;
    string n;
    int s;
    lista *next;
};
typedef lista *ptr;

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
    colours colore;
    string user;

public:
    ptr creazione_lista ();
    ptr newscore (ptr h, int nscore, string user);
    void cout_lista (ptr h);
    void scelta_car();
    int get_scelta();
    void post_menu (string user, int score);
    void presentazione();
    string get_user();
    void scelta_colore();
    colours get_colore();

    Menu();

    int crea_menu(int counter);

};




#endif //CHARMAGEDDON_1_MENU_HPP
