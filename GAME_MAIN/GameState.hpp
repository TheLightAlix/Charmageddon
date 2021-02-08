//
// Created by TheLi on 05/02/2021.
//

#ifndef CHARMAGEDDON_GAMESTATE_HPP
#define CHARMAGEDDON_GAMESTATE_HPP

#include <windows.h>
#include <iostream>

using namespace std;



enum state{
    MENU,
    PLAYING,
    GAMEOVER
    };

struct ListSpawnedObject{

    int pointsWhenSpawned;
    short xObjSpawnCoord;
    class InteractableObject* MyObject;
    ListSpawnedObject* next;
    ListSpawnedObject* previous;
};
typedef ListSpawnedObject* ListSpawnedObjectPtr;




class GameState{

protected:
    ListSpawnedObjectPtr head;
    bool bIdecreasedLvl;
    int bonusChance;
    int generalSpawnChance;
    int points,pointsThisLvl;
    int pointPerTickVariation;
    int millisecToUpdatePoints,millisecToSpawn;
    COORD rightSpawn;
    COORD leftSpawn;
    COORD midSpawn;
    short currentLvl;
    int basePointsToIncreaseLvl;
    float levelUpScaling;
    state currentState;
    class Menu *MyMenu;



public:

    GameState();
    //GameState();
    void SetGameState(state myState);
    void PointsProgression(class Player* myPlayer);
    void AddPoints(int addedPoints);
    void LvlIncrease(InteractableObject* myObject);
    void IncreaseDifficulty(InteractableObject* myObject);
    void InitializeSpwnCoord(class Map* myMap);
    void NewNodeSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject);
    void SpawnObjects();
    bool Chance(int myPercent);
    int GetPoints();
    short GetCurrentLvl();
    int Clamp(int myNumber,int lower,int upper);
    state GetCurrentState();


};












#endif //CHARMAGEDDON_GAMESTATE_HPP
