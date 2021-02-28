//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
#define CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP


#include <windows.h>
#include <string>
#include <iostream>

using namespace std;


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
    int variation;
    bool hit;
    bool onScreen;
    chrono::steady_clock::time_point spawn;
    chrono::steady_clock::time_point move;
    float millisecToMove;
    int xMovement;


public:
    InteractableObject();

    virtual void PrintObj(class Map* myMap,string myObj[]);
    virtual bool MoveObject(Map* myMap,class Player *myPlayer,class GameState *myGameState);
    void SetObjCoord(short x,short y,int xCentralSpawn);
    int GetObjWidth();
    void SetHitbox(int hit1);
    int GetHitbox(int hitboxLenght);
    bool GetIsBonus();
    int GetPointsExchange();
    short getY();
    void Reset(short myYCoord,short myXCoord);
    void setHorizontalMov(int xCentralSpawn);
    void SetMillisecToMove(float myMillisecToMove);
    void SpeedVariation();

};

#endif //CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
