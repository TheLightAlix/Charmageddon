//
// Created by TheLi on 07/02/2021.
//

#ifndef CHARMAGEDDON_BONUS_HPP
#define CHARMAGEDDON_BONUS_HPP

#include "InteractableObject.hpp"
#include "GameState.hpp"



class Bonus:public InteractableObject
{
protected:
    string fruit[4];
    string clearFru[4];
    string hitPariclesBon[4];

public:
    Bonus();
    string GetBonus(int index);
    void MoveBonus(class Map* myMap, class Player *myPLayer,int);
    virtual void ObjectMovement(Map* myMap,Player *myPlayer,int millisec);
};





#endif //CHARMAGEDDON_BONUS_HPP
