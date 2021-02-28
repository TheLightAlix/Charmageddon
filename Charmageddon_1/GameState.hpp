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
    class Menu *MyMenu;

    state currentState;

    ListSpawnedObjectPtr headSpawned;
    ListOnScreenObjectPtr headScreen;
    ListSpawnedObjectPtr object;

    bool bIdecreasedLvl;
    bool bIsInvincible;

    int bonusChance;
    int generalSpawnChance;
    int points,pointsThisLvl;
    int basePointsToIncreaseLvl;
    int maxLevel;
    int pointPerTickVariation;
    int giftedPoints;
    int xSpawn;
    int ySpawn;
    short currentLvl;
    COORD rightSpawn;
    COORD leftSpawn;
    COORD midSpawn;
    COORD midRightSpawn;
    COORD midLeftSpawn;
    float invincibleDuration;
    float millisecToUpdatePoints,millisecToSpawn;
    float levelUpScaling;

    chrono::steady_clock::time_point spawn;
    chrono::steady_clock::time_point game_time;
    chrono::steady_clock::time_point startINVINCIBLEmode;
    chrono::steady_clock::time_point checkINVINCIBLEmode;

    //Test the chance of a condition with succes prob = myPercent
    bool Chance(int myPercent);

    //Set spawn coord when an object is spawned, used in SpawnObjects
    //precondition: input should be an int x>=0&&x<5, even tho it can handle wrong input
    void SwitchSpawnPos(int lessThanFive);

    //handle var points
    void PointsProgression(class Player* myPlayer);

    // Used to set spawn coord in relation to console screen
    void InitializeSpwnCoord(class Map* myMap);

    //New node with head insert in a double linked list
    void NewNodeSpawnedSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject);
    //New node with head insert in a double linked list
    void NewNodeScreenSetting(short xObjSpawnCoord,class InteractableObject* MyObject);

    //If we didn't decrease lvl it spawns new object according to a timer and chances
    //Else call the method RecyclingOldObjects
    void SpawnObjects();

    void LvlChange();
    void IncreaseDifficulty();


public:

    GameState();
    void SetGameState(state myState);

    //Handle points and pointsThisLevel when and interactableObject is hit
    void AddPoints(int addedPoints);






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
