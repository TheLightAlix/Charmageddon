//
// Created by TheLi on 07/02/2021.
//

#ifndef CHARMAGEDDON_OBSTACLE_HPP
#define CHARMAGEDDON_OBSTACLE_HPP

#include "InteractableObject.hpp"

class Obstacle : public InteractableObject
{

protected:
    string enemy[4];
    string clearEn[4];
    string hitParticlesMal[4];

public:
    Obstacle();
    string GetObstacle(int index);
    void MoveObstacle(class Map* myMap);

};

#endif //CHARMAGEDDON_OBSTACLE_HPP
