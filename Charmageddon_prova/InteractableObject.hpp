//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
#define CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP


#include <windows.h>
#include <string>
#include <iostream>
#include <chrono>


using namespace std;


class InteractableObject{

protected:
    COORD objCoord;
    int objWidth;
    bool isBonus;
    int hitbox[2];
    int pointsExchange;
    bool hit;
    bool onScreen;
    chrono::steady_clock::time_point spawn;
    chrono::steady_clock::time_point move;
    float millisecToMove;



public:
    InteractableObject();

    virtual void PrintObj(class Map* myMap,string myObj[]);
    virtual bool MoveObject(Map* myMap,class Player *myPlayer,class GameState *myGameState);
    void SetObjCoord(short x,short y);
    int GetObjWidth();
    void SetHitbox(int hit1);
    int GetHitbox(int hitboxLenght);
    bool GetIsBonus();
    int GetPointsExchange();
    short getY();


};

#endif //CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
