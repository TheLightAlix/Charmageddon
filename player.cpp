#include "Player.hpp"
Player::Player(Map *map,int type,colours col) {
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
}
int Player::xCarPosition(float rp) {
    return (screenWidth/2 + (int)(screenWidth*rp/2) - carWidth/2);
}
void Player::printCar(Map *map) {
    int screenHeight = map->getScreenHeight();
    int xPos= xCarPosition(relPos);
    map->setCarPos(xPos);
    map->setAndPrintStrCol(car,4,xPos,screenHeight,colour);
    map->setCursor(screenWidth,0);
}
void Player::disappear(Map *map, int xCarPos) {
    map->setAndPrintStrCol(disapp,4,xCarPos,map->getScreenHeight());
}
void Player::resetAndPrint(Map *map,int xCarPos) {
    string danger[7];
    if((xCarPos <= map->getSLR()) || (xCarPos+carWidth >= map->getSRR())){ //per come sono fatte le macchine deve funzionare così.
        danger[0] ="/_____________\\";
        danger[1]=" /     .     \\";
        danger[2]="  /    |    \\";
        danger[3]="   /   |   \\";
        danger[4]="    /  |  \\";
        danger[5]="     / | \\";
        danger[6]="      / \\";
        outOfRoad = true;
    }else{
        danger[0] ="               ";
        danger[1]="              ";
        danger[2]="             ";
        danger[3]="            ";
        danger[4]="           ";
        danger[5]="          ";
        danger[6]="         ";
        outOfRoad = false;
    }
    map->setAndPrintStrCol(danger,7,map->getScreenWidth()/2-7,map->getScreenHeight()/2.8,RED);
    int i = rand()%1000;
    map->runGrass(i); // preso in un qualche modo
    map->printMap();
    printCar(map);
}
void Player::moveCar(Map *map) {
    int xCarPos;
    if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)) {
        disappear(map,xCarPosition(relPos));
        xCarPos=xCarPosition(relPos-movement);
        if(xCarPos>=0){
            relPos-=movement;
        }
        resetAndPrint(map,xCarPos);
    }
    else if(GetAsyncKeyState(VK_RIGHT)& (0x8000 != 0)){
        disappear(map,xCarPosition(relPos));
        xCarPos=xCarPosition(relPos+movement);
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
void Player::getRightCarPos(int positions[]) {
    string prova;
    int xCarPos = xCarPosition(relPos);
    for(int i = 0; i < 4 ;i++ ){
        prova = car[i];
        positions[i] = xCarPos+prova.length()-1;//il meno 1 perchè xCarPos mi dice la prima posizione
    }
}
bool Player::getOutOfRoad() {
    return outOfRoad;
}

bool Player::CheckHit(InteractableObject *obj) {
    int carDesPos[4];
    int xCarPos = xCarPosition(relPos);
    getRightCarPos(carDesPos);
    bool hit = false;
    int x1 = obj->GetHitbox(0);
    int x2 = obj->GetHitbox(1);
    int counter = 0;
    while ((!hit) && (counter < 4)){
        if(((x1 >= xCarPos) && (x1 <= carDesPos[counter])) || ((x2 >= xCarPos) && (x2 <= carDesPos[counter]))){
            hit = true;
        }
        counter++;
    }
    return hit;
}

void Player::handleHit(bool hit) {
    if(hit){
        //do something
    }
}


