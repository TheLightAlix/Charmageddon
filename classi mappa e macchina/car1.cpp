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
    map->set('[',xLeftWR,yWheels);map->set(']',xLeftWR+1,yWheels);
    map->set('[',xRightWR-1,yWheels);map->set(']',xRightWR,yWheels);
    map->set('(',xLeftLW,yWheels-1);map->set('*',xLeftLW+1,yWheels-1);
    map->set('[',xLeftLW+3,yWheels-1);map->set('#',xLeftLW+4,yWheels-1);
    map->set('#',xLeftLW+5,yWheels-1);map->set('#',xLeftLW+6,yWheels-1);
    map->set('#',xRightLW-5,yWheels-1);map->set('#',xRightLW-4,yWheels-1);
    map->set(']',xRightLW-3,yWheels-1); map->set('*',xRightLW-1,yWheels-1);
    map->set(')',xRightLW,yWheels-1);
    map->set('_',xLeftLW+1,yRoof+1);map->set('_',xLeftLW+2,yRoof+1);
    map->set('.',xLeftLW+3,yRoof+1);map->set('.',xLeftLW+4,yRoof+1);
    map->set('.',xLeftLW+5,yRoof+1);map->set('.',xLeftLW+6,yRoof+1);
    map->set('.',xRightLW-5,yRoof+1);map->set('.',xRightLW-4,yRoof+1);
    map->set('_',xRightLW-1,yRoof+1);map->set('_',xRightLW-2,yRoof+1);
    map->set('/',xLeftLW,yRoof+1);map->set('\\',xRightLW,yRoof+1);
    for(int i=xLeftWR;i<=xRightWR;i++){
        map->set('_',i,yRoof);
    }
    map->print();
}

void Car::disappear(Map *map) {
    for(int i=xLeftWR;i<=xRightWR;i++){
        map->set(' ',i,yWheels);
        map->set(' ',i,yRoof);
    }
    for(int i=xLeftLW;i<=xRightLW;i++){
        map->set(' ',i,yWheels-1);
        map->set(' ',i,yRoof+1);
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
