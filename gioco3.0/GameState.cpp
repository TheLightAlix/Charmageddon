//
// Created by TheLi on 05/02/2021.
//

#include "GameState.hpp"
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




GameState::GameState(){

    points=0;
    pointsThisLvl=0;
    pointPerTickVariation=1;
    millisecToUpdatePoints=250;
    millisecToSpawn=5000;
    generalSpawnChance=30;
    bonusChance=10;
    currentLvl=1;
    basePointsToIncreaseLvl=10000;
    levelUpScaling=1.f;
    currentState=MENU;
    MyMenu=new Menu();
    myMap = new Map();
    myPlayer = new Player(myMap,1,WHITE,this);//da completare con il menu nuovo
    head=new ListSpawnedObject;
    tail = head;
    bIdecreasedLvl=false;
    maxLevel = 0;
}


void GameState::SetGameState(state myState) {

    currentState=myState;

    switch(currentState) {
        case MENU :

            points=MyMenu->crea_menu();


            break;
        case PLAYING:


            break;
        case GAMEOVER:

            break;
        default:;

    }
}

void GameState::SpawnObjects() {
    while((currentState == PLAYING) && (bIdecreasedLvl == false)){
        this_thread::sleep_for(chrono::milliseconds(millisecToSpawn));

        for(int spawnPoint=2;spawnPoint>-1;spawnPoint++){
            if(Chance(generalSpawnChance)) {
                if (Chance(bonusChance)) {
                    Bonus *myBonus = new Bonus();
                    if (spawnPoint == 2) {
                        myBonus->SetObjCoord(rightSpawn.X, rightSpawn.Y);
                        NewNodeSetting(points, rightSpawn.X, myBonus);
                        myBonus->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                    } else if (spawnPoint == 1) {
                        myBonus->SetObjCoord(midSpawn.X, midSpawn.Y);
                        NewNodeSetting(points, midSpawn.X, myBonus);
                        myBonus->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                    } else {
                        myBonus->SetObjCoord(leftSpawn.X, leftSpawn.Y);
                        NewNodeSetting(points, leftSpawn.X, myBonus);
                        myBonus->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                    }
                } else {
                    Obstacle *myObstacle = new Obstacle();
                    if (spawnPoint == 2) {
                        myObstacle->SetObjCoord(rightSpawn.X, rightSpawn.Y);
                        NewNodeSetting(points, rightSpawn.X, myObstacle);
                        myObstacle->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                    } else if (spawnPoint == 1) {
                        myObstacle->SetObjCoord(midSpawn.X, midSpawn.Y);
                        NewNodeSetting(points, midSpawn.X, myObstacle);
                        myObstacle->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                    } else {
                        myObstacle->SetObjCoord(leftSpawn.X, leftSpawn.Y);
                        NewNodeSetting(points, leftSpawn.X, myObstacle);
                        myObstacle->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                    }
                }
            }
        }
    }
    if(bIdecreasedLvl == true){
        //chiamare nuova funzione
    }
}
void GameState::RecyclingOldObjects() {
    ListSpawnedObjectPtr tmp = head;
    if(points < 0){
        SetGameState(GAMEOVER);
    }
    else{
        while((tmp->pointsWhenSpawned > points) && (tmp != nullptr)){
            tmp = tmp->next;
        }
        if(tmp->pointsWhenSpawned < points){
            //
        }
    }
}


void GameState::PointsProgression(Player *myPlayer) {

    while(currentState==PLAYING) {

        this_thread::sleep_for(chrono::milliseconds(millisecToUpdatePoints));
        if (myPlayer->getOutOfRoad() == false) {
            points += pointPerTickVariation ;
            pointsThisLvl += pointPerTickVariation ;
        }
        else {
            points -= pointPerTickVariation;
            pointsThisLvl -= pointPerTickVariation;
            if(pointsThisLvl < 0){
                currentLvl--;
                bIdecreasedLvl = true;
                pointsThisLvl = basePointsToIncreaseLvl + pointsThisLvl;
            }
        }
    }

}

void GameState::AddPoints(int addedPoints) {

    points += addedPoints;
    pointsThisLvl += addedPoints;
    if(pointsThisLvl < 0){
        currentLvl--;
        bIdecreasedLvl = true;
        pointsThisLvl = basePointsToIncreaseLvl + pointsThisLvl;
    }
}



void GameState::IncreaseDifficulty() {

    if ((currentLvl % 2 == 0) && (millisecToSpawn >= 3200)) {
          millisecToSpawn -= 100;
    }else if((currentLvL % 2 == 1) && (millisecToUpdatePoints >= 100)){
        millisecToUpdatePoints -= 10;
    }
}
    void GameState::LvlIncrease() {

        short temp=currentLvl;
        while (currentState==PLAYING){

            if(pointsThisLvl>basePointsToIncreaseLvl){
                maxLevel++;
                currentLvl++;
                pointsThisLvl = 0;
                IncreaseDifficulty();
            }

        }


    }

    void GameState::NewNodeSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject) {
        ListSpawnedObjectPtr temp_ptr;
        temp_ptr= new ListSpawnedObject;
        temp_ptr->pointsWhenSpawned=pointsWhenSpawned;
        temp_ptr->xObjSpawnCoord=xObjSpawnCoord;
        temp_ptr->MyObject=MyObject;
        temp_ptr->previous = nullptr;
        temp_ptr->next=head;
        head->previous = temp_ptr;
        head=temp_ptr;
    }


    void GameState::InitializeSpwnCoord(class Map* myMap) {
        rightSpawn.X=myMap->getERR()-8;
        leftSpawn.X=myMap->getELF()+1;
        midSpawn.X=myMap->getScreenWidth()/2;
        rightSpawn.Y=myMap->getScreenHeight()/(2.3+1);
        leftSpawn.Y=myMap->getScreenHeight()/(2.3+1);
        midSpawn.Y=myMap->getScreenHeight()/(2.3+1);

    }

    bool GameState::Chance(int myPercent) {

        srand(time(0));
        int temp=rand()%100000;
        if(temp<=myPercent*1000)
            return true;
        else
            return false;
    }
    int GameState::Clamp(int myNumber,int lower,int upper){

        return std::max(lower, std::min(myNumber,upper));
    }