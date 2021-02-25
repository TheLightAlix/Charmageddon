//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_BONUS_HPP
#define CHARMAGEDDON_1_BONUS_HPP

#include "InteractableObject.hpp"
#include "Map.hpp"
#include "Player.hpp"


class Bonus:public InteractableObject
{
protected:
    string fruit[4];
    string clearFru[4];
    string hitPariclesBon[4];

public:
    Bonus();
    string GetBonus(int index);
    void MoveBonus(Map* myMap,class Player *myPlayer,int millisec);
};


#endif //CHARMAGEDDON_1_BONUS_HPP
