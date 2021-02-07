//
// Created by leola on 07/02/2021.
//

#include "contak.h"


contak::contak(float speed, float maxspeed) {
int intspeed;
int intmaxspeed;

intspeed = static_cast<int>(speed);
intmaxspeed = static_cast<int>(maxspeed);

int i;

i = (intspeed*50)/intmaxspeed;

    cout << intspeed << "  ";
    for(i; i>0; i--) {
    cout << "|";
}

}