//
// Created by leola on 05/02/2021.
//

#include "menu.h"


void menu::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void menu::window() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    x = csbi.srWindow.Right * 0.5 -6;
    y = csbi.srWindow.Bottom * 0.5 -2;
}
ptr menu::creazione_lista () {

    string name;
    int pos, score;


    ifstream  file("record.txt");
    if (file.is_open()){

        while (file >> pos >> name >> score){ //riporta il file txt nella lista
            if (h == NULL) {
                h = new list;
                h->pz = pos;
                h->n = name;
                h->s = score;
                h->next = NULL;
            } else {
                p = h;
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = new list;
                p = p->next;
                p->pz = pos;
                p->n = name;
                p->s = score;
                p->next = NULL;
            }
        }

        file.close();

    };
    return h;
}
ptr menu::newscore (ptr h, int nscore, string user) {
    ptr p;
    p = h;
    while (p->next != NULL) {
        if (nscore > p->s) {
            ptr tmp;
            tmp = new list;
            tmp->n = user;
            tmp->s = nscore;
            tmp->pz = 1;
            tmp->next = h;
            h = tmp;
            p = h;
            while (p->next->next != NULL) {
                p = p->next;
                p->pz = p->pz + 1;
            }
            delete p->next;
            p->next = NULL;
        } else {
            if (nscore > p->next->s) {
                if (p->next->next == NULL) {
                    p = p->next;
                    p->n = user;
                    p->s = nscore;
                    p->next = NULL;
                } else {
                    ptr tmp;
                    tmp = new list;
                    tmp->pz = p->next->pz;
                    tmp->s = nscore;
                    tmp->n = user;
                    tmp->next = p->next;
                    p->next = tmp;
                    p = p->next;
                    while (p->next->next != NULL) {
                        p = p->next;
                        p->pz = p->pz + 1;
                    }

                    if (p->next->next ==  NULL) {
                        delete p->next;
                        p->next = NULL;
                    }
                }
            } else {
                p = p->next;
            }
        }

    }
    ptr iter;
    ofstream scrivi; //salva nel documento txt la nuova lista di record aggiornata
    iter = h;
    scrivi.open("record.txt");
    while (iter != NULL) {
        scrivi << iter->pz << " " << iter->n << " " << iter->s << endl;
        iter = iter->next;
    }

    scrivi.close();
    return h;

}
void menu::cout_lista (ptr h) {
    ptr iter;
    iter = h;
    int i = 10;

    for (y ;iter !=NULL ;y++) {
        gotoxy(x-5, y-3);
        cout << iter->pz << " " << iter->n << " " << iter->s << endl;
        iter = iter->next;
    }
}
string menu::presentazione() {
    string user;
    gotoxy(x-18, y+2);
    cout << "Hello World! Good to see you again! Take a ride!" <<endl <<endl;
    gotoxy(x-18, y+6);
    system("pause");

    system("cls");
    gotoxy(x-16, y+2);
    cout << "What's your name again? " << "Username: ";
    cin >> user;

    return user;
}
void menu::post_menu (string user, int score, ptr h) {

    char key;
    gotoxy(x-4, y+2);
    cout << "G A M E   O V E R";
    gotoxy(x-16, y+5);
    system("pause");
    system ("cls");
    ptr iter;
    bool controllo = false;
    bool record = false;
    bool esc = false;
    iter = h;
    while (controllo == false && iter != NULL) {
        if (score > iter->s) {
            record = true;
            controllo = true;
        } else {
            iter = iter->next;
        }
    }

    if (record == true) {
        gotoxy(x-11, y+2);
        cout << "CONGRATS! That's a new record!!!";
        gotoxy(x-16, y+5);
        system("pause");
        system("cls");
        gotoxy(x-15, y+3);
        cout << "Press any key to show your position!";
        gotoxy(x-16, y+5);
        system("pause");

        system("cls");
        h = newscore(h, score, user);
        cout_lista(h);

        esc = false;
        while (esc == false) {
            gotoxy(x-5, y);
            cout << "Press ESC to go back to the main menu!" << endl;
            key = _getch();
            if (key == 27) {
                esc = true;
            }
        }

    }

    else if (record == false) {
        gotoxy(20, 15);
        cout << "Thanks for playing!!!";

        esc = false;
        while (esc == false) {
            gotoxy(20, 20);
            cout << "Press ESC to go back to the main menu!" << endl;
            key = _getch();
            if (key == 27) {
                esc = true;
            }
        }

    }

}


menu::menu(int counter) {

    system("cls");

    h = NULL;
    p = NULL;
    h = creazione_lista();

    char key;
    bool controllo = false;

    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);


    while (controllo == false) {

        window();


        gotoxy(x, y);
        cout << "Play now!";

        gotoxy(x, y+1);
        cout << "Top 10 Records";

        gotoxy(x, y+2);
        cout << "About" ;

        gotoxy(x, y+3);
        cout << "Exit";

        key = _getch();


        if (key == 72 && (counter >= 2 && counter <= 4)) { //72 = up arrow key
            counter--;
        }

        else if (key == 80 && (counter >= 1 && counter <= 3)) { //80 = down arrow key
            counter++;
        }

        else if (key == '\r') { //enter key
            controllo = true;
        }

        if (counter == 1) {
            system ("cls");
            gotoxy(x-2, y);
            cout << ">>" ;
        }

        else if (counter == 2) {
            system ("cls");
            gotoxy(x-2, y+1);
            cout << ">>" ;
        }

        else if (counter == 3) {
            system ("cls");
            gotoxy(x-2, y+2);
            cout << ">>" ;
        }

        else if (counter == 4) {
            system ("cls");
            gotoxy(x-2, y+3);
            cout << ">>" ;
        }

    }

    system("cls");


    if (counter == 1) {
        window();
        string user = presentazione();
        //score = gioco.
        system("cls");
        window();
        post_menu(user, 130, h);
        menu(1);
    }

    else if (counter == 2) {
        controllo = false;
        while (controllo == false) {
            system("cls");
            window();
            cout_lista(h); //cout lista è usato per stampare nella console la lista che precedentemente era stata creata da txt in creazione_lista
            gotoxy(x, y+4);
            cout << "Press ESC to go back!" << endl;
            key = _getch();
            if (key == 27) {
                controllo = true;
            }
        }
        menu(2);
    }

    else if (counter == 3) {
        controllo = false;

        while (controllo == false) {
            system("cls");
            window();
            gotoxy(x-23, y);
            cout << "This is a project we made to complete our programming exam!" <<endl;
            gotoxy(x-23, y+1);
            cout <<  "It's a console-based game and we're so proud of it! Take a ride!";
            gotoxy(x, y+16);
            cout << "Press ESC to go back!" << endl;
            key = _getch();
            if (key == 27) {
                controllo = true;
            }
        }
        menu(3);
    } else {
        return;
    }
}
