
#include "Map.h"
#ifndef GIOCO2_0_CAR_H
#define GIOCO2_0_CAR_H

class Player {
protected:
    float relPos; //compreso tra -1 e 1, ed è posizione relativa rispetto al centro dello screen
    float movement;
    int xCarPosition(float, int);//serve per calcolare la posizione in cui verrà stampata la macchina.
    colours colour; //decide il colore da dare alla macchina
public:
    Player(Map *, colours);
    void printCar(Map *); //serve per stampare la macchina all'interno della mappa.
    void moveCar(Map *); //serve per far muovere la macchiana a destra e sinistra.
    float getMovement();
    void setMovement(float);
};

#endif //GIOCO2_0_CAR_H
