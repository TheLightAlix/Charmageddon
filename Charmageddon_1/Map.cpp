//
// Created by TheLi on 21/02/2021.
//

#include "Map.hpp"

Map::Map() {
    srand(time(0));
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    screenWidth = csbi.srWindow.Right;
    screenHeight = csbi.srWindow.Bottom;
    xMiddle = 0.5;
    roadWidth = 0.85; //strada occupa l'85% della finestra
    startLeftRoad = (xMiddle-roadWidth/2)*screenWidth;
    startRightRoad = (xMiddle+roadWidth/2)*screenWidth;
    startStars();
    startGrass();
}
void Map::setCursor(short x,short y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
void Map::setAndPrintChar(char c,short x, short y) {
    setCursor(x,y);
    cout<<c;
}
void Map::chooseColor(colours col) {
    switch(col) {
        case BLUE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            break;
        case RED:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            break;
        case GREEN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            break;
        case OCHRE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case VIOLET:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE);
            break;
        case CYAN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN);
            break;
        default: ;

    }
}

void Map::setAndPrintStr(string str, short x, short y, colours col = WHITE) {
    chooseColor(col);
    setCursor(x,y);
    cout<<str;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}

void Map::setAndPrintStrCol(string str[],int length, short x, short y, colours col=WHITE) {
    chooseColor(col);
    //stampa per prima l'ultima riga (dello sprite), poi la penultima etc etc
    for(int i = 0; i < length;i++){
        setCursor(x,y-i);
        cout<<str[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}

void Map::printMap() {
    for(int y = screenHeight;y >= screenHeight/2.3;y--){ //il 2.3 serve per dare più di metà schermo alla strada
        for (int x = 0;x <= screenWidth;x++){
            if(x == (startLeftRoad + screenHeight - y)){
                setAndPrintChar('/',x,y);
            }
            else if(x == (startRightRoad - screenHeight + y)){
                setAndPrintChar('\\',x,y);
            }
        }
    }
    //printGrass();
}

void Map::setCarPos(int x) {
    carPosition = x;
}
int Map::getScreenWidth() {
    return screenWidth;
}
int Map::getScreenHeight() {
    return screenHeight;
}
int Map::getSLR() {
    return startLeftRoad;
}
int Map::getSRR(){
    return startRightRoad;
}
int Map::getELF() {
    return endLeftRoad;
}
int Map::getERR() {
    return endRightRoad;
}
//stars
void Map::startStars() {
    lastStarsMove = chrono::steady_clock::now();
    millisecToMoveStars = 5000;
    starsAStarts = 1;
    starsA = "*";
    starsB = "  *";
    int spaces = 3;
    // creo starA: "*   *   *   *   *.."
    for(int i = 1;i <= screenWidth;i++){
        if(spaces > 0){
            starsA += " ";
            spaces--;
        }else{
            starsA += "*";
            spaces=3;
        }
    }
    spaces = 3;
    //creo starB: "  *   *   *   *   *..."
    for(int i = 3;i <= screenWidth;i++){
        if(spaces > 0){
            starsB += " ";
            spaces--;
        }else{
            starsB += "*";
            spaces=3;
        }
    }
}

void Map::printStars() {
    string stars[(int)(screenHeight/2.8 - 6)];
    if(starsAStarts == 1){
        for(int i = screenHeight/2.8 - 7;i >= 0;i--){
            if (i%2 == 0){
                stars[i] = starsA;
            }else{
                stars[i] = starsB;
            }
        }
    }else{
        for(int i = screenHeight/2.8 - 7;i >= 0;i--){
            if (i%2 == 0){
                stars[i] = starsB;
            }else{
                stars[i] = starsA;
            }
        }
    }
    starsAStarts = starsAStarts * (-1);
    setAndPrintStrCol(stars,screenHeight/2.8-6,0,screenHeight/2.8-7,OCHRE);
}
//grass

void Map::startGrass() {
    lastGrassMove =  std::chrono::steady_clock::now(); //diciamo che lo spawn lo contiamo come una move
    milliSecToMoveGrass = 500;
    length = screenHeight-screenHeight/2.3;
    endLeftRoad = startLeftRoad + length;
    endRightRoad = startRightRoad - length;
    create = endLeftRoad-1;
    head = new bilista;
    head->next = NULL;
    head->prev = head;
    for(int i = 0;i < length;i++){
        insert();
    }
    tail = head->prev;
    tail->next = head;
    random=rand()%5+1;
    createLine(0);//qui ho un create line, tanto è costruttore, metto come punteggio 0.
}
void Map::insert() {
    ptrBilista newHead = new bilista;
    string str = " ";
    for(int i = 1;i < create;i++){
        str += " ";
    }
    create--;//creo stringhe di spazi, ma della dimensione giusta.
    newHead->line = str;//per ora li inizializzo tutti così, mi evito delle beghe a esecuzione
    newHead->next = head;
    newHead->prev = head->prev;
    head->prev = newHead;
    head = newHead;
}
void Map::createLine(int score) {
    string line = " ";
    int density = score%10+1;
    int spaces = endLeftRoad/(density+random);
    int copy = spaces;
    string add;
    for(int i = 1;i < endLeftRoad;i++)
    {
        if(copy == 0){
            int type = i%5;
            switch(type){
                case 0:
                    add = "#";
                    break;
                case 1:
                    add = "*";
                    break;
                case 2:
                    add = "@";
                    break;
                default:
                    add = " ";
            }
            copy = spaces;
        }else {
            add = " ";
            copy--;
        }
        line += add;
    }
    tail->line =  line;
}
void Map::printGrass() {
    ptrBilista tmp = tail;
    int xDx = endRightRoad + 1;
    int firstY=screenHeight/2.3 + 1;
    string str;
    do {
        str = tmp->line;
        setAndPrintStr(str,0,firstY,GREEN);
        reverseString(&str,0,str.length()-1);
        setAndPrintStr(str,xDx,firstY,GREEN);
        tmp = tmp->prev;
        firstY++;
        xDx++;
    } while (tmp != tail);
}
void Map::reverseString(string *string,int left,int right) {
    if(left >= right){
        return;
    }
    else{
        char tmp = (*string)[left];
        (*string)[left] = (*string)[right];
        (*string)[right] = tmp;
        reverseString(string, ++left, --right);
    }
}

void Map::runGrass(int score) {
    string str;
    ptrBilista tmp = head;
    do {
        str = tmp->next->line;
        str.erase(str.begin());
        tmp->line = str;
        tmp = tmp->next;
    }while(tmp != tail);//per ora rimango così, poi vediamo.
    createLine(score);
    printGrass();
}

void Map::runDecorations(int score) {
    move = chrono::steady_clock::now();
    if(timer(lastGrassMove,move, milliSecToMoveGrass)){
        runGrass(score);
        lastGrassMove = chrono::steady_clock::now();
    }

    if(timer(lastStarsMove,move,millisecToMoveStars)){
        printStars();
        lastStarsMove = chrono::steady_clock::now();
    }
}

bool Map::timer(chrono::steady_clock::time_point timeStart,chrono::steady_clock::time_point timeCheck, float numToMillisec) {
    float elapsedTime = chrono::duration_cast<chrono::milliseconds>(timeCheck - timeStart).count();
    if(elapsedTime >= numToMillisec)
        return true;
    else
        return false;
}