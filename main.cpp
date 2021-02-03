#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

class menu{

protected:

    void color(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
    void gotoxy(int x, int y) {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }
    struct list {
        int pz;
        string n;
        int s;
        list *next;
    };
    typedef list *ptr;
    ptr h, p;

public:

    ptr creazione_lista () {

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

    ptr newscore (ptr h, int nscore, string user) {
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

    void cout_lista (ptr h) {
        ptr iter;
        iter = h;
        int i = 10;

        for (i=6 ;iter !=NULL ;i++) {
            gotoxy(20, i);
            cout << iter->pz << " " << iter->n << " " << iter->s << endl;
            iter = iter->next;
        }
    }

    void post_menu (string user, int score, ptr h) {
        char key;
        gotoxy(20, 15);
        cout << "G A M E   O V E R";
        gotoxy(20, 16);
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
            gotoxy(20, 15);
            cout << "CONGRATS! That's a new record!!!";
            gotoxy(20, 20);
            system("pause");
            gotoxy(20, 15);
            cout << "Press any key to show your position!";
            gotoxy(20, 20);
            system("pause");

            system("cls");
            h = newscore(h, score, user);
            cout_lista(h);

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

    string presentazione() {
        string user;
        gotoxy(20, 15);
        cout << "Hello World! Good to see you again! Take a ride!" <<endl <<endl;
        gotoxy(20, 18);
        system("pause");

        system("cls");
        gotoxy(20, 15);
        cout << "What's your name again? " << "Username: ";
        cin >> user;

        return user;
    }

    menu(int counter = 1) {

        system("cls");

        h = NULL;
        p = NULL;
        h = creazione_lista();

        int Set [] = {7, 7, 7, 7, 7, 7, 7}; //colors
        char key;
        bool controllo = false;

        keybd_event(VK_SPACE, 0, 0, 0);
        keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);


        while (controllo == false) {

            gotoxy(20, 10);
            color(Set[0]);
            cout << "Play now!";

            gotoxy(20, 11);
            color(Set[1]);
            cout << "Top 10 Records";

            gotoxy(20, 12);
            color(Set[2]);
            cout << "About" ;

            gotoxy(20, 13);
            color(Set[3]);
            cout << "Exit";

            key = _getch();


            if (key == 72 && (counter >= 2 && counter <= 4)) { //72 = up arrow key
                counter--;
            }

            if (key == 80 && (counter >= 1 && counter <= 3)) { //80 = down arrow key
                counter++;
            }

            if (key == '\r') { //enter key
                controllo = true;
            }

            Set[0] = 7; //colore default
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;
            Set[4] = 7;
            Set[5] = 7;
            Set[6] = 7;

            if (counter == 1) {
                Set[0] = 32; //verde
            }
            if (counter == 2) {
                Set[1] = 32; //verde
            }
            if (counter == 3) {
                Set[2] = 32; //verde
            }
            if (counter == 4) {
                Set[3] = 32; //verde
            }
        }

        system("cls");

        if (counter == 1) {
            string user = presentazione();
            //score = gioco.
            system("cls");
            post_menu(user, 77, h);
            menu(1);
        }

        if (counter == 2) {
            controllo = false;
            cout_lista(h); //cout lista è usato per stampare nella console la lista che precedentemente era stata creata da txt in creazione_lista

            while (controllo == false) {
                gotoxy(20, 20);
                cout << "Press ESC to go back!" << endl;
                key = _getch();
                if (key == 27) {
                    controllo = true;
                }
            }
            menu(2);
        }

        if (counter == 3) {
            controllo = false;
            gotoxy(20, 10);
            cout << "This is a project we made to complete our programming exam!" <<endl;
            gotoxy(20, 11);
            cout <<  "It's a console-based game and we're so proud of it! Take a ride!";

            while (controllo == false) {
                gotoxy(20, 20);
                cout << "Press ESC to go back!" << endl;
                key = _getch();
                if (key == 27) {
                    controllo = true;
                }
            }
            menu(3);
        }

        if (counter == 4) {
            return;
        }
    }

};

int main() {

    menu a;

    return 0;
}
