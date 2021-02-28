#include "Player.hpp"


Player::Player(Map *map,int type,colours col) {
    relPos = 0.0;
    movement=0.05;
    colour=col;
    this->map = map;
    switch(type){ //type mi dice il tipo di macchina.
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
    screenHeight = map->getScreenHeight();
}
int Player::xCarPosition(float rp) {
    return (screenWidth/2 + (int)(screenWidth*rp/2) - carWidth/2); //la x da cui parto a stampare la macchina.
    //-carWidth/2 serve per avere la macchina centrata a schermo quando rp = 0.
}
void Player::printCar() {
    int xPos= xCarPosition(relPos);
    map->setAndPrintStrCol(car,4,xPos,screenHeight,colour);
}
void Player::disappear(int xCarPos) {
    map->setAndPrintStrCol(disapp,4,xCarPos,map->getScreenHeight(),WHITE);
}
void Player::resetAndPrint(int xCarPos) {
    string danger[7];
    //sono fuoristrada se la x della macchian è a sx di startLeftRoad o se la x+width()posizione a dx della macchina
    //è a dx di startRightRoad
    if((xCarPos <= map->getSLR()) || (xCarPos+carWidth >= map->getSRR())){
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
    map->setAndPrintStrCol(danger,7,screenWidth/2-7,screenHeight/2.8,RED);
    map->printMap();
}

void Player::moveCar() {
    int xCarPos;
    if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)) { //se viene premuta la freccia sinistra
        disappear(xCarPosition(relPos)); //faccio sparire la macchina
        xCarPos = xCarPosition(relPos-movement);//cambio posizione della macchina
        if(xCarPos >= 0){ //se non sono troppo a sinistra aggiorno la posizione relativa della macchina
            relPos -= movement;
        }
        resetAndPrint(xCarPos);
    }
    else if(GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0)){//se viene premuta la freccia destra
        disappear(xCarPosition(relPos));
        xCarPos = xCarPosition(relPos+movement);
        if(xCarPos<=screenWidth-carWidth){//se non sono troppo a destra aggiorno la posizione relativa della macchina
            relPos += movement;
        }
        resetAndPrint(xCarPos);
    }
}

void Player::getRightCarPos(int positions[]) {
    string prova;
    int xCarPos = xCarPosition(relPos);
    for(int i = 0; i < 4 ;i++ ){
        prova = car[i];
        positions[i] = xCarPos + prova.length()-1;//mi restituisce x del carattere più a destra di quella riga della macchina
    }
}

bool Player::getOutOfRoad() {
    return outOfRoad;
}

bool Player::CheckHit(InteractableObject *obj,int heightCheck) {
    //diamo per scontato che l'oggetto sia ad una altezza per cui sia possibile la collisione
    //quindi controlliamo solo le x.
    int carDesPos[4];
    int end = 3; //ultima posizione valida in carDesPos
    int xCarPos = xCarPosition(relPos);
    getRightCarPos(carDesPos);
    bool hit = false;
    int x1 = obj->GetHitbox(0);
    int x2 = obj->GetHitbox(1);
    int counter = 0;
    while ((!hit) && (counter < heightCheck)){
        //se la x1 del bonus/malus è all'interno di dove sta la mia macchina, oppure se lo è la x2, allora c'è hit
        if(((x1 >= xCarPos) && (x1 <= carDesPos[end-counter])) || ((x2 >= xCarPos) && (x2 <= carDesPos[end-counter]))){
            hit = true;
        }
        counter++;
    }
    return hit;
}
