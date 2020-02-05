//
// Created by Andrea Tozzi on 30/01/2020.
//

#include "car1.hpp"

car1::car1() {
    x1=51;
    y1=20;
    x2=63;
    y2=17;
}
void car1::appear(map *map) {//crea la macchina.
    map->set('[',x1+1,y1);map->set(']',x1+2,y1); map->set('[',x2-2,y1);map->set(']',x2-1,y1);
    map->set('(',x1,y1-1);map->set('*',x1+1,y1-1);map->set('[',x1+3,y1-1);map->set('#',x1+4,y1-1);
    map->set('#',x1+5,y1-1);map->set('#',x1+6,y1-1);map->set('#',x2-5,y1-1);map->set('#',x2-4,y1-1);
    map->set(']',x2-3,y1-1); map->set('*',x2-1,y1-1);map->set(')',x2,y1-1);
    map->set('_',x1+1,y1-2);map->set('_',x1+2,y1-2);map->set('.',x1+3,y1-2);map->set('.',x1+4,y1-2);
    map->set('.',x1+5,y1-2);map->set('.',x1+6,y1-2);map->set('.',x2-5,y1-2);map->set('.',x2-4,y1-2);
    map->set('_',x2-1,y1-2);map->set('_',x2-2,y1-2);map->set('/',x1,y1-2);map->set('\\',x2,y1-2);
    for(int i=x1+1;i<x2;i++){
        map->set('_',i,y2);
    }
    map->print();
}
void car1::disappear(map *map) {//fa sparire la macchina
    for (int j=y2;j>=y1;j++){
        for (int i=x1;i<=x2;i++){
            map->set(' ',i,j);
        }
    }
}
void car1::moveleft(map *map) {
    car1::disappear(map);
    if ((x1==15)||(x1==0)){//nelle posizione cardine fa in modo che lo spostamento avvenga bene.
        x1=0;
        x2=12;
    }
    else if(x2==114){
        x1=87;
        x2=99;
    }
    else{
        x1=x1-12;
        x2=x2-12;
    }
}

void car1::moveright(map *map) {
    car1::disappear(map);
    if ((x2==99)||(x2==114)){
        x1=102;
        x2=114;
    }
    else if(x1==0){
        x1=15;
        x2=27;
    }
    else{
        x1=x1+12;
        x2=x2+12;
    }
}
