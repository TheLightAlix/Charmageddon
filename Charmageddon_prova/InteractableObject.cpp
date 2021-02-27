//
// Created by TheLi on 21/02/2021.
//

#include "InteractableObject.hpp"
#include "Map.hpp"
#include "GameState.hpp"


InteractableObject::InteractableObject() {


}

bool InteractableObject::MoveObject(Map* myMap,class Player *myPlayer,GameState *myGameState) {
    return true;
}

void InteractableObject::SetObjCoord(short x, short y) {
    objCoord.X=x;
    objCoord.Y=y;
    SetHitbox(x);
}

void InteractableObject::SetHitbox(int hit1) {
    hitbox[0] = hit1;
    hitbox[1] = hit1 + objWidth -1;
}

int InteractableObject::GetHitbox(int hitboxLenght){
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
