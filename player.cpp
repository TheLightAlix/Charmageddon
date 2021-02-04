
#include "Player.h"
Player::Player(Map *map, colours col) {
    relPos = 0.0;
    movement=0.05;
    colour=col;
}
int Player::xCarPosition(float rp, int screenWidth) {
    return (screenWidth/2 + (int)(screenWidth*rp/2) - 5);
}

void Player::printCar(Map *map) {
    string car[4];
    car[3]="  _____";
    car[2]=" /_..._\\";
    car[1]="(*[###]*)";
    car[0]=" []   []";
    int screenWidth = map->getScreenWidth();
    int screenHeight = map->getScreenHeight();
    int xPos= xCarPosition(relPos,screenWidth);
    map->setCarPos(xPos);
    map->setAndPrintStrCol(car,4,xPos,screenHeight,colour);
    map->setCursor(screenWidth,screenHeight);
}

void Player::moveCar(Map *map) {
    int screenWidth=map->getScreenWidth();
    if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)) {
        if(xCarPosition(relPos-movement,screenWidth)>=0){
            relPos-=movement;
        }
        system("cls");
        map->printMap();
        printCar(map);
    }
    else if(GetAsyncKeyState(VK_RIGHT)& (0x8000 != 0)){
        if(xCarPosition(relPos+movement,screenWidth)<=screenWidth-9){
            relPos+=movement;
        }
        system("cls");
        map->printMap();
        printCar(map);
    }
}
void Player::setMovement(float mv) {
    movement=mv;
}

float Player::getMovement() {
    return movement;
}
