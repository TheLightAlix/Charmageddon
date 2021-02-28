//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_GAMESTATE_HPP
#define CHARMAGEDDON_1_GAMESTATE_HPP

#include <windows.h>
#include <iostream>
#include <chrono>


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
    ListSpawnedObjectPtr object;
    bool bIdecreasedLvl;
    int bonusChance;
    int generalSpawnChance;
    int points,pointsThisLvl;
    int pointPerTickVariation;
    int giftedPoints;
    float millisecToUpdatePoints,millisecToSpawn;
    COORD rightSpawn;
    COORD leftSpawn;
    COORD midSpawn;
    COORD midRightSpawn;
    COORD midLeftSpawn;
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
    bool bIsRecycling;
    chrono::steady_clock::time_point spawn;
    chrono::steady_clock::time_point game_time;
    chrono::steady_clock::time_point startINVINCIBLEmode;
    chrono::steady_clock::time_point checkINVINCIBLEmode;
    float invincibleDuration;
    bool bIsInvincible;

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
    bool Timer(chrono::steady_clock::time_point timeStart,chrono::steady_clock::time_point timeCheck, float numToMillisec);
    void DeleteFromObjOnScreenList(bool shouldIRemoveObj,ListOnScreenObjectPtr index);

};


#endif //CHARMAGEDDON_1_GAMESTATE_HPP
