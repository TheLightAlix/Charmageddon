//
// Created by TheLi on 21/02/2021.
//


#include "Bonus.hpp"
#include "Map.hpp"
#include "Player.hpp"


Bonus::Bonus(){

    fruit[3]="   (   ";
    fruit[2]=" /   \\ ";
    fruit[1]="(     )";
    fruit[0]="  `\"'  ";

    objWidth=7;
    pointsExchange=500;
    time(&timeSpawn);
    hit = false;
    millisecToMove = 4000;
    bool onScreen = true;
    isBonus=true;

    clearFru[3]="       ";
    clearFru[2]="       ";
    clearFru[1]="       ";
    clearFru[0]="       ";

    hitPariclesBon[3]="*+    +";
    hitPariclesBon[2]="   +   ";
    hitPariclesBon[1]=" ++  + ";
    hitPariclesBon[0]="+     +";
}



bool Bonus::MoveObject(Map *myMap,Player *myPlayer,GameState *myGameState) {
    time(&timeMove);
    int screenHeight = myMap->getScreenHeight();
    myMap->setCursor(0,screenHeight);
    cout<<objCoord.Y;
    if( (!hit) && (onScreen)) // controllare che la macchina non venga sovrascritta in stampa
    {
        if(myGameState->Timer(timeSpawn,timeMove,millisecToMove) && objCoord.Y<=screenHeight){
            myMap->setAndPrintStrCol(clearFru,clearFru->length(),objCoord.X,objCoord.Y,WHITE);
            objCoord.Y++;
            myMap->setAndPrintStrCol(fruit,fruit->length(),objCoord.X,objCoord.Y,WHITE);
            if((objCoord.Y >= screenHeight-3) && (objCoord.Y <= screenHeight)){
                hit = myPlayer->CheckHit(this);
                myPlayer->handleHit(hit,pointsExchange);
                if(objCoord.Y == screenHeight){ //se è così cancella il bonus
                    onScreen = false;
                }
            }
            time(&timeSpawn);
        }
        return false;
    }
    else{
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(clearFru[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y--;
        }
        return true;
    }


}

string Bonus::GetBonus(int index) {

    if(index>-1&&index<4)
        return fruit[index];
}