//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_OBSTACLE_HPP
#define CHARMAGEDDON_1_OBSTACLE_HPP


#include "InteractableObject.hpp"
#include "Map.hpp"
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
    void MoveObject(class Map* myMap,class Player *myPlayer);

};


#endif //CHARMAGEDDON_1_OBSTACLE_HPP
