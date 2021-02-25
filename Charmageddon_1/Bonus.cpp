//
// Created by TheLi on 21/02/2021.
//

#include "Bonus.hpp"

Bonus::Bonus(){

    fruit[3]="   (   ";
    fruit[2]=" /   \\ ";
    fruit[1]="(     )";
    fruit[0]="  `\"'  ";

    speed=1;
    objWidth=7;
    pointsExchange=500;
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
void Bonus::MoveBonus(Map* myMap,Player *myPlayer,int millisec){ //aggiungere un thread movement
    for(int index =3 ;index>-1;index--) {
        myMap->setAndPrintStr(fruit[index], objCoord.X, objCoord.Y, WHITE);
        objCoord.Y++;
    }
    bool hit = false;
    bool onScreen = true;
    int screenHeight = myMap->getScreenHeight();
    while( (!hit) && (onScreen))
    {
        //this_thread::sleep_for(chrono::milliseconds(millisec));
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(clearFru[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y++;
        }
        objCoord.Y=objCoord.Y-speed+4;
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(fruit[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y++;
        }

        if((objCoord.Y >= screenHeight-3) && (objCoord.Y <= screenHeight)){
            hit = myPlayer->CheckHit(this);
            myPlayer->handleHit(hit,pointsExchange);
            if(objCoord.Y >= screenHeight){ //se è così cancella il bouns
                    onScreen = false;
            }
        }
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
