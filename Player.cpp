//
// Created by TheLi on 31/01/2021.
//

#include "Player.hpp"
#include <string>

Player::Player(Map *map,int type,colours col) {
    relPos = 0.0;
    movement=0.05;
    colour=col;
    switch(type){
        case 1:
            car[3]="  _____";
            car[2]=" /_..._\\";
            car[1]="(*[###]*)";
            car[0]=" []   []";
            carWidth=9;
            break;
        default:
            car[3]="  ||+++||";
            car[2]="    +++";
            car[1]="||| +++ |||";
            car[0]="|||+++++|||";
            carWidth=11;
            break;
    }
}
int Player::xCarPosition(float rp, int screenWidth) {
    return (screenWidth/2 + (int)(screenWidth*rp/2) - carWidth/2);
}

void Player::printCar(Map *map) {
    int screenWidth = map->getScreenWidth();
    int screenHeight = map->getScreenHeight();
    int xPos= xCarPosition(relPos,screenWidth);
    map->setCarPos(xPos);
    map->setAndPrintStrCol(car,4,xPos,screenHeight,colour);
    map->setCursor(screenWidth,0);
}
void Player::resetAndPrint(Map *map,int xCarPos) {
    system("cls");
    if((xCarPos<map->getSLR())||(xCarPos+carWidth>map->getSRR())){
        string danger[7];
        danger[0] ="/_____________\\";
        danger[1]=" /     .     \\";
        danger[2]="  /    |    \\";
        danger[3]="   /   |   \\";
        danger[4]="    /  |  \\";
        danger[5]="     / | \\";
        danger[6]="      / \\";
        map->setAndPrintStrCol(danger,7,map->getScreenWidth()/2-7,map->getScreenHeight()/2.8,RED);
    }
    map->printMap();
    printCar(map);
}
void Player::moveCar(Map *map) {
    int screenWidth=map->getScreenWidth();
    int xCarPos;
    if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)) {
        xCarPos=xCarPosition(relPos-movement,screenWidth);
        if(xCarPos>=0){
            relPos-=movement;
        }
        resetAndPrint(map,xCarPos);
    }
    else if(GetAsyncKeyState(VK_RIGHT)& (0x8000 != 0)){
        xCarPos=xCarPosition(relPos+movement,screenWidth);
        if(xCarPos<=screenWidth-carWidth){
            relPos+=movement;
        }
        resetAndPrint(map,xCarPos);
    }
}
void Player::setMovement(float mv) {
    movement=mv;
}

float Player::getMovement() {
    return movement;
}
int Player::getCarWidth() {
    return carWidth;
}

//Added
void Player::SetSpeed(int mySpeed) {
    speed=mySpeed;
}

bool Player::GetBIsOutOfTrack() {
    return bIsOutOfTrack;
}

int Player::GetSpeed() {
    return speed;
}

int Player::GetMaxSpeed() {
    return maxSpeed;
}

int Player::GetMinSpeed() {
    return minSpeed;
}


