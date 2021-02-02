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
        ofstream scrivi;
        iter = h;
        scrivi.open("record.txt");
        while (iter != NULL) {
            scrivi << iter->pz << " " << iter->n << " " << iter->s << endl;
            iter = iter->next;
        }

        scrivi.close();

    }

    void cout_lista (ptr h) {
        ptr iter;
        iter = h;
        int i = 10;

        for (i=10;iter !=NULL ;i++) {
            gotoxy(10, i);
            cout << iter->pz << " " << iter->n << " " << iter->s << endl;
            iter = iter->next;
        }
    }

    string presentazione() {
        string user;
        gotoxy(10, 15);
        cout << "Ciao!" <<endl <<endl;
        system("pause");

        system("cls");
        gotoxy(10, 15);
        cout << "Inserisci il tuo user qui! >>" << " ";
        cin >> user;

        return user;
    }

    menu() {

        string user = presentazione();
        system("cls");
        h = NULL;
        p = NULL;
        h = creazione_lista();

        int counter = 1;
        int Set [] = {7, 7, 7, 7, 7, 7, 7}; //colors
        char key;
        bool controllo = false;

        keybd_event(VK_SPACE, 0, 0, 0);
        keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);


        while (controllo == false) {

            gotoxy(10, 15);
            color(Set[0]);
            cout << "1. Play now!";

            gotoxy(10, 16);
            color(Set[1]);
            cout << "2. Top 10 Records";

            gotoxy(10, 17);
            color(Set[2]);
            cout << "3. About" << endl;

            gotoxy(10, 18);
            color(Set[3]);
            cout << "4. Exit" << endl;

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
            cout << endl << "here the game" <<endl; //qui metteremo il gioco
            system ("pause");
        }

        if (counter == 2) {
            cout_lista(h); //cout lista è usato per stampare nella console la lista che precedentemente era stata creata da txt in creazione_lista
            system("pause");
        }

        if (counter == 3) {
            gotoxy(10, 15);
            cout << "Menu 3" <<endl;
            system("pause");

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
