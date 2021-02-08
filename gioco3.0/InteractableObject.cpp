//
// Created by TheLi on 07/02/2021.
//

#include "InteractableObject.hpp"
#include "Map.hpp"


InteractableObject::InteractableObject() {

}

void InteractableObject::ObjectMovement(Map* myMap,Player *myPlayer,int millisec){

}


void InteractableObject::SetObjCoord(short x, short y) {

    objCoord.X=x;
    objCoord.Y=y;
}


void InteractableObject::SetSpeed(int newSpeed){

    speed=newSpeed;
}

int InteractableObject::GetHitbox(int hitboxLenght){

    if(hitboxLenght<2&&hitboxLenght>-1)
        return hitbox[hitboxLenght];
}

void InteractableObject::PrintObj(Map *myMap, string myObj[]) {


}

void InteractableObject::SetHitPlayer(bool myHitplayer) {

    hitPlayer=myHitplayer;
}

int InteractableObject::GetObjWidth() {
    return objWidth;
}

int  InteractableObject::GetPointsExchange(){

    return pointsExchange;
}

bool InteractableObject::GetIsBonus() {
    return  isBonus;
}