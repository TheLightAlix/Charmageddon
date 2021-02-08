//
// Created by TheLi on 07/02/2021.
//

#include "Obstacle.hpp"
#include "Map.hpp"


Obstacle::Obstacle(){

    enemy[3]="  ___  ";
    enemy[2]=" ( \"o) ";
    enemy[1]="(o\\./o)";
    enemy[0]=" \"   \" ";

    speed=1;
    objWidth=7;
    pointsExchange=-500;
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

void Obstacle::MoveObstacle(class Map* myMap){

    for(int index =3 ;index>-1;index--) {
        myMap->setAndPrintStr(clearEn[index], objCoord.X, objCoord.Y, WHITE);
        objCoord.Y++;
    }
    objCoord.Y=objCoord.Y-speed+4;
    for(int index =3 ;index>-1;index--) {
        myMap->setAndPrintStr(enemy[index], objCoord.X, objCoord.Y, WHITE);
        objCoord.Y++;
    }

}

string Obstacle::GetObstacle(int index) {
    if(index>-1&&index<4)
    return enemy[index];
}