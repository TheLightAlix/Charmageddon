//
// Created by TheLi on 07/02/2021.
//

#ifndef CHARMAGEDDON_INTERACTABLEOBJECT_HPP
#define CHARMAGEDDON_INTERACTABLEOBJECT_HPP



class InteractableObject{

protected:
    float movement;

public:
    InteractableObject();
    void SetMovement(float myMovement);
    float GetMovement();

};

#endif //CHARMAGEDDON_INTERACTABLEOBJECT_HPP
