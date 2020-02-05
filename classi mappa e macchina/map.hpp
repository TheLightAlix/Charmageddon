
using namespace std;
#include <iostream>	

#ifndef NOMEPROGETTO_MAP_HPP
#define NOMEPROGETTO_MAP_HPP


class map{
protected:
    char matrix[116][21];
public:
    map();
    void print();
    void set(char, int, int);
};

#endif //NOMEPROGETTO_MAP_HPP
