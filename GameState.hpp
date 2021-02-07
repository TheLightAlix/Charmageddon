//
// Created by TheLi on 05/02/2021.
//

#ifndef CHARMAGEDDON_GAMESTATE_HPP
#define CHARMAGEDDON_GAMESTATE_HPP

#include "Player.cpp"
#include "InteractableObject.hpp"



enum state{
    MENU,
    PLAYING,
    GAMEOVER
    };

struct ListSpawnedObject{

    int pointsWhenSpawned;
    InteractableObject* MyObject;
    ListSpawnedObject* next;
};
typedef ListSpawnedObject* ListSpawnedObjectPtr;

class GameState{

protected:

    int points;
    int pointPerTickVariation;
    int millisecToUpdatePoints,millisecToSpawnObj;
    short maxNumSpawnedObj;
    short currentLvl;
    int basePointsToIncreaseLvl;
    float levelUpScaling;
    state currentState;


public:

    GameState();
    //GameState();
    void SetGameState(state myState);
    void PointsProgression(Player* myPlayer);
    void AddPoints(int addedPoints);
    void LvlIncrease(InteractableObject* myObject);
    void IncreaseDifficulty(InteractableObject* myObject);
    void SpawnObjects(InteractableObject* myObject);
    bool Chance(int myPercent);
    int GetPoints();
    short GetCurrentLvl();
    state GetCurrentState();
    GameState GetGameState();

};












#endif //CHARMAGEDDON_GAMESTATE_HPP
