//
// Created by TheLi on 21/02/2021.
//

#include "InteractableObject.hpp"
#include "Map.hpp"
#include "GameState.hpp"


InteractableObject::InteractableObject() {



}

bool InteractableObject::MoveObject(Map* myMap,class Player *myPlayer,GameState *myGameState) {

}

void InteractableObject::SetObjCoord(short x, short y) {

    objCoord.X=x;
    objCoord.Y=y;
}



int InteractableObject::GetHitbox(int hitboxLenght){

    if(hitboxLenght<2&&hitboxLenght>-1)
        return hitbox[hitboxLenght];
}

void InteractableObject::PrintObj(Map *myMap, string myObj[]) {

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
short InteractableObject::getY() {
    return objCoord.Y;
}
