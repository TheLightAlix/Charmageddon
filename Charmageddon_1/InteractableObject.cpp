//
// Created by TheLi on 21/02/2021.
//

#include "InteractableObject.hpp"
#include "Map.hpp"


#include <windows.h>
#include <string>
#include <iostream>
#include <chrono>


using namespace std;


InteractableObject::InteractableObject() {


}

bool InteractableObject::MoveObject(Map* myMap,class Player *myPlayer,GameState *myGameState) {
    return true;
}

void InteractableObject::SetObjCoord(short x, short y,int xCentralSpawn) {
    objCoord.X=x;
    objCoord.Y=y;
    SetHitbox(x);
    setHorizontalMov(xCentralSpawn);
}

void InteractableObject::setHorizontalMov(int xCentralSpawn) {
    srand(time(0));
    if(objCoord.X < xCentralSpawn){
        xMovement = -1;
    }
    else if(objCoord.X > xCentralSpawn){
        xMovement = 1;
    }
    else{
        xMovement = rand()%3-1; //un numero intero compreso tra -1 e 1.
    }
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

void InteractableObject::Reset(short myYCoord,short myXCoord){

    hit=false;
    onScreen=true;
    objCoord.Y=myYCoord;
    objCoord.X = myXCoord;
    SetHitbox(myXCoord);
}