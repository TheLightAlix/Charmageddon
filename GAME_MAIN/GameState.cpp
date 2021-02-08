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
    head=new ListSpawnedObject;
    bIdecreasedLvl=false;
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
    this_thread::sleep_for(chrono::milliseconds(millisecToSpawn));

    for(int spawnPoint=2;spawnPoint>-1;spawnPoint++){
        if(Chance(generalSpawnChance))
            if(Chance(bonusChance)){
                Bonus* myBonus= new Bonus();
                if(spawnPoint==2){
                    myBonus->SetObjCoord(rightSpawn.X,rightSpawn.Y);

                }
            }

            }else{

            }
    }
}

void GameState::PointsProgression(Player *myPlayer) {

    while(currentState==PLAYING) {

            this_thread::sleep_for(chrono::milliseconds(millisecToUpdatePoints));
            if (myPlayer->GetBIsOutOfTrack() == false) {
                points = points + pointPerTickVariation ;
                pointsThisLvl = + pointPerTickVariation ;
            }
            else {
                points = points - pointPerTickVariation;
                pointsThisLvl = - pointPerTickVariation;
            }
    }

}

void GameState::AddPoints(int addedPoints) {

    points=points+addedPoints;
    pointsThisLvl = + addedPoints;
}



void GameState::IncreaseDifficulty(InteractableObject* myObject) {

    levelUpScaling=levelUpScaling + 0.5f;

    if(currentLvl%2==0){
        pointPerTickVariation++;


}

void GameState::LvlIncrease(InteractableObject* myObject) {

    short temp=currentLvl;
    while (currentState==PLAYING){

        if(pointsThisLvl>basePointsToIncreaseLvl*levelUpScaling){
            currentLvl++;
            IncreaseDifficulty(myObject);
        }

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