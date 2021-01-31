//
// Created by Lorenzo on 26/01/2021.
//
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <ctime>

#ifndef NOMEPROGETTO_MAP_HPP
#define NOMEPROGETTO_MAP_HPP

class Map {
protected:
    char matrix[21][116];
    int nOfLines=21;
    int nOfColumns=116;
    int horizon=9;
    int colTopLeftRoad=22;//column where the top left road margin begins '/'
    int colTopRightRoad=92;//column where the top right road margin begins '\'
    int colBottomLeftRoad=12;//column where the bottom left road margin begins '/'
    int colBottomRightRoad=102;//column where the bottom right road margin begins '\'
public:
    Map();
    void print();
    void set(char, int, int);
    void defGrass(int, int);
    void createLineGrass();
    void runGrass();
};

#endif //NOMEPROGETTO_MAP_HPP
