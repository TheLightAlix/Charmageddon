//
// Created by TheLi on 21/02/2021.
//

#include "Obstacle.hpp"



Obstacle::Obstacle(){

    enemy[3]="  ___  ";
    enemy[2]=" ( \"o) ";
    enemy[1]="(o\\./o)";
    enemy[0]=" \"   \" ";

    objWidth=7;
    pointsExchange=-500;
    time(&timeSpawn);
    hit = false;
    millisecToMove = 500;
    bool onScreen = true;
    isBonus= false;

    clearEn[3]="       ";
    clearEn[2]="       ";
    clearEn[1]="       ";
    clearEn[0]="       ";


    hitParticlesMal[3]="X     X";
    hitParticlesMal[2]=" X  X  ";
    hitParticlesMal[1]="  X   X";
    hitParticlesMal[0]=" X  X  ";

}

//da cambiare senza thread
bool Obstacle::MoveObject(Map* myMap, Player *myPlayer,GameState *myGameState){
    time(&timeMove);
    //metti timer
    int screenHeight = myMap->getScreenHeight();
    myMap->setCursor(0,screenHeight);
    cout<<objCoord.Y;
    if( (!hit) && (onScreen)) {
        if (myGameState->Timer(timeSpawn,timeMove,millisecToMove)) {
            for (int index = 3; index > -1; index--) {
                myMap->setAndPrintStr(clearEn[index], objCoord.X, objCoord.Y, WHITE);
                objCoord.Y++;
            }
            objCoord.Y = objCoord.Y - 4 + 1;

            for (int index = 3; index > -1; index--) {
                myMap->setAndPrintStr(enemy[index], objCoord.X, objCoord.Y, WHITE);
                objCoord.Y++;
            }

            if ((objCoord.Y + 3>= screenHeight - 3) && (objCoord.Y + 3 <= screenHeight)) {
                hit = myPlayer->CheckHit(this);
                myPlayer->handleHit(hit, pointsExchange);
                if (objCoord.Y +3 == screenHeight) { //se è così cancella il bouns
                    onScreen = false;
                }
            }
            time(&timeSpawn);
        }
        return false;
    }else {
        for (int index = 3; index > -1; index--) {
            myMap->setAndPrintStr(clearEn[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y--;
        }
        return true;

    }
}

string Obstacle::GetObstacle(int index) {
    if(index>-1&&index<4)
        return enemy[index];
}