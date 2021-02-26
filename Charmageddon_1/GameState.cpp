//
// Created by TheLi on 21/02/2021.
//

#include "GameState.hpp"





GameState::GameState(){

    points=0;
    pointsThisLvl=0;
    pointPerTickVariation=1;
    millisecToUpdatePoints=250;
    millisecToSpawn=5000;
    generalSpawnChance=80;
    bonusChance=10;
    currentLvl=1;
    basePointsToIncreaseLvl=10000;
    levelUpScaling=1.f;
    currentState=MENU;
    MyMenu=new Menu();
    myMap = new Map();
    myPlayer = new Player(myMap,1,WHITE,this);//da completare con il menu nuovo
    headSpawned=NULL;
    headScreen= NULL;
    bIdecreasedLvl=false;
    maxLevel = 0;
}


void GameState::SetGameState(state myState) {

    currentState=myState;
    int choice = 4;
    switch(currentState) {
        case MENU :
            MyMenu = new Menu();
            choice = MyMenu->crea_menu(1);
            if(choice == 1)
                SetGameState(PLAYING);
            break;

        case PLAYING:
            time(&spawn);
            myMap = new Map();
            myMap->printMap();
            myPlayer = new Player(myMap,MyMenu->get_scelta(),MyMenu->get_colore(),this);
            myPlayer->printCar(myMap);
            InitializeSpwnCoord(myMap);
            while((currentState == PLAYING) && !GetAsyncKeyState(VK_ESCAPE)){
                time(&game_time);
                myPlayer->moveCar(myMap);
                if(Timer(spawn,game_time,millisecToSpawn)){
                    //controllo di spawn
                    myMap->setAndPrintChar('c',0,0);
                    SpawnObjects();
                    time(&spawn);
                }
                MoveObjOnScreen();
                PointsProgression(myPlayer);
                LvlIncrease();
            }
            break;
        case GAMEOVER:

            break;
        default:;

    }
}

void GameState::SpawnObjects() {
    if(bIdecreasedLvl == false){
        for(int spawnPoint=2;spawnPoint>-1;spawnPoint--){
            if(Chance(generalSpawnChance)) {                                                //check if an object is spawning
                if (Chance(bonusChance)) {//previous condition is true, check if it is a bonus
                    myMap->setAndPrintStr("PREbonus",0,0,WHITE);
                    Bonus *myBonus = new Bonus();
                    SwitchSpawnPos(spawnPoint);
                    myBonus->SetObjCoord(xSpawn,ySpawn);
                    NewNodeSpawnedSetting(points,xSpawn, myBonus);
                    NewNodeScreenSetting(xSpawn,myBonus);
                    myMap->setAndPrintStr("endbonus",0,0,WHITE);
                    //myBonus->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                }else{
                    myMap->setAndPrintStr("preobstacle",0,0,WHITE);
                    Obstacle *myObstacle = new Obstacle();
                    SwitchSpawnPos(spawnPoint);
                    myObstacle->SetObjCoord(xSpawn,ySpawn);
                    NewNodeSpawnedSetting(points,xSpawn, myObstacle);
                    NewNodeScreenSetting(xSpawn,myObstacle);
                    myMap->setAndPrintStr("endOBSTACLE",0,0,WHITE);
                    //myObstacle->MoveBonus(myMap, myPlayer, millisecToUpdatePoints);
                }
            }
        }
    }
    else{
        RecyclingOldObjects();
    }
}


void GameState::PointsProgression(Player *myPlayer) {

    if (myPlayer->getOutOfRoad() == false) {
        points = points + pointPerTickVariation ;
        pointsThisLvl +=  pointPerTickVariation ;
    }else{
        points = points - pointPerTickVariation;
        pointsThisLvl -=  pointPerTickVariation;
    }
}



void GameState::AddPoints(int addedPoints) {

    points +=  addedPoints;
    pointsThisLvl +=  addedPoints;
}


