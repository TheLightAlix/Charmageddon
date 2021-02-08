
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

void Obstacle::MoveObstacle(class Map* myMap, Player *myPlayer, int millisec){
    bool hit = false;
    bool onScreen = true;
    int screenHeight = myMap->getScreenHeight()
    while( (!hit) && (onScreen)){
        this_thread::sleep_for(chrono::milliseconds(millisec));
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(clearEn[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y++;
        }
        objCoord.Y=objCoord.Y-speed+4;
        for(int index =3 ;index>-1;index--) {
            myMap->setAndPrintStr(enemy[index], objCoord.X, objCoord.Y, WHITE);
            objCoord.Y++;
        }

        if((objCoord.Y >= screenHeight-3) && (objCoord.Y <= screenHeight)){
            bool hit = myPlayer->CheckHit(this);
            myPlayer->handleHit(hit,pointsExchange);
            if(objCoord.Y == screenHeight){ //se è così cancella il bouns
                onScreen = false;
            }
        }
    }
    for(int index =3 ;index>-1;index--) {
        myMap->setAndPrintStr(clearEn[index], objCoord.X, objCoord.Y, WHITE);
        objCoord.Y--;
    }
}

void Obstacle::ObjectMovement(Map* myMap,Player *myPlayer,int millisec){
    MoveObstacle(myMap, myPlayer, millisec);
}


string Obstacle::GetObstacle(int index) {
    if(index>-1&&index<4)
        return enemy[index];
}
