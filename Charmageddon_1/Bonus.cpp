//
// Created by TheLi on 21/02/2021.
//

#include "Bonus.hpp"

Bonus::Bonus(){

    fruit[3]="   (   ";
    fruit[2]=" /   \\ ";
    fruit[1]="(     )";
    fruit[0]="  `\"'  ";

    objWidth=7;
    pointsExchange=500;
    time(&timeSpawn);
    hit = false;
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


//da cambiare senza thread
void Bonus::MoveObject(Map *myMap,Player *myPlayer){
    time(&timeMove);
    /*
    for(int index =3 ;index>-1;index--) {
        myMap->setAndPrintStr(fruit[index], objCoord.X, objCoord.Y, WHITE);
        objCoord.Y++;
    }*/
    float elapsedTime = difftime(timeMove,timeSpawn)*1000;
    bool onScreen = true;
    int screenHeight = myMap->getScreenHeight();
    //da rivedere e da controllare il timer.
    if( (!hit) && (onScreen) && (elapsedTime/millisecToMove >=1)) // controllare che la macchina non venga sovrascritta in stampa
    {
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(clearFru[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y++;
        }
        objCoord.Y=objCoord.Y-4+1;
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(fruit[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y++;
        }

        if((objCoord.Y >= screenHeight-3) && (objCoord.Y <= screenHeight)){
            hit = myPlayer->CheckHit(this);
            myPlayer->handleHit(hit,pointsExchange);
            if(objCoord.Y >= screenHeight){ //se è così cancella il bonus
                    onScreen = false;
            }
        }
        time(&timeSpawn);
    }
    for(int index =3 ;index>-1;index--) {
        myMap->setAndPrintStr(clearFru[index], objCoord.X, objCoord.Y, WHITE);
        objCoord.Y--;
    }

}

string Bonus::GetBonus(int index) {

    if(index>-1&&index<4)
        return fruit[index];
}
