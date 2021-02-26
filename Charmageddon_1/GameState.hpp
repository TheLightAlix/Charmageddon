//
// Created by TheLi on 21/02/2021.
//
#ifndef CHARMAGEDDON_1_GAMESTATE_HPP
#define CHARMAGEDDON_1_GAMESTATE_HPP

#include <windows.h>
#include <iostream>
#include "Player.hpp"
#include "InteractableObject.hpp"
#include "Bonus.hpp"
#include "Obstacle.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>


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
    ListSpawnedObject* pre;
};


struct ListOnScreenObject{

    short xObjSpawnCoord;
    class InteractableObject* MyObject;
    ListOnScreenObject* next;
    ListOnScreenObject* pre;
};




typedef ListSpawnedObject* ListSpawnedObjectPtr;
typedef ListOnScreenObject* ListOnScreenObjectPtr;




class GameState{

protected:
    class Map *myMap;
    class Player *myPlayer;
    ListSpawnedObjectPtr headSpawned;
    ListOnScreenObjectPtr headScreen;
    bool bIdecreasedLvl;
    int bonusChance;
    int generalSpawnChance;
    int points,pointsThisLvl;
    int pointPerTickVariation;
    float millisecToUpdatePoints,millisecToSpawn;
    COORD rightSpawn;
    COORD leftSpawn;
    COORD midSpawn;
    int xSpawn;
    int ySpawn;
    short currentLvl;
    int basePointsToIncreaseLvl;
    float levelUpScaling;
    state currentState;
    class Menu *MyMenu;
    int maxLevel;
    bool Chance(int myPercent);
    void SwitchSpawnPos(int lessThanThree);
    time_t spawn;
    time_t game_time;
    int millisecToMove;

public:

    GameState();
    void SetGameState(state myState);
    void PointsProgression(class Player* myPlayer);
    void AddPoints(int addedPoints);
    void LvlIncrease();
    void IncreaseDifficulty();
    void InitializeSpwnCoord(class Map* myMap);
    void NewNodeSpawnedSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject);
    void NewNodeScreenSetting(short xObjSpawnCoord,class InteractableObject* MyObject);
    void SpawnObjects();
    void RecyclingOldObjects();
    void MoveObjOnScreen();
    ListSpawnedObjectPtr SearchObjList(int points);
    int GetPoints();
    short GetCurrentLvl();
    int Clamp(int myNumber,int lower,int upper);
    state GetCurrentState();
    bool Timer(time_t timeStart,time_t timeCheck, float numToMillisec);
    void DeleteFromObjOnScreenList(bool shouldIRemoveObj,ListOnScreenObjectPtr *index);


};

#endif //CHARMAGEDDON_1_GAMESTATE_HPP