//
// Created by TheLi on 21/02/2021.
//

#include "Bonus.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <thread>
#include <chrono>
#include "GameState.hpp"



Bonus::Bonus(){

    fruit[3]="   (   ";
    fruit[2]=" /   \\ ";
    fruit[1]="(     )";
    fruit[0]="  `\"'  ";

    objWidth=7;
    pointsExchange=2500;
    spawn = std::chrono::steady_clock::now();
    millisecToMove = 300;
    hit = false;
    onScreen = true;
    isBonus=true;

    clearFru[3]="       ";
    clearFru[2]="       ";
    clearFru[1]="       ";
    clearFru[0]="       ";
}

void Bonus::PrintObj(class Map *myMap, string *myObj) {
    myMap->setAndPrintStrCol(myObj,myObj->length(),objCoord.X,objCoord.Y,WHITE);
}


bool Bonus::MoveObject(Map *myMap,Player *myPlayer,GameState *myGameState) {
    move = std::chrono::steady_clock::now();
    int screenHeight = myMap->getScreenHeight();
    if( (!hit) && (onScreen)) // controllare che la macchina non venga sovrascritta in stampa
    {
        if(myGameState->Timer(spawn,move,millisecToMove)){
            PrintObj(myMap,clearFru);
            objCoord.Y++;
            objCoord.X += xMovement;
            SetHitbox(objCoord.X);
            PrintObj(myMap,fruit);
            myMap->printMap();
            if((objCoord.Y >= screenHeight-3) && (objCoord.Y <= screenHeight)){
                hit = myPlayer->CheckHit(this,objCoord.Y-screenHeight+4);
                if(hit){
                    myGameState->AddPoints(pointsExchange);
                    return MoveObject(myMap,myPlayer,myGameState);
                }
                if(objCoord.Y == screenHeight){ //se è così cancella il bonus
                    onScreen = false;
                }
            }
            spawn =  std::chrono::steady_clock::now();
        }
        return false;
    }
    else{
        PrintObj(myMap,clearFru);
        return true;
    }


}

string Bonus::GetBonus(int index) {

    if(index>-1&&index<4)
        return fruit[index];
    else
        return "error";
}