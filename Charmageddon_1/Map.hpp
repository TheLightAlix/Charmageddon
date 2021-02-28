//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_MAP_HPP
#define CHARMAGEDDON_1_MAP_HPP

using namespace std;
#include <windows.h>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h>

struct bilista{
    string line;
    bilista* prev;
    bilista* next;
};
typedef bilista* ptrBilista;

enum colours {
    BLUE,
    RED,
    GREEN,
    OCHRE,
    VIOLET,
    CYAN,
    WHITE
};

class Map {
protected:
    //tutta mappa
    CONSOLE_SCREEN_BUFFER_INFO csbi; //serve per prendere le informazioni della console, come l'altezza e larghezza.
    int screenWidth;
    int screenHeight;
    float xMiddle;
    float roadWidth; //percentuale dello schermo dedicata alla strada
    int startLeftRoad; //inizio dal basso delle / per indicare la strada
    int startRightRoad;//inizio dal basso delle \ per indicare la strada
    //auto
    int carPosition=0; //posizione più a sinistra dell'auto.
    //stelle
    int starsAStarts; //mi indica quale stringa di stelle stampare
    string starsA;
    string starsB;
    //erba
    int length; //lunghezza delle righe d'erba
    int endLeftRoad; // ultima / che dall'alto che rappresenta la strada
    int endRightRoad; // ultima \ che dall'alto che rappresenta la strada
    int create; //serve per creare la lista circolare con tutti i componenti
    int random; //crea randomicità tra le partite.
    ptrBilista head; //ultima riga d'erba(in basso)
    ptrBilista tail; //prima riga d'erba(in alto)
    chrono::steady_clock::time_point lastGrassMove;
    chrono::steady_clock::time_point move;
    chrono::steady_clock::time_point lastStarsMove;
    float milliSecToMoveGrass;
    float millisecToMoveStars;

    //serve per settare la console in modo da stampare il colore adeguato!
    void chooseColor(colours);

    //inizializza le variabili riguardanti le stelle
    void startStars();

    //mi inizializza le variabili della parte inerente all'erba
    void startGrass();

    //operazione di insert della lista circolare
    void insert();

    //micrea una linea d'erba
    void createLine(int);

    //serve per invertire una stringa.
    //i due int in input mi dicono l'inizio e la fine della stringa da invertire.
    void reverseString(string *,int,int);

public:
    Map();

    //serve per spostare il cursore ad una certa zona della console.
    void setCursor(short,short);

    //serve per stampare un carattere in una certa zona della console
    void setAndPrintChar(char,short,short);

    //serve per stampare una stringa colorata in una certa zona della console
    void setAndPrintStr(string,short,short,colours);

    //serve per stampare un'array di stringhe colorate in una certa zona della console
    void setAndPrintStrCol(string[],int,short,short,colours);

    //stampa tutta gli elementi della mappa.
    void printMap();

    //restituisce la larghezza dello schermo
    int getScreenWidth();

    //restituisce l'altezza dello schermo
    int getScreenHeight();

    //restituisce startLeftRoad
    int getSLR();

    //restituisce startRightRoad
    int getSRR();

    //restituisce endLefRoad
    int getELR();

    //restituisce endLeftRoad,
    int getERR();

    //stars

    //stampa le stelle
    void printStars();

    //grass

    //serve a stampare l'erba
    void printGrass();

    //serve a muovere l'erba da una una riga x, alla riga x-1(quindi quella sotto)
    void runGrass(int);

    //serve per far muovere tutte le decorazioni a schermo.
    //se muovo erba ristampa anche player, in modo da non sovrascriverlo.
    void runDecorations(int);

    //serve per calcolare se è passato il tempo rappresentato in millisecondi dal float passato in input.
    //restituisce true se passato, false altrimenti
    bool timer(chrono::steady_clock::time_point,chrono::steady_clock::time_point,float);
};



#endif //CHARMAGEDDON_1_MAP_HPP