//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
#define CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP


#include <windows.h>
#include <string>
#include <iostream>
#include <ctime>


using namespace std;


class InteractableObject{

protected:
    COORD objCoord;
    int objWidth;
    bool hitPlayer;
    bool isBonus;
    int hitbox[2];
    int pointsExchange;
    time_t timeSpawn;
    time_t timeMove;
    float millisecToMove;
    bool hit;
    bool onScreen;


public:
    InteractableObject();

    void PrintObj(class Map* myMap,string myObj[]);
    virtual bool MoveObject(Map* myMap,class Player *myPlayer,class GameState *myGameState);
    void SetObjCoord(short x,short y);
    void SetHitPlayer(bool myHitplayer);
    int GetObjWidth();
    int GetHitbox(int hitboxLenght);
    bool GetIsBonus();
    int GetPointsExchange();
    short getY();
    short getX();


};

#endif //CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
