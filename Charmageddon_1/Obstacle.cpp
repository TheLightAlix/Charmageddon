//
// Created by TheLi on 21/02/2021.
//

#include "Obstacle.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "GameState.hpp"


Obstacle::Obstacle(){

    enemy[3]="  ___  ";
    enemy[2]=" ( \"o) ";
    enemy[1]="(o\\./o)";
    enemy[0]=" \"   \" ";

    objWidth=7;
    pointsExchange=-5000;
    spawn = std::chrono::steady_clock::now();
    millisecToMove = 300;
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
    move = std::chrono::steady_clock::now();
    if( (!hit) && (onScreen)) {
        if(myGameState->Timer(spawn,move,millisecToMove)){
            PrintObj(myMap,clearEn);
            objCoord.Y++;
            objCoord.X += xMovement;
            SetHitbox(objCoord.X);
            PrintObj(myMap,enemy);
            myMap->printMap(); //questa è qui perchè i bonus non vengono cancellati alla perfezione.
            if ((objCoord.Y >= screenHeight - 3) && (objCoord.Y  <= screenHeight)) {
                hit = myPlayer->CheckHit(this,objCoord.Y-screenHeight+4);
                if(hit){
                    myPlayer->handleHit(pointsExchange);
                    return MoveObject(myMap,myPlayer,myGameState);
                }
                if (objCoord.Y == screenHeight) { //se è così cancella il bouns
                    onScreen = false;
                }
            }
            spawn =  std::chrono::steady_clock::now();
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
