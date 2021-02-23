//
// Created by TheLi on 21/02/2021.
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
    previous = head;
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

    //while((currentState == PLAYING) && (bIdecreasedLvl == false)){
    for(int spawnPoint=2;spawnPoint>-1;spawnPoint--){
        if(Chance(generalSpawnChance)) {                                                //check if an object is spawning
            if (Chance(bonusChance)) {                                                  //previous condition is true, check if it is a bonus

                Bonus *myBonus = new Bonus();
                SwitchSpawnPos(spawnPoint);
                myBonus->SetObjCoord(xSpawn,ySpawn);
                NewNodeSetting(points,xSpawn, myBonus);
                //myBonus->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
            }else{
                Obstacle *myObstacle = new Obstacle();
                SwitchSpawnPos(spawnPoint);
                myObstacle->SetObjCoord(xSpawn,ySpawn);
                NewNodeSetting(points,xSpawn, myObstacle);
                //myObstacle->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
            }
        }
    }
    if(bIdecreasedLvl == true){
        //chiamare nuova funzione
    }
}


void GameState::PointsProgression(Player *myPlayer) {

    if (myPlayer->getOutOfRoad() == false) {
       points = points + pointPerTickVariation ;
       pointsThisLvl = + pointPerTickVariation ;
    }else{
        points = points - pointPerTickVariation;
        pointsThisLvl = - pointPerTickVariation;
    }
}



void GameState::AddPoints(int addedPoints) {

    points +=  addedPoints;
    pointsThisLvl +=  addedPoints;
}


//aggiungere roba
void GameState::IncreaseDifficulty() {

    levelUpScaling = levelUpScaling + 0.5f;

    if (currentLvl % 2 == 0) {
        pointPerTickVariation++;


    }
}

    void GameState::LvlIncrease() {

        if(pointsThisLvl>basePointsToIncreaseLvl*levelUpScaling){

            currentLvl++;
            pointsThisLvl=0;
            IncreaseDifficulty();
        }




    }

    void GameState::NewNodeSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject) {
        ListSpawnedObjectPtr temp_ptr;
        temp_ptr= new ListSpawnedObject;
        temp_ptr->pointsWhenSpawned=pointsWhenSpawned;
        temp_ptr->xObjSpawnCoord=xObjSpawnCoord;
        temp_ptr->MyObject=MyObject;
        temp_ptr->next=head;
        head=temp_ptr;
        previous->pre=head;
        previous=head;
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


    void GameState::SwitchSpawnPos(int lessThanThree){

        switch(lessThanThree){

            case 2:
                xSpawn=leftSpawn.X;
                ySpawn=leftSpawn.Y;
                break;
            case 1:
                xSpawn=midSpawn.X;
                ySpawn=midSpawn.Y;
                break;
            case 0:
                xSpawn=rightSpawn.X;
                ySpawn=rightSpawn.Y;
                break;

            default: xSpawn=midSpawn.X;ySpawn=midSpawn.Y;
        }
    }


