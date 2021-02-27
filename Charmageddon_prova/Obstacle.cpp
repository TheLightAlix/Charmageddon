//
// Created by TheLi on 21/02/2021.
//

#include "Obstacle.hpp"



Obstacle::Obstacle(){

    enemy[3]="  ___  ";
    enemy[2]=" ( \"o) ";
    enemy[1]="(o\\./o)";
    enemy[0]=" \"   \" ";

    hitbox[0] = objCoord.X;
    hitbox[1] = objCoord.X + objWidth -1;
    objWidth=7;
    pointsExchange=-500;
    hit = false;
    onScreen = true;
    isBonus= false;

    clearEn[3]="       ";
    clearEn[2]="       ";
    clearEn[1]="       ";
    clearEn[0]="       ";


}

bool Obstacle::MoveObject(Map* myMap, Player *myPlayer,GameState *myGameState){
    int screenHeight = myMap->getScreenHeight();
    if( (!hit) && (onScreen)) {
        PrintObj(myMap,clearEn);
        objCoord.Y++;
        PrintObj(myMap,enemy);
        if ((objCoord.Y >= screenHeight - 3) && (objCoord.Y  <= screenHeight)) {
            //hit = myPlayer->CheckHit(this);
            //myPlayer->handleHit(hit, pointsExchange);
            if (objCoord.Y == screenHeight) { //se è così cancella il bouns
                onScreen = false;
            }
        }
        return false;
    }else {
        PrintObj(myMap,clearEn);
        return true;
    }
}

void Obstacle::PrintObj(class Map *myMap, string *myObj) {
    myMap->setAndPrintStrCol(myObj,myObj->length(),objCoord.X,objCoord.Y,WHITE);
}

string Obstacle::GetObstacle(int index) {
    if(index>-1&&index<4)
        return enemy[index];
}