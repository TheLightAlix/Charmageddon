//
// Created by TheLi on 05/02/2021.
//

#include "GameState.hpp"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;


GameState::GameState(){

    points=0;
    pointPerTickVariation=1;
    millisecToUpdatePoints=250;
    currentLvl=1;
    MenuState=1;
    basePointsToIncreaseLvl=10000;
    levelUpScaling=1.f;
    currentState=MENU;
    MyMenu=new Menu();
}


void GameState::SetGameState(state myState) {

    currentState=myState;

    switch(currentState) {
        case MENU :
            cout<<"test1";
            points=MyMenu->crea_menu();
            cout<<points;
            SetGameState(PLAYING);

            break;
        case PLAYING:
            cin>>points;
            cout<<points;

            break;
        case GAMEOVER:

            break;
        default:;

    }
}

void GameState::PointsProgression(Player *myPlayer) {

    while(currentState==PLAYING) {

            //this_thread::sleep_for(chrono::milliseconds(millisecToUpdatePoints));
            if (myPlayer->GetBIsOutOfTrack() == false)
                points = points + pointPerTickVariation * (myPlayer->GetSpeed() / 100);
            else
                points = points - pointPerTickVariation;
    }

}

void GameState::AddPoints(int addedPoints) {

    points=points+addedPoints;
}

bool GameState::Chance(int myPercent) {

    srand(time(0));
    int temp=rand()%100000;
    if(temp<=myPercent*1000)
        return true;
    else
        return false;
}


void GameState::IncreaseDifficulty(InteractableObject* myObject) {

    levelUpScaling=levelUpScaling + 0.5f;

}

void GameState::LvlIncrease(InteractableObject* myObject) {

    short temp=currentLvl;
    while (currentState==PLAYING){

        currentLvl=points/(basePointsToIncreaseLvl*levelUpScaling)+1;
        if(temp<currentLvl){

            IncreaseDifficulty(myObject);
        }

    }


}

GameState GameState::GetGameState() {

    return *this;
}