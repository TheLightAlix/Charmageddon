//
// Created by TheLi on 05/02/2021.
//

#ifndef CHARMAGEDDON_GAMESTATE_HPP
#define CHARMAGEDDON_GAMESTATE_HPP

#include <windows.h>
#include <iostream>
#include "Map.hpp"
#include "Player.hpp"

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
    Map *myMap;
    Player *myPlayer;
    ListSpawnedObjectPtr head;
    ListSpawnedObjectPtr tail;
    bool bIdecreasedLvl;
    int bonusChance;
    int generalSpawnChance;
    int points,pointsThisLvl;
    int pointPerTickVariation;
    float millisecToUpdatePoints,millisecToSpawn;
    COORD rightSpawn;
    COORD leftSpawn;
    COORD midSpawn;
    short currentLvl;
    int basePointsToIncreaseLvl;
    float levelUpScaling;
    state currentState;
    class Menu *MyMenu;
    int maxLevel;


public:

    GameState();
    //GameState();
    void SetGameState(state myState);
    void PointsProgression(class Player* myPlayer);
    void AddPoints(int addedPoints);
    void LvlIncrease();
    void IncreaseDifficulty();
    void InitializeSpwnCoord(class Map* myMap);
    void NewNodeSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject);
    void SpawnObjects();
    void RecyclingOldObjects();
    bool Chance(int myPercent);
    int GetPoints();
    short GetCurrentLvl();
    int Clamp(int myNumber,int lower,int upper);
    state GetCurrentState();


};












#endif //CHARMAGEDDON_GAMESTATE_HPP
