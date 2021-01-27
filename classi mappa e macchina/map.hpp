//
// Created by Lorenzo on 26/01/2021.
//
using namespace std;
#include <iostream>

#ifndef NOMEPROGETTO_MAP_HPP
#define NOMEPROGETTO_MAP_HPP

class Map{
protected:
    char matrix[116][21];
public:
    Map();
    void print();
    void set(char, int, int);
    void defGrass(int, int);
    void createLineGrass(int);
};

#endif //NOMEPROGETTO_MAP_HPP
