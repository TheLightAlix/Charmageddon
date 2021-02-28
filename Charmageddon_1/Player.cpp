//
// Created by TheLi on 21/02/2021.
//

#include "Player.hpp"


Player::Player(Map *map,int type,colours col,GameState *gm) {
    relPos = 0.0;
    movement=0.05;
    colour=col;
    switch(type){
        case 1:
            car[3] = "  _____";
            car[2] = " /_..._\\";
            car[1] = "(*[###]*)";
            car[0] = " []   []";
            carWidth=9;
            disapp[0] = "        ";
            disapp[1] = "         ";
            disapp[2] = "        ";
            disapp[3] = "       ";
            break;
        default:
            car[3] = "  ||+++||";
            car[2] = "    +++";
            car[1] = "||| +++ |||";
            car[0] = "|||+++++|||";
            carWidth = 11;
            disapp[3] = "         ";
            disapp[2] = "       ";
            disapp[1] = "           ";
            disapp[0] = "           ";
    }
    screenWidth = map->getScreenWidth();
    myGameState = gm;
}
int Player::xCarPosition(float rp) {
    return (screenWidth/2 + (int)(screenWidth*rp/2) - carWidth/2);
}
void Player::printCar(Map *map) {
    int screenHeight = map->getScreenHeight();
    int xPos= xCarPosition(relPos);
    map->setCarPos(xPos);
    map->setAndPrintStrCol(car,4,xPos,screenHeight,colour);
}
void Player::disappear(Map *map, int xCarPos) {
    map->setAndPrintStrCol(disapp,4,xCarPos,map->getScreenHeight(),WHITE);
}
void Player::resetAndPrint(Map *map,int xCarPos) {
    string danger[7];
    if((xCarPos <= map->getSLR()) || (xCarPos+carWidth >= map->getSRR())){ //per come sono fatte le macchine deve funzionare così.
        danger[0] = "/_____________\\";
        danger[1] = " /     .     \\";
        danger[2] = "  /    |    \\";
        danger[3] = "   /   |   \\";
        danger[4] = "    /  |  \\";
        danger[5] = "     / | \\";
        danger[6] = "      / \\";
        outOfRoad = true;
    }else{
        danger[0] = "               ";
        danger[1] = "              ";
        danger[2] = "             ";
        danger[3] = "            ";
        danger[4] = "           ";
        danger[5] = "          ";
        danger[6] = "         ";
        outOfRoad = false;
    }
    map->setAndPrintStrCol(danger,7,map->getScreenWidth()/2-7,map->getScreenHeight()/2.8,RED);
    map->printMap();
    //qui c'era anche un print map prima ma in teoria non dovrebbe cambiare niente
    //printCar(map);
}

void Player::moveCar(Map *map) {
    int xCarPos;
    if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)) {
        disappear(map,xCarPosition(relPos));
        xCarPos = xCarPosition(relPos-movement);
        if(xCarPos >= 0){
            relPos -= movement;
        }
        resetAndPrint(map,xCarPos);
    }
    else if(GetAsyncKeyState(VK_RIGHT)& (0x8000 != 0)){
        disappear(map,xCarPosition(relPos));
        xCarPos = xCarPosition(relPos+movement);
        if(xCarPos<=screenWidth-carWidth){
            relPos += movement;
        }
        resetAndPrint(map,xCarPos);
    }
}

void Player::setMovement(float mv) {
    movement = mv;
}

float Player::getMovement() {
    return movement;
}
int Player::getCarWidth() {
    return carWidth;
}
void Player::getRightCarPos(int positions[]) {
    string prova;
    int xCarPos = xCarPosition(relPos);
    for(int i = 0; i < 4 ;i++ ){
        prova = car[i];
        positions[i] = xCarPos + prova.length()-1;//il meno 1 perchè xCarPos mi dice la prima posizione
    }
}
bool Player::getOutOfRoad() {
    return outOfRoad;
}

bool Player::CheckHit(InteractableObject *obj,int heightCheck) {
    //se heightCheck == 2 devo guardare le due righe più in alto della macchina.
    int carDesPos[4];
    int end = 3; //ultima posizione valida in carDesPos
    int xCarPos = xCarPosition(relPos);
    getRightCarPos(carDesPos);
    bool hit = false;
    int x1 = obj->GetHitbox(0);
    int x2 = obj->GetHitbox(1);
    int counter = 0;
    while ((!hit) && (counter < heightCheck)){
        if(((x1 >= xCarPos) && (x1 <= carDesPos[end-counter])) || ((x2 >= xCarPos) && (x2 <= carDesPos[end-counter]))){
            hit = true;
        }
        counter++;
    }
    return hit;
}

void Player::handleHit( int points) {
    myGameState->AddPoints(points);
}
