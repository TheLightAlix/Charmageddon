//
// Created by TheLi on 21/02/2021.
//

#include "GameState.hpp"

GameState::GameState(){

    srand(time(0));
    points=0;
    pointsThisLvl=0;
    pointPerTickVariation=1;
    millisecToUpdatePoints=250;
    millisecToSpawn=3000;
    generalSpawnChance=30;
    bonusChance=10;
    currentLvl=1;
    basePointsToIncreaseLvl=30000;
    levelUpScaling=1.f;
    currentState=MENU;
    MyMenu=new Menu();
    myMap = new Map();
    myPlayer = new Player(myMap,1,WHITE,this);//da completare con il menu nuovo
    headSpawned=NULL;
    headScreen= NULL;
    bIsRecycling = false;
    bIdecreasedLvl=false;
    maxLevel = 0;
}


void GameState::SetGameState(state myState) {

    currentState=myState;
    int choice = 4;
    Obstacle *p;
    string str;
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
            myPlayer = new Player(myMap,2,RED,this);
            myPlayer->printCar(myMap);
            InitializeSpwnCoord(myMap);
            while((currentState == PLAYING) && !GetAsyncKeyState(VK_ESCAPE)){
                game_time =  std::chrono::steady_clock::now();
                myPlayer->moveCar(myMap);
                if(Timer(spawn,game_time,millisecToSpawn)){
                    SpawnObjects();
                    spawn =  std::chrono::steady_clock::now();
                }
                MoveObjOnScreen();
                PointsProgression(myPlayer);
                myMap->setCursor(0,0);
                cout<<points;
                LvlIncrease();
                myMap->setCursor(0,1);
                cout<<currentLvl;
            }

            SetGameState(GAMEOVER);
            break;
        case GAMEOVER:
                MyMenu->post_menu(MyMenu->get_user(),points);
            break;

    }
}
//ora facciamo spawnare un solo oggetto e facciamo muovere.
void GameState::SpawnObjects() {
    if(bIdecreasedLvl == false){
        for(int spawnPoint=2;spawnPoint>-1;spawnPoint--){
            if(Chance(generalSpawnChance)) {                                                //check if an object is spawning
                if (Chance(bonusChance)) {                                                  //previous condition is true, check if it is a bonus
                    Bonus *myBonus = new Bonus();
                    SwitchSpawnPos(spawnPoint);
                    myBonus->SetObjCoord(xSpawn,ySpawn);
                    NewNodeSpawnedSetting(points,xSpawn, myBonus);
                    NewNodeScreenSetting(xSpawn,myBonus);
                }else{
                    Obstacle *myObstacle = new Obstacle();
                    SwitchSpawnPos(spawnPoint);
                    myObstacle->SetObjCoord(xSpawn,ySpawn);
                    NewNodeSpawnedSetting(points,xSpawn, myObstacle);
                    NewNodeScreenSetting(xSpawn,myObstacle);
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
        if (points < 0){
            SetGameState(GAMEOVER);
        }
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
        bIdecreasedLvl = false;
    }
    else if(pointsThisLvl < 0){
        currentLvl--;
        levelUpScaling = levelUpScaling - 0.5f;
        pointsThisLvl = basePointsToIncreaseLvl * levelUpScaling + pointsThisLvl;
        bIdecreasedLvl = true;
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
        temp_ptr->next->pre=headSpawned;
    }
    //

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
    if(points < 0){
        SetGameState(GAMEOVER);
    }
    else{
        ListSpawnedObjectPtr object = SearchObjList(points);
        if(object != NULL){ 
            int object_points = object->pointsWhenSpawned;
            bool isHead = false;
            while(!isHead && (object->pointsWhenSpawned == object_points)){
                NewNodeScreenSetting(object->xObjSpawnCoord,object->MyObject);
                if(object == headSpawned)
                    isHead = true;
                else
                    object = object->pre;
            }
            if(isHead){
                bIdecreasedLvl = false;
            }
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


void GameState::InitializeSpwnCoord(class Map* myMap) {
    rightSpawn.X=myMap->getERR()-8;
    leftSpawn.X=myMap->getELF()+1;
    midSpawn.X=myMap->getScreenWidth()/2-3;
    rightSpawn.Y=(int)myMap->getScreenHeight()/(2.3)+3;
    leftSpawn.Y=(int)myMap->getScreenHeight()/(2.3)+3;
    midSpawn.Y=(int)myMap->getScreenHeight()/(2.3)+3;

}

void GameState::SwitchSpawnPos(int lessThanThree) {

    switch (lessThanThree) {

        case 2:
            xSpawn = leftSpawn.X;
            ySpawn = leftSpawn.Y;
            break;
        case 1:
            xSpawn = midSpawn.X;
            ySpawn = midSpawn.Y;
            break;
        default :
            xSpawn = rightSpawn.X;
            ySpawn = rightSpawn.Y;
            break;
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