//aggiungere roba
void GameState::IncreaseDifficulty() {

    levelUpScaling = levelUpScaling + 0.5f;

    /*if (currentLvl % 2 == 0) {
        pointPerTickVariation++;


    }*/
}

void GameState::LvlIncrease() {

    if(pointsThisLvl>basePointsToIncreaseLvl*levelUpScaling){
        currentLvl++;
        pointsThisLvl=0;
        IncreaseDifficulty();
    }


}

void GameState::NewNodeSpawnedSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject) {
    ListSpawnedObjectPtr temp_ptr;
    temp_ptr= new ListSpawnedObject;
    temp_ptr->pointsWhenSpawned=pointsWhenSpawned;
    temp_ptr->xObjSpawnCoord=xObjSpawnCoord;
    temp_ptr->MyObject=MyObject;
    temp_ptr->next=headSpawned;
    headSpawned=temp_ptr;
    if(temp_ptr->next != NULL){
        temp_ptr->next->pre=headSpawned;
    }
    //

}

void GameState::NewNodeScreenSetting(short xObjSpawnCoord, class InteractableObject *MyObject) {
    ListOnScreenObjectPtr t_ptr;
    t_ptr = new ListOnScreenObject;
    t_ptr->xObjSpawnCoord=xObjSpawnCoord;
    t_ptr->MyObject=MyObject;
    t_ptr->next=headScreen;
    headScreen=t_ptr;
    if(t_ptr->next != NULL){
        t_ptr->next->pre=headScreen;
    }
}

void GameState::RecyclingOldObjects() {
    ListSpawnedObjectPtr tmp = headSpawned;
    if(points < 0){
        SetGameState(GAMEOVER);
    }
    else{
        ListSpawnedObjectPtr object = SearchObjList(points);
        int object_points = object->pointsWhenSpawned;
        while(object->pointsWhenSpawned == object_points){
            NewNodeScreenSetting(object->xObjSpawnCoord,object->MyObject);
            object->pre;
        }
    }
}

ListSpawnedObjectPtr GameState::SearchObjList(int points){
    ListSpawnedObjectPtr tmp = headSpawned;
    while(tmp->pointsWhenSpawned >= points){
        tmp = tmp->next;
    }
    tmp = tmp->pre;
    return tmp;
}

void GameState::MoveObjOnScreen() {
    ListOnScreenObjectPtr tmp = headScreen;
    while(tmp != NULL){
        myMap->setAndPrintStr("move",myMap->getScreenWidth()-8,0,RED);
        bool isToRemove = tmp->MyObject->MoveObject(myMap,myPlayer,this);
        myMap->setAndPrintStr("aftermove",myMap->getScreenWidth()-10,0,RED);
        DeleteFromObjOnScreenList(isToRemove,&tmp);
        tmp = tmp->next;
    }
    myMap->setAndPrintStr("afterwhile",myMap->getScreenWidth()-10,0,RED);
}

void GameState::DeleteFromObjOnScreenList(bool shouldIRemoveObj,ListOnScreenObjectPtr *index){

    if(shouldIRemoveObj){
        ListOnScreenObjectPtr tmp = *index;
        if(tmp->pre==NULL){
            if(tmp->next == NULL){
                *index = NULL;
                delete tmp;
            }
            else{
                tmp->next->pre = NULL;
                *index = (*index)->next;
            }
        }
        else if(tmp->next == NULL){
            tmp->pre->next = NULL;
            delete tmp;
        }
        else{
            tmp->pre->next = tmp->next;
            tmp->next->pre = tmp->pre;
            delete tmp;
        }
    }
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


bool GameState::Timer(time_t timeStart,time_t timeCheck, float numToMillisec){
    float elapsedTime=difftime(timeCheck,timeStart)*1000;

    float tmp = elapsedTime / numToMillisec;
    if(tmp >= 1)
        return true;
    else
        return false;
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
        default:
            xSpawn=midSpawn.X;ySpawn=midSpawn.Y;
    }
}



