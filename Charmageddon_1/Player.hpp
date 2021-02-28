#ifndef CHARMAGEDDON_1_PLAYER_HPP
#define CHARMAGEDDON_1_PLAYER_HPP


#include "Map.hpp"
#include "GameState.hpp"
#include "InteractableObject.hpp"

class Player {
protected:
    float relPos; //compreso tra -1 e 1, ed è posizione relativa rispetto al centro dello screen -> 0 è centrata
    float movement;
    string car[4]; //sprite della macchina
    string disapp[4];//per far sparire la macchina
    int carWidth;
    int screenWidth;
    int screenHeight;
    int xCarPosition(float);//serve per calcolare la posizione in cui verrà stampata la macchina.
    colours colour; //decide il colore da dare alla macchina
    void disappear(int);
    void resetAndPrint(int);
    bool outOfRoad;
    class Map *map; // mi salvo un puntatore alla mappa.
public:
    Player(Map *,int,colours);

    //serve per stampare la macchina all'interno della mappa.
    void printCar();

    //serve per far muovere la macchiana a destra e sinistra.
    void moveCar();

    //prende un array e inserisce le x riferite alla destra dello sprite della macchina
    //visto che ci riferiasmo alla macchian sempre con un int riferito alla parte sinistra
    void getRightCarPos(int[]);

    //restituisce il bool outOfRoad per vedere se la macchiana è fuori strada
    bool getOutOfRoad();

    //controlla se è evvenuto uno scontro tra macchina e bonus/malus.
    //restituisce true se avvenuto, false se non avvenuto
    bool CheckHit(class InteractableObject *,int );

};



#endif //CHARMAGEDDON_1_PLAYER_HPP
