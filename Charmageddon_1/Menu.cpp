//
// Created by TheLi on 21/02/2021.
//

#include "Menu.hpp"


void Menu::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Menu::window() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    x = csbi.srWindow.Right * 0.5;
    y = csbi.srWindow.Bottom * 0.5;
}
ptr Menu::creazione_lista () {

    string name;
    int pos, score;

    ifstream  file("record.txt");
    if (file.is_open()){

        while (file >> pos >> name >> score){ //riporta il file txt nella lista
            if (h == NULL) {
                h = new lista;
                h->pz = pos;
                h->n = name;
                h->s = score;
                h->next = NULL;
            } else {
                p = h;
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = new lista;
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
ptr Menu::newscore (ptr h, int nscore, string user) {
    ptr p;
    p = h;
    while (p->next != NULL) {
        if (nscore > p->s) {
            ptr tmp;
            tmp = new lista;
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
                    tmp = new lista;
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
void Menu::cout_lista (ptr h) {
    ptr iter;
    iter = h;
    int i = 10;

    for (y ;iter !=NULL ;y++) {
        gotoxy(x-6, y-6);
        cout << iter->pz << " " << iter->n << " " << iter->s << endl;
        iter = iter->next;
    }
}
void Menu::presentazione() {
    window();
    gotoxy(x-24, y-2);
    cout << "Hello World! Good to see you again! Take a ride!" <<endl <<endl;
    window();
    gotoxy(x-19, y+2);
    system("pause");

    system("cls");
    gotoxy(x-17, y-2);
    cout << "What's your name again? " << "Username: ";
    cin >> user;
    return;
}
string Menu::get_user(){
    return user;
};
void Menu::post_menu (string user, int score) {
    system("cls");
    char key;
    window();
    gotoxy(x-9, y);
    cout << "G A M E    O V E R";
    window();
    gotoxy(x-19, y+10);
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
        window();
        gotoxy(x-16, y-1);
        cout << "CONGRATS! That's a new record!!!";
        window();
        gotoxy(x-19, y+6);
        system("pause");
        system("cls");
        window();
        gotoxy(x-18, y-1);
        cout << "Press any key to show your position!";
        window();
        gotoxy(x-19, y+6);
        system("pause");

        system("cls");
        h = newscore(h, score, user);
        cout_lista(h);

        esc = false;
        while (esc == false) {
            window();
            gotoxy(x-19, y+12);
            cout << "Press ESC to esc!" << endl;
            key = _getch();
            if (key == 27) {
                esc = true;
            }
        }

    }

    else if (record == false) {
        window();
        gotoxy(x-11, y);
        cout << "Thanks for playing!!!";
        esc = false;
        while (esc == false) {
            window();
            gotoxy(x-19, y+3);
            cout << "Press ESC to go back to the main Menu!" << endl;
            key = _getch();
            if (key == 27) {
                esc = true;
            }
        }

    }

}
void Menu::scelta_car() {
    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
    system("cls");
    char key;
    bool controllo = false;

    string car1[4];
    car1[3]="  _____";
    car1[2]=" /_..._\\";
    car1[1]="(*[###]*)";
    car1[0]=" []   []";

    string car2[4];
    car2[3]="  ||+++||";
    car2[2]="    +++";
    car2[1]="||| +++ |||";
    car2[0]="|||+++++|||";

    scelta =1;
    while (controllo == false) {

        window();
        gotoxy(x-8, y-6);
        cout << "Choose your car!";

        key = _getch();

        if (key == 75 && (scelta > 1)) { //left arrow key
            scelta--;
        }

        else if (key == 77 && (scelta < 2)) { //right arrow key
            scelta++;
        }
        window();

        if (scelta == 1) {
            system ("cls");

            window();

            for (int i=3;i>=0;i--,y++) {
                gotoxy(x-20, y);
                cout << car1[i] << endl;
            }
            window();
            for (int i=3;i>=0;i--,y++) {
                gotoxy(x+12, y+5);
                cout << car2[i] << endl;
            }
        }

        if (scelta == 2){
            system ("cls");

            window();

            for (int i=3;i>=0;i--,y++) {
                gotoxy(x-20, y+5);
                cout << car1[i] << endl;
            }

            window();

            for (int i=3;i>=0;i--,y++) {
                gotoxy(x+12, y);
                cout << car2[i] << endl;
            }
        }

        if (key == '\r'){
            controllo = true;
        }

    }
    system ("cls");
    return;
}
int Menu::get_scelta() {
    return scelta;
}
void Menu::scelta_colore(){
    int scelta =1;
    bool controllo = false;
    char key;
    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
    while (controllo == false) {
        window();
        gotoxy(x-16,y);
        cout << "Choose your colour:";
        key = _getch();

        if (key == 72 && (scelta >= 2 && scelta <=6)){ //up
            scelta--;
        }

        if (key == 80 && (scelta >= 1 && scelta <=5)){ //up
            scelta++;
        }

        if (key == '\r') {
            controllo = true;
        }

        system("cls");
        switch (scelta) {
            case 1:
                gotoxy(x+5,y);
                cout << "blue";
                break;
            case 2:
                gotoxy(x+5,y);
                cout << "red";
                break;
            case 3:
                gotoxy(x+5,y);
                cout << "ochre";
                break;
            case 4:
                gotoxy(x+5,y);
                cout << "violet";
                break;
            case 5:
                gotoxy(x+5,y);
                cout << "cyan";
                break;
            default:
                gotoxy(x+5,y);
                cout << "white";
                break;
        }

    }

    switch (scelta) {
        case 1:
            colore = BLUE;
            break;
        case 2:
            colore = RED;
            break;
        case 3:
            colore = OCHRE;
            break;
        case 4:
            colore = VIOLET;
            break;
        case 5:
            colore = CYAN;
            break;
        default:
            colore = WHITE;
            break;
    }

};
colours Menu::get_colore(){
    return colore;
}



Menu::Menu() {
    x = 0;
    y = 0;
    counter = 1;
    h = NULL;
    p = NULL;
    h = creazione_lista();
    scelta = 1;
}

int Menu::crea_menu(int counter = 1) {
    bool controllo = false;
    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);

    while (controllo == false) {

        window();

        gotoxy(x - 5, y - 2);
        cout << "Play now!";

        gotoxy(x - 5, y - 1);
        cout << "Top 10 Records";

        gotoxy(x - 5, y);
        cout << "About";

        gotoxy(x - 5, y + 1);
        cout << "Exit";

        key = _getch();


        if (key == 72 && (counter >= 2 && counter <= 4)) { //72 = up arrow key
            counter--;
        } else if (key == 80 && (counter >= 1 && counter <= 3)) { //80 = down arrow key
            counter++;
        } else if (key == '\r') { //enter key
            controllo = true;
        }

        if (counter == 1) {
            system("cls");
            gotoxy(x - 7, y - 2);
            cout << ">>";
        } else if (counter == 2) {
            system("cls");
            gotoxy(x - 7, y - 1);
            cout << ">>";
        } else if (counter == 3) {
            system("cls");
            gotoxy(x - 7, y);
            cout << ">>";
        } else if (counter == 4) {
            system("cls");
            gotoxy(x - 7, y + 1);
            cout << ">>";
        }

    }

    system("cls");


    if (counter == 1) {
        presentazione();
        system("cls");
        scelta_colore();
        scelta_car();
        return counter;
        // system("cls");
        // post_menu(user, 130, h);

    } else if (counter == 2) {
        controllo = false;
        while (controllo == false) {
            system("cls");
            window();
            cout_lista(h); //cout lista è usato per stampare nella console la lista che precedentemente era stata creata da txt in creazione_lista
            gotoxy(x - 11, y + 4);
            cout << "Press ESC to go back!" << endl;
            key = _getch();
            if (key == 27) {
                controllo = true;
            }
        }
        crea_menu(2);
    } else if (counter == 3) {
        controllo = false;

        while (controllo == false) {
            system("cls");
            window();
            gotoxy(x - 30, y);
            cout << "This is a project we made to complete our programming exam!" << endl;
            gotoxy(x - 32, y + 1);
            cout << "It's a console-based game and we're so proud of it! Take a ride!";
            gotoxy(x - 11, y + 16);
            cout << "Press ESC to go back!" << endl;
            key = _getch();
            if (key == 27) {
                controllo = true;
            }
        }
        crea_menu(3);
    } else {
        return counter;
    }
}