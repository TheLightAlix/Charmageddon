//
// Created by TheLi on 21/02/2021.
//

#ifndef CHARMAGEDDON_1_GAMESTATE_HPP
#define CHARMAGEDDON_1_GAMESTATE_HPP

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
    ListSpawnedObject* pre;
};
typedef ListSpawnedObject* ListSpawnedObjectPtr;




class GameState{

protected:
    class Map *myMap;
    class Player *myPlayer;
    ListSpawnedObjectPtr head;
    ListSpawnedObjectPtr previous;
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

    int GetPoints();
    short GetCurrentLvl();
    int Clamp(int myNumber,int lower,int upper);
    state GetCurrentState();


};

#endif //CHARMAGEDDON_1_GAMESTATE_HPP
