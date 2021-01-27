//
// Created by Lorenzo on 26/01/2021.
//
#include "map.hpp"
#ifndef NOMEPROGETTO_CAR1_HPP
#define NOMEPROGETTO_CAR1_HPP

class Car {
protected:
    int xLeftWR;
    int xRightWR;
    int yWheels;
    int xLeftLW;
    int xRightLW;
    int yRoof;
    //le x si riferiscono alla parte più esterna dell'oggetto
public:
    Car();
    void appear(Map *);
    void disappear(Map *);
    void moveLeft(Map *);
    void moveRight(Map *);
};


#endif //NOMEPROGETTO_CAR1_HPP
