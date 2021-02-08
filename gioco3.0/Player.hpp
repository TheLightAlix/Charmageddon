
#include "Map.hpp"
#include "InteractableObject.hpp"
#include "GameState.hpp"
#ifndef GIOCO2_0_CAR_H
#define GIOCO2_0_CAR_H

class Player {
protected:
    float relPos; //compreso tra -1 e 1, ed è posizione relativa rispetto al centro dello screen -> 0 è centrata
    float movement;
    string car[4]; //sprite della macchina
    string disapp[4];//per far sparire la macchina
    int carWidth;
    int screenWidth;
    int xCarPosition(float);//serve per calcolare la posizione in cui verrà stampata la macchina.
    colours colour; //decide il colore da dare alla macchina
    void disappear(Map *,int);
    void resetAndPrint(Map *,int);
    bool outOfRoad;
    GameState *myGameState;
public:
    Player(Map *,int,colours,class GameState *);
    void printCar(Map *); //serve per stampare la macchina all'interno della mappa.
    void moveCar(Map *); //serve per far muovere la macchiana a destra e sinistra.
    float getMovement();
    void setMovement(float);
    int getCarWidth();
    void getRightCarPos(int[]);
    bool getOutOfRoad();
    bool CheckHit(InteractableObject *);
    void handleHit(bool,int);
};

#endif //GIOCO2_0_CAR_H
