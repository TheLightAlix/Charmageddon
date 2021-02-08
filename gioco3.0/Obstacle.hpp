//
// Created by TheLi on 07/02/2021.
//

#ifndef CHARMAGEDDON_OBSTACLE_HPP
#define CHARMAGEDDON_OBSTACLE_HPP

#include "InteractableObject.hpp"
#include "Player.hpp"

class Obstacle : public InteractableObject
{

protected:
    string enemy[4];
    string clearEn[4];
    string hitParticlesMal[4];

public:
    Obstacle();
    string GetObstacle(int index);
    void MoveObstacle(class Map* myMap,class Player *myPlayer, int);
    virtual void ObjectMovement(Map* myMap,Player *myPlayer,int millisec);

};

#endif //CHARMAGEDDON_OBSTACLE_HPP
