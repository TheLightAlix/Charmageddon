//
// Created by Lorenzo on 26/01/2021.
//
#include "car1.hpp"
Car::Car(){
    xLeftWR=52;
    xRightWR=62;
    yWheels=20;
    xLeftLW=51;
    xRightLW=63;
    yRoof=17;

}

void Car::appear(Map *map) {
    map->set('[',yWheels,xLeftWR);map->set(']',yWheels,xLeftWR+1);
    map->set('[',yWheels,xRightWR-1);map->set(']',yWheels,xRightWR);
    map->set('(',yWheels-1,xLeftLW);map->set('*',yWheels-1,xLeftLW+1);
    map->set('[',yWheels-1,xLeftLW+3);map->set('#',yWheels-1,xLeftLW+4);
    map->set('#',yWheels-1,xLeftLW+5);map->set('#',yWheels-1,xLeftLW+6);
    map->set('#',yWheels-1,xRightLW-5);map->set('#',yWheels-1,xRightLW-4);
    map->set(']',yWheels-1,xRightLW-3); map->set('*',yWheels-1,xRightLW-1);
    map->set(')',yWheels-1,xRightLW);
    map->set('_',yRoof+1,xLeftLW+1);map->set('_',yRoof+1,xLeftLW+2);
    map->set('.',yRoof+1,xLeftLW+3);map->set('.',yRoof+1,xLeftLW+4);
    map->set('.',yRoof+1,xLeftLW+5);map->set('.',yRoof+1,xLeftLW+6);
    map->set('.',yRoof+1,xRightLW-5);map->set('.',yRoof+1,xRightLW-4);
    map->set('_',yRoof+1,xRightLW-1);map->set('_',yRoof+1,xRightLW-2);
    map->set('/',yRoof+1,xLeftLW);map->set('\\',yRoof+1,xRightLW);
    for(int j=xLeftWR;j<=xRightWR;j++){
        map->set('_',yRoof,j);
    }
    map->print();
}

void Car::disappear(Map *map) {
    for(int j=xLeftWR;j<=xRightWR;j++){
        map->set(' ',yWheels,j);
        map->set(' ',yRoof,j);
    }
    for(int j=xLeftLW;j<=xRightLW;j++){
        map->set(' ',yWheels-1,j);
        map->set(' ',yRoof+1,j);
    }
}

void Car::moveLeft(Map *map) {
    Car::disappear(map);
    if((xLeftLW==0)||(xLeftLW==15)){
        //in entrambi i casi si deve muovere nella posizione ad estrema sx.
        xLeftLW=0;
        xLeftWR=1;
        xRightLW=12;
        xRightWR=11;
    } else if(xRightLW==114){ //posizione ad estrema destra
        xLeftLW=87;
        xLeftWR=88;
        xRightLW=99;
        xRightWR=98;
    } else{
        xLeftLW-=12;
        xLeftWR-=12;
        xRightLW-=12;
        xRightWR-=12;
    }
}
void Car::moveRight(Map *map) {
    Car::disappear(map);
    if ((xRightLW == 99) || (xRightLW == 114)) {
        xLeftLW = 102;
        xLeftWR = 103;
        xRightLW = 114;
        xRightWR = 113;
    } else if (xLeftLW == 0) {
        xLeftLW = 15;
        xLeftWR = 16;
        xRightLW = 27;
        xRightWR = 26;
    } else {
        xLeftLW += 12;
        xLeftWR += 12;
        xRightLW += 12;
        xRightWR += 12;
    }
}
//anche fare feedback schermo!!
bool Car::outOfRoad() {
    if((xLeftLW==0)||(xRightLW==114)){
        return true;
    }
    else{
        return false;
    }
}
