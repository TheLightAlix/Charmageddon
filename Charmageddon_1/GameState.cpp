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
#include <cstdlib>
#include <ctime>




GameState::GameState(){

    srand(time(0));
    points=0;
    pointsThisLvl=0;
    pointPerTickVariation=1;
    millisecToUpdatePoints=250;
    millisecToSpawn=3000;
    giftedPoints=100;
    generalSpawnChance=30;
    bonusChance=10;
    currentLvl=1;
    basePointsToIncreaseLvl=30000;
    levelUpScaling=1.f;
    currentState=MENU;
    MyMenu=new Menu();
    myMap = new Map();
    myPlayer = new Player(myMap,1,WHITE);//da completare con il menu nuovo
    headSpawned=NULL;
    headScreen= NULL;
    object=NULL;
    bIdecreasedLvl=false;
    maxLevel = 0;
    invincibleDuration = 2000; //in millisec
    bIsInvincible = false;
}


void GameState::SetGameState(state myState) {

    currentState=myState;
    int choice = 4;
    spawn = std::chrono::steady_clock::now();
    game_time = std::chrono::steady_clock::now();
    switch(currentState) {
        case MENU :
            MyMenu = new Menu();
            choice = MyMenu->crea_menu(1);
            if(choice == 1)
                SetGameState(PLAYING);
            break;

        case PLAYING:
            spawn =  std::chrono::steady_clock::now();
            myMap = new Map();
            myMap->printMap();
            myPlayer = new Player(myMap,MyMenu->get_scelta(),MyMenu->get_colore());
            myPlayer->printCar();
            InitializeSpwnCoord(myMap);
            myMap->printStars();
            while((currentState == PLAYING) && !GetAsyncKeyState(VK_ESCAPE)){
                myPlayer->moveCar();
                SpawnObjects();
                MoveObjOnScreen();
                myMap->runDecorations(points);
                myPlayer->printCar();
                PointsProgression(myPlayer);
                myMap->setCursor(0,myMap->getScreenHeight()/2.7);
                cout<<points<<"        ";
                LvlIncrease();
                myMap->setCursor(0,myMap->getScreenHeight()/2.7+1);
                cout<<currentLvl;
            }
            break;
        case GAMEOVER:
            MyMenu->post_menu(MyMenu->get_user(),points);
            break;
    }
}
//ora facciamo spawnare un solo oggetto e facciamo muovere.
void GameState::SpawnObjects() {
    game_time =  std::chrono::steady_clock::now();
    if(!bIdecreasedLvl){
        if(Timer(spawn,game_time,millisecToSpawn)){
            for(int spawnPoint=4;spawnPoint>-1;spawnPoint--){
                if(Chance(generalSpawnChance)) {                                                //check if an object is spawning
                    if (Chance(bonusChance)) {                                                  //previous condition is true, check if it is a bonus
                        Bonus *myBonus = new Bonus();
                        SwitchSpawnPos(spawnPoint);
                        myBonus->SetObjCoord(xSpawn,ySpawn,midSpawn.X);
                        NewNodeSpawnedSetting(points,xSpawn, myBonus);
                        NewNodeScreenSetting(xSpawn,myBonus);
                    }else{
                        Obstacle *myObstacle = new Obstacle();
                        SwitchSpawnPos(spawnPoint);
                        myObstacle->SetObjCoord(xSpawn,ySpawn,midSpawn.X);
                        NewNodeSpawnedSetting(points,xSpawn, myObstacle);
                        NewNodeScreenSetting(xSpawn,myObstacle);
                    }
                }
            }
            spawn =  std::chrono::steady_clock::now();
        }
    }
    else{
        RecyclingOldObjects();
        spawn =  std::chrono::steady_clock::now();
    }
}




void GameState::NewNodeSpawnedSetting(int pointsWhenSpawned,short xObjSpawnCoord,class InteractableObject* MyObject) {
    ListSpawnedObjectPtr temp_ptr;
    temp_ptr= new ListSpawnedObject;
    temp_ptr->pointsWhenSpawned=pointsWhenSpawned;
    temp_ptr->xObjSpawnCoord=xObjSpawnCoord;
    temp_ptr->MyObject=MyObject;
    temp_ptr->next=headSpawned;
    temp_ptr->pre = NULL;
    headSpawned=temp_ptr;
    if(temp_ptr->next != NULL){
        temp_ptr->next->pre=temp_ptr;
    }
}

void GameState::NewNodeScreenSetting(short xObjSpawnCoord, class InteractableObject *MyObject) {
    ListOnScreenObjectPtr t_ptr;
    t_ptr = new ListOnScreenObject;
    t_ptr->xObjSpawnCoord=xObjSpawnCoord;
    t_ptr->MyObject=MyObject;
    t_ptr->pre = NULL;
    t_ptr->next=headScreen;
    if(t_ptr->next != NULL){
        t_ptr->next->pre=t_ptr;
    }
    headScreen=t_ptr;
}

void GameState::RecyclingOldObjects() {
    //ListSpawnedObjectPtr object = SearchObjList(points); // noi voglaimo solo il punteggio esatto.
    bool isHead = false;
    int object_points = object->pointsWhenSpawned;
    if(object_points <= points){
        while(!isHead && (object->pointsWhenSpawned == object_points)) {
            object->MyObject->Reset(ySpawn,object->xObjSpawnCoord);
            NewNodeScreenSetting(object->xObjSpawnCoord, object->MyObject);
            if (object == headSpawned)
                isHead = true;
            else
                object = object->pre;
        }
        if(isHead){
            bIdecreasedLvl = false;
        }
    }
}

