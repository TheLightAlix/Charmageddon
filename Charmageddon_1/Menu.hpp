//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_MENU_HPP
#define CHARMAGEDDON_1_MENU_HPP

#include <Windows.h>
#include <iostream>


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

    int crea_menu();

};


#endif //CHARMAGEDDON_1_MENU_HPP
