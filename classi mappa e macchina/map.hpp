//
// Created by Lorenzo on 26/01/2021.
//
using namespace std;
#include <iostream>

#ifndef NOMEPROGETTO_MAP_HPP
#define NOMEPROGETTO_MAP_HPP

class Map {
protected:
    char matrix[21][116];
    int nOfLines=21;
    int nOfColumns=116;
    int horizon=9;
public:
    Map();
    void print();
    void set(char, int, int);
};

#endif //NOMEPROGETTO_MAP_HPP