ListSpawnedObjectPtr GameState::SearchObjList(int points){
    ListSpawnedObjectPtr tmp = headSpawned;
    ListSpawnedObjectPtr tmp_pre = headSpawned;
    bool isEnd = false;
    while(tmp->pointsWhenSpawned >= points && !isEnd){
        tmp_pre = tmp;
        if(tmp->next == NULL){
            isEnd = true;
        }else
            tmp = tmp->next;
    }
    return tmp_pre;
}

void GameState::MoveObjOnScreen() {
    ListOnScreenObjectPtr tmp = headScreen;
    bool isToRemove;
    while(tmp != NULL){
        isToRemove = tmp->MyObject->MoveObject(myMap,myPlayer,this);
        DeleteFromObjOnScreenList(isToRemove,tmp);
        tmp = tmp->next;
    }
}

void GameState::DeleteFromObjOnScreenList(bool shouldIRemoveObj,ListOnScreenObjectPtr index){
    if(shouldIRemoveObj){
        if(index->pre==NULL){
            if(index->next == NULL){
                headScreen = NULL;
                delete index;
            }
            else{
                index->next->pre = NULL;
                headScreen = headScreen->next;
                delete index;
            }
        }
        else if(index->next == NULL){
            index->pre->next = NULL;
            delete index;
        }
        else{
            index->pre->next = index->next;
            index->next->pre = index->pre;
            delete index;
        }
    }
}

void GameState::PointsProgression(Player *myPlayer) {

    if (myPlayer->getOutOfRoad() == false) {
        points = points + pointPerTickVariation ;
        pointsThisLvl +=  pointPerTickVariation ;
    }
    else if(bIsInvincible){
        checkINVINCIBLEmode = chrono::steady_clock::now();
        if(Timer(startINVINCIBLEmode,checkINVINCIBLEmode,invincibleDuration)){ //se è finita
            bIsInvincible = false;
        }
    }
    else{
        points = points - pointPerTickVariation;
        pointsThisLvl -=  pointPerTickVariation;
        if (points < 0){
            SetGameState(GAMEOVER);
        }
    }
}

void GameState::AddPoints(int addedPoints) {
    if(!bIsInvincible){
        points +=  addedPoints;
        pointsThisLvl +=  addedPoints;
        if (points < 0){
            SetGameState(GAMEOVER);
        }
    }
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
    else if(pointsThisLvl < 0){
        currentLvl--;
        levelUpScaling = levelUpScaling - 0.5f;
        pointsThisLvl = giftedPoints;
        points= points - (basePointsToIncreaseLvl* levelUpScaling) + giftedPoints;
        bIdecreasedLvl = true;
        object = SearchObjList(points);
        bIsInvincible = true;
        startINVINCIBLEmode = chrono::steady_clock::now();
    }

}


void GameState::InitializeSpwnCoord(class Map* myMap) {
    rightSpawn.X=myMap->getERR()-8;
    leftSpawn.X=myMap->getELR()+1;
    midSpawn.X=myMap->getScreenWidth()/2-3;
    midRightSpawn.X=((myMap->getScreenWidth()/2-3)+(myMap->getERR()-8))/2;
    midLeftSpawn.X=((myMap->getScreenWidth()/2-3)+(myMap->getELR()+1))/2;
    rightSpawn.Y=myMap->getScreenHeight()/(2.3)+3;
    leftSpawn.Y=myMap->getScreenHeight()/(2.3)+3;
    midSpawn.Y=myMap->getScreenHeight()/(2.3)+3;
    midRightSpawn.Y=myMap->getScreenHeight()/(2.3)+3;
    midLeftSpawn.Y=myMap->getScreenHeight()/(2.3)+3;

}

void GameState::SwitchSpawnPos(int lessThanThree) {

    switch (lessThanThree) {

        case 4:
            xSpawn = leftSpawn.X;
            ySpawn = leftSpawn.Y;
            break;
        case 3:
            xSpawn = midLeftSpawn.X;
            ySpawn = midLeftSpawn.Y;
            break;
        case 2:
            xSpawn = midSpawn.X;
            ySpawn = midSpawn.Y;
            break;
        case 1:
            xSpawn = midRightSpawn.X;
            ySpawn = midRightSpawn.Y;
            break;
        case 0:
            xSpawn = rightSpawn.X;
            ySpawn = rightSpawn.Y;
            break;
        default :
            xSpawn = midSpawn.X;
            ySpawn = midSpawn.Y;
    }
}


bool GameState::Chance(int myPercent) {

    int temp=rand()%100;
    if(temp<=myPercent)
        return true;
    else
        return false;
}

int GameState::Clamp(int myNumber,int lower,int upper){

    return std::max(lower, std::min(myNumber,upper));
}


bool GameState::Timer(chrono::steady_clock::time_point timeStart,chrono::steady_clock::time_point timeCheck, float numToMillisec){
    float elapsedTime = chrono::duration_cast<chrono::milliseconds>(timeCheck - timeStart).count();
    if(elapsedTime >= numToMillisec)
        return true;
    else
        return false;
}




