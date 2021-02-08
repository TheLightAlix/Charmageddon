//
// Created by TheLi on 31/01/2021.
//

#ifndef CHARMAGEDDON_PLAYER_HPP
#define CHARMAGEDDON_PLAYER_HPP

#include "Map.hpp"

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
    void resetAndPrint(Map *,int);
    bool outOfRoad;
public:
    Player(Map *,int,colours);
    void printCar(Map *); //serve per stampare la macchina all'interno della mappa.
    void disappear(Map *,int);
    void moveCar(Map *); //serve per far muovere la macchiana a destra e sinistra.
    float getMovement();
    void setMovement(float);
    int getCarWidth();
    void getRightCarPos(int[]);
    //
    void CheckHit();
};




#endif //CHARMAGEDDON_PLAYER_HPP
