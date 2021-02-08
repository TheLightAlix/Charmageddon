//
// Created by TheLi on 07/02/2021.
//

#ifndef CHARMAGEDDON_INTERACTABLEOBJECT_HPP
#define CHARMAGEDDON_INTERACTABLEOBJECT_HPP


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
    void MoveObject(class Map* myMap);
    void PrintObj(class Map* myMap,string myObj[]);
    void SetMovement(float myMovement);
    void SetObjCoord(short x,short y);
    void SetHitPlayer(bool myHitplayer);
    void SetSpeed(int newSpeed);
    string GetObj(int index);
    int GetObjWidth();
    float GetMovement();
    int GetHitbox(int hitboxLenght);
    bool GetIsBonus();



};

#endif //CHARMAGEDDON_INTERACTABLEOBJECT_HPP
