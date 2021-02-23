//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
#define CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP


#include <windows.h>
#include <string>
#include <iostream>

using namespace std;


class InteractableObject{

protected:
    int speed;
    COORD objCoord;
    int objWidth;
    bool hitPlayer;
    bool isBonus;
    int hitbox[2];
    int pointsExchange;



public:
    InteractableObject();

    void PrintObj(class Map* myMap,string myObj[]);

    void SetObjCoord(short x,short y);
    void SetHitPlayer(bool myHitplayer);
    void SetSpeed(int newSpeed);
    int GetObjWidth();
    int GetHitbox(int hitboxLenght);
    bool GetIsBonus();
    int GetPointsExchange();



};

#endif //CHARMAGEDDON_1_INTERACTABLEOBJECT_HPP
