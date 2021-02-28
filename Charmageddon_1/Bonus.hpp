//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_BONUS_HPP
#define CHARMAGEDDON_1_BONUS_HPP

#include "InteractableObject.hpp"



class Bonus:public InteractableObject
{
protected:
    string fruit[4];
    string clearFru[4];
    string hitPariclesBon[4];

public:
    Bonus();
    void PrintObj(class Map* myMap,string myObj[]) override;
    string GetBonus(int index);
    bool MoveObject(Map* myMap,class Player *myPlayer,class GameState *myGameState) override;
};




#endif //CHARMAGEDDON_1_BONUS_HPP
