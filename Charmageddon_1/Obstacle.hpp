//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_OBSTACLE_HPP
#define CHARMAGEDDON_1_OBSTACLE_HPP


#include "InteractableObject.hpp"

class Obstacle : public InteractableObject
{

protected:
    string enemy[4];
    string clearEn[4];
    string hitParticlesMal[4];

public:
    Obstacle();
    void PrintObj(class Map *myMap, string *myObj) override;
    string GetObstacle(int index);
    bool MoveObject(class Map* myMap,class Player *myPlayer,class GameState *myGameState) override;
};



#endif //CHARMAGEDDON_1_OBSTACLE_HPP
